#include "InputStream.h"
#include "ISString.h"
#include "ISFile.h"

std::string InputStream::read() {
    return this->input_string;
}

InputStream * InputStream::getStream(const std::string& input) {
    if (input.find('\"') == std::string::npos)
        return new ISFile(input);

    return new ISString(input.substr(1, input.length() - 2));

}
