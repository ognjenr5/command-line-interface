#ifndef CLI_TOUCH_H
#define CLI_TOUCH_H

#include <string>

#include "SingleLineCommand.h"

class Touch : public SingleLineCommand {
public:
    // If a file with the passed name doesn't exist, creates a new file, otherwise throws FileExists exception
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
private:
    explicit Touch(std::string filename = "");
};

inline std::string Touch::get_name() { return "touch"; }

#endif //CLI_TOUCH_H