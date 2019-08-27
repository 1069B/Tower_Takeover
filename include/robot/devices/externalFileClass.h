#include "main.h"

#ifndef EXTERNALFILECLASS_H
#define EXTERNALFILECLASS_H

class ExternalFile{
private:
    std::fstream m_file;
    std::string m_fileAddress;
public:
    ExternalFile(std::string address);

    int addVarible(std::string varibleName, std::string varibleValue);

    int updateVarible(std::string varibleName, std::string varibleValue);

    std::string readVarible(std::string varibleName);
};

#endif // EXTERNALFILECLASS_H
