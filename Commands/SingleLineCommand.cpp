#include "SingleLineCommand.h"
#include "../Core/CommandExceptions.h"

SingleLineCommand::SingleLineCommand(std::string argument) : argument(std::move(argument)) {}

bool SingleLineCommand::can_execute() {
    return !argument.empty();
}

void SingleLineCommand::load_argument(std::string argument) {
    this->argument = std::move(argument);
}


