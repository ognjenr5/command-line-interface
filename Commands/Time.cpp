#include <ctime>
#include <iostream>
#include <iomanip>

#include "Time.h"
#include "../Core/CommandExceptions.h"

void Time::do_execute() {
    // Get current time
    const time_t t = std::time(nullptr);

    // Get local system time
    const std::tm tm = *std::localtime(&t);

    std::stringstream ss;

    ss << std::setw(2) << std::setfill('0') << tm.tm_hour << ":";
    ss << std::setw(2) << std::setfill('0') << tm.tm_min << ":";
    ss << std::setw(2) << std::setfill('0') << tm.tm_sec;

    print(ss.str());
}

Command * Time::create_command(const std::vector<std::string> &args, bool pipe) {
    if (!args.empty())
        throw InvalidArgumentCount(0);

    return new Time();
}

