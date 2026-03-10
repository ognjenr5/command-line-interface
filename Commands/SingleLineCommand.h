#ifndef CLI_SINGLE_LINE_COMMAND_H
#define CLI_SINGLE_LINE_COMMAND_H

#include "Command.h"

class SingleLineCommand : public Command{
public:
    // Base class for commands that can only take one argument in a single line
    explicit SingleLineCommand(std::string argument);

    // Command can execute if its argument isn't empty
    bool can_execute() override;

    void load_argument(std::string argument) override;

protected:
    std::string argument;
};


#endif //CLI_SINGLE_LINE_COMMAND_H