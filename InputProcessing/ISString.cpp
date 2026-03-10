#include "ISString.h"
#include <string>

ISString::ISString(std::string input_string) {
    this->input_string = std::move(input_string);
}
