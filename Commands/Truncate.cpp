#include <string>
#include <fstream>
#include "Truncate.h"
#include "../Core/FileExceptions.h"
#include "../Core/CommandExceptions.h"

Truncate::Truncate(std::string filename) : SingleLineCommand(std::move(filename)) {}

void Truncate::do_execute() {
    if (!std::ifstream(argument))
        throw FileNotFound(argument);

    const std::ofstream file(argument, std::ios::trunc);
}

Command * Truncate::create_command(const std::vector<std::string> &args, bool pipe) {
    // Piped command can be created empty
    if (pipe && args.empty())
        return new Truncate();

    if (args.size() > 1)
        throw InvalidArgumentCount(1);

    if (Parser::check_quoted(args[0])  || Parser::check_valid_option(args[0]))
        throw InvalidArgument("Expected filename argument.");

    return new Truncate(args[0]);
}
