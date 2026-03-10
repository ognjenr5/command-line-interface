#include <iostream>

#include "Echo.h"
#include "../Core/CommandExceptions.h"

Echo::Echo(InputStream *is) : MultilineCommand(is) {}

void Echo::do_execute() {
    std::string input = is->read();
    print(input);
}

Command * Echo::create_command(const std::vector<std::string> &args, bool pipe) {
    if (args.size() > 1)
        throw InvalidArgumentCount(1);

    if (args.size() == 1 && Parser::check_valid_option(args[0]))
        throw InvalidArgument("Expected argument in quotes or filename argument.");

    if (args.size() == 1)
        return new Echo(InputStream::getStream(args[0]));

    return new Echo();
}
