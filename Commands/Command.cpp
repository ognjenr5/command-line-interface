#include <string>
#include <utility>
#include <fstream>

#include "Command.h"
#include "../Core/CommandExceptions.h"

std::string Command::prompt = "$";
std::string Command::previous_output;
std::ostream* Command::error_output_stream = &std::cerr;
bool Command::has_previous_output = false;

Command::~Command() {
    // Deletes commands output stream pointer if it's a file output stream
    if (output_stream != &std::cout)
        delete output_stream;

}

void Command::execute() {
    // Pipeline commands that aren't first, load argument from previous command's output
    if (position != PipePosition::NOT_IN && !can_execute())
        load_argument(previous_output);

    // Executes current function
    do_execute();

    // Last pipeline command clears saved previous output
    if (position == PipePosition::LAST)
        has_previous_output = false;

    // Non-last pipeline command signals existing previous output
    else if (position != PipePosition::NOT_IN)
        has_previous_output = true;
}

void Command::set_input_redirection(const std::string &filename) {
    throw RedirectionException("Input redirection not allowed for this command.\n");
}


void Command::set_output_redirection(const std::string &filename) {

    // Differentiates between append mode and regular output
    bool append_mode = filename[0] == '>';
    std::ofstream* f;

    // Creates new output filestream and sets it
    if (append_mode)
        f = new std::ofstream(filename.substr(1).c_str(), std::fstream::app);
    else
        f = new std::ofstream(filename.c_str());

    output_stream = f;
}


bool Command::has_piped_output() {
    return has_previous_output;
}

void Command::set_prompt(std::string new_prompt) {
    prompt = std::move(new_prompt);
}

void Command::set_ostream(std::ostream *os) {
    output_stream = os;
}

void Command::print(const std::string &output) const {
    // Command prints to output stream if it's last in pipe or isn't in a pipe
    // Otherwise, saves output for next command in pipe

    if (position != PipePosition::IN)
        *output_stream << output << (output_stream == &std::cout ? "\n" : "");
    else
        previous_output = output;
}
