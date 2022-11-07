//这个头文件定义了一个用于修改ini文件的类

#ifndef _MYSETTINGS_H_
#define _MYSETTINGS_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <QString>

class MySettings{
 public:
    ~MySettings();

    //创建一个与ini文件关联的类
    int Open(const std::string& file);
    int Open(const QString& file){
        return this->Open(file.toStdString());
    }

    //读取对应节列表中的某个键值
    std::string GetValues(const std::string& section_name, const std::string& key_name);
    QString GetValues(const QString& section_name, const QString& key_name){
        return QString::fromStdString(this->GetValues(section_name.toStdString(),key_name.toStdString()));
    }

    //删除节
    int RemoveSection(const std::string& section_name);
    int RemoveSection(const QString& section_name){
        return this->RemoveSection(section_name.toStdString());
    }

    //删除键值
    int RemoveKey(const std::string& section_name, const std::string& key_name);
    int RemoveKey(const QString& section_name, const QString& key_name){
        return this->RemoveKey(section_name.toStdString(),key_name.toStdString());
    }

    //添加键值
    int SetValue(const std::string& section_name, const std::string& key_name, const std::string& value);
    int SetValue(const QString& section_name, const QString& key_name, const QString& value){
        return this->SetValue(section_name.toStdString(),key_name.toStdString(),value.toStdString());
    }

 private:
    //读取数据后，读取数据中的节列表，返回节的数量
    int GetSections();
    //从类变量中的ini文件中读取数据，忽略#/;开头的注释和空白行，每一行存在一个vector<string>容器内
    int ReadData();
    //分离键值
    static std::pair<std::string,std::string> KVSplit(const std::string&);
    //同步数据内容
    int Sync();


    std::string filePath;
    std::vector<std::string> data;
    std::vector<int> section;
};

#endif //_MYSETTINGS_H_

