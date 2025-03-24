# 📋 To-Do List CLI Application

A **Command Line Interface (CLI) To-Do List Application** built using **C++** that helps users manage tasks efficiently. The application supports adding, updating, viewing, deleting, and sorting tasks while maintaining persistent storage through a CSV file. Additionally, tasks can be sorted by **priority** or **deadline** for better task management.

---

## 🚀 Features
- ✅ **Add Tasks:** Create tasks with relevant details.
- 📚 **View Tasks:** Display all tasks with task ID, status, priority, and deadlines.
- 📊 **Sort Tasks:** Sort tasks either by:
  - 🔼 **Priority:** Integer-based sorting (`1` → High, `2` → Medium, `3` → Low).
  - ⏰ **Deadline:** Sort tasks based on upcoming deadlines.
- ✏️ **Update Tasks:** Modify task details or change task status.
- ❌ **Delete Tasks:** Remove tasks by ID.
- 📂 **Persistent Storage:** Task data is stored in `tasks.csv` to retain changes after closing the application.
- 🔄 **Rename CSV File:** Rename the data file for better organization.

---

## 🛠️ Tech Stack
- **Language:** C++
- **Storage:** CSV file for data persistence
- **IDE/Editor:** VS Code, Code::Blocks, or any C++ compatible IDE

---

🔥 Usage Guide

1. Add a Task
Enter task details when prompted.
Provide:
Task description
Task status (1 for Complete, 0 for Incomplete)
Task priority (integer value)
Date added in the format DD-MM-YYYY
Deadline in the format DD-MM-YYYY
Task data is stored in tasks.csv.

2. View All Tasks
Displays all tasks with:
Serial Number
Task description
Status (Complete/Incomplete)
Priority (integer)
Date Added
Deadline

3. Sort Tasks
Choose to sort tasks by:
📊 Priority: Sorts tasks based on priority (1 → High, 2 → Medium, 3 → Low).
⏰ Deadline: Sorts tasks based on the earliest deadline.

4. Update a Task
Choose a task by its serial number.
Modify task description, status, priority, or deadline as needed.

5. Delete a Task
Remove tasks using their corresponding serial number.

6. Rename CSV File
Rename tasks.csv to a new filename.
The new filename is used for all subsequent operations.

---

📂 CSV File Format
Task data is stored in tasks.csv in the following format:

TaskDescription,Status,Priority,DateAdded,Deadline
Complete Assignment,1,1,24-03-2025,30-03-2025
Read Research Paper,0,2,25-03-2025,05-04-2025

---

🎯 Future Improvements
🔄 Task Categories: Group tasks into different sections.

📅 Recurring Tasks: Add support for repeating tasks.

🌐 Web-Based Version: Transition to a web interface for better user interaction.

📣 Notification Reminders: Notify users about upcoming deadlines.

