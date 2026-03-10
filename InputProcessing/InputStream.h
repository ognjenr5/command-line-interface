#ifndef CLI_INPUT_STREAM_H
#define CLI_INPUT_STREAM_H

#include <string>

class InputStream {
public:
    // Abstract InputStream class, handles the different ways of reading arguments,
    // from a file or from a string ( quoted argument or multiline argument )

    virtual ~InputStream() = default;
    virtual std::string read();

    // Returns either file or string input based on argument
    static InputStream* getStream(const std::string& input);

protected:

    std::string input_string;
};

#endif //CLI_INPUT_STREAM_H