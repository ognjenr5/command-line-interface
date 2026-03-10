#include <string>
#include <fstream>
#include "Touch.h"
#include "../Core/FileExceptions.h"
#include "../Core/CommandExceptions.h"

Touch::Touch(std::string filename) : SingleLineCommand(std::move(filename)) {}

void Touch::do_execute() {
    if (std::ifstream(this->argument))
        throw FileExists(this->argument);

    std::ofstream file(this->argument);
    if (!file)
        throw FileNotCreated(this->argument);
}

Command * Touch::create_command(const std::vector<std::string> &args, bool pipe) {
    // Piped command can be created empty
    if (pipe && args.empty())
        return new Touch();

    if (args.size() != 1)
        throw InvalidArgumentCount(1);

    if (Parser::check_quoted(args[0])  || Parser::check_valid_option(args[0]))
        throw InvalidArgument("Expected filename argument.");


    return new Touch(args[0]);
}


