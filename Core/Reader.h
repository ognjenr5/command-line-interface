#ifndef CLI_READER_H
#define CLI_READER_H

#include <string>
#include <istream>

class Reader {
public:
    explicit Reader(std::istream* is);

    // Reads a single line from the input stream
    std::string read_line();

    // Reads multiple lines until it detects 'EOF'
    std::string read_multiline_argument();

private:
    std::istream* is;
};


#endif //CLI_READER_H