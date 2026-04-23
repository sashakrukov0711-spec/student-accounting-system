// Массив для хранения студентов
let students = [];

// Загрузка данных при запуске
function loadData() {
    const saved = localStorage.getItem('students');
    if (saved) {
        students = JSON.parse(saved);
    } else {
        // Тестовые студенты для примера
        students = [
            { id: 1, lastName: 'Иванов', firstName: 'Иван', age: 20, gpa: 4.5 },
            { id: 2, lastName: 'Петрова', firstName: 'Анна', age: 19, gpa: 4.8 },
            { id: 3, lastName: 'Сидоров', firstName: 'Петр', age: 21, gpa: 4.2 }
        ];
        saveData();
    }
    displayStudents();
    updateStats();
}

// Сохранение данных
function saveData() {
    localStorage.setItem('students', JSON.stringify(students));
}

// Отображение студентов
function displayStudents(filteredStudents = null) {
    const studentList = document.getElementById('studentList');
    const studentsToShow = filteredStudents || students;
    
    if (studentsToShow.length === 0) {
        studentList.innerHTML = '<div style="padding:20px;text-align:center;">Студентов не найдено</div>';
        return;
    }
    
    let html = '';
    for (let student of studentsToShow) {
        html += `
            <div class="student-item">
                <div class="student-info">
                    <div class="student-name">${student.lastName} ${student.firstName}</div>
                    <div class="student-details">
                        ID: ${student.id} | Возраст: ${student.age} | Средний балл: ${student.gpa}
                    </div>
                </div>
                <button class="delete-btn" onclick="deleteStudent(${student.id})">Удалить</button>
            </div>
        `;
    }
    studentList.innerHTML = html;
}

// Обновление статистики
function updateStats() {
    const stats = document.getElementById('stats');
    const total = students.length;
    let avgGpa = 0;
    
    if (total > 0) {
        const sum = students.reduce((acc, s) => acc + s.gpa, 0);
        avgGpa = (sum / total).toFixed(2);
    }
    
    stats.innerHTML = `
        📊 Всего студентов: ${total} | 
        📈 Средний балл: ${avgGpa} | 
        👥 Группа: ИКБО-01-24
    `;
}

// Добавление студента
function addStudent(event) {
    event.preventDefault();
    
    const lastName = document.getElementById('lastName').value;
    const firstName = document.getElementById('firstName').value;
    const age = parseInt(document.getElementById('age').value);
    const gpa = parseFloat(document.getElementById('gpa').value);
    
    if (!lastName || !firstName || !age || !gpa) {
        alert('Заполните все поля!');
        return;
    }
    
    const newId = students.length > 0 ? Math.max(...students.map(s => s.id)) + 1 : 1;
    const newStudent = {
        id: newId,
        lastName: lastName,
        firstName: firstName,
        age: age,
        gpa: gpa
    };
    
    students.push(newStudent);
    saveData();
    displayStudents();
    updateStats();
    
    document.getElementById('studentForm').reset();
    alert(`Студент ${lastName} ${firstName} успешно добавлен!`);
}

// Удаление студента
function deleteStudent(id) {
    if (confirm('Вы уверены, что хотите удалить этого студента?')) {
        students = students.filter(s => s.id !== id);
        saveData();
        displayStudents();
        updateStats();
        document.getElementById('searchInput').value = '';
    }
}

// Поиск студента
function searchStudent() {
    const searchTerm = document.getElementById('searchInput').value.toLowerCase();
    
    if (!searchTerm) {
        displayStudents();
        return;
    }
    
    const filtered = students.filter(s => 
        s.lastName.toLowerCase().includes(searchTerm) ||
        s.firstName.toLowerCase().includes(searchTerm)
    );
    
    displayStudents(filtered);
    
    const resultDiv = document.getElementById('searchResult');
    if (filtered.length === 0) {
        resultDiv.innerHTML = '<div style="margin-top:10px;padding:10px;background:#fff3cd;border-radius:8px;">❌ Студенты не найдены</div>';
    } else {
        resultDiv.innerHTML = `<div style="margin-top:10px;padding:10px;background:#d4edda;border-radius:8px;">✅ Найдено студентов: ${filtered.length}</div>`;
    }
    
    setTimeout(() => {
        resultDiv.innerHTML = '';
    }, 3000);
}

// Очистка поиска
function clearSearch() {
    document.getElementById('searchInput').value = '';
    displayStudents();
    document.getElementById('searchResult').innerHTML = '';
}

// Экспорт данных
function exportData() {
    const dataStr = JSON.stringify(students, null, 2);
    const blob = new Blob([dataStr], {type: 'application/json'});
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'students_export.json';
    a.click();
    URL.revokeObjectURL(url);
}

// Запуск при загрузке страницы
document.addEventListener('DOMContentLoaded', () => {
    loadData();
    document.getElementById('studentForm').addEventListener('submit', addStudent);
    document.getElementById('searchBtn').addEventListener('click', searchStudent);
    document.getElementById('clearSearchBtn').addEventListener('click', clearSearch);
    
    const statsDiv = document.getElementById('stats');
    const exportBtn = document.createElement('button');
    exportBtn.textContent = '📥 Экспорт в JSON';
    exportBtn.className = 'btn btn-secondary';
    exportBtn.style.marginLeft = '10px';
    exportBtn.onclick = exportData;
    statsDiv.appendChild(exportBtn);
});
