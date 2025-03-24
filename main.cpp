#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Task {
    int serialNo;
    string description;
    bool status;
    int priority;
    string dateAdded;
    string deadline;
    Task* next;

    Task(int sNo, string desc, bool stat, int prio, string dateAdd, string dead) {
        serialNo = sNo;
        description = desc;
        status = stat;
        priority = prio;
        dateAdded = dateAdd;
        deadline = dead;
        next = nullptr;
    }
};

class TaskList {
private:
    Task* head;
    int taskCounter;

public:
    TaskList() {
        head = nullptr;
        taskCounter = 0;
    }

    ~TaskList();
    void createTask(string desc, bool stat, int prio, string dateAdd, string dead);
    void displayTasks();
    void updateTask(int sNo);
    void deleteTask(int sNo);
    void sortByPriority();
    void sortByDeadline();
    void loadTasksFromCSV(string filename);
    void saveTasksToCSV(string filename);
    void renameDataFile(string oldName, string newName);
    bool isDuplicateTask(Task* newTask);
    void handleDuplicate(Task* newTask);
};
void TaskList::createTask(string desc, bool stat, int prio, string dateAdd, string dead) {
    Task* newTask = new Task(++taskCounter, desc, stat, prio, dateAdd, dead);

    if (isDuplicateTask(newTask)) {
        handleDuplicate(newTask);
        delete newTask;
        return;
    }

    if (!head) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    cout << "Task created successfully!\n";
}
void TaskList::displayTasks() {
    if (!head) {
        cout << "Task list is empty.\n";
        return;
    }
    Task* temp = head;
    cout << "Task List:\n";
    while (temp) {
        cout << temp->serialNo << ". " << temp->description
             << " | Status: " << (temp->status ? "Complete" : "Incomplete")
             << " | Priority: " << temp->priority
             << " | Date Added: " << temp->dateAdded
             << " | Deadline: " << temp->deadline << "\n";
        temp = temp->next;
    }
}

void TaskList::updateTask(int sNo) {
    Task* temp = head;
    while (temp) {
        if (temp->serialNo == sNo) {
            cout << "Updating Task " << sNo << "\n";
            cout << "Enter new description: ";
            cin.ignore();
            getline(cin, temp->description);
            cout << "Enter new status (1 for Complete, 0 for Incomplete): ";
            cin >> temp->status;
            cout << "Enter new priority: ";
            cin >> temp->priority;
            cout << "Enter new deadline (DD-MM-YYYY): ";
            cin >> temp->deadline;
            cout << "Task updated successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Task not found.\n";
}
void TaskList::deleteTask(int sNo) {
    Task* temp = head;
    Task* prev = nullptr;

    while (temp) {
        if (temp->serialNo == sNo) {
            if (prev) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp;
            cout << "Task deleted successfully!\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Task not found.\n";
}

bool TaskList::isDuplicateTask(Task* newTask) {
    Task* temp = head;
    while (temp) {
        if (temp->description == newTask->description &&
            temp->status == newTask->status &&
            temp->priority == newTask->priority &&
            temp->dateAdded == newTask->dateAdded &&
            temp->deadline == newTask->deadline) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void TaskList::handleDuplicate(Task* newTask) {
    cout << "Duplicate task found! Do you want to delete it? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        deleteTask(newTask->serialNo);
        cout << "Duplicate task deleted.\n";
    } else {
        cout << "Task retained.\n";
    }
}
void TaskList::sortByPriority() {
    if (!head || !head->next) return;

    Task* sorted = nullptr;
    Task* current = head;

    while (current) {
        Task* next = current->next;
        if (!sorted || sorted->priority > current->priority) {
            current->next = sorted;
            sorted = current;
        } else {
            Task* temp = sorted;
            while (temp->next && temp->next->priority <= current->priority) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

void TaskList::sortByDeadline() {
    if (!head || !head->next) return;

    Task* sorted = nullptr;
    Task* current = head;

    while (current) {
        Task* next = current->next;
        if (!sorted || sorted->deadline > current->deadline) {
            current->next = sorted;
            sorted = current;
        } else {
            Task* temp = sorted;
            while (temp->next && temp->next->deadline <= current->deadline) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}
void TaskList::loadTasksFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File not found or corrupt. Please add tasks manually.\n";
        return;
    }

    string line, desc, dateAdd, dead, statusStr, priorityStr;
    bool stat;
    int prio;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, desc, ',');
        getline(ss, statusStr, ',');
        getline(ss, priorityStr, ',');
        getline(ss, dateAdd, ',');
        getline(ss, dead, ',');

        stat = (statusStr == "1");
        prio = stoi(priorityStr);
        createTask(desc, stat, prio, dateAdd, dead);
    }
    file.close();
}

void TaskList::saveTasksToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not save tasks.\n";
        return;
    }

    Task* temp = head;
    while (temp) {
        file << temp->description << ","
             << temp->status << ","
             << temp->priority << ","
             << temp->dateAdded << ","
             << temp->deadline << "\n";
        temp = temp->next;
    }
    file.close();
    cout << "Tasks saved successfully!\n";
}
void TaskList::renameDataFile(string oldName, string newName) {
    if (rename(oldName.c_str(), newName.c_str()) == 0)
        cout << "File renamed successfully to " << newName << "\n";
    else
        perror("Error renaming file");
}

TaskList::~TaskList() {
    Task* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}
int main() {
    TaskList taskList;

    // Load tasks from CSV file
    string filename = "tasks.csv";
    taskList.loadTasksFromCSV(filename);

    int choice, sNo;
    string desc, dateAdd, dead, newFilename;
    bool stat;
    int prio;

    while (true) {
        cout << "\n========== Task Manager CLI ==========\n";
        cout << "1. Create Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Update Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Sort by Priority\n";
        cout << "6. Sort by Deadline\n";
        cout << "7. Save Tasks to CSV\n";
        cout << "8. Rename CSV File\n";
        cout << "9. Exit\n";
        cout << "======================================\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Enter task status (1 for Complete, 0 for Incomplete): ";
            cin >> stat;
            cout << "Enter task priority: ";
            cin >> prio;
            cout << "Enter date added (DD-MM-YYYY): ";
            cin >> dateAdd;
            cout << "Enter deadline (DD-MM-YYYY): ";
            cin >> dead;
            taskList.createTask(desc, stat, prio, dateAdd, dead);
            break;

        case 2:
            taskList.displayTasks();
            break;

        case 3:
            cout << "Enter task serial number to update: ";
            cin >> sNo;
            taskList.updateTask(sNo);
            break;

        case 4:
            cout << "Enter task serial number to delete: ";
            cin >> sNo;
            taskList.deleteTask(sNo);
            break;

        case 5:
            taskList.sortByPriority();
            cout << "✅ Tasks sorted by priority successfully.\n";
            break;

        case 6:
            taskList.sortByDeadline();
            cout << "✅ Tasks sorted by deadline successfully.\n";
            break;

        case 7:
            taskList.saveTasksToCSV(filename);
            cout << "✅ Tasks saved to '" << filename << "' successfully.\n";
            break;

        case 8:
            cout << "Enter new file name (with .csv extension): ";
            cin >> newFilename;
            taskList.renameDataFile(filename, newFilename);
            filename = newFilename; // Update filename for future operations
            break;

        case 9:
            cout << "Exiting the Task Manager CLI. Goodbye!\n";
            return 0;

        default:
            cout << "❌ Invalid choice! Please choose a valid option.\n";
        }
    }
}
