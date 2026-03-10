#include <fstream>

#include "Batch.h"
#include "../Core/CommandExceptions.h"
#include "../Core/Controller.h"
#include "../Core/FileExceptions.h"
#include "../Core/Reader.h"
#include "../Core/Parser.h"

void Batch::do_execute() {
    // Open batch file and handle exception
    std::ifstream file(argument);
    if (!file) throw FileNotFound(argument);

    // Batch owns new reader and controller to not interfere with outer commands
    const auto reader = new Reader(&file);
    const auto controller = new Controller();

    std::string line;

    // Execute commands in batch file
    while (!(line = reader->read_line()).empty()) {
        controller->execute_commands(line, this->default_output_redirection);
        controller->clear_commands();
    }

    // Reader and controller aren't needed after execution
    delete reader;
    delete controller;
}

Command * Batch::create_command(const std::vector<std::string> &args, bool pipe) {

    // Piped command can be created empty
    if (pipe && args.empty())
        return new Batch();

    if (args.size() != 1)
        throw InvalidArgumentCount(1);

    if (Parser::check_quoted(args[0])  || Parser::check_valid_option(args[0]))
        throw InvalidArgument("Expected filename argument.");

    return new Batch(args[0]);
}

void Batch::set_output_redirection(const std::string &filename) {
    // Set own output redirection and default output redirection for batch commands
    Command::set_output_redirection(filename);
    this->default_output_redirection = filename;
}

Batch::Batch(std::string filename) : SingleLineCommand(std::move(filename)) {}
