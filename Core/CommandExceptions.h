#ifndef CLI_COMMAND_EXCEPTIONS_H
#define CLI_COMMAND_EXCEPTIONS_H

#include <exception>
#include <string>

class CommandExceptions : public std::exception {
public:
    const char* what() const noexcept override;
protected:
    std::string err_msg;
};

class InvalidArgument : public CommandExceptions {
public:
    explicit InvalidArgument(const std::string& message = "");
};

class InvalidCommandFormat : public CommandExceptions {
public:
    explicit InvalidCommandFormat(const std::string& message = "");
};

class InvalidArgumentCount : public CommandExceptions {
public:
    explicit InvalidArgumentCount(const int& a);

    InvalidArgumentCount(const int& a, const int& b);
};

class NonexistentCommand : public CommandExceptions {
public:
    explicit NonexistentCommand(const std::string& command_name);
};

class UnexpectedCharacters : public CommandExceptions {
public:
    UnexpectedCharacters(const std::string& command, const int& pos);
};

class PipelineException : public CommandExceptions {
public:
    explicit PipelineException(const std::string& msg);
};

class RedirectionException : public CommandExceptions {
public:
    explicit RedirectionException(const std::string& msg);
};

#endif //CLI_COMMAND_EXCEPTIONS_H