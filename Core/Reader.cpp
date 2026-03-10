#include <istream>

#include "Reader.h"

Reader::Reader(std::istream* is) {
    this->is = is;
}

std::string Reader::read_line() {
    std::string line;
    getline(*is, line);

    if (line.length() > 512)
        line.resize(512);

    return line;
}

std::string Reader::read_multiline_argument() {
    std::string input, line;

    // Reads until it detects 'EOF'
    while (std::getline(*is, line)) {
        if (line.length() > 512)
            line.resize(512);
        input += line + "\n";
    }

    // Clears EOF error, so the command reading loop can go on working
    is->clear();

    return input;
}
