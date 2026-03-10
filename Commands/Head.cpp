#include "Head.h"
#include <sstream>

#include "../Core/CommandExceptions.h"

Head::Head(InputStream *is, int nn) : MultilineCommand(is), n(nn) {}

void Head::do_execute() {
    std::string input = is->read();
    std::string output;

    int line_count = 0;
    size_t new_pos, pos = 0;
    while (line_count < n && (new_pos = input.find('\n', pos)) != std::string::npos) {
        line_count++;
        output += input.substr(pos, new_pos-pos) + '\n';
        pos = new_pos + 1;
    }

    // If argument is in quotes, no newlines will be found
    if (pos == 0 && n > 0)
        output = input;

    print(output);
}

Command * Head::create_command(const std::vector<std::string> &args, bool pipe) {
    if (args.size() > 2 || args.empty())
        throw InvalidArgumentCount(1,2);

    // Checks only for format of the function argument -n<number>, doesn't check if there are numbers
    if (!Parser::check_number_option(args[0]))
        throw InvalidArgument("Expected -n<number>, where number is 1 to 5 digits.");

    int n;
    try {
        // Tries to get number from the argument, throws std::invalid_argument if it fails
        n = std::stoi(args[0].substr(2));
    }
    // Catches thrown std::invalid_argument th
    catch (const std::exception& e) {
        throw InvalidArgument("Expected -n<number>, where number is 1 to 5 digits.");
    }

    if (args.size() == 2 && Parser::check_valid_option(args[1]))
        throw InvalidArgument("Expected argument in quotes or filename argument.");

    InputStream *is = args.size() == 2 ? InputStream::getStream(args[1]) : nullptr;

    return new Head(is, n);
}


