#include <string>
#include <fstream>

#include "Rm.h"
#include "../Core/FileExceptions.h"
#include "../Core/CommandExceptions.h"

Rm::Rm(std::string filename) : SingleLineCommand(std::move(filename)) {}

void Rm::do_execute() {
    if (!std::ifstream(argument))
        throw FileNotFound(argument);

    std::remove(argument.c_str());
}

Command * Rm::create_command(const std::vector<std::string> &args, bool pipe) {
    // Piped command can be created empty
    if (pipe && args.empty())
        return new Rm();

    if (args.size() != 1)
        throw InvalidArgumentCount(1);

    if (Parser::check_quoted(args[0])  || Parser::check_valid_option(args[0]))
        throw InvalidArgument("Expected filename argument.");


    return new Rm(args[0]);
}
