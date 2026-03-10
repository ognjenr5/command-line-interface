#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include <string>
#include <iostream>

#include "../Core/Parser.h"

class Command {
public:
    // Command template abstract class
    Command();

    virtual ~Command();

    // Executes command, abstract
    virtual void do_execute() = 0;

    // Returns name of specific command, abstract
    virtual std::string get_name() = 0;

    // Checks if command can be executed, by default returns true
    virtual bool can_execute();

    // Loads argument for command that can load multiline arguments, by default does nothing
    virtual void load_argument(std::string argument);

    // Takes care of normal and pipeline execution
    void execute();

    // Redirection handling
    virtual void set_input_redirection(const std::string& filename);

    virtual void set_output_redirection(const std::string& filename);

    bool has_default_output_redirection() const;

    static std::string get_prompt();

    // For pipeline, check for previous output
    static bool has_piped_output();

    // Pipe position enumeration
    enum class PipePosition {NOT_IN, IN, LAST};

    // Pipeline handling
    void set_pipeline_position(PipePosition p);

    PipePosition get_pipeline_position() const;

    bool is_in_pipe() const;

    // Error output stream
    static std::ostream* get_error_os ();

    static void set_error_os (std::ostream* os);

protected:

    // Commands output stream setter
    void set_ostream(std::ostream* os);

    // Called by functions with output, handles printing to file/standard output/next pipeline command
    void print(const std::string& output) const;

    static void set_prompt(std::string new_prompt);

    static std::string previous_output;

    static bool has_previous_output;

    static std::string prompt;

    std::ostream* output_stream;

    static std::ostream* error_output_stream;

    PipePosition position;
};

inline Command::Command() : output_stream(&std::cout), position(PipePosition::NOT_IN) {}

inline bool Command::has_default_output_redirection() const { return output_stream == &std::cout; }

inline void Command::set_pipeline_position(PipePosition p) { position = p; }

inline Command::PipePosition Command::get_pipeline_position() const { return position; }

inline bool Command::is_in_pipe() const { return position != PipePosition::NOT_IN; }

inline std::string Command::get_prompt() { return prompt; }

inline bool Command::can_execute() { return true; }

inline void Command::load_argument(std::string argument) {}

inline std::ostream *Command::get_error_os() { return error_output_stream; }

inline void Command::set_error_os(std::ostream *os) { error_output_stream = os; }







#endif //CLI_COMMAND_H