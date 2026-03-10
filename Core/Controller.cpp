#include <iostream>

#include "Controller.h"
#include "Parser.h"
#include "Reader.h"
#include "FileExceptions.h"
#include "CommandExceptions.h"
#include "../Commands/Command.h"

Controller::Controller() {
    this->parser = new Parser(this);
    this->reader = new Reader(&std::cin);
}

Controller::~Controller() {
    delete this->parser;
    delete this->reader;
}

void Controller::execute_commands(const std::string &line, const std::string &output_redirection_filename) const {
    try {
        // Create command from the read line
        parser->add_commands(line);

        for (auto c : commands) {
            // If command isn't created, skip to next input
            if (!c) continue;

            // If command is multiline (including first in a pipe), waits for the argument
            if (!c->can_execute() && (!c->is_in_pipe() || !Command::has_piped_output()))
                c->load_argument(reader->read_multiline_argument());

            // If command is called by batch and doesn't have its own redirection, set it to batch redirection
            if (c->has_default_output_redirection() && !output_redirection_filename.empty())
                c->set_output_redirection(output_redirection_filename);

            c->execute();
        }
    }
    catch (FileException& e) {
        *Command::get_error_os() << e.what();
    }
    catch (CommandExceptions& e) {
        *Command::get_error_os() << e.what();
    }

}

void Controller::clear_commands() {
    for (auto& c : commands)
        delete c;
    commands.clear();
}

void Controller::run() {
    // Infinite loop to run console line interface
    while (true) {
        std::cout << "\n" << Command::get_prompt() << " ";

        execute_commands(reader->read_line());

        clear_commands();
    }
}
