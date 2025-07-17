#include <bits/stdc++.h>
using namespace std;

class Task
{
private:
    string title, deadline;
    int priority;
    bool completed;
    

public:
    Task(string t, string d, int p)
        : title(t), deadline(d), priority(p), completed(false) {}

    void markCompleted()
    {
        completed = true;
    }

    void display() const
    {
        cout << (completed ? "[Done] " : "[Pending] ")
             << "Task: " << title
             << " | Deadline: " << deadline
             << " | Priority: " << priority << "\n";
    }

    string getDeadline() const { return deadline; }

    int getPriority() const {
    return priority;
}

    bool operator<(const Task &other) const 
    {
        return deadline < other.deadline;
    }
    //Without this overload, the compiler wouldn’t know how to compare two Task objects.
    //this uses lexicographical comparison based on the deadline.4

    string getTitle() const {
    return title;
}
};

class Exam {
private:
    string title, date, course;

public:
    Exam(string t, string d, string c)
        : title(t), date(d), course(c) {}

    void display() const {
        cout << "Exam: " << title
                  << " | Date: " << date
                  << " | Course: " << course << "\n";
    }

    string getDate() const { return date; }

    bool operator<(const Exam &other) const {
        return date < other.date;
    }
};

class AttendanceRecord {
private:
    string date;
    bool present;

public:
    AttendanceRecord(std::string d, bool p)
        : date(d), present(p) {}

    void display() const {
        std::cout << date << " : " << (present ? "Present" : "Absent") << "\n";
    }

    string getDate() const { return date; }
    bool isPresent() const { return present; }

    bool operator<(const AttendanceRecord &other) const {
        return date < other.date;
    }
};



class Student  {
private:
   int id;
   string name;
   vector<Task> tasks;
   vector<Exam> exams;
   vector<AttendanceRecord> attendance;

   public:
     Student() : id(0), name("Unknown") {} // ✅ default constructor
   Student(int id, string name) : id(id), name(name) {}

     // Add a task (Binary Search insertion)
    void addTask(const Task &t) {
        auto pos = std::lower_bound(tasks.begin(), tasks.end(), t);
        tasks.insert(pos, t);
        cout << "Task added successfully for " << name << "!\n";
    }
    
      // Add an exam (Binary Search insertion)
    void addExam(const Exam &e) {
        auto pos = std::lower_bound(exams.begin(), exams.end(), e);
        exams.insert(pos, e);
        cout << "Exam added successfully for " << name << "!\n";
    }


      void markAttendance(const AttendanceRecord &a) {
        auto pos = std::lower_bound(attendance.begin(), attendance.end(), a);
        if (pos != attendance.end() && pos->getDate() == a.getDate()) {
            cout << "Attendance already marked for " << a.getDate() << "\n";
            return;
        }
        attendance.insert(pos, a);
        cout << "Attendance marked for " << a.getDate() << "\n";
    }

      void displayTasks() const {
        cout << "\nTasks for " << name << ":\n";
        for (const auto &t : tasks)
            t.display();
    }

    void displayExams() const {
        cout << "\nExams for " << name << ":\n";
        for (const auto &e : exams)
            e.display();
    }

     void displayAttendance() const {
        cout << "\nAttendance for " << name << ":\n";
        for (const auto &a : attendance)
            a.display();
    }

    void findTaskByTitle(const string &searchTitle) const {
    vector<Task> titleSortedTasks = tasks;

    // Sort by title for binary search
   sort(titleSortedTasks.begin(), titleSortedTasks.end(),
              [](const Task &a, const Task &b) {
                  return a.getTitle() < b.getTitle();
              });

    auto it = lower_bound(titleSortedTasks.begin(), titleSortedTasks.end(), searchTitle,
                               [](const Task &t, const string &title) {
                                   return t.getTitle() < title;
                               });

    if (it != titleSortedTasks.end() && it->getTitle() == searchTitle) {
        cout << "Task Found:\n";
        it->display();
    } else {
        cout << "Task \"" << searchTitle << "\" not found.\n";
    }
    }

   
    struct Comparator {
        bool operator()(const Task &a, const Task &b) const {
            return a.getPriority() > b.getPriority(); // Lower priority value means higher priority
        }
    };

    void showTopKTasks(int k) const {
        priority_queue<Task, vector<Task>, Comparator> pq;

        for (const auto &t : tasks)
            pq.push(t);

        cout << "\nTop " << k << " High Priority Tasks:\n";
        for (int i = 0; i < k && !pq.empty(); ++i) {
            pq.top().display();
            pq.pop();
        }
    }

    void showAttendanceStats() const {
    if (attendance.empty()) {
        std::cout << "No attendance records.\n";
        return;
    }

    int total = attendance.size();
    int presentCount = 0;
    for (const auto &a : attendance)
        if (a.isPresent()) presentCount++;

    double percentage = (presentCount * 100.0) / total;
    std::cout << "\nAttendance: " << presentCount << "/" << total
              << " (" << percentage << "%)\n";
}

    string getName() const { return name; }
    int getId() const { return id; }


};

class ProductivitySuite {
private:
    unordered_map<int, Student> students;

public:
    void addStudent(int id, const string &name) {
        if (students.find(id) != students.end()) {
            std::cout << "Student with ID " << id << " already exists!\n";
            return;
        }
        students[id] = Student(id, name);
        cout << "Student " << name << " added successfully!\n";
    }

    Student* getStudent(int id) {
        auto it = students.find(id);
        if (it != students.end()) {
            return &(it->second);
        } else {
            cout << "Student with ID " << id << " not found!\n";
            return nullptr;
        }
    }

    void listAllStudents() const {
        cout << "\n--- All Students ---\n";
        for (const auto &pair : students) {
            std::cout << "ID: " << pair.first << ", Name: " << pair.second.getName() << "\n";
        }
    }
};


int main() {
    ProductivitySuite suite;
    int choice;

    while (true) {
        cout << "\n===== Student Productivity Suite =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Task to Student\n";
        cout << "3. Add Exam to Student\n";
        cout << "4. Mark Attendance for Student\n";
        cout << "5. View Student Details\n";
        cout << "6. List All Students\n";
        cout << "7. Exit\n";
        cout << "8. Find Task by Title\n";
        cout << "9. Show Top K Tasks\n";
        cout << "10. Show Attendance Stats\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Student Name: ";
            getline(cin, name);
            suite.addStudent(id, name);
        }
        else if (choice >= 2 && choice <= 5) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            Student *student = suite.getStudent(id);
            if (student == nullptr) continue;

            if (choice == 2) {
                string title, deadline;
                int priority;
                cin.ignore();
                cout << "Enter Task Title: ";
                getline(cin, title);
                cout << "Enter Deadline (YYYY-MM-DD): ";
                cin >> deadline;
                cout << "Enter Priority (1=High, 2=Medium, 3=Low): ";
                cin >> priority;
                student->addTask(Task(title, deadline, priority));
            }
            else if (choice == 3) {
                string title, date, course;
                cin.ignore();
                cout << "Enter Exam Title: ";
                getline(cin, title);
                cout << "Enter Exam Date (YYYY-MM-DD): ";
                cin >> date;
                cin.ignore();
                cout << "Enter Course: ";
                getline(cin, course);
                student->addExam(Exam(title, date, course));
            }
            else if (choice == 4) {
                string date;
                bool present;
                cin.ignore();
                cout << "Enter Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Present? (1=Yes, 0=No): ";
                cin >> present;
                student->markAttendance(AttendanceRecord(date, present));
            }
            else if (choice == 5) {
                student->displayTasks();
                student->displayExams();
                student->displayAttendance();
            }
        }
        else if (choice == 6) {
            suite.listAllStudents();
        }
        else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
        else if (choice == 8) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            Student *student = suite.getStudent(id);
            if (!student) continue;

            cin.ignore();
            string title;
            cout << "Enter Task Title to Search: ";
            getline(cin, title);
            student->findTaskByTitle(title);
        }
        else if (choice == 9) {
            int id, k;
            cout << "Enter Student ID: ";
            cin >> id;
            Student *student = suite.getStudent(id);
            if (!student) continue;

            cout << "Enter value of K: ";
            cin >> k;
            student->showTopKTasks(k);
        }
        else if (choice == 10) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            Student *student = suite.getStudent(id);
            if (!student) continue;

            student->showAttendanceStats();
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}