#include <ctime>
#include <iomanip>

#include "Date.h"
#include "../Core/CommandExceptions.h"

void Date::do_execute() {

    // Get current time
    const time_t t = std::time(nullptr);

    // Get local system time
    const std::tm tm = *std::localtime(&t);

    std::stringstream ss;

    ss << std::setw(2) << std::setfill('0') << tm.tm_mday<< ".";
    ss << std::setw(2) << std::setfill('0') << (tm.tm_mon+1) << ".";
    ss << std::setw(2) << std::setfill('0') << (tm.tm_year+1900) << ".";

    print(ss.str());
}

Command * Date::create_command(const std::vector<std::string> &args, bool pipe) {
    if (!args.empty())
        throw InvalidArgumentCount(0);

    return new Date();
}
