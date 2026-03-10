#ifndef CLI_DATE_H
#define CLI_DATE_H

#include <stringstream>
#include "Command.h"

class Date : public Command{
public:
    // Prints current date in format DD.MM.YYYY.
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
};

inline std::string Date::get_name() { return "date"; }


#endif //CLI_DATE_H
