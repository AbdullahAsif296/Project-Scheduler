#include<iostream>
#include"i221527.h"
#include<windows.h>
using namespace std;

void printMenu() {
    cout << "========================================\n";
    cout << "              Project Menu              \n";
    cout << "========================================\n";
    cout << "1. Add Resources\n";
    cout << "2. Add Tasks\n";
    cout << "3. Set Task Duration\n";
    cout << "4. Set Nth Task Duration\n";
    cout << "5. Print Task Dependency List\n";
    cout << "6. Calculate Basic Schedule\n";
    cout << "7. Print Critical Tasks\n";
    cout << "8. Calculate Completion Time With Resources\n";
    cout << "9. Calculate Completion Time With Resource Proficiency\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    ProjectManagement projectManager;
    int c1;

    cout << "========================================\n";
    cout << "         Project Management Menu        \n";
    cout << "========================================\n";
    cout << "1. Use default values.\n";
    cout << "2. Enter your own values.\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
    cin >> c1;

    if (c1 == 1) {
        projectManager.addResource(1, new Skill(0.5));
        projectManager.addResource(1, new Skill(1));
        projectManager.addTask(3, projectManager.findSkillById(1), -1);
        projectManager.addTask(4, projectManager.findSkillById(1), -1);
        projectManager.addTask(1, projectManager.findSkillById(1), -1);
        projectManager.addTask(1, projectManager.findSkillById(2), 1, 2, 3);
        projectManager.addTask(2, projectManager.findSkillById(2), 4);
        projectManager.addTask(5, projectManager.findSkillById(2), 4);
        projectManager.printTaskDependencyList();
        projectManager.calculateBasicSchedule();
        projectManager.printCriticalTasks();
        projectManager.completionTimeWithResources();
        projectManager.completionTimeWithResourceProficiency();
    }
    else if (c1 == 2) {
        int choice;
        do {
            system("CLS");
            printMenu();
            cin >> choice;

            switch (choice) {
            case 1: {
                float skillLevel;
                cout << "Enter resource skill proficiency level: ";
                cin >> skillLevel;
                projectManager.addResource(1, new Skill(skillLevel));
                cout << "Resource added successfully.\n";
                break;
            }
            case 2: {
                int duration, skillId;
                cout << "Enter task duration: ";
                cin >> duration;
                cout << "Enter required skill Id (1-Developing, 2-Testing, ...): ";
                cin >> skillId;
                projectManager.addTask(duration, projectManager.findSkillById(skillId));
                cout << "Task added successfully.\n";
                break;
            }
            case 3: {
                int duration;
                cout << "Enter new duration for all tasks: ";
                cin >> duration;
                projectManager.setTaskDuration(duration);
                cout << "Task duration updated successfully.\n";
                break;
            }
            case 4: {
                int taskId, duration;
                cout << "Enter task ID: ";
                cin >> taskId;
                cout << "Enter new duration: ";
                cin >> duration;
                projectManager.set_nth_TaskDuration(taskId, duration);
                cout << "Nth task duration updated successfully.\n";
                break;
            }
            case 5:
                projectManager.printTaskDependencyList();
                break;
            case 6:
                projectManager.calculateBasicSchedule();
                break;
            case 7:
                projectManager.printCriticalTasks();
                break;
            case 8:
                projectManager.completionTimeWithResources();
                break;
            case 9:
                projectManager.completionTimeWithResourceProficiency();
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
            }

            if (choice != 0) {
                system("PAUSE");
            }

        } while (choice != 0);
    }
    else {
        cout << "Invalid choice\n";
    }

    return 0;
}
