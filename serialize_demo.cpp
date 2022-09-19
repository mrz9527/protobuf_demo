// author : zhoukang
// date   : 2022-07-27 14:49:04

#include "fstream"
#include "serialize/serialize.h"
#include "common/ClassOperator.h"

int main()
{
    GOOGLE_PROTOBUF_VERSION;

    atexit([]{
        printf("exit\n");
        google::protobuf::ShutdownProtobufLibrary();
    }); // 程序退出时释放protobuf资源

    const char *filepath = "/home/zhoukang/projects/mygithub/protobuf_demo/build/classInfo.bin";
    printf("班级学生信息管理\n");

    ClassOperator classOperator;

    while (1) {
        if (!Serialize::ParseFromFile(classOperator.GetClassInfo(), filepath)) // 反序列化失败
            return 0;

        int operatorCode;
        printf("查看班级学生信息(1), 添加班级学生信息(2), 退出(其他):");
        scanf("%d", &operatorCode);

        if (operatorCode == 1) { // 查看班级信息
            classOperator.PrintClassInfo(); // 打印
        } else if (operatorCode == 2) {
            classOperator.AddStudent();
            Serialize::SerializeToFile(classOperator.GetClassInfo(), filepath);
        } else
            return 0;
    }

    return 0;
}