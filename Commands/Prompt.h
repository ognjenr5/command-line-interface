#ifndef CLI_PROMPT_H
#define CLI_PROMPT_H

#include "SingleLineCommand.h"

class Prompt : public SingleLineCommand {
public:
    // Changes prompt string that displays at the start of commands
    void do_execute() override;

    std::string get_name() override;

    void load_argument(std::string argument) override;

    bool can_execute() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe = false);

private:
    explicit Prompt(std::string prompt = "");
};

inline std::string Prompt::get_name() { return "prompt"; }

#endif //CLI_PROMPT_H