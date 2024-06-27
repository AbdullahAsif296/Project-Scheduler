# README for Project Management Application

## Table of Contents

1. [Introduction](#introduction)
2. [Design and Architecture](#design-and-architecture)
3. [Usage](#usage)
4. [References](#references)

---

## 1. Introduction <a name="introduction"></a>

This C++ project is a Project Management Application that helps users manage tasks, resources, and skills within a project. It provides features such as task scheduling, critical path analysis, resource allocation, and resource proficiency consideration. The application is designed to assist project managers in planning and tracking project schedules efficiently.

## 2. Design and Architecture <a name="design-and-architecture"></a>

The application is structured around the following core classes:

- `Skill`: Represents a skill with an associated proficiency level.
- `TaskDependency`: Represents dependencies between tasks.
- `Task`: Represents a project task with information like ID, duration, start and finish times, required skill, dependencies, and Slack.
- `Resource`: Represents a resource with availability and associated skills.
- `Project`: Manages the project and contains tasks and resources.
- `ProjectManagement`: Provides the core functionality for managing the project, calculating task schedules, and considering resource proficiency levels.

### Key Features:

- **Task Dependency Management**: Users can specify dependencies between tasks, ensuring that tasks are scheduled based on their dependencies.

- **Basic Schedule Calculation**: The application implements the Critical Path Method (CPM) to calculate the early start (ES), early finish (EF), late start (LS), late finish (LF), and slack for each task. This information helps users identify critical tasks and determine the project's completion time.

- **Resource Allocation**: The application allows the allocation of resources to tasks, considering their availability and required skills. The scheduling takes into account resource availability to create a project schedule.

- **Resource Proficiency**: Users can specify proficiency levels for skills, and the application adjusts task durations based on proficiency. Tasks requiring higher proficiency can be completed faster, whereas tasks with lower proficiency take more time.

### Execution Flow:

1. The application initializes by creating skill, task, resource, and project instances.

2. Users can add skills and resources to the project.

3. Users can add tasks to the project, specifying their durations, required skills, and dependencies.

4. The application calculates the basic project schedule using the Critical Path Method (CPM). It computes ES, EF, LS, LF, and Slack for each task.

5. Users can identify critical tasks by examining their slack values (tasks with slack = 0 are critical).

6. The application schedules tasks considering resource availability. It uses the early start times and slack to create a project schedule.

7. Users can specify proficiency levels for skills, and the application adjusts task durations based on proficiency.

8. The final project schedule, including resource allocation and proficiency consideration, is displayed.

## 3. Usage <a name="usage"></a>

To use the Project Management Application, follow these steps:

1. Include the necessary C++ header files and code for the project in your C++ development environment.

2. Compile and run the project.

3. Use the application to add skills, resources, and tasks to your project.

4. Specify task dependencies if required.

5. Calculate the basic project schedule and identify critical tasks.

6. Allocate resources and consider proficiency levels for skills.

7. View the final project schedule, including resource allocation and proficiency consideration.

## 4. References <a name="references"></a>

1. [Asana - Critical Path Method (CPM)](https://asana.com/resources/critical-path-method)
2. [GeeksforGeeks - Software Engineering | Critical Path Method (CPM)](https://www.geeksforgeeks.org/software-engineering-critical-path-method/)

These references were consulted for understanding and implementing the Critical Path Method (CPM) and project management principles. They provide valuable insights into project scheduling and management techniques.
