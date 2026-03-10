#ifndef CLI_ISFILE_H
#define CLI_ISFILE_H
#include <string>

#include "InputStream.h"

class ISFile : public InputStream{
public:
    // InputStream derived class that reads input from file
    explicit ISFile(std::string filename);

private:
    // Helper function to read from file
    std::string read_from_file() const;

    std::string filename;
};

#endif //CLI_ISFILE_H