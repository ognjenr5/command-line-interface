#ifndef CLI_BATCH_H
#define CLI_BATCH_H

#include "SingleLineCommand.h"
#include "../Core/Controller.h"

class Batch : public SingleLineCommand {
public:
    // Executes all commands that exist in a file, one by one, independently
    void do_execute() override;

    // Set default output redirection for commands in batch
    void set_output_redirection(const std::string& filename) override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);

    std::string get_name() override;

private:

    explicit Batch(std::string filename = "");

    std::string default_output_redirection;

};

inline std::string Batch::get_name() { return "batch"; }

#endif //CLI_BATCH_H