#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task
{
    int id;
    char description[100];
    int isCompleted;
    struct Task *next;
} Task;

Task *head = NULL;
Task *tail = NULL;
int taskCounter = 1;

int readInt(int *n, int skip)
{
    char buffer[10];
    if (skip != 0 && skip != 1)
        skip = 0;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (skip == 1 && buffer[0] == '\n')
        {
            return 1;
        }
        if (sscanf(buffer, "%d", n) == 1)
        {
            return 1;
        }
        else
        {
            printf("\n Invalid input! Please enter a valid integer.\n");
        }
    }

    return 0;
}

int stoi(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }

    int result = 0;
    int sign = 1;

    while (*str == ' ')
    {
        str++;
    }

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str && *str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

int Strcspn(char *input, char delim)
{
    int len = 0;
    while (*input != '\0')
    {
        if (*input == delim)
            return len;
        len++;
        input++;
    }
    return len;
}

void addTask()
{
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (!newTask)
    {
        printf("\n Memory allocation failed.\n");
        return;
    }

    printf("\n ======= Add Task =======\n");
    newTask->id = taskCounter++;
    printf("\n Enter task description: ");
    fgets(newTask->description, sizeof(newTask->description), stdin);
    newTask->description[Strcspn(newTask->description, '\n')] = '\0';
    newTask->isCompleted = 0;

    if (head == NULL)
    {
        head = newTask;
        tail = newTask;
    }
    else
    {
        tail->next = newTask;
        tail = newTask;
    }
    newTask->next = NULL;

    if (tail != NULL)
    {
        printf("\n === Task Successfully! ===\n");
    }
    else
    {
        printf("\n Task Unsucessfull!\n");
        free(newTask);
    }
}

Task *searchTask(int taskId)
{
    Task *current = head;
    while (current != NULL)
    {
        if (current->id == taskId)
            return current;
        current = current->next;
    }
    return NULL;
}

void markTask(int taskId)
{
    Task *task = searchTask(taskId);
    if (task == NULL)
    {
        printf("\n Task ID does not exist.\n");
        return;
    }
    task->isCompleted = 1;
}

void unMarkTask(int taskId)
{
    Task *task = searchTask(taskId);
    if (task == NULL)
    {
        printf("\n Task ID does not exist.\n");
        return;
    }
    task->isCompleted = 0;
}

void deleteTask(int taskId)
{
    Task *current = head;
    Task *prev = NULL;

    if (head == NULL)
    {
        printf("\n Task List Empty.\n");
        return;
    }

    while (current != NULL && current->id != taskId)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("\n Task Id does not exists.\n");
        return;
    }

    if (prev == NULL)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }
    free(current);
}

void viewAllTasks()
{
    if (!head)
    {
        printf("\n To-Do List Empty.\n");
        return;
    }

    Task *current = head;
    char buffer[10];
    printf("\n =============== All Tasks ================\n");
    while (current)
    {
        printf("\n %d. \t %s \t\t  [%s]\n", current->id, current->description, current->isCompleted ? "X" : " ");
        current = current->next;
    }
    printf("\n\n Mark: <m><space><task-id> \t Unmark: <u><<space>task-id> \t Delete: <d><space><task-id> ");
    printf("\t Back: <b> \t Refresh List: <r>\n");
    do
    {
        printf("\n --> ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[Strcspn(buffer, '\n')] = '\0';

        char *action = strtok(buffer, " ");
        int taskId = stoi(strtok(NULL, " "));
        switch (*action)
        {
        case 'm':
            markTask(taskId);
            break;
        case 'u':
            unMarkTask(taskId);
            break;
        case 'd':
            deleteTask(taskId);
            break;
        case 'b':
            return;
        case 'r':
        {
            viewAllTasks();
            return;
        }
        default:
            printf("\n Invalid Action. (Valid: m, u, d, b ,r)\n");
        }
    } while (1);
}

void viewPendingTasks()
{
    if (!head)
    {
        printf("\n Task List Empty.\n");
        return;
    }

    char buffer[15];
    Task *current = head;

    printf("\n\n ================ Pending Tasks ================ \n");
    while (current)
    {
        if (!current->isCompleted)
            printf("\n %d. \t %s \t\t  [%s]\n", current->id, current->description, " ");
        current = current->next;
    }
    printf("\n\n Mark: <m><space>task-id> \t Delete: <d><space><task-id> ");
    printf("\t Back: <b> \t Refresh List: <r>\n");

    do
    {
        printf("\n --> ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[Strcspn(buffer, '\n')] = '\0';

        char *action = strtok(buffer, " ");
        int taskId = stoi(strtok(NULL, " "));
        switch (*action)
        {
        case 'm':
            markTask(taskId);
            break;
        case 'd':
            deleteTask(taskId);
            break;
        case 'b':
            return;
        case 'r':
        {
            viewPendingTasks();
            return;
        }
        default:
            printf("\n Invalid Action. (Valid: m, d, b, r)\n");
        }
    } while (1);
}

void viewCompletedTasks()
{
    if (!head)
    {
        printf("\n Task List Empty.\n");
        return;
    }

    char buffer[15];
    Task *current = head;

    printf("\n\n ================ Completed Tasks ================ \n");
    while (current)
    {
        if (current->isCompleted)
            printf("\n %d. \t %s \t\t  [%s]\n", current->id, current->description, "X");
        current = current->next;
    }
    printf("\n\n Unmark: <u><<space>task-id> \t Delete: <d><space><task-id> ");
    printf("\t Back: <b> \t Refresh List: <r>\n");

    do
    {
        printf("\n --> ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[Strcspn(buffer, '\n')] = '\0';

        char *action = strtok(buffer, " ");
        int taskId = stoi(strtok(NULL, " "));
        switch (*action)
        {
        case 'u':
            unMarkTask(taskId);
            break;
        case 'd':
            deleteTask(taskId);
            break;
        case 'b':
            return;
        case 'r':
        {
            viewCompletedTasks();
            return;
        }
        default:
            printf("\n Invalid Action. (Valid: u, d, b, r)\n");
        }
    } while (1);
}

void freeAll()
{
    Task *current = head;
    while (current)
    {
        Task *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int choice;
    do
    {
        printf("\n ========== To-Do List ==========\n\n");
        printf(" 1. Add a new task\n");
        printf(" 2. View all tasks\n");
        printf(" 3. View pending tasks\n");
        printf(" 4. View completed tasks\n");
        printf(" 5. Exit\n");
        printf("\nEnter your choice: ");
        while (readInt(&choice, 0) != 1)
            ;

        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            viewAllTasks();
            break;
        case 3:
            viewPendingTasks();
            break;
        case 4:
            viewCompletedTasks();
            break;
        case 5:
            freeAll();
            printf("\n Exiting!\n");
            break;
        default:
            printf("\n Invalid choice. Please try again.\n");
        }
        printf("\n\n");
    } while (choice != 5);

    return 0;
}
