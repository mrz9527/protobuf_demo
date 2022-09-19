#include <iostream>

#include "common/StudentInfo.pb.h"

void ClientSend(size_t studentId);

void ClientRecv(const char *msg, size_t len);

void ServerSend(const char *msg, size_t len);

void ServerRecv(const char *msg, size_t len);

void ClientSend(size_t studentId)
{
    StudentInfo::StudentInfoRequest req;
    req.set_id(studentId); // 学生编号

    // 序列化
    std::string msg;
    req.SerializeToString(&msg);

    // 发给服务器，也就是服务器接收
    ServerRecv(msg.data(), msg.length());
}

void ClientRecv(const char *msg, size_t len)
{
    // 解析响应
    StudentInfo::StudentInfoRespond resp;
    resp.ParseFromArray(msg, len);

    // 打印信息
    std::cout << "name:" << resp.name() << std::endl;
    std::cout << "age:" << resp.age() << std::endl;
    std::cout << "gender:" << resp.gender() << std::endl;
    std::cout << "homeAdress:" << resp.homeaddress() << std::endl;
    std::cout << "成绩:" << std::endl;
    for (int i = 0; i < resp.scores_size(); ++i) {
        std::cout << "\t" << resp.scores(i).score() << "\t" << resp.scores(i).major() << std::endl;
    }

}

void ServerSend(const char *msg, size_t len)
{
    ClientRecv(msg, len);
}

void AddScore(StudentInfo::StudentScore *studentScore, const char *major, float score)
{
    studentScore->set_major(major);
    studentScore->set_score(score);
}

void ServerRecv(const char *msg, size_t len)
{
    // 解析请求
    StudentInfo::StudentInfoRequest req;

    // 反序列化
    req.ParseFromArray(msg, len);

    if (req.id() != 10001) {
        printf("身份验证失败\n");
        return;
    }
    printf("身份验证通过\n");

    // 填充响应信息
    StudentInfo::StudentInfoRespond resp;
    resp.set_name("张三");
    resp.set_age(18);
    resp.set_gender(StudentInfo::StudentInfoRespond_GenderType::StudentInfoRespond_GenderType_GT_BOY);
    resp.set_homeaddress("北京市朝阳区xxxx街道yyy小区z号楼");

    AddScore(resp.add_scores(), "语文", 121.0);
    AddScore(resp.add_scores(), "数学", 129.0);
    AddScore(resp.add_scores(), "英语", 76.0);
    AddScore(resp.add_scores(), "理综", 242.0);

    // 序列化
    std::string strResp;
    resp.SerializeToString(&strResp);

    // 服务端发送数据
    ServerSend(strResp.data(), strResp.length());

    //
}

int main()
{
    GOOGLE_PROTOBUF_VERSION;
    std::cout << "this is test for protobuf..." << std::endl;

    ClientSend(10001);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
