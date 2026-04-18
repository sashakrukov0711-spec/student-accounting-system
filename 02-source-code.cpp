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
    
   void addStudent() {
        Student s;
        s.id = nextId++;
        
        cout << "Введите фамилию: ";
        cin >> s.lastName;
        cout << "Введите имя: ";
        cin >> s.firstName;
        cout << "Введите возраст: ";
        cin >> s.age;
        cout << "Введите средний балл: ";
        cin >> s.gpa;
        
        students.push_back(s);
        saveToFile();
        cout << "Студент добавлен! ID: " << s.id << endl;
    }
};
