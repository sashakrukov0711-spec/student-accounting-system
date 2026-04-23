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
private:
    void saveToFile() {
        ofstream file(fileName);
        for (const auto& s : students) {
            file << s.id << "|"
                 << s.lastName << "|"
                 << s.firstName << "|"
                 << s.age << "|"
                 << s.gpa << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(fileName);
        if (!file.is_open()) return;
        
        Student s;
        char delimiter;
        while (file >> s.id >> delimiter && delimiter == '|' &&
               file >> s.lastName >> delimiter && delimiter == '|' &&
               file >> s.firstName >> delimiter && delimiter == '|' &&
               file >> s.age >> delimiter && delimiter == '|' &&
               file >> s.gpa) {
            students.push_back(s);
            if (s.id >= nextId) nextId = s.id + 1;
        }
        file.close();
    }

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
int main() {
    StudentGroup group;
    int choice;
    
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Добавить студента\n";
        cout << "2. Показать всех\n";
        cout << "3. Найти по фамилии\n";
        cout << "4. Удалить студента\n";
        cout << "5. Выход\n";
        cout << "Выберите: ";
        cin >> choice;
        
        switch (choice) {
            case 1: group.addStudent(); break;
            case 2: group.showAll(); break;
            case 3: group.searchByLastName(); break;
            case 4: group.deleteStudent(); break;
            case 5: cout << "Пока!\n"; break;
            default: cout << "Неверный выбор!\n";
        }
    } while (choice != 5);
    
    return 0;
}
