// M.ABDULLAH ASIF        22i-1527        Assignment # 2      SE-D
#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
// Static ID counters
static int skillIdCounter = 1;
static int taskIdCounter = 1;
static int resourceIdCounter = 1;
static bool flag = false;
class Skill;
class TaskDependency;
class Task;
class Resources;
// Skill class
class Skill {
public:
    int id;
    float proficiencyLevel;

    Skill(float proficiencyLevel)
        : id(skillIdCounter++), proficiencyLevel(proficiencyLevel) {}
};
// TaskDependency class
class TaskDependency {
public:
    Task* task;
    TaskDependency* next;

    TaskDependency(Task* task)
        : task(task), next(NULL) {}
};
// Task class 
class Task {
public:
    int id;
    int duration;
    int EarlyStartTime;
    int EarlyFinishTime;
    int ResourceEarlyStartTime;
    int ResourceEarlyFinishTime;
    int ResourceProfEarlyStartTime;
    int ResourceProfEarlyFinishTime;
    int ResourceProfduration;
    int LateStartTime;
    int LateFinishTime;
    int Slack;
    Task* prev;
    Task* next;
    Skill* requiredSkill;
    TaskDependency* Dependency;

    Task(int duration, Skill* requiredSkill)
        : id(taskIdCounter++), duration(duration), EarlyStartTime(0), EarlyFinishTime(0),
        LateStartTime(0), LateFinishTime(0), ResourceEarlyStartTime(0), ResourceEarlyFinishTime(0), ResourceProfEarlyFinishTime(0), ResourceProfEarlyStartTime(0), ResourceProfduration(duration), Slack(0), requiredSkill(requiredSkill),
        prev(NULL), next(NULL), Dependency(NULL) {
    }
    // Function to add a dependency to the linked list
    void addDependency(Task* dependencyTask) {
        TaskDependency* newDependency = new TaskDependency(dependencyTask);
        newDependency->next = Dependency;
        Dependency = newDependency;
    }
    ~Task()
    {
        taskIdCounter--;
    }
};
// Resource class
class Resource {
public:
    int id;
    int availability;
    Skill* skill;
    Resource* next;

    Resource(int availability, Skill* skill)
        : id(resourceIdCounter++), availability(availability), skill(skill), next(NULL) {}
};

// Project class with a doubly linked list of tasks
class Project {
public:
    int id;
    int duration;
    Task* head;
    Task* tail;
    Resource* resources;

    Project(int id = 1)
        : id(id), duration(0), head(NULL), tail(NULL), resources(NULL) {}

    void addTask(Task* task) {
        if (!head) {
            head = task;
            tail = task;
        }
        else {
            tail->next = task;
            task->prev = tail;
            tail = task;
        }
    }

    void addResource(Resource* resource) {
        resource->next = resources;
        resources = resource;
    }

    void setTaskDuration(int duration) {
        Task* current = head;
        while (current) {
            current->duration = duration;
            current = current->next;
        }
    }

    void set_nth_TaskDuration(int taskId, int duration) {
        Task* current = head;
        while (current) {
            if (current->id == taskId) {
                current->duration = duration;
                break;
            }
            current = current->next;
        }
    }
};
// ProjectManagement class
class ProjectManagement {
public:
    Project project;

    ProjectManagement() {}

    void addResource(int availability, Skill* skill) {
        Resource* resource = new Resource(availability, skill);
        project.addResource(resource);
    }

    void addTask(int duration, Skill* requiredSkill, int dId1 = 0, int dId2 = 0, int dId3 = 0) {
        Task* task = new Task(duration, requiredSkill);
        project.addTask(task);
        if (dId1 == 0)
        {
            int num;
            cout << "How many dependencies you want to add for this task (0 for no dependency): ";
            cin >> num;

            if (num > 0) {
                for (int i = 0; i < num; i++) {
                    int depId;
                    cout << "Enter dependency task ID: ";
                    cin >> depId;

                    Task* dependencyTask = findTaskById(depId);
                    if (dependencyTask) {
                        task->addDependency(dependencyTask);
                    }
                }
            }
        }
        else
        {
            if (dId1 > 0)
            {
                Task* dependencyTask = findTaskById(dId1);
                if (dependencyTask) {
                    task->addDependency(dependencyTask);
                }
            }
            if (dId2 > 0)
            {
                Task* dependencyTask = findTaskById(dId2);
                if (dependencyTask) {
                    task->addDependency(dependencyTask);
                }
            }
            if (dId3 > 0)
            {
                Task* dependencyTask = findTaskById(dId3);
                if (dependencyTask) {
                    task->addDependency(dependencyTask);
                }
            }
        }
    }

    Task* findTaskById(int taskId) {
        Task* current = project.head;
        while (current) {
            if (current->id == taskId) {
                return current;
            }
            current = current->next;
        }

        // If the loop finishes without finding the task, print a debug message
        cout << "Task with ID " << taskId << " not found." << endl;
        return NULL;
    }
    void setTaskDuration(int duration)
    {
        project.setTaskDuration(duration);
    }
    void set_nth_TaskDuration(int taskId, int duration) {
        project.set_nth_TaskDuration(taskId, duration);
    }
    void printTaskDependencyList() {
        Task* current = project.head;
        while (current) {
            cout << "Dependencies for Task " << current->id << ": ";
            TaskDependency* dependency = current->Dependency; // Start from the head of the linked list
            if (!dependency)
            {
                cout << "None";
            }
            while (dependency) {
                cout << dependency->task->id << "  ";
                dependency = dependency->next;
            }
            cout << endl;
            current = current->next;
        }
    }
    Skill* findSkillById(int skillId) {
        // Iterate through the resources and their associated skills
        Resource* currentResource = project.resources;
        while (currentResource) {
            if (currentResource->skill->id == skillId) {
                return currentResource->skill;
            }
            currentResource = currentResource->next;
        }
        // If the skill is not found, print a debug message
        cout << "Skill with ID " << skillId << " not found." << endl;
        return NULL;
    }

    void calculateBasicSchedule() {
        // Implement the Critical Path Method (CPM) algorithm here
        // Update the EarlyStart, EarlyFinish, LateStart, LateFinish, and Slack values for tasks
        // Print the project's schedule and completion time
        if (!flag)
        {
            Task* current = project.head;

            // Step 1: Calculate Early Start (ES) and Early Finish (EF) for each task
            for (; current != NULL; current = current->next) {
                if (!current->Dependency) {
                    current->EarlyStartTime = 0;
                    current->EarlyFinishTime = current->duration;
                }
                else {
                    TaskDependency* temp = current->Dependency;
                    int maxDur = 0;
                    while (temp) {
                        if (temp->task->EarlyFinishTime > maxDur)
                            maxDur = temp->task->EarlyFinishTime;
                        temp = temp->next;
                    }
                    current->EarlyStartTime = maxDur;
                    current->EarlyFinishTime = maxDur + current->duration;
                }
                // cout << "Task " << current->id << ": Early Start = " << current->EarlyStartTime << ", Early Finish = " << current->EarlyFinishTime << endl;
            }

            // Step 2: Initialize Late Finish (LF) for the last task to its Early Finish (EF)
            Task* lastTask = project.tail;

            lastTask->LateFinishTime = lastTask->EarlyFinishTime;
            lastTask->LateStartTime = lastTask->EarlyFinishTime - lastTask->duration;
            int ProjectDuration = lastTask->LateFinishTime;
            //cout << "Task " << lastTask->id << ": Late Start = " << lastTask->LateStartTime << ", Late Finish = " << lastTask->LateFinishTime << endl;
            if (lastTask->Dependency) {
                for (lastTask->Dependency; lastTask->Dependency != NULL; lastTask->Dependency = lastTask->Dependency->next) {
                    lastTask->Dependency->task->LateFinishTime = lastTask->LateStartTime;
                    lastTask->Dependency->task->LateStartTime = lastTask->Dependency->task->LateFinishTime - lastTask->Dependency->task->duration;
                }
            }

            // Step 3: Calculate Late Start (LS) and Late Finish (LF) for each task in reverse order
            for (lastTask = lastTask->prev; lastTask != NULL; lastTask = lastTask->prev) {
                TaskDependency* temp = lastTask->Dependency;
                if (!temp && lastTask->LateFinishTime == 0) {
                    lastTask->LateFinishTime = lastTask->next->LateFinishTime;
                    lastTask->LateStartTime = lastTask->LateFinishTime - lastTask->duration;
                }
                else {
                    if (lastTask->LateFinishTime == 0) {
                        lastTask->LateFinishTime = ProjectDuration;
                        lastTask->LateStartTime = lastTask->LateFinishTime - lastTask->duration;
                    }
                    for (lastTask->Dependency; lastTask->Dependency != NULL; lastTask->Dependency = lastTask->Dependency->next) {
                        if (lastTask->LateStartTime < lastTask->Dependency->task->LateFinishTime || lastTask->Dependency->task->LateFinishTime == 0) {
                            lastTask->Dependency->task->LateFinishTime = lastTask->LateStartTime;
                            lastTask->Dependency->task->LateStartTime = lastTask->Dependency->task->LateFinishTime - lastTask->Dependency->task->duration;
                        }
                    }
                }
            }

            // Step 4: Calculate the Slack for each task
            for (current = project.head; current != NULL; current = current->next) {
                current->Slack = current->LateStartTime - current->EarlyStartTime;
            }
            flag = true;
        }
        int dur = 0;
        cout << "Basic schedule:\n";
        cout << " " << setw(4) << "ID" << setw(4) << "ES" << setw(4) << "EF" << setw(4) << "LS" << setw(4) << "LF" << setw(6) << "Slack" << "\n";
        for (Task* crr = project.head; crr != NULL; crr = crr->next) {
            cout << setw(4) << crr->id << setw(4) << crr->EarlyStartTime << setw(4) << crr->EarlyFinishTime << setw(4) << crr->LateStartTime << setw(4) << crr->LateFinishTime << setw(6) << crr->Slack << "\n";
            dur = crr->LateFinishTime;
        }
        cout << "Total duration of basic schedule = " << dur << endl;
    }

    // Identify and return the critical tasks while displaying them
    // The sum of their durations should match the project's completion time
    void printCriticalTasks() {
        // Identify critical tasks based on Slack values
        // Print the critical tasks and their durations
        Task* current = project.head;
        cout << "\n Critical Tasks : \n";
        for (current = project.head; current != NULL; current = current->next) {
            if (current->Slack == 0) {
                cout << "Task ID : " << current->id << endl;
            }
        }
    }

    void completionTimeWithResources() {
        // Implement scheduling with resource availability
        //// Print the project's schedule and completion time
        bool check = true;
        if (!flag)
            calculateBasicSchedule();

        Resource* res = project.resources;
        Task* current = project.head;
        int Duration = 0; // Reset Duration for each skill level
        Task* newTaskHead = NULL; // Linked list for newTask
        Task* newTaskTail = NULL; // Tail pointer for newTask
        int maxSkill = 0;

        for (; res != NULL; res = res->next) {
            if (res->skill && res->skill->id > maxSkill) {
                maxSkill = res->skill->id;
            }
        }
        cout << maxSkill << endl;

        for (int skillLevel = 1; skillLevel <= maxSkill; skillLevel++) {
            current = project.head; // Reset current for each skill level
            while (current) {
                if (current->requiredSkill && current->requiredSkill->id == skillLevel) {
                    // Create a new task node
                    Task* newTaskNode = new Task(current->duration, current->requiredSkill);
                    newTaskNode->ResourceEarlyStartTime = 0; // Reset EarlyStartTime
                    newTaskNode->ResourceEarlyFinishTime = 0; // Reset EarlyFinishTime
                    newTaskNode->id = current->id;
                    newTaskNode->Slack = current->Slack;

                    if (!newTaskHead) {
                        newTaskHead = newTaskNode;
                        newTaskTail = newTaskNode;
                    }
                    else {
                        newTaskTail->next = newTaskNode;
                        newTaskTail = newTaskNode;
                    }
                }
                current = current->next; // Move to the next task
            }

            Task* currentTask = newTaskHead;
            int n = 0; // Count the number of tasks in newTask
            while (currentTask) {
                n++;
              
                currentTask = currentTask->next;
            }

            bool swapped;

            for (int i = 0; i < n - 1; i++) {
                swapped = false;
                currentTask = newTaskHead;
                Task* prevTask = nullptr;

                for (int j = 0; (j < n - i - 1) && currentTask; j++) {
                    if (currentTask && currentTask->next &&
                        ( currentTask->Slack > currentTask->next->Slack ||
                            ( currentTask->Slack == currentTask->next->Slack && currentTask->duration > currentTask->next->duration ) )) {

                        // Swap currentTask and currentTask->next
                        Task* temp = currentTask->next;
                        currentTask->next = temp->next;
                        temp->next = currentTask;
                        if (prevTask) {
                            prevTask->next = temp;
                        }
                        else {
                            newTaskHead = temp;
                        }
                        swapped = true;
                    }

                    prevTask = currentTask;
                    currentTask = currentTask->next;
                }

                // If no two elements were swapped in inner loop, the linked list is already sorted
                if (!swapped) {
                    break;
                }
            }
            if (check) {
                cout << "Resource schedule:" << endl;
                cout << setw(4) << "ID" << setw(4) << "ES" << setw(4) << "EF" << setw(5) << "Slac" << setw(4) << " Res" << endl;
            }
            currentTask = newTaskHead;
            for (int i = 0; i < n; i++) {
                currentTask->ResourceEarlyStartTime = Duration;
                Duration += currentTask->duration;
                currentTask->ResourceEarlyFinishTime = currentTask->duration + currentTask->ResourceEarlyStartTime;
                cout << setw(4) << currentTask->id << setw(4) << currentTask->ResourceEarlyStartTime << setw(4) << currentTask->ResourceEarlyFinishTime << setw(5) << currentTask->Slack << setw(4) << currentTask->requiredSkill->id << endl;
                currentTask = currentTask->next;
            }
            if (!check)
                cout << "Total duration of resource schedule = " << Duration << endl;
            check = false;

            // Clean up the linked list for the next skill level
            while (newTaskHead) {
                Task* temp = newTaskHead;
                newTaskHead = newTaskHead->next;
                delete temp;
            }
        }
    }
    // Compute the project's completion time, taking into account resource availability
    // and their proficiency levels
    // Enable tasks to commence accordingly
    // Display the schedule as well
    void completionTimeWithResourceProficiency() {
        // Implement scheduling with resource availability and proficiency levels
        // Update the task durations based on the proficiency of the required skill
        if (!flag)
            calculateBasicSchedule();

        Resource* res = project.resources;
        Task* current = project.head;
        int Duration = 0; // Reset Duration for each skill level
        Task* newTaskHead = NULL; // Linked list for newTask
        Task* newTaskTail = NULL; // Tail pointer for newTask
        Task* SortedTaskHead = NULL;
        Task* SortedTaskTail = NULL;
        int maxSkill = 0;
        bool check = true;
        for (; res != NULL; res = res->next) {
            if (res->skill && res->skill->id > maxSkill) {
                maxSkill = res->skill->id;
            }
        }
        for (int skillLevel = 1; skillLevel <= maxSkill; skillLevel++) {
            current = project.head; // Reset current for each skill level
            while (current) {
                if (current->requiredSkill && current->requiredSkill->id == skillLevel) {
                    // Create a new task node
                    Task* newTaskNode = new Task(current->duration, current->requiredSkill);
                    // cout << current->duration << "      " << newTaskNode->duration << endl;
                    newTaskNode->id = current->id;
                    newTaskNode->Slack = current->Slack;

                    if (!newTaskHead) {
                        newTaskHead = newTaskNode;
                        newTaskTail = newTaskNode;

                    }
                    else {
                        newTaskTail->next = newTaskNode;
                        newTaskTail = newTaskNode;

                    }
                }
                current = current->next; // Move to the next task
            }

            Task* currentTask = newTaskHead;
            int n = 0; // Count the number of tasks in newTask
            while (currentTask) {
                n++;
                /// <summary>
                /// 
                /// </summary>
                currentTask = currentTask->next;
            }

            bool swapped;

            for (int i = 0; i < n - 1; i++) {
                swapped = false;
                currentTask = newTaskHead;
                Task* prevTask = nullptr;

                for (int j = 0; (j < n - i - 1) && currentTask; j++) {
                    if (currentTask && currentTask->next &&
                        ( currentTask->Slack > currentTask->next->Slack ||
                            ( currentTask->Slack == currentTask->next->Slack && currentTask->duration > currentTask->next->duration ) )) {

                        // Swap currentTask and currentTask->next
                        Task* temp = currentTask->next;
                        currentTask->next = temp->next;
                        temp->next = currentTask;
                        if (prevTask) {
                            prevTask->next = temp;
                        }
                        else {
                            newTaskHead = temp;
                        }
                        swapped = true;
                    }
                    prevTask = currentTask;
                    currentTask = currentTask->next;
                }
                // If no two elements were swapped in inner loop, the linked list is already sorted
                if (!swapped) {
                    break;
                }
            }

            current = newTaskHead;
            while (current) {
                // Calculate the updated duration based on proficiency
                if (current->requiredSkill) {
                    float proficiency = current->requiredSkill->proficiencyLevel;
                    if (proficiency > 0 && proficiency <= 1.0) {
                        current->ResourceProfduration *= ( 1.0 / proficiency );
                        current->ResourceProfduration = ceil(current->ResourceProfduration);
                    }
                    else {
                        cout << "Invalid proficiency level for Task " << endl;
                    }
                }
                current = current->next;
            }
            currentTask = newTaskHead;
            if (check) {
                cout << "Resource Proficiency schedule:" << endl;
                cout << setw(4) << "ID" << setw(4) << "ES" << setw(4) << "EF" << setw(5) << "Slac" << setw(4) << " Skill" << endl;
            }
            for (int i = 0; i < n; i++) {
                currentTask->ResourceProfEarlyStartTime = Duration;
                Duration += currentTask->ResourceProfduration;
                currentTask->ResourceProfEarlyFinishTime = currentTask->ResourceProfduration + currentTask->ResourceProfEarlyStartTime;
                cout << setw(4) << currentTask->id << setw(4) << currentTask->ResourceProfEarlyStartTime << setw(4) << currentTask->ResourceProfEarlyFinishTime << setw(5) << currentTask->Slack << setw(4) << currentTask->requiredSkill->id << endl;
                currentTask = currentTask->next;
            }
            if (!check)
                cout << "Total duration of Resource Proficiency schedule = " << Duration << endl;
            check = false;
            // Clean up the linked list for the next skill level
            while (newTaskHead) {
                Task* temp = newTaskHead;
                newTaskHead = newTaskHead->next;
                delete temp;
            }
        }

    }
};
