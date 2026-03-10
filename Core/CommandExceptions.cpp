#include "CommandExceptions.h"

#include <ostream>

const char * CommandExceptions::what() const noexcept{
    return this->err_msg.c_str();
}

InvalidArgument::InvalidArgument(const std::string& message) {
    this->err_msg = "Invalid argument. " + message + '\n';
}

InvalidCommandFormat::InvalidCommandFormat(const std::string &message) {
    this->err_msg = "Invalid command format. " + message + '\n';
}

InvalidArgumentCount::InvalidArgumentCount(const int &a) {
    this->err_msg = "Invalid argument count. Expected: " + std::to_string(a) + " argument(s).\n";
}

InvalidArgumentCount::InvalidArgumentCount(const int &a, const int &b) {
    this->err_msg = "Invalid argument count. Expected: "
    + std::to_string(a) + " to " + std::to_string(b) + " argument(s).\n";
}

NonexistentCommand::NonexistentCommand(const std::string& command_name) {
    this->err_msg = "Non-existent command: " + command_name + "\n";
}

UnexpectedCharacters::UnexpectedCharacters(const std::string &command, const int &pos) {
    this->err_msg = "Unexpected characters: \n" + command + "\n";
    for (int i = 0; i < pos; i++) this->err_msg += " ";
    this->err_msg += "^\n";
}

PipelineException::PipelineException(const std::string &msg) {
    this->err_msg = "Pipeline error. " + msg;
}

RedirectionException::RedirectionException(const std::string &msg) {
    this->err_msg = "Redirection error. " + msg;
}

