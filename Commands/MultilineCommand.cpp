#include "MultilineCommand.h"
#include "../InputProcessing/ISString.h"
#include "../InputProcessing/ISFile.h"
#include "../Core/CommandExceptions.h"

MultilineCommand::MultilineCommand(InputStream *is) {
    this->is = is;
}

MultilineCommand::~MultilineCommand() {
    delete this->is;
}

bool MultilineCommand::can_execute() {
    return this->is != nullptr;
}

void MultilineCommand::load_argument(std::string argument) {
    this->is = new ISString(std::move(argument));
}

void MultilineCommand::set_input_redirection(const std::string& filename) {
    if (is != nullptr)
        throw RedirectionException("Command " + get_name() + " already has a defined input stream.\n");
    this->is = new ISFile(filename);
}
