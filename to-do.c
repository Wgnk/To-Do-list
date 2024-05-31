#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

typedef struct {
    char description[MAX_LENGTH];
    int completed;
    char priority[10];
    char dueDate[11];
} Task;

void addTask(Task tasks[], int *taskCount);
void editTask(Task tasks[], int taskCount);
void removeTask(Task tasks[], int *taskCount);
void markCompleted(Task tasks[], int taskCount);
void displayTasks(const Task tasks[], int taskCount);
void searchTasks(const Task tasks[], int taskCount);
void saveTasks(const Task tasks[], int taskCount, const char *filename);
void loadTasks(Task tasks[], int *taskCount, const char *filename);

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    while (1) {
        printf("Simple To-Do List\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Remove Task\n");
        printf("4. Mark Task as Completed\n");
        printf("5. Display Tasks\n");
        printf("6. Search Tasks\n");
        printf("7. Save Tasks\n");
        printf("8. Load Tasks\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character left by scanf

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                editTask(tasks, taskCount);
                break;
            case 3:
                removeTask(tasks, &taskCount);
                break;
            case 4:
                markCompleted(tasks, taskCount);
                break;
            case 5:
                displayTasks(tasks, taskCount);
                break;
            case 6:
                searchTasks(tasks, taskCount);
                break;
            case 7:
                saveTasks(tasks, taskCount, "tasks.txt");
                break;
            case 8:
                loadTasks(tasks, &taskCount, "tasks.txt");
                break;
            case 9:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
        printf("\n");
    }

    return 0;
}

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }
    printf("Enter task description: ");
    fgets(tasks[*taskCount].description, MAX_LENGTH, stdin);
    tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0'; // Remove newline character

    printf("Enter priority (Low, Medium, High): ");
    fgets(tasks[*taskCount].priority, 10, stdin);
    tasks[*taskCount].priority[strcspn(tasks[*taskCount].priority, "\n")] = '\0'; // Remove newline character

    printf("Enter due date (YYYY-MM-DD): ");
    fgets(tasks[*taskCount].dueDate, 11, stdin);
    tasks[*taskCount].dueDate[strcspn(tasks[*taskCount].dueDate, "\n")] = '\0'; // Remove newline character

    tasks[*taskCount].completed = 0;
    (*taskCount)++;
    printf("Task added successfully.\n");
}

void editTask(Task tasks[], int taskCount) {
    int taskIndex;
    printf("Enter task number to edit: ");
    scanf("%d", &taskIndex);
    getchar(); // to consume the newline character left by scanf
    if (taskIndex < 1 || taskIndex > taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    printf("Enter new task description: ");
    fgets(tasks[taskIndex - 1].description, MAX_LENGTH, stdin);
    tasks[taskIndex - 1].description[strcspn(tasks[taskIndex - 1].description, "\n")] = '\0'; // Remove newline character

    printf("Enter new priority (Low, Medium, High): ");
    fgets(tasks[taskIndex - 1].priority, 10, stdin);
    tasks[taskIndex - 1].priority[strcspn(tasks[taskIndex - 1].priority, "\n")] = '\0'; // Remove newline character

    printf("Enter new due date (YYYY-MM-DD): ");
    fgets(tasks[taskIndex - 1].dueDate, 11, stdin);
    tasks[taskIndex - 1].dueDate[strcspn(tasks[taskIndex - 1].dueDate, "\n")] = '\0'; // Remove newline character

    printf("Task edited successfully.\n");
}

void removeTask(Task tasks[], int *taskCount) {
    int taskIndex;
    printf("Enter task number to remove: ");
    scanf("%d", &taskIndex);
    getchar(); // to consume the newline character left by scanf
    if (taskIndex < 1 || taskIndex > *taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    for (int i = taskIndex; i < *taskCount; i++) {
        tasks[i - 1] = tasks[i];
    }
    (*taskCount)--;
    printf("Task removed successfully.\n");
}

void markCompleted(Task tasks[], int taskCount) {
    int taskIndex;
    printf("Enter task number to mark as completed: ");
    scanf("%d", &taskIndex);
    getchar(); // to consume the newline character left by scanf
    if (taskIndex < 1 || taskIndex > taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    tasks[taskIndex - 1].completed = 1;
    printf("Task marked as completed.\n");
}

void displayTasks(const Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks to display.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [Priority: %s, Due: %s] [%s]\n", i + 1, tasks[i].description, tasks[i].priority, tasks[i].dueDate, tasks[i].completed ? "Completed" : "Not Completed");
    }
}

void searchTasks(const Task tasks[], int taskCount) {
    char keyword[MAX_LENGTH];
    printf("Enter keyword to search: ");
    fgets(keyword, MAX_LENGTH, stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (strstr(tasks[i].description, keyword) != NULL) {
            printf("%d. %s [Priority: %s, Due: %s] [%s]\n", i + 1, tasks[i].description, tasks[i].priority, tasks[i].dueDate, tasks[i].completed ? "Completed" : "Not Completed");
            found = 1;
        }
    }
    if (!found) {
        printf("No tasks found with the keyword '%s'.\n", keyword);
    }
}

void saveTasks(const Task tasks[], int taskCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s;%s;%s;%d\n", tasks[i].description, tasks[i].priority, tasks[i].dueDate, tasks[i].completed);
    }
    fclose(file);
    printf("Tasks saved successfully.\n");
}

void loadTasks(Task tasks[], int *taskCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    *taskCount = 0;
    while (fscanf(file, "%99[^;];%9[^;];%10[^;];%d\n", tasks[*taskCount].description, tasks[*taskCount].priority, tasks[*taskCount].dueDate, &tasks[*taskCount].completed) == 4) {
        (*taskCount)++;
    }
    fclose(file);
    printf("Tasks loaded successfully.\n");
}
