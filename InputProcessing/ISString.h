#ifndef CLI_ISSTRING_H
#define CLI_ISSTRING_H

#include <string>
#include "InputStream.h"

class ISString : public InputStream{
public:
    // InputStream derived class that reads from a string
    explicit ISString(std::string input_string);
};


#endif //CLI_ISSTRING_H