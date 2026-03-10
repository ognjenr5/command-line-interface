#ifndef CLI_FILE_EXCEPTIONS_H
#define CLI_FILE_EXCEPTIONS_H

#include <exception>
#include <string>

class FileException : public std::exception {
public:
    const char* what() const noexcept override;
protected:
    std::string err_msg;
};

class FileNotFound : public FileException{
public:
    explicit FileNotFound(std::string filename);
};

class FileExists : public FileException{
public:
    explicit FileExists(std::string filename);
};

class FileNotCreated : public FileException{
public:
    explicit FileNotCreated(std::string filename);
};

#endif //CLI_FILE_EXCEPTIONS_H
