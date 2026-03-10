#ifndef CLI_ECHO_H
#define CLI_ECHO_H

#include "MultilineCommand.h"
#include "../InputProcessing/InputStream.h"

class Echo : public MultilineCommand {
public:
    // Prints received text from InputStream
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);

private:
    explicit Echo(InputStream *is = nullptr);
};

inline std::string Echo::get_name() { return "echo"; }

#endif //CLI_ECHO_H