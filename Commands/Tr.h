#ifndef CLI_TR_H
#define CLI_TR_H

#include <string>
#include "MultilineCommand.h"
#include "../Core/Parser.h"
#include "../InputProcessing/InputStream.h"

class Tr : public MultilineCommand{
public:
    // Replaces every occurrence of array of characters "what" with the array of characters "with"
    void do_execute() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);

    std::string get_name() override;
private:
    Tr(InputStream* is, std::string what, std::string with = "");

    // Helper function to replace all "what" with "with"
    std::string replace_all() const;

    std::string what;
    std::string with;
};

inline std::string Tr::get_name() { return "tr"; }


#endif //CLI_TR_H