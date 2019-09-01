#include "externalFileClass.h"

ExternalFile::ExternalFile(std::string address){
    m_fileAddress = "/usd/" + address;
    m_file.open(m_fileAddress, std::ios::in);
    if(m_file.is_open()){
        std::cout << "File Exists" << std::endl;
        m_file.close();
    }
    else{
        std::cout << "File Doesn't Exist" << std::endl;
        m_file.open(m_fileAddress, std::ios::out);
        m_file.close();
        std::cout << "Default File Created" << std::endl;
    }
}

int ExternalFile::addLine(const std::string varibleName,const std::string lineValue){
    if(readLine(varibleName) == "Error"){
        m_file.open(m_fileAddress, std::ios::app);
        m_file << lineValue << std::endl;
        m_file.close();
        return 0;
    }
    return -1;
}
int ExternalFile::updateLine(const std::string varibleName, const std::string lineValue){
    std::vector<std::string> stringVector;
    std::string tempString;
    m_file.open(m_fileAddress, std::ios::in);
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleName)){
            tempString = lineValue;
            stringVector.push_back(tempString);
        }
        else{
            stringVector.push_back(tempString);
        }
    }
    m_file.close();

    m_file.open(m_fileAddress, std::ios::out);
    for(int x = 0; x < stringVector.size(); x++){
        m_file << stringVector.at(x) << std::endl;
    }
    m_file.close();
    return 0;
}
std::string ExternalFile::readLine(const std::string varibleName){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleName)){
            m_file.close();
            return tempString;
        }
    }
    m_file.close();
    return "Error";
}

int ExternalFile::addInt(const std::string varibleName,const int varibleValue){
    std::string lineValue = varibleName + ":Int= " + std::to_string(varibleValue);
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateInt(const std::string varibleName, const int varibleValue){
    std::string lineValue = varibleName + ":Int= " + std::to_string(varibleValue);
    return updateLine(varibleName, lineValue);
}
int ExternalFile::readInt(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    return std::stoi(lineValue.substr(lineValue.find(":Int= ")+6));
}

int ExternalFile::addDouble(const std::string varibleName, const double varibleValue){
    std::string lineValue = varibleName + ":Double= " + std::to_string(varibleValue);
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateDouble(const std::string varibleName, const double varibleValue){
    std::string lineValue = varibleName + ":Double= " + std::to_string(varibleValue);
    return updateLine(varibleName, lineValue);
}
double ExternalFile::readDouble(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    return std::stod(lineValue.substr(lineValue.find(":Double= ")+9));
}

int ExternalFile::addChar(const std::string varibleName, const char varibleValue){
    std::string lineValue = varibleName + ":Char= " + varibleValue;
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateChar(const std::string varibleName, const char varibleValue){
    std::string lineValue = varibleName + ":Char= " + varibleValue;
    return updateLine(varibleName, lineValue);
}
char ExternalFile::readChar(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    return lineValue.at(lineValue.find(":Char= ")+7);
}

int ExternalFile::addBool(const std::string varibleName, const bool varibleValue){
    std::string lineValue = varibleName + ":Bool= " + std::to_string(varibleValue);
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateBool(const std::string varibleName, const bool varibleValue){
    std::string lineValue = varibleName + ":Bool= " + std::to_string(varibleValue);
    return updateLine(varibleName, lineValue);
}
bool ExternalFile::readBool(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    return std::stoi(lineValue.substr(lineValue.find(":Bool= ")+7));
}

int ExternalFile::addString(const std::string varibleName, const std::string varibleValue){
    std::string lineValue = varibleName + ":String= " + varibleValue;
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateString(const std::string varibleName, const std::string varibleValue){
    std::string lineValue = varibleName + ":String= " + varibleValue;
    return updateLine(varibleName, lineValue);
}
std::string ExternalFile::readString(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    return lineValue.substr(lineValue.find(":String= ")+9);
}

// Array of Varibles
int ExternalFile::addIntArray(const std::string varibleName,const std::vector<int> varibleValue){
    std::string lineValue = varibleName + ":IntArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateIntArray(const std::string varibleName, const std::vector<int> varibleValue){
    std::string lineValue = varibleName + ":IntArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.size()-1)+"~";
    return updateLine(varibleName, lineValue);
}
std::vector<int> ExternalFile::readIntArray(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    std::vector<int> tempVec;
    int position = (int)lineValue.find(":IntArray= ")+11;
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stoi(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
            tempVec.push_back(std::stoi(tempString.substr(0,tempString.find(","))));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::addDoubleArray(const std::string varibleName, const std::vector<double> varibleValue){
    std::string lineValue = varibleName + ":DoubleArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateDoubleArray(const std::string varibleName, const std::vector<double> varibleValue){
    std::string lineValue = varibleName + ":DoubleArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return updateLine(varibleName, lineValue);
}
std::vector<double> ExternalFile::readDoubleArray(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    std::vector<double> tempVec;
    int position = (int)lineValue.find(":DoubleArray= ")+14;
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stod(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
            tempVec.push_back(std::stod(tempString.substr(0,tempString.find(","))));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::addCharArray(const std::string varibleName, const std::vector<char> varibleValue){
    std::string lineValue = varibleName + ":CharArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::string(1,varibleValue.at(x)) + ", ";
    }
    lineValue += std::string(1, varibleValue.at(varibleValue.size()-1))+"~";
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateCharArray(const std::string varibleName, const std::vector<char> varibleValue){
    std::string lineValue = varibleName + ":CharArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::string(1,varibleValue.at(x)) + ", ";
    }
    lineValue += std::string(1, varibleValue.at(varibleValue.size()-1))+"~";
    return updateLine(varibleName, lineValue);
}
std::vector<char> ExternalFile::readCharArray(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    std::vector<char> tempVec;
    int position = (int)lineValue.find(":CharArray= ")+12;
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(tempString.at(0));
            x = false;
        }
        else{
            tempVec.push_back(tempString.at(0));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::addBoolArray(const std::string varibleName, const std::vector<bool> varibleValue){
    std::string lineValue = varibleName + ":BoolArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateBoolArray(const std::string varibleName, const std::vector<bool> varibleValue){
    std::string lineValue = varibleName + ":BoolArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return updateLine(varibleName, lineValue);
}
std::vector<bool> ExternalFile::readBoolArray(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    std::vector<bool> tempVec;
    int position = (int)lineValue.find(":BoolArray= ")+12;
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(std::stoi(tempString.substr(0, tempString.find("~"))));
            x = false;
        }
        else{
            tempVec.push_back(std::stoi(tempString.substr(0,tempString.find(","))));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::addStringArray(const std::string varibleName, const std::vector<std::string> varibleValue){
    std::string lineValue = varibleName + ":StringArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += varibleValue.at(x)+ ", ";
    }
    lineValue += varibleValue.at(varibleValue.size()-1)+"~";
    return addLine(varibleName, lineValue);
}
int ExternalFile::updateStringArray(const std::string varibleName, const std::vector<std::string> varibleValue){
    std::string lineValue = varibleName + ":StringArray= ";
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += varibleValue.at(x) + ", ";
    }
    lineValue += varibleValue.at(varibleValue.size()-1)+"~";
    return updateLine(varibleName, lineValue);
}
std::vector<std::string> ExternalFile::readStringArray(const std::string varibleName){
    std::string lineValue = readLine(varibleName);
    std::vector<std::string> tempVec;
    int position = (int)lineValue.find(":StringArray= ")+14;
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(tempString.substr(0, tempString.find("~")));
            x = false;
        }
        else{
            tempVec.push_back(tempString.substr(0,tempString.find(",")));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}
