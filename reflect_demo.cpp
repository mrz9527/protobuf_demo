// author : zhoukang
// date   : 2022-08-04 18:50:54

#include "common/ClassOperator.h"
#include "serialize/serialize.h"
#include "reflect/reflect.h"

int main()
{
    const char* filepath = "/home/zhoukang/projects/mygithub/protobuf_demo/build/classInfo.bin";
    printf("班级学生信息管理\n");

    ClassOperator classOperator;

    if (!Serialize::ParseFromFile(classOperator.GetClassInfo(), filepath)) {
        std::cout << "反序列化失败: " << filepath << std::endl;
        return -1;
    }

    auto classInfo = classOperator.GetClassInfo();
    Reflect::PrintMessage(classInfo, std::cout);

    return 0;

//
//    enum Label {
//        LABEL_OPTIONAL = 1,  // optional
//        LABEL_REQUIRED = 2,  // required
//        LABEL_REPEATED = 3,  // repeated
//
//        MAX_LABEL = 3,  // Constant useful for defining lookup tables
//        // indexed by Label.
//    };
//
//
//    USAGE_CHECK_SINGULAR(HasField);
//
//#define USAGE_CHECK_SINGULAR(HasField)                                      \
//  USAGE_CHECK_NE(LABEL_REPEATED, FieldDescriptor::LABEL_REPEATED, HasField, \
//                 "Field is repeated; the method requires a singular field.")
//
//
//
//#define USAGE_CHECK_NE(LABEL_REPEATED, FieldDescriptor::LABEL_REPEATED, HasField, ERROR_DESCRIPTION) \
//  USAGE_CHECK((LABEL_REPEATED) != (FieldDescriptor::LABEL_REPEATED), HasField, ERROR_DESCRIPTION)
//
//
//#define USAGE_CHECK(CONDITION, METHOD, ERROR_DESCRIPTION) \
//  if (!(CONDITION))                                       \
//  ReportReflectionUsageError(descriptor_, field, #METHOD, ERROR_DESCRIPTION)
}