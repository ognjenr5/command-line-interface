#ifndef CLI_HEAD_H
#define CLI_HEAD_H

#include "MultilineCommand.h"
#include "../InputProcessing/InputStream.h"

class Head : public MultilineCommand{
public:
    // Displays first n lines of text
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);

private:
    Head(InputStream* is, int nn);

    int n;
};

inline std::string Head::get_name() { return "head"; }

#endif //CLI_HEAD_H