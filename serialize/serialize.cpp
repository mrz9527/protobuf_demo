// author : zhoukang
// date   : 2022-07-27 14:49:04

#include "serialize.h"

std::string Serialize::MessageToJson(const Message& message)
{
    std::string strJson;
    google::protobuf::util::MessageToJsonString(message, &strJson);

    return strJson;
}

void Serialize::JsonToMessage(std::string strJson, Message* message)
{
    google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(strJson, message);
}

bool Serialize::SerializeToFile(const tutorial::ClassInfo &classInfo, const char *filepath)
{
    // 打开文件流
    std::ofstream ofstream;
    ofstream.open(filepath, std::ios::out | std::ios::trunc);
    if (!ofstream.is_open()) {
        printf("ofstream.open(%s) failed\n", filepath);
        return false;
    }

    // 序列化到文件
    bool res = classInfo.SerializeToOstream(&ofstream);

    // 关闭文件流
    ofstream.close();

    return res;
}

bool Serialize::ParseFromFile(tutorial::ClassInfo &classInfo, const char *filePath)
{
    // 打开文件流
    std::fstream fstream;
    fstream.open(filePath, std::ios::in);
    if (!fstream.is_open()) { // 文件可能不存在，就创建文件
        fstream.open(filePath, std::ios::out);
        fstream.close();
        return true;
    }

    // 反序列化
    bool res = classInfo.ParseFromIstream(&fstream);

    // 关闭文件流
    fstream.close();

    return res;
}