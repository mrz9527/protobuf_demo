// author : zhoukang
// date   : 2022-07-28 11:40:51

#include "reflect.h"

Message* Reflect::CreateMessage(std::string messageName)
{
    // 创建【描述池】
    const google::protobuf::DescriptorPool* descriptorPool = google::protobuf::DescriptorPool::generated_pool();
    // 创建【message工厂】
    google::protobuf::MessageFactory* factory = google::protobuf::MessageFactory::generated_factory();

    // 在【描述池】中查找【message描述】
    const google::protobuf::Descriptor* messageDescriptor = descriptorPool->FindMessageTypeByName(messageName);
    // 在【message工厂】中获取指定【message描述】的【message类型】
    const Message* messageType = factory->GetPrototype(messageDescriptor);

    // 通过【message类型】来创建message
    Message* message = messageType->New();
    // 填充message中的数据。通过reflect->AddString AddInt Add...(message, fieldDescriptor, val)
    return message;
}

void Reflect::PrintIndent(std::ostream& stream, int indent)
{
    int i = 0;
    while (i < indent) {
        stream << "\t";
        ++i;
    }
}

// 常规field遍历
void Reflect::PrintField(const google::protobuf::Reflection* reflection, const google::protobuf::Message& message,
                const google::protobuf::FieldDescriptor* fieldDescriptor, std::ostream& stream, int indent)
{
    if (!reflection->HasField(message, fieldDescriptor)) { //HasField函数，只针对singular field字段使用，repeated field字段不能使用HasField函数。
        return;
    }

#define CASE_FIELD_TYPE(cpptype, method, valuetype)\
                case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{\
                    valuetype value = reflection->Get##method(message, fieldDescriptor);\
                    stream << value; \
                    break;\
                }

    PrintIndent(stream, indent);

    std::string cppTypeName = fieldDescriptor->cpp_type_name();
    std::string fieldName = fieldDescriptor->name();

    stream << cppTypeName << "\t" << fieldName << "\t";

    auto cppType = fieldDescriptor->cpp_type();

    switch (cppType) {
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {   // message字段
            auto& subMessage = reflection->GetMessage(message, fieldDescriptor);
            stream << std::endl;
            PrintMessage(subMessage, stream, indent + 1); // subMessage,缩进+1
            break;
        }
        case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
            auto fieldValue = reflection->GetEnum(message, fieldDescriptor)->number();
            stream << fieldValue;
            break;
        }

        CASE_FIELD_TYPE(INT32, Int32, int);
        CASE_FIELD_TYPE(INT64, Int64, int64_t);
        CASE_FIELD_TYPE(UINT32, UInt32, uint32_t);
        CASE_FIELD_TYPE(UINT64, UInt64, uint64_t);
        CASE_FIELD_TYPE(DOUBLE, Double, double);
        CASE_FIELD_TYPE(FLOAT, Float, float);
        CASE_FIELD_TYPE(BOOL, Bool, bool);
        CASE_FIELD_TYPE(STRING, String, std::string);
    }
    stream << std::endl;
}

// repeater field遍历
void Reflect::PrintRepeatedField(const google::protobuf::Reflection* reflection, const google::protobuf::Message& message,
                        const google::protobuf::FieldDescriptor* fieldDescriptor, std::ostream& stream, int indent)
{
#define CASE_REPEATEDFIELD_TYPE(cpptype, method, valuetype)\
                case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{\
                    valuetype value = reflection->Get##method(message, fieldDescriptor);\
                    stream << value; \
                    break;\
                }

    PrintIndent(stream, indent);

    std::string cppTypeName = fieldDescriptor->cpp_type_name();
    std::string fieldName = fieldDescriptor->name();

    stream << cppTypeName << "\t" << fieldName << std::endl;

    indent += 1;

    auto cppType = fieldDescriptor->cpp_type();
    int fieldSize = reflection->FieldSize(message, fieldDescriptor);
    for (int i = 0; i < fieldSize; ++i) {
        PrintIndent(stream, indent);
        stream << "[" << i << "]\t";
        switch (cppType) {
            case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {   // message字段
                auto& subMessage = reflection->GetRepeatedMessage(message, fieldDescriptor, i);
                stream << std::endl;
                PrintMessage(subMessage, stream, indent + 1); // subMessage,缩进+1
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                auto fieldValue = reflection->GetEnum(message, fieldDescriptor)->number();
                stream << fieldValue;
                break;
            }

            CASE_REPEATEDFIELD_TYPE(INT32, Int32, int);
            CASE_REPEATEDFIELD_TYPE(INT64, Int64, int64_t);
            CASE_REPEATEDFIELD_TYPE(UINT32, UInt32, uint32_t);
            CASE_REPEATEDFIELD_TYPE(UINT64, UInt64, uint64_t);
            CASE_REPEATEDFIELD_TYPE(DOUBLE, Double, double);
            CASE_REPEATEDFIELD_TYPE(FLOAT, Float, float);
            CASE_REPEATEDFIELD_TYPE(BOOL, Bool, bool);
            CASE_REPEATEDFIELD_TYPE(STRING, String, std::string);
        }
    }
}

// 遍历Message
void Reflect::PrintMessage(const Message& message, std::ostream& stream, int indent)
{
    // 通过message来获取描述和反射
    auto messageDescriptor = message.GetDescriptor();
    auto reflection = message.GetReflection();

    int fieldCount = messageDescriptor->field_count();
    for (int i = 0; i < fieldCount; ++i) {
        auto fieldDescriptor = messageDescriptor->field(i);

        if (fieldDescriptor->is_repeated()) {
            PrintRepeatedField(reflection, message, fieldDescriptor, stream, indent);
        } else {
            PrintField(reflection, message, fieldDescriptor, stream, indent);
        }
    }
}