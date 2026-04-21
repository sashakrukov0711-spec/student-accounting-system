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
    void showAll() {
        if (students.empty()) {
            cout << "Список пуст!" << endl;
            return;
        }
        
        cout << "\n=== СПИСОК СТУДЕНТОВ ===\n";
        for (const auto& s : students) {
            cout << "ID: " << s.id 
                 << " | " << s.lastName << " " << s.firstName
                 << " | Возраст: " << s.age
                 << " | Балл: " << s.gpa << endl;
        }
    }
    void searchByLastName() {
        string searchName;
        cout << "Введите фамилию для поиска: ";
        cin >> searchName;
        
        bool found = false;
        for (const auto& s : students) {
            if (s.lastName == searchName) {
                cout << "Найден: " << s.lastName << " " << s.firstName 
                     << ", возраст: " << s.age << ", балл: " << s.gpa << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "Студент с фамилией " << searchName << " не найден!" << endl;
        }
    }

    void deleteStudent() {
        int id;
        cout << "Введите ID студента для удаления: ";
        cin >> id;
        
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].id == id) {
                students.erase(students.begin() + i);
                saveToFile();
                cout << "Студент удален!" << endl;
                return;
            }
        }
        
        cout << "Студент с ID " << id << " не найден!" << endl;
    }
};
