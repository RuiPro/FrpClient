#include "mysettings.h"

MySettings::~MySettings() {
    std::vector<std::string>().swap(data);
    std::vector<int>().swap(section);
}

//对一个ini文件进行操作
int MySettings::Open(const std::string& file) {
    filePath = file;
    int i = ReadData();
    if(i > 0){
        GetSections();
        return 0;
    }
    else return -1;
}

//读取ini文件内容,若读取成功，返回有效数据的行数，若失败，返回-1
int MySettings::ReadData() {
    if(filePath.empty()) return -1;

    std::fstream fileStream;
    fileStream.open(filePath, std::ios::in);
    if (!fileStream.is_open())
    {
        std::cout << "Open ini file failed." << std::endl;
        return -1;
    }
    std::string str;
    int res = 0;
    while (getline(fileStream, str))
    {
        data.push_back(str);
        ++res;
    }
    fileStream.close();
    return res;
}

//解析节，如果解析成功返回节的数量
int MySettings::GetSections(){
    if(filePath.empty()) return -1;
    if(!data.empty()){
        section.clear();
        for(int i = 0; i < data.size(); ++i){
            std::string line = data.at(i);
            if(line.size() > 1 && line.at(0) == '[' && line.at(line.size() - 1) == ']'){
                section.push_back(i);
            }
        }
        return (int)section.size();
    }
    return 0;
}

std::string MySettings::GetValues(const std::string& section_name, const std::string& key_name){
    if(filePath.empty()) return "";
    if(data.empty()) return "";
    if(section.empty()) return "";
    int i = 0, j = 0;
    //找出对应的节的位置：i -> section
    for(; i < section.size(); ++i){
        if(data.at(section.at(i)).substr(1,data.at(section.at(i)).size() - 2) == section_name) {
            j = section.at(i);
            break;
        }
    }
    if(i == section.size()) return  "";
    //使用i在section中的值找出节在data中的实际位置，并循环操作其下的键值对：(j,k) -> data
    std::pair<std::string,std::string> KV;
    int k = (i < (section.size()-1) ? section.at(i+1) : data.size());
    for(j += 1; j < k; ++j){
        if(!data.at(j).empty() && data.at(j).at(0) != '#' && data.at(j).at(0) != ';'){
            KV = KVSplit(data.at(j));
            if(KV.first == key_name){
                break;
            }
        }
    }
    if(j == k) return "";
    return KV.second;
}

std::pair<std::string,std::string> MySettings::KVSplit(const std::string& str) {
    int split = str.find('=');
    std::string K = str.substr(0,split);
    std::string V = str.substr(split + 1, str.size() - 1);
    for(int i = K.size() - 1; i >=0; --i){
        std::cout << K << "===" << V <<std::endl;
        if(K.at(i) != ' ') break;
        if(K.at(i) == ' ') K.pop_back();
    }
    for(int i = V.size() - 1; i >=0; --i){
        if(K.at(i) != ' ') break;
        if(K.at(i) == ' ') K.pop_back();
    }
    std::pair<std::string,std::string> KV = std::make_pair(K,V);
    return KV;
}

int MySettings::Sync() {
    if(filePath.empty()) return -1;
    std::ofstream out;
    out.open(filePath);
    if(!out.good()) return -1;
    out.flush();
    for(auto x : data){
        out << x << std::endl;
    }
    out.close();
    return 0;
}

int MySettings::RemoveSection(const std::string& section_name) {
    if(filePath.empty()) return -1;
    if(data.empty()) return -1;
    if(section.empty()) return -1;
    int i = 0, j = 0;
    //找出对应的节的位置：i -> section
    for(; i < section.size(); ++i){
        if(data.at(section.at(i)).substr(1,data.at(section.at(i)).size() - 2) == section_name) {
            j = section.at(i);
            break;
        }
    }
    if(i == section.size()) return -1;
    //使用i在section中的值找出节在data中的实际位置，并操作其和其键值对：[j,k) -> data
    int k = (i < (section.size()-1) ? section.at(i+1) : data.size());
    std::vector<std::string> temp;
    for(int l = 0; l < data.size(); ++l){
        if(l < j || l >= k){
            temp.push_back(data.at(l));
        }
        else if(data.at(l).empty() || data.at(l).at(0) == '#' || data.at(l).at(0) == ';') {
            temp.push_back(data.at(l));
        }
    }
    data.swap(temp);
    Sync();
    return 0;
}

int MySettings::RemoveKey(const std::string& section_name, const std::string& key_name) {
    if(filePath.empty()) return -1;
    std::ifstream f(filePath);
    if(!f.good()) return -1;
    if(data.empty()) return -1;
    if(section.empty()) return -1;
    int i = 0, j = 0;
    //找出对应的节的位置：i -> section
    for(; i < section.size(); ++i){
        if(data.at(section.at(i)).substr(1,data.at(section.at(i)).size() - 2) == section_name) {
            j = section.at(i);
            break;
        }
    }
    if(i == section.size()) return  -1;
    //使用i在section中的值找出节在data中的实际位置，并循环操作其下的键值对：(j,k) -> data
    std::pair<std::string,std::string> KV;
    int k = (i < (section.size()-1) ? section.at(i+1) : data.size());
    for(j += 1; j < k; ++j){
        if(!data.at(j).empty() && data.at(j).at(0) != '#' && data.at(j).at(0) != ';'){
            KV = KVSplit(data.at(j));
            if(KV.first == key_name){
                break;
            }
        }
    }
    if(j == k) return -1;

    std::vector<std::string> temp;
    for(int l = 0; l < data.size(); ++l){
        if(l != j){
            temp.push_back(data.at(l));
        }
    }
    data.swap(temp);
    Sync();
    return 0;
}

int MySettings::SetValue(const std::string& section_name, const std::string& key_name, const std::string& value) {
    if(value.empty()) return 0;
    for(auto x : key_name){
        if(x == '=' || x == '[' || x == ']') return -2;
    }
    for(auto x : value){
        if(x == '=' || x == '[' || x == ']') return -2;
    }
    if(filePath.empty()) return -1;
    if(section_name.empty()) return -1;

    //找出对应的节的位置：i -> section
    int i = 0, j = 0;
    for(; i < section.size(); ++i){
        if(data.at(section.at(i)).substr(1,data.at(section.at(i)).size() - 2) == section_name) {
            j = section.at(i);
            break;
        }
    }
    if(i == section.size()){				//如果该节不存在，新建节
        data.push_back("[" + section_name + "]");
        data.push_back(key_name + "=" + value);
        GetSections();
        Sync();
        return data.size() - 1;
    }
    else{									//如果该节存在
        if(key_name.empty()) return -2;
        //使用i在section中的值找出节在data中的实际位置，并循环操作其下的键值对：(j,k) -> data
        std::pair<std::string,std::string> KV;
        int k = (i < (section.size()-1) ? section.at(i+1) : data.size());
        for(j += 1; j < k; ++j){
            if(!data.at(j).empty() && data.at(j).at(0) != '#' && data.at(j).at(0) != ';'){
                KV = KVSplit(data.at(j));
                if(KV.first == key_name){
                    break;
                }
            }
        }
        if(j == k) {		//如果该键不存在，在节的后面插入键值
            std::vector<std::string> temp;
            int ret;
            for(int n = 0; n < data.size(); ++n){
                temp.push_back(data.at(n));
                if(n == section.at(i)){
                    temp.push_back(key_name + "=" + value);
                    ret = n + 1;
                }
            }
            data.swap(temp);
            Sync();
            return ret;
        }
        else{				//如果该键存在，直接修改键值
            data.at(j) = std::string(key_name + "=" + value);
            Sync();
            return j;
        }
    }
}
