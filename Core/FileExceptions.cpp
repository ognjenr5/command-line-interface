#include "FileExceptions.h"

const char * FileException::what() const noexcept{
    return this->err_msg.c_str();
}

FileNotFound::FileNotFound(std::string filename) {
    this->err_msg = "File: " + filename + " not found.\n";
}

FileExists::FileExists(std::string filename) {
    this->err_msg = "File: " + filename + " already exists.\n";
}

FileNotCreated::FileNotCreated(std::string filename) {
    this->err_msg = "File: " + filename + " not created.\n";
}
