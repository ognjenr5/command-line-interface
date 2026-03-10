#include <iostream>
#include <string>

#include "Wc.h"

#include <sstream>

#include "../InputProcessing/InputStream.h"
#include "../Core/CommandExceptions.h"

Wc::Wc(InputStream *is, const char option) : MultilineCommand(is) {
    this->option = option;
}

void Wc::do_execute() {
    const std::string input = this->is->read();
    std::stringstream ss;

    // Helper function calls based on what to count (w - words, c - chars)
    if (this->option == 'w')
        ss << this->count_words(input);
    else
        ss << this->count_chars(input);

    print(ss.str());
}

Command * Wc::create_command(const std::vector<std::string> &args, bool pipe) {
    if (args.empty() || args.size() > 2)
        throw InvalidArgumentCount(1,2);

    if (!Parser::check_valid_option(args[0]) || (args[0][1] != 'w' && args[0][1] != 'c') || args[0].length() > 2)
        throw InvalidArgument("Expected option argument -w or -c.");

    const char option = args[0][1];

    if (args.size() == 2 && Parser::check_valid_option(args[1]))
        throw InvalidArgument("Expected argument in quotes or filename argument.");

    InputStream *is = args.size() == 2 ? InputStream::getStream(args[1]) : nullptr;

    return new Wc(is, option);
}

int Wc::count_words(std::string input){

    if (input.empty()) return 0;

    int count = 0;
    bool is_blank = std::isspace(input[0]);

    for (char c : input) {
        if (!is_blank && std::isspace(c)) {
            is_blank = true;
            count++;
        }
        else if (is_blank && !std::isspace(c))
            is_blank = false;
    }

    if (!is_blank) count++;

    return count;
}

int Wc::count_chars(std::string input) {

    int count = 0;

    for (char c : input) count++;

    return count;
}
