# Command Line Interpreter (C++)

A command-line interpreter written in C++ that simulates a simplified shell environment. The program parses user input, validates command arguments, and executes commands with support for pipelines, redirection, and extensible commands.

---

## Supported Commands

| Command | Description | Format |
|--------|-------------|-------------|
| `echo` | Prints text to output | echo \[*argument*\] |
| `prompt` | Change displayed prompt | prompt *argument* |
| `time` | Displays the current system time | time |
| `date` | Displays the current system date | date |
| `touch` | Creates a new file | touch *filename* |
| `truncate` | Truncates an existing file | truncate *filename* |
| `rm` | Removes an existing file | rm *filename* |
| `wc` | Counts words/characters in text | wc -*opt* \[*argument*\] |
| `wc` | Preforms character substitution in text | tr \[*argument*\] -*what* \[*with*\]  |
| `head` | Prints the first *n* lines of input | head -n*count* \[*argument*\]
| `batch` | Executes all commands from file | batch *filename* |

---

## Pipes and redirections

Commands can be combined using pipes and redirections, similar to a Unix shell.

Example:
` echo < file.txt | tr -"a" | wc -c >> out.txt `

---
