#ifndef CLI_RM_H
#define CLI_RM_H

#include "SingleLineCommand.h"

class Rm : public SingleLineCommand{
public:
    // If a file with the passed name exists, removes it
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
private:
    explicit Rm(std::string filename = "");
};

inline std::string Rm::get_name() { return "rm"; }

#endif //CLI_RM_H