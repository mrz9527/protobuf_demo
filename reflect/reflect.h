// author : zhoukang
// date   : 2022-08-04 18:57:24

#ifndef PROTOBUF_DEMO_REFLECT_H
#define PROTOBUF_DEMO_REFLECT_H

#include "google/protobuf/message.h"

using google::protobuf::Message;

class Reflect {
public:
    static Message* CreateMessage(std::string messageName);

// 遍历Message
    static void PrintMessage(const Message& message, std::ostream& stream, int indent = 0);

private:
    static void PrintIndent(std::ostream& stream, int indent);

// 常规field遍历
    static void PrintField(const google::protobuf::Reflection* reflection, const google::protobuf::Message& message,
                    const google::protobuf::FieldDescriptor* fieldDescriptor, std::ostream& stream, int indent);

// repeater field遍历
    static void PrintRepeatedField(const google::protobuf::Reflection* reflection, const google::protobuf::Message& message,
                            const google::protobuf::FieldDescriptor* fieldDescriptor, std::ostream& stream, int indent);
};

#endif //PROTOBUF_DEMO_REFLECT_H
