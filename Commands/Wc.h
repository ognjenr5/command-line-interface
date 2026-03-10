#ifndef CLI_WC_H
#define CLI_WC_H

#include <string>
#include "MultilineCommand.h"
#include "../InputProcessing/InputStream.h"

class Wc : public MultilineCommand{
public:
    // Counts either words or characters in the InputStream argument
    void do_execute() override;

    std::string get_name() override;

    static Command* create_command(const std::vector<std::string> &args, bool pipe);
private:
    Wc(InputStream* is, char option);

    // Counts words in the input argument
    int count_words(std::string input);

    // Counts characters in the input argument
    int count_chars(std::string input);

    // Stores the option, whether to read words or characters
    char option;
};

inline std::string Wc::get_name() { return "wc"; }

#endif //CLI_WC_H