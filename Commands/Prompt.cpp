#include "Prompt.h"

#include "Command.h"
#include "../Core/Parser.h"
#include "../Core/CommandExceptions.h"

Prompt::Prompt(std::string prompt) : SingleLineCommand(prompt) {}

void Prompt::do_execute() {
    set_prompt(this->argument);
}

void Prompt::load_argument(std::string argument) {
    this->argument = std::move(argument);
}

bool Prompt::can_execute() {
    return !argument.empty();
}

Command * Prompt::create_command(const std::vector<std::string> &args, bool pipe) {
    // Piped command can be created empty
    if (pipe && args.empty())
        return new Prompt();

    if (args.size() != 1)
        throw InvalidArgumentCount(1);

    if (!Parser::check_quoted(args[0]))
        throw InvalidArgument("Expected argument in quotes.");

    std::string a_prompt = args[0].substr(1, args[0].length() - 2);

    if (a_prompt.empty())
        throw InvalidArgument("Prompt must be at least one character long.");

    return new Prompt(a_prompt);
}
