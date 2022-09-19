// author : zhoukang
// date   : 2022-08-04 18:59:57

#ifndef PROTOBUF_DEMO_SERIALIZE_H
#define PROTOBUF_DEMO_SERIALIZE_H

#include "../common/ClassInfo.pb.h"
#include "fstream"

#include "google/protobuf/util/json_util.h"

using google::protobuf::Message;

class Serialize {
public:
    // 通过google::protobuf::util工具来转换protubuf和json
    static std::string MessageToJson(const Message& message);

    static void JsonToMessage(std::string strJson, Message* message);

    // 通过序列化方式
    static bool SerializeToFile(const tutorial::ClassInfo& classInfo, const char* filepath);

    static bool ParseFromFile(tutorial::ClassInfo& classInfo, const char* filePath);

    static std::string SerializeToString(const Message& message)
    {
        // 序列化
        std::string str;
        message.SerializeToString(&str);

        return str;
    }
};


#endif //PROTOBUF_DEMO_SERIALIZE_H
