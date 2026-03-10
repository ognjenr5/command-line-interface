#ifndef CLI_CONTROLLER_H
#define CLI_CONTROLLER_H


#include "Parser.h"
#include "Reader.h"
#include "../Commands/Batch.h"


class Controller {
public:
    // Objects that controls the work of the CLI
    Controller();

    // Destroys parser and reader
    ~Controller();

    // Execute commands in list and handle possible outer redirection (batch)
    void execute_commands(const std::string &line, const std::string& output_redirection_filename = "") const;

    // Clear list of commands
    void clear_commands();

    // Core of the program, reads line(s) from the console, parses,
    // creates a command and executes it, while handling exceptions
    void run();

    void add_command (Command *c);
private:
    // Parser object that parses line of input into a command
    Parser* parser;

    // Reader object that reads either one or multiple lines from the console
    Reader* reader;

    // List of commands to be executed
    std::vector<Command* > commands;
};

inline void Controller::add_command(Command* c) { commands.push_back(c); }

#endif //CLI_CONTROLLER_H