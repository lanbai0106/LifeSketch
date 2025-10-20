#ifndef LOADDATA1_H
#define LOADDATA1_H

#include <fstream>
#include <queue>
#include <sstream>
#include "BOBHash32.h"
#include <filesystem>
// namespace fs = std::filesystem;
const int MAX_INSERT_PACKAGE = 2.5e7;
int packetnum;

struct Object {
    vector<uint32_t> pac_list;
    vector<uint64_t> timestamp;
};
uint64_t calc(uint32_t a, uint32_t b) {
    return 1ll * a * 1000000 + b;
}
uint32_t convertIPv4ToUint32(char* ipAddress) {
    uint32_t result = 0;
    int octet =0;
    char ipCopy[40];
    strncpy(ipCopy,ipAddress,sizeof(ipCopy)-1);
    ipCopy[sizeof(ipCopy)-1]='\0';
    char* token=strtok(ipCopy,".");
    while(token !=nullptr) {
        octet =std::stoi(token);
        result=(result<<8)+octet;
        token = std::strtok(nullptr,".");
    }
    return result;
}

class DataLoader {
    private:
        Object obj;
        string filePath;
    public:
        DataLoader(string filePath): filePath(filePath){
            if(filePath == "ca19") {
                filePath = "data/CAIDA19.txt";
            }else if(filePath == "ca16") {
                filePath = "data/CAIDA16.txt";
            }else if(filePath == "so") {
                filePath = "data/stackoverflow.txt";
            }else if(filePath == "wd") {
                filePath = "data/webdocs.txt";
                // clear();
                // load_data_(filePath);
                // cout << "Loading dataset" << endl;
                // return;
            }
            clear();
            load_data(filePath);
            cout << "Loading dataset" << endl;
        }
        void clear() {
            obj.pac_list.clear();
            obj.timestamp.clear();
        }
        void load_data_(string filePath) {
            ofstream sandianLS("D:\\code\\LifeSketch\\LifeSketch\\data\\webdocs.txt");
            ifstream fin(filePath);  // 打开文件
            if (!fin.is_open()) {
                cerr << "Error: cannot open file." << endl;
                exit(-1);
            }
            int ret = 0;
            string line;

            while (getline(fin, line)) {
                stringstream ss(line);
                string str2;

                while (ss >> str2) {
                    char *s2 = &str2[0];
                    uint32_t x = convertIPv4ToUint32(s2);
                    obj.pac_list.push_back(x);
                    obj.timestamp.push_back(ret);
                    sandianLS << ret << " " << str2 << endl;
                    // obj.timestamp.push_back(calc(*((uint32_t *) x), *((uint32_t *) x+1))) ; // time-based
                    ret++;
                    cout << ret <<" "<< MAX_INSERT_PACKAGE << endl;
                    if (ret >= MAX_INSERT_PACKAGE)
                        break;
                }
                if (ret >= MAX_INSERT_PACKAGE)
                    break;
            }
            packetnum = ret;

            fin.close();
            sandianLS.close();
        }
        void load_data(string filePath) {
            std::ifstream pf(filePath);
            if (!pf) {
                cerr << filePath << " not found." << endl;
                exit(-1);
            }

            int ret = 0;
            string line;

            while (getline(pf, line)) {
                std::istringstream stream(line);
                std::string str1, str2;
                stream >> str1 >> str2;
                bool f1 = std::any_of(str1.begin(), str1.end(), [](char ch) {
                    return std::isalpha(static_cast<unsigned char>(ch));
                }),f2 = std::any_of(str2.begin(), str2.end(), [](char ch) {
                    return std::isalpha(static_cast<unsigned char>(ch));
                });
                if(f2) {
                    continue;
                }
                char *s2 = &str2[0];
                uint32_t x = convertIPv4ToUint32(s2);
                // uint32_t x = stoul(s1), y = stoul(s2);
                if(x != 0){
                    obj.pac_list.push_back(x);
                    obj.timestamp.push_back(ret);
                    // obj.timestamp.push_back(calc(*((uint32_t *) x), *((uint32_t *) x+1))) ; // time-based
                    ret++;
                    if (ret == MAX_INSERT_PACKAGE)
                        break;

                }
                packetnum = ret;
            }
            pf.close();

        }
    Object get_object() {return obj;}
};
#endif //LOADDATA_H
