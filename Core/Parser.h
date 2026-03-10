#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <set>
#include <map>
#include <string>
#include <vector>

// Forward declarations
class Command;
class Controller;

class Parser {
public:
    explicit Parser(Controller* c);

    // Takes a single line input and creates the required command
    Command* parse_command(std::string input, bool pipe = false);

    void handle_redirections(Command *c, const std::string &input_redirection, const std::string &output_redirection);

    // Add commands to controller based on input string
    void add_commands(const std::string &input);

    // Add commands to controller if pipeline is detected
    void add_commands_to_pipeline(const std::string &input);

    // Pipeline exception handler
    void check_valid_pipe_command(Command *c, int c_count);

    // Various checks for argument types
    static bool check_option_quoted(const std::string& argument);

    static bool check_valid_option(const std::string& argument);

    static bool check_quoted(const std::string& argument);

    static bool check_number_option(const std::string& argument);

private:

    // Tokenize input to argument list
    static std::vector<std::string> get_token_list(const std::string &command_name, std::stringstream &ss);

    // Find and remove input redirection from argument list
    static std::string find_input_redirection(std::vector<std::string> &args);

    // Find and remove output redirection from argument list
    static std::string find_output_redirection(std::vector<std::string> &args);

    // Format input redirection for easier handling
    static void format_redirections(std::vector<std::string>& args);

    // Helper function to find pipe separator '|' that's not in quotes
    static int find_separator(const std::string &input, int pos = 0);

    // Sets of commands based on having input or output (for pipeline creation)
    std::set<std::string> no_output;
    std::set<std::string> no_input;

    // Map of functions to create commands, based on their name
    std::map<std::string, Command* (*)(const std::vector<std::string>&, bool)> make;

    // Association to controller which executes parsed commands
    Controller* controller;
};

#endif //CLI_PARSER_H