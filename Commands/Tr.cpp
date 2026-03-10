#include "Tr.h"
#include "../Core/CommandExceptions.h"
#include "../Core/Parser.h"
#include <iostream>

Tr::Tr(InputStream* is, std::string what, std::string with) : MultilineCommand(is) {
    this->what = std::move(what);
    this->with = std::move(with);
}

void Tr::do_execute() {
    std::string replaced = replace_all();
    print(replaced);
}

Command * Tr::create_command(const std::vector<std::string> &args, bool pipe) {
    if (args.empty() || args.size() > 3)
        throw InvalidArgumentCount(1,3);

    // Determine if argument is passed, or the command will be multiline
    const bool first_is_option = Parser::check_option_quoted(args[0]);

    // Position of required argument what is determined on existence of [argument]
    const int what_index = first_is_option ? 0 : 1;

    if (what_index == 0 && args.size() > 2 || what_index == 1 && args.size() < 2)
        throw InvalidCommandFormat("Expected: tr [argument] -\"what\" [\"with\"]");

    // Check if what is in correct format: -"what"
    if (args.size() >= what_index && !Parser::check_option_quoted(args[what_index]))
        throw InvalidArgument("Expected argument what in format -\"what\".");

    InputStream* is = first_is_option ? nullptr : InputStream::getStream(args[0]);
    std::string a_what = args[what_index].substr(2, args[what_index].length() - 3);

    // Since a_with is optional, it's set to ""
    std::string a_with;

    // Check existence of optional with argument and its format: "with"
    if (args.size() > what_index + 1) {
        if (!Parser::check_quoted(args[what_index + 1]))
            throw InvalidArgument("Expected argument with in format \"with\".");
        a_with = args[what_index + 1].substr(1, args[what_index+1].length() - 2);
    }

    return new Tr(is, a_what, a_with);
}

std::string Tr::replace_all() const {
    std::string input = is->read();

    // If what is empty, there's nothing to replace
    if (what.empty()) return input;

    const size_t len = what.length();
    size_t pos = 0, new_pos;

    while ((new_pos = input.find(what, pos)) != std::string::npos) {
        input.replace(new_pos, len, with);
        pos = new_pos + with.length();
    }

    return input;
}




