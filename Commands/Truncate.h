#ifndef CLI_TRUNCATE_H
#define CLI_TRUNCATE_H

#include <string>
#include "SingleLineCommand.h"

class Truncate : public SingleLineCommand{
public:
    // If a file with the passed name exists, truncates the contents of the file
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
private:
    explicit Truncate(std::string filename = "");
};

inline std::string Truncate::get_name() { return "truncate"; }

#endif //CLI_TRUNCATE_H