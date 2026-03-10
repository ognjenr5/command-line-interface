#ifndef CLI_MULTILINE_COMMAND_H
#define CLI_MULTILINE_COMMAND_H

#include <string>

#include "Command.h"
#include "../InputProcessing/InputStream.h"

class MultilineCommand : public Command {
public:
    // Base class for commands that accept multiline input arguments
    explicit MultilineCommand(InputStream* is);

    // Destructor deletes the InputStream object
    ~MultilineCommand() override;

    // Command can execute if InputStream argument is not null
    bool can_execute() override;

    // Creates InputStream object from multiline input passed through input string
    void load_argument(std::string argument) override;

    void set_input_redirection(const std::string& filename) override;

protected:
    InputStream *is;
};

#endif //CLI_MULTILINE_COMMAND_H