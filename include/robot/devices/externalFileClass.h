#include "main.h"

#ifndef EXTERNALFILECLASS_H
#define EXTERNALFILECLASS_H

class ExternalFile{
private:
    std::fstream m_file;
    std::string m_fileAddress;

    bool varExist(const std::string varibleTitle);
    int addLine(const std::string lineValue);
    int updateLine(const std::string varibleTitle, const std::string lineValue);
    int storeVar(const std::string varibleTitle, const std::string lineValue);
    std::string readLine(const std::string varibleTitle);
public:
    ExternalFile(std::string address);

    //Single Varibles
    int storeInt(const std::string varibleName,const int varibleValue);
    int readInt(const std::string varibleName);

    int storeDouble(const std::string varibleName, const double varibleValue);
    double readDouble(const std::string varibleName);

    int storeChar(const std::string varibleName, const char varibleValue);
    char readChar(const std::string varibleName);

    int storeBool(const std::string varibleName, const bool varibleValue);
    bool readBool(const std::string varibleName);

    int storeString(const std::string varibleName, const std::string varibleValue);
    std::string readString(const std::string varibleName);

    // Array of Varibles
    int storeIntArray(const std::string varibleName,const std::vector<int> varibleValue);
    std::vector<int> readIntArray(const std::string varibleName);

    int storeDoubleArray(const std::string varibleName, const std::vector<double> varibleValue);
    std::vector<double> readDoubleArray(const std::string varibleName);

    int storeCharArray(const std::string varibleName, const std::vector<char> varibleValue);
    std::vector<char> readCharArray(const std::string varibleName);

    int storeBoolArray(const std::string varibleName, const std::vector<bool> varibleValue);
    std::vector<bool> readBoolArray(const std::string varibleName);

    int storeStringArray(const std::string varibleName, const std::vector<std::string> varibleValue);
    std::vector<std::string> readStringArray(const std::string varibleName);
};

#endif // EXTERNALFILECLASS_H
