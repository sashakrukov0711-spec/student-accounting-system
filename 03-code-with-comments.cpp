#include <iostream>   // Для ввода/вывода
#include <string>     // Для работы со строками
#include <vector>     // Для динамического массива
#include <fstream>    // Для работы с файлами

using namespace std;

// Структура "Студент" - хранит данные одного студента
struct Student {
    int id;           // Уникальный номер
    string lastName;  // Фамилия
    string firstName; // Имя
    int age;          // Возраст
    float gpa;        // Средний балл
};

// Класс для управления группой студентов
class StudentGroup {
private:
    vector<Student> students;  // Вектор (динамический массив) студентов
    int nextId = 1;            // Следующий ID для нового студента
    string fileName = "students.txt"; // Имя файла для сохранения

public:
    // Конструктор - загружает данные из файла при запуске
    StudentGroup() {
        loadFromFile();
    }

    // Добавление нового студента
    void addStudent() {
        Student s;
        s.id = nextId++;  // Присваиваем ID и увеличиваем счётчик
        
        cout << "Введите фамилию: ";
        cin >> s.lastName;
        cout << "Введите имя: ";
        cin >> s.firstName;
        cout << "Введите возраст: ";
        cin >> s.age;
        cout << "Введите средний балл: ";
        cin >> s.gpa;
        
        students.push_back(s);  // Добавляем в вектор
        saveToFile();           // Сохраняем в файл
        cout << "Студент добавлен! ID: " << s.id << endl;
    }

    // Показать всех студентов
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

    // Поиск студента по фамилии
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

    // Удаление студента по ID
    void deleteStudent() {
        int id;
        cout << "Введите ID студента для удаления: ";
        cin >> id;
        
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].id == id) {
                students.erase(students.begin() + i);  // Удаляем из вектора
                saveToFile();  // Сохраняем изменения
                cout << "Студент удален!" << endl;
                return;
            }
        }
        cout << "Студент с ID " << id << " не найден!" << endl;
    }

private:
    // Сохранение всех студентов в файл
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

    // Загрузка студентов из файла
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
};

// Главная функция - точка входа в программу
int main() {
    StudentGroup group;  // Создаем объект (автоматически загружаются данные)
    int choice;
    
    do {
        // Вывод меню
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Добавить студента\n";
        cout << "2. Показать всех\n";
        cout << "3. Найти по фамилии\n";
        cout << "4. Удалить студента\n";
        cout << "5. Выход\n";
        cout << "Выберите: ";
        cin >> choice;
        
        // Обработка выбора
        switch (choice) {
            case 1: group.addStudent(); break;
            case 2: group.showAll(); break;
            case 3: group.searchByLastName(); break;
            case 4: group.deleteStudent(); break;
            case 5: cout << "Программа завершена!\n"; break;
            default: cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 5);
    
    return 0;
}
