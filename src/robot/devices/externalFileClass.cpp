#include "externalFileClass.h"

ExternalFile::ExternalFile(std::string address){
    m_fileAddress = address;
    m_file.open(m_fileAddress, std::ios::in);
    if(m_file.is_open()){
        std::cout << "File Exists" << std::endl;
        m_file.close();
    }
    else{
        std::cout << "File Doesn't Exist" << std::endl;
        m_file.open(m_fileAddress, std::ios::out);
        m_file << "Robot_Mode:= Debug" << std::endl;
        m_file << "Competition_Mode:= Practice" << std::endl;
        m_file << "Open_Last_Screen:= True" << std::endl;
        m_file << "Last_Screen:= Home" << std::endl;

        std::cout << "Default File Created" << std::endl;
        m_file.close();
    }
}

int ExternalFile::addVarible(std::string varibleName, std::string varibleValue){
    if(readVarible(varibleName) == "Didn't Find Var"){
        m_file.open(m_fileAddress, std::ios::app);
        m_file << varibleName << ":= " << varibleValue << std::endl;
        m_file.close();
        return 0;
    }
    return -1;
}

int ExternalFile::updateVarible(std::string varibleName, std::string varibleValue){
    std::vector<std::string> stringVector;
    std::string tempString;
    m_file.open(m_fileAddress, std::ios::in);
    while(std::getline(m_file, tempString)){
        if(!tempString.find(varibleName)){
            tempString = varibleName + ":= " + varibleValue;
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

std::string ExternalFile::readVarible(std::string varibleName){
    m_file.open(m_fileAddress, std::ios::in);
    std::string tempString;
    while(!m_file.eof()){
        m_file >> tempString;
        if(tempString == varibleName+":="){
            m_file >> tempString;
            m_file.close();
            return tempString;
        }
    }
    m_file.close();
    return "Didn't Find Var";
}
