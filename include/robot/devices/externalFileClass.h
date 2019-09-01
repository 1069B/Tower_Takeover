#include "main.h"

#ifndef EXTERNALFILECLASS_H
#define EXTERNALFILECLASS_H

class ExternalFile{
private:
    std::fstream m_file;
    std::string m_fileAddress;

    int addLine(const std::string varibleName,const std::string lineValue);
    int updateLine(const std::string varibleName, const std::string lineValue);
    std::string readLine(const std::string varibleName);
public:
    ExternalFile(std::string address);

    //Single Varibles
    int addInt(const std::string varibleName,const int varibleValue);
    int updateInt(const std::string varibleName, const int varibleValue);
    int readInt(const std::string varibleName);

    int addDouble(const std::string varibleName, const double varibleValue);
    int updateDouble(const std::string varibleName, const double varibleValue);
    double readDouble(const std::string varibleName);

    int addChar(const std::string varibleName, const char varibleValue);
    int updateChar(const std::string varibleName, const char varibleValue);
    char readChar(const std::string varibleName);

    int addBool(const std::string varibleName, const bool varibleValue);
    int updateBool(const std::string varibleName, const bool varibleValue);
    bool readBool(const std::string varibleName);

    int addString(const std::string varibleName, const std::string varibleValue);
    int updateString(const std::string varibleName, const std::string varibleValue);
    std::string readString(const std::string varibleName);

    // Array of Varibles
    int addIntArray(const std::string varibleName,const std::vector<int> varibleValue);
    int updateIntArray(const std::string varibleName, const std::vector<int> varibleValue);
    std::vector<int> readIntArray(const std::string varibleName);

    int addDoubleArray(const std::string varibleName, const std::vector<double> varibleValue);
    int updateDoubleArray(const std::string varibleName, const std::vector<double> varibleValue);
    std::vector<double> readDoubleArray(const std::string varibleName);

    int addCharArray(const std::string varibleName, const std::vector<char> varibleValue);
    int updateCharArray(const std::string varibleName, const std::vector<char> varibleValue);
    std::vector<char> readCharArray(const std::string varibleName);

    int addBoolArray(const std::string varibleName, const std::vector<bool> varibleValue);
    int updateBoolArray(const std::string varibleName, const std::vector<bool> varibleValue);
    std::vector<bool> readBoolArray(const std::string varibleName);

    int addStringArray(const std::string varibleName, const std::vector<std::string> varibleValue);
    int updateStringArray(const std::string varibleName, const std::vector<std::string> varibleValue);
    std::vector<std::string> readStringArray(const std::string varibleName);
};

#endif // EXTERNALFILECLASS_H
