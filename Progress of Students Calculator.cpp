// Progress of Students Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
class User
{
    static int currentID;
    int m_ID;
    std::string m_Name;
public:
    User(std::string name) : m_Name{ name }, m_ID{ currentID++ }{
    }
    int ID() const { return m_ID; }
    std::string name() const { return m_Name; }
};
int User::currentID = 1;
class Subject {
    static int currentID;
    int m_ID;
    std::string m_Name;
public:
    Subject(std::string name) :m_ID{ currentID++ }, m_Name{ name }{}
    int ID()const { return m_ID; }
    std::string name()const { return m_Name; }
};
int Subject::currentID = 1;
class Department {
    static int currentID;
    int m_ID;
    std::string m_Name;
public:
    Department(std::string name) :m_ID{ currentID++ }, m_Name{ name }{}
    int ID()const { return m_ID; }
    std::string name()const { return m_Name; }
};
int Department::currentID = 1;

class Lecturer : public User {
    int m_SubjectID;
    int m_DepartmentID;
public:
    Lecturer(std::string name, int subjectID, int departmentID)
        :User(name), m_SubjectID(subjectID), m_DepartmentID(departmentID) {}
    int subjectID()const { return m_SubjectID; }
    int departmentID()const { return m_DepartmentID; }
};

class Student : public User {

    int m_Result;
public:
    Student(std::string name, int result)
        :User(name), m_Result(result) {}
    int result() const { return m_Result; }

};

class Class
{
    static int currentID;
    int m_ID;
    int m_LecturerID;
    int m_Size;
    int m_TotalScore;
    std::vector<int>studentIDs;
    bool find_studentID(int ID) {
        for (auto& studentID : studentIDs) {
            if (studentID == ID) {
                return true;
            }
        }
        return false;
    }
public:
    Class(int lecturerID)
        :m_ID{ currentID++ }, m_LecturerID{ lecturerID }, m_Size{ 0 }, m_TotalScore{ 0 }
    {
    }
    int ID()const { return m_ID; }
    int lecturer_ID() const { return m_LecturerID; }
    int size() const { return m_Size; }
    void increment_size() { m_Size++; }
    int total_score() const { return m_TotalScore; }
    void total_score(int result) { m_TotalScore += result; }
    void add_studentID_to_class(int studentID) {
        studentIDs.push_back(studentID);
    }
    
    
    auto get_students(const std::vector<Student>&allStudents) {
        std::vector<Student>students;
        for (const Student& student : allStudents) {
            if (find_studentID(student.ID())) {
                students.push_back(student);
            }
        }
        return students;
    }
};
int Class::currentID = 1;

class University {
private:
    std::vector<Department>objDepartments;
    std::vector<Subject>objSubjects;
    std::vector<Lecturer>objLecturers;
    std::vector<Student>objStudents;
    std::vector<Class>objClasses;

    auto find_lecturer_by_id(int ID) const {

        return std::find_if(objLecturers.begin(), objLecturers.end(), [&](const Lecturer &lecturer) {return lecturer.ID() == ID; });
    }
    auto find_subject_by_id(int ID) const {

        return std::find_if(objSubjects.begin(), objSubjects.end(), [&](const Subject &subject) {return subject.ID() == ID; });
    }
    auto find_department_by_id(int ID) const {
        return std::find_if(objDepartments.begin(), objDepartments.end(), [&](const Department department) {return department.ID() == ID; });
    }
    auto find_class_by_id(int ID) {
        return std::find_if(objClasses.begin(), objClasses.end(), [&](Class objClass) {return objClass.ID() == ID; });
    }
    auto find_student_by_id(int ID) {
        return std::find_if(objStudents.begin(), objStudents.end(), [&](Student objStudent) {return objStudent.ID() == ID; });

    }
public:
    University() {
        objSubjects.emplace_back(Subject{ "Programming" });
        objSubjects.emplace_back(Subject{ "Web App Development" });
        objSubjects.emplace_back(Subject{ "Networking" });
        objDepartments.emplace_back(Department{ "Winter Gardens" });
        objDepartments.emplace_back(Department{ "South West Skills Campus" });
        objLecturers.emplace_back(Lecturer{ "Sean Shearing", 1, 1 });
        objClasses.emplace_back(Class{ 1 });
        objClasses.emplace_back(Class{ 1 });

        //Test data
        add_new_student("Jack Cole", 1, 56);
        add_new_student("Sam Cole", 1, 78);
        add_new_student("Devon Phillips", 1, 91);
        add_new_student("Thomas Saunders", 1, 54);
        add_new_student("Jack Kimmins", 2, 58);
        add_new_student("Oli Stahmer", 2, 91);
        add_new_student("George Bradley", 2, 78);
        add_new_student("Joshua Price", 2, 54);
    }

    auto best_performing_class() {
        return std::max_element(objClasses.begin(), objClasses.end(), [&](const Class& lhs, const Class& rhs)
            {
                return lhs.total_score() < rhs.total_score();
            });
    }
    auto worst_performing_class() {
        return std::min_element(objClasses.begin(), objClasses.end(), [&](const Class& lhs, const Class& rhs)
            {
                return lhs.total_score() < rhs.total_score();
            });
    }
    
    double average(std::vector<Student>& students) {

        auto sum = std::transform_reduce(students.begin(), students.end(), 0.0, std::plus<>(),
            [](auto& student) { return student.result(); });
        return (double)sum / (double)students.size();
    }
    
    auto find_class_students(int classID) { 
        auto objClass = find_class_by_id(classID);
        auto students = objClass->get_students(objStudents);
        return students;
    }

    int class_median_score(int class_id) {
        std::vector<int>scores;
        auto students = find_class_students(class_id);
        for (Student& student : students) {
            scores.push_back(student.result());
        }
        std::sort(scores.begin(), scores.end());
        if (scores.size() % 2 == 0)
        {
            return (scores.at(scores.size() / 2 - 1) + scores.at(scores.size() / 2)) / 2;
        }
        return scores.at(scores.size() / 2);
    }
    void view_class_students(int classID) {
        auto students = find_class_students(classID);
        display_students(students);

    }
    void display_students(std::vector<Student>& objStudents) {
        for (const Student& objStudent : objStudents) {
            std::cout << "ID: " << objStudent.ID() << " | ";
            std::cout << "Name: " << objStudent.name() << " | ";
            std::cout << "Score: " << objStudent.result() << "\n";
        }
    }
    auto highest_mark_by_student(std::vector<Student>& objStudents) {
        return std::max_element(objStudents.begin(), objStudents.end(), [&](const Student& lhs, const Student& rhs)
            {
                return lhs.result() < rhs.result();
            });
    }
    auto lowest_mark_by_student(std::vector<Student>& objStudents) {
        return std::min_element(objStudents.begin(), objStudents.end(), [&](const Student& lhs, const Student& rhs)
            {
                return lhs.result() < rhs.result();
            });
    }

    void class_report(int class_id)
    {
        auto students = find_class_students(class_id);
        auto highestScorer = highest_mark_by_student(students);
        auto lowestScorer = lowest_mark_by_student(students);
        std::cout << "Highest scorer: Student ID: " << highestScorer->ID() << " | Name: " << highestScorer->name() << " | score: " << highestScorer->result() << "\n";
        std::cout << "Lowest scorer: Student ID: " << lowestScorer->ID() << " | Name: " << lowestScorer->name() << " | score: " << lowestScorer->result() << "\n";
        std::cout << "Median score: " << class_median_score(class_id) << "\n";
        std::cout << "Average score: " << average(students) << "\n";
    }

    void overall_classes_report() {
        auto bestClass = best_performing_class();
        auto worstClass = worst_performing_class();
        std::cout << "\nBest Performing Class(s)...\n";
        std::cout << "ID: " << bestClass->ID() << " | Lecturer: " << find_lecturer_by_id(bestClass->lecturer_ID())->name() << " | score: " << bestClass->total_score() << "\n";
        std::cout << "\n";
        std::cout << "\nWorst Performing Class(s)...\n";
        std::cout << "ID: " << worstClass->ID() << " | Lecturer: " << find_lecturer_by_id(worstClass->lecturer_ID())->name() << " | score: " << worstClass->total_score() << "\n";
        std::cout << "\n";
    }

    void display_classes() {
        for (const Class& objClass : objClasses)
        {
            auto lecturer = find_lecturer_by_id(objClass.lecturer_ID());
            auto subject = find_subject_by_id(objClass.lecturer_ID());
            auto department = find_department_by_id(lecturer->departmentID());
            auto students = find_class_students(objClass.ID());

            std::cout << "Class ID: " << objClass.ID() << "\n";
            std::cout << "Class Size: " << objClass.size() << "\n";
            std::cout << "Lecturer: " << lecturer->name() << "\n";
            std::cout << "Subject: " << subject->name() << "\n";
            std::cout << "Department: " << department->name() << "\n\n";
        }
    }

    bool is_class_id_valid(int class_id) {
        if (auto it = std::find_if(objClasses.begin(), objClasses.end(), [&](auto& objClass) {
            return class_id == objClass.ID();
            }) == objClasses.end()) {
            return false;
        }
        return true;
    }


    bool add_new_student(std::string name, int classID, int result) {
        if (is_class_id_valid(classID)) {         
            objStudents.emplace_back(Student{ name, result });
            find_class_by_id(classID)->add_studentID_to_class(objStudents.back().ID());
            find_class_by_id(classID)->total_score(result);
            find_class_by_id(classID)->increment_size();
            return true;
        }
        return false;
    }
};

int main()
{
    University objUniversity;

    //viewing class 1
    std::cout << "View class students...\n";
    objUniversity.view_class_students(1);

    std::cout << "Class report...\n";
    objUniversity.class_report(1);

    //viewing class 2
    std::cout << "View class students...\n";
    objUniversity.view_class_students(2);

    std::cout << "Class report...\n";
    objUniversity.class_report(2);

    std::cout << "Overall classes report...\n";
    objUniversity.overall_classes_report();

    //Run via menu system
    //menu_options(objUniversity);
}