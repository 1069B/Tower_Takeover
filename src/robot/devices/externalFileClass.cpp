#include "externalFileClass.h"

ExternalFile::ExternalFile(std::string address){
    m_fileAddress = "/usd/" + address;
    m_file.open(m_fileAddress, std::ios::in);
    if(m_file.is_open()){
        m_file.close();
    }
    else{
        m_file.open(m_fileAddress, std::ios::out);
        m_file.close();
    }
}

bool ExternalFile::varExist(const std::string varibleTitle){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleTitle)){
            m_file.close();
            return true;
        }
    }
    m_file.close();
    return false;
}
int ExternalFile::addLine(const std::string lineValue){
    m_file.open(m_fileAddress, std::ios::app);
    m_file << lineValue << std::endl;
    m_file.close();
    return 0;
}
int ExternalFile::updateLine(const std::string varibleTitle, const std::string lineValue){
    std::vector<std::string> stringVector;
    std::string tempString;
    m_file.open(m_fileAddress, std::ios::in);
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleTitle)){
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
std::string ExternalFile::readLine(const std::string varibleTitle){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleTitle)){
            m_file.close();
            return tempString;
        }
    }
    m_file.close();
    return "Error";
}

int ExternalFile::storeVar(const std::string varibleTitle, const std::string lineValue){
    if(varExist(varibleTitle)){
        updateLine(varibleTitle, lineValue);
    }
    else{
        addLine(lineValue);
    }
    return 1;
}

int ExternalFile::storeInt(const std::string varibleName, const int varibleValue){
    std::string varibleTitle = varibleName + ":Int= ";
    std::string lineValue = varibleTitle + std::to_string(varibleValue);
    return storeVar(varibleTitle, lineValue);
}
int ExternalFile::readInt(const std::string varibleName){
    std::string varibleTitle = varibleName + ":Int= ";
    std::string lineValue = readLine(varibleTitle);
    return std::stoi(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeDouble(const std::string varibleName, const double varibleValue){
    std::string varibleTitle = varibleName + ":Double= ";
    std::string lineValue = varibleTitle + std::to_string(varibleValue);
    return storeVar(varibleTitle, lineValue);
}
double ExternalFile::readDouble(const std::string varibleName){
    std::string varibleTitle = varibleName + ":Double= ";
    std::string lineValue = readLine(varibleTitle);
    return std::stod(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeChar(const std::string varibleName, const char varibleValue){
    std::string varibleTitle = varibleName + ":Char= ";
    std::string lineValue = varibleTitle + varibleValue;
    return storeVar(varibleTitle, lineValue);
}
char ExternalFile::readChar(const std::string varibleName){
    std::string varibleTitle = varibleName + ":Char= ";
    std::string lineValue = readLine(varibleTitle);
    return lineValue.at(varibleTitle.size());
}

int ExternalFile::storeBool(const std::string varibleName, const bool varibleValue){
    std::string varibleTitle = varibleName + ":Bool= ";
    std::string lineValue = varibleTitle + std::to_string(varibleValue);
    return storeVar(varibleTitle, lineValue);
}
bool ExternalFile::readBool(const std::string varibleName){
    std::string varibleTitle = varibleName + ":Bool= ";
    std::string lineValue = readLine(varibleTitle);
    return std::stoi(lineValue.substr(varibleTitle.size()));
}

int ExternalFile::storeString(const std::string varibleName, const std::string varibleValue){
    std::string varibleTitle = varibleName + ":String= ";
    std::string lineValue = varibleTitle + varibleValue;
    return storeVar(varibleTitle, lineValue);
}
std::string ExternalFile::readString(const std::string varibleName){
    std::string varibleTitle = varibleName + ":String= ";
    std::string lineValue = readLine(varibleTitle);
    return lineValue.substr(varibleTitle.size());
}

// Array of Varibles
int ExternalFile::storeIntArray(const std::string varibleName,const std::vector<int> varibleValue){
    std::string varibleTitle = varibleName + ":IntArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<int> ExternalFile::readIntArray(const std::string varibleName){
    std::string varibleTitle = varibleName + ":IntArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<int> tempVec;
    int position = (int)varibleTitle.size();
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

int ExternalFile::storeDoubleArray(const std::string varibleName, const std::vector<double> varibleValue){
    std::string varibleTitle = varibleName + ":DoubleArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<double> ExternalFile::readDoubleArray(const std::string varibleName){
    std::string varibleTitle = varibleName + ":DoubleArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<double> tempVec;
    int position = (int)varibleTitle.size();
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

int ExternalFile::storeCharArray(const std::string varibleName, const std::vector<char> varibleValue){
    std::string varibleTitle = varibleName + ":CharArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::string(1, varibleValue.at(x))+ ", ";
    }
    lineValue += std::string(1, varibleValue.at(varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<char> ExternalFile::readCharArray(const std::string varibleName){
    std::string varibleTitle = varibleName + ":CharArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<char> tempVec;
    int position = (int)varibleTitle.size();
    bool x = true;
    while(x){
        std::string tempString = lineValue.substr(position);
        if(tempString.find(",") == -1){
            tempVec.push_back(tempString.at(tempString.find("~")-1));
            x = false;
        }
        else{
            tempVec.push_back(tempString.at(tempString.find(",")-1));
            position+=tempString.find(",")+2;
        }
    }
    return tempVec;
}

int ExternalFile::storeBoolArray(const std::string varibleName, const std::vector<bool> varibleValue){
    std::string varibleTitle = varibleName + ":BoolArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += std::to_string(varibleValue.at(x))+ ", ";
    }
    lineValue += std::to_string(varibleValue.at(varibleValue.size()-1))+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<bool> ExternalFile::readBoolArray(const std::string varibleName){
    std::string varibleTitle = varibleName + ":BoolArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<bool> tempVec;
    int position = (int)varibleTitle.size();
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

int ExternalFile::storeStringArray(const std::string varibleName, const std::vector<std::string> varibleValue){
    std::string varibleTitle = varibleName + ":StringArray= ";
    std::string lineValue = varibleTitle;
    for(int x = 0; x<varibleValue.size()-1; x++){
        lineValue += varibleValue.at(x)+ ", ";
    }
    lineValue += varibleValue.at(varibleValue.size()-1)+"~";
    return storeVar(varibleTitle, lineValue);
}
std::vector<std::string> ExternalFile::readStringArray(const std::string varibleName){
    std::string varibleTitle = varibleName + ":StringArray= ";
    std::string lineValue = readLine(varibleTitle);
    std::vector<std::string> tempVec;
    int position = (int)varibleTitle.size();
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
