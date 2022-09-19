// author : zhoukang
// date   : 2022-08-04 19:02:56

#ifndef PROTOBUF_DEMO_CLASSOPERATOR_H
#define PROTOBUF_DEMO_CLASSOPERATOR_H

#include "../common/ClassInfo.pb.h"

class ClassOperator {
public:
    bool AddStudent();

    bool AddStudent(int id, const char *name, int age, tutorial::Student_GenderType gender,
                    const char *address, const std::vector<std::pair<const char *, float>> &subjects);

    tutorial::ClassInfo& GetClassInfo() {
        return classInfo;
    }

    // 打印方式不够通用，通用打印方式，通过反射实现
    void PrintClassInfo();

private:
    tutorial::ClassInfo classInfo;
};


#endif //PROTOBUF_DEMO_CLASSOPERATOR_H
