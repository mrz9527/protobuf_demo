// author : zhoukang
// date   : 2022-08-04 19:02:56

#include "ClassOperator.h"

bool ClassOperator::AddStudent()
{
    tutorial::Student *student = classInfo.add_students();
    int val;
    std::cout << "id:";
    std::cin >> val;
    student->set_id(val);

    std::cout << "name:";
    std::cin >> *student->mutable_name();

    std::cout << "age:";
    std::cin >> val;
    student->set_age(val);

    std::cout << "gender(boy=0,girl=1):";
    std::cin >> val;
    student->set_gender((tutorial::Student_GenderType) val);

    std::cout << "homeAddress:";
    std::cin >> *student->mutable_homeaddress();
    while (1) {
        char major[128]{0};
        std::cout << "major(0表示结束添加):";
        std::cin >> major;
        if (strcmp(major, "0") == 0) {
            break;
        }

        tutorial::Subject *subject = student->add_subjects();
        subject->set_major(major);
        float score;
        std::cout << "score:";
        std::cin >> score;
        subject->set_score(score);
    }
}

bool ClassOperator::AddStudent(int id, const char *name, int age, tutorial::Student_GenderType gender,
                const char *address, const std::vector<std::pair<const char *, float>> &subjects)
{
    tutorial::Student *student = classInfo.add_students();
    student->set_id(id);
    student->set_name(name);
    student->set_age(age);

    student->set_gender(gender);
    student->set_homeaddress(address);

    for (auto elem : subjects) {
        tutorial::Subject *subject = student->add_subjects();
        subject->set_major(elem.first);
        subject->set_score(elem.second);
    }
}

void ClassOperator::PrintClassInfo()
{
    int studentSize = classInfo.students_size();
    for (int i = 0; i < studentSize; ++i) {
        const tutorial::Student student = classInfo.students(i);
        std::cout << "id:" << student.id() << "\tname:" << student.name() << "\tage:" << student.age() << "\tgender:"
                  << student.gender() << "\taddress:" << student.homeaddress() << std::endl;

        std::cout << "subjects:" << std::endl;
        int subjectSize = student.subjects_size();
        for (int j = 0; j < subjectSize; ++j) {
            std::cout << "\tmajor:" << student.subjects(j).major() << "\tscore:" << student.subjects(j).score()
                      << std::endl;
        }
        std::cout << std::endl;
    }
}
