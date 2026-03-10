#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "Parser.h"
#include "CommandExceptions.h"
#include "Controller.h"

#include "../Commands/Commands.h"

Parser::Parser(Controller* c) : controller(c) {

    // Set create_command for each command
    make["date"] =      &Date::create_command;
    make["echo"] =      &Echo::create_command;
    make["prompt"] =    &Prompt::create_command;
    make["rm"] =        &Rm::create_command;
    make["time"] =      &Time::create_command;
    make["touch"] =     &Touch::create_command;
    make["tr"] =        &Tr::create_command;
    make["truncate"] =  &Truncate::create_command;
    make["wc"] =        &Wc::create_command;
    make["head"] =      &Head::create_command;
    make["batch"] =     &Batch::create_command;

    //Initialize sets of commands without inputs/outputs (for pipe creation)
    no_output.insert("prompt");
    no_output.insert("touch");
    no_output.insert("truncate");
    no_output.insert("rm");
    no_output.insert("batch");

    no_input.insert("time");
    no_input.insert("date");
}



void Parser::add_commands (const std::string& input) {
    // Command addition based on pipe existence

    if (find_separator(input) == -1)
        controller->add_command(parse_command(input));

    else add_commands_to_pipeline(input);
}

void Parser::add_commands_to_pipeline (const std::string& input) {
    int pos = 0, new_pos = 0;
    int c_count = 0;

    // Extract commands from pipe
    while ((new_pos = find_separator(input, pos)) != -1) {

        // Generate command based on input string
        Command* c = parse_command(input.substr(pos, new_pos - pos), true);
        c -> set_pipeline_position(Command::PipePosition::IN);

        // Pipe exception handling
        check_valid_pipe_command(c, c_count);

        controller->add_command(c);

        pos = new_pos + 1; c_count ++;
    }

    // Last pipeline command is marked differently to help with redirection and exception handling
    Command* c = parse_command(input.substr(pos), true);
    c->set_pipeline_position(Command::PipePosition::LAST);

    check_valid_pipe_command(c, c_count);

    controller->add_command(c);
}

void Parser::check_valid_pipe_command (Command* c, int c_count) {
    // Pipe exception handler function

    // Commands without output cannot be first in pipe
    if (c_count == 0 && no_output.find(c->get_name()) != no_output.end())
        throw PipelineException(c->get_name() + " cannot be first in pipeline.\n");

    // Commands without output/input cannot be in the middle of pipe
    if (c->get_pipeline_position() == Command::PipePosition::IN && c_count != 0
        && no_input.find(c->get_name()) != no_input.end() && no_output.find(c->get_name()) ==  no_output.end())
        throw PipelineException(c->get_name() + " has to first or last in pipeline.\n");

    // Commands without input cannot be last in pipe
    if (c->get_pipeline_position() == Command::PipePosition::LAST && no_input.find(c->get_name()) != no_input.end())
        throw PipelineException(c->get_name() + " cannot be last in pipeline.\n");

    if ((c->get_pipeline_position() == Command::PipePosition::IN && c_count != 0 ||
        c->get_pipeline_position() == Command::PipePosition::LAST) && c->can_execute())
        throw PipelineException("Piped input command " + c->get_name() +" cannot have input arguments.\n");

    if (c->get_pipeline_position() != Command::PipePosition::LAST && !c->has_default_output_redirection())
        throw PipelineException("Piped output command " + c->get_name() +" cannot have output redirection.\n");

}

Command* Parser::parse_command(std::string input, bool pipe) {
    std::stringstream ss(input);
    std::string name;
    ss >> name;

    // Handle non-existent commands
    if (make.find(name) == make.end())
        throw NonexistentCommand(name);

    // Tokenize command, and separate input and output redirection from the list if they exists
    std::vector<std::string> args = get_token_list(name, ss);
    std::string input_redirection = find_input_redirection(args);
    std::string output_redirection = find_output_redirection(args);

    // Create command based on name, arguments and pipeline existence
    Command* c = make[name](args, pipe);

    handle_redirections(c, input_redirection, output_redirection);

    return c;
}

void Parser::handle_redirections (Command * c, const std::string& input_redirection, const std::string& output_redirection) {

    // Handle output redirection exception
    if (!output_redirection.empty() && no_output.find(c->get_name()) != no_output.end() && c->get_name() != "batch")
        throw RedirectionException("Output redirection not allowed for this command.\n");

    // Set redirections
    if (!input_redirection.empty())
        c->set_input_redirection(input_redirection);

    if (!output_redirection.empty())
        c->set_output_redirection(output_redirection);
}

std::vector<std::string> Parser::get_token_list(const std::string& name, std::stringstream &ss) {
    std::string tmp, curr_token, line;
    std::vector<std::string> tokens;
    getline(ss, line);

    bool inQuotes = false;

    // Parse line char by char, while handling potential exceptions
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];

        // Start of quoted argument
        if (!inQuotes && c == '\"') {

            // If quoted argument is not an option argument or ordinary argument, there are unexpected characters
            if (!tmp.empty() && tmp != "-")
                throw UnexpectedCharacters(name + line, name.length() + i - tmp.size());

            inQuotes = true;
            tmp += c;
        }

        // End of quoted argument
        else if (inQuotes && c == '\"') {

            // If non-whitespace or redirection characters follow quoted argument, there are unexpected characters
            if (i < line.size() - 1 && line[i + 1] != '\t' && line[i+1] != ' '  && line[i+1] != '<' && line[i+1] != '>')
                throw UnexpectedCharacters(name + line, name.length() + i + 1);

            inQuotes = false;
            tmp += c;
            tokens.push_back(tmp);
            tmp.clear();
        }

        // Whitespace or redirection signalize end of current argument
        else if ((c == '\t' || c == ' ' || c == '<' || c == '>' && i>0 && line[i-1] != '>') && !inQuotes && !tmp.empty()) {
            tokens.push_back(tmp);
            tmp.clear();
            if (c == '>' || c == '<')
                tmp += c;
        }

        else if (inQuotes || (c != '\t' && c != ' '))
            tmp += c;

    }

    // If remaining argument is in quotes, but doesn't end, it's irregular
    if (inQuotes && !tmp.empty())
        throw UnexpectedCharacters(name + line, name.length() + line.length() - tmp.size());

    // Otherwise add the last unquoted argument
    if (!inQuotes && !tmp.empty())
        tokens.push_back(tmp);

    // Format redirections: '< example.txt' to '<example.txt', for simpler handling
    if (!tokens.empty())
        format_redirections(tokens);

    return tokens;
}


std::string Parser::find_input_redirection(std::vector<std::string> &args) {
    // Extract input redirection from argument list

    bool foundInputRedirection = false;
    int redirection_pos = -1;
    std::string input_redirection;

    for (int i = 0; i < args.size(); i++) {
        if (!foundInputRedirection && args[i][0] == '<') {
            input_redirection = args[i].substr(1);
            redirection_pos = i;
            foundInputRedirection = true;
        }

        // Handle multiple input redirection
        else if (foundInputRedirection && args[i][0] == '<')
            throw RedirectionException("Multiple input redirections.\n");
    }

    // Handle bad redirection placement
    if (redirection_pos != -1 && redirection_pos != args.size() - 1 &&
        (redirection_pos != args.size() - 2 || args[args.size() - 1][0] != '>'))
        throw RedirectionException("Redirection must be found at the end of command.\n");

    // If redirection is found, erase from argument list
    if (redirection_pos != -1)
        args.erase(args.begin() + redirection_pos);

    if (redirection_pos != -1 && input_redirection.empty())
        throw RedirectionException("Input redirection filename is empty.\n");

    return input_redirection;
}

std::string Parser::find_output_redirection(std::vector<std::string> &args) {
    // Extract output redirection from argument list

    bool foundOutputRedirection = false;
    int redirection_pos = -1;
    std::string output_redirection;

    for (int i = 0; i < args.size(); i++) {
        if (!foundOutputRedirection && args[i][0] == '>') {
            output_redirection = args[i].substr(1);
            redirection_pos = i;
            foundOutputRedirection = true;
        }

        // Handle multiple output redirection
        else if (foundOutputRedirection && args[i][0] == '>')
            throw RedirectionException("Multiple output redirections.\n");
    }

    // Handle bad redirection placement
    if (redirection_pos != -1 && redirection_pos != args.size() - 1 &&
    (redirection_pos != args.size() - 2 || args[args.size() - 1][0] != '<'))
        throw RedirectionException("Redirection must be found at the end of command.\n");

    // If redirection is found, erase from argument list
    if (redirection_pos != -1)
        args.erase(args.begin() + redirection_pos);

    if (redirection_pos != -1 && output_redirection.length() < 2)
        throw RedirectionException("Output redirection filename is empty.\n");

    return output_redirection;
}

void Parser::format_redirections(std::vector<std::string> &args) {
    // Format redirections: '> example.txt' to '>example.txt'

    for (int i = 0; i < args.size() - 1; i++) {
        if (args[i] == "<" || args[i] == ">" || args[i] == ">>") {
            if (args[i+1][0] == '\"' || args[i+1][0] == '-' || args[i+1][0] == '>' || args[i+1][0] == '<')
                throw RedirectionException("Expected redirection format: < or > or >> followed by filename.\n");
            args[i] = args[i] + args[i+1];
            args.erase(args.begin() + i + 1);
        }
    }
}

int Parser::find_separator (const std::string& input, int pos) {
    bool inQuotes = false;

    for (int i = pos; i < input.length(); i++) {
        // If '|' isn't in quotes, return position
        if (!inQuotes && input[i] == '|')
            return i;

        if (!inQuotes && input[i] == '\"')
            inQuotes = true;
        else if (inQuotes && input[i] == '\"')
            inQuotes = false;
    }

    // Separator isn't found
    return -1;
}

bool Parser::check_option_quoted(const std::string& argument) {
    return (argument[0] == '-' && argument[1] == '\"' && argument[argument.size()-1] == '\"');
}

bool Parser::check_valid_option(const std::string& argument) {
    return (argument[0] == '-');
}

bool Parser::check_quoted(const std::string& argument) {
    return (argument[0] == '\"' && argument[argument.size()-1] == '\"');
}

bool Parser::check_number_option(const std::string& argument) {
    // Check format first
    if (!(argument.size() > 1 && argument.size() < 8 && argument[0] == '-' && argument[1] == 'n')) return false;

    // Check if number option argument contains only digits
    for (int i = 2; i < argument.size(); i++)
        if (!isdigit(argument[i]))
            return false;

    return true;
}

