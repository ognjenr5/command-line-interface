#include <string>
#include <fstream>

#include "ISFile.h"
#include "../Core/FileExceptions.h"

ISFile::ISFile(std::string filename){
    this->filename = std::move(filename);
    this->input_string = this->read_from_file();
}

std::string ISFile::read_from_file() const {
    // Tries to open file with given filename
    std::ifstream file(filename);
    if (!file)
        throw FileNotFound(filename);

    // If file is opened, read everything from it
    std::string input_string, line;
    while (getline(file, line))
        input_string += line + "\n";

    file.close();

    return input_string.substr(0, input_string.size() - 1);
}
