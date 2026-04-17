#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Student {
    int id;
    string lastName;
    string firstName;
    int age;
    float gpa;
};

class StudentGroup {
private:
    vector<Student> students;
    int nextId = 1;
    string fileName = "students.txt";

public:
    StudentGroup() {
        loadFromFile();
    }
    
    // Функции будут добавлены позже
};
