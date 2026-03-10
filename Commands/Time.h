#ifndef CLI_TIME_H
#define CLI_TIME_H

#include <sstream>
#include "Command.h"

class Time : public Command {
public:
    // Prints current time in format HH:MM:SS
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
};

inline std::string Time::get_name() { return "time"; }


#endif //CLI_TIME_H

