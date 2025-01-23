#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1000
#define SUBJECTS_LEN 3

typedef struct Student
{
    char name[MAX_INPUT_LEN];
    int roll;
    int marks[3]; // say English Hindi Science
    struct Student *next;
} Student;

Student *head = NULL;
Student *tail = NULL;
const char Subjects[SUBJECTS_LEN][20] = {"English", "Hindi", "Science"};

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

int scanInt(int *n, int skip)
{
    char buffer[10];
    if (skip != 0 || skip != 1)
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
            printf("Invalid input! Please enter a valid integer.\n");
        }
    }

    return 0;
}

void printStudentInfo(Student *student)
{
    printf("\n Student Name: %s\n", student->name);
    printf("\n Student Roll: %d\n", student->roll);
    printf("\n Student Marks:\n\n");
    for (int i = 0; i < SUBJECTS_LEN; i++)
        printf("\t %s: %d\n", Subjects[i], student->marks[i]);
}

Student *searchStudent(int roll)
{
    Student *current = head;

    while (current != NULL)
    {
        if (current->roll == roll)
            return current;
        current = current->next;
    }

    return NULL;
}

void addRecord()
{
    printf("\n========= Add Record =========\n");
    int roll;

    printf("\n Enter Roll Number: ");
    if (!scanInt(&roll, 0))
        return;

    if (searchStudent(roll) != NULL)
    {
        printf("\n Record already exists.");
        return;
    }
    Student *student = (Student *)malloc(sizeof(Student));
    student->roll = roll;

    printf("\n Enter Student Name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[Strcspn(student->name, '\n')] = '\0';

    for (int i = 0; i < SUBJECTS_LEN; i++)
    {
        printf("\n Enter %s marks: ", Subjects[i]);
        scanInt(&student->marks[i], 0);
    }

    if (head == NULL)
    {
        head = student;
        tail = student;
        student->next = NULL;
    }
    else
    {
        tail->next = student;
        tail = student;
        student->next = NULL;
    }
    if (tail != NULL)
    {
        printf("\n === Record Added Successfully! ===\n");
    }
    else
    {
        printf("\n Not able to add Record!\n");
        free(student);
    }
}

void displayAllRecords()
{
    Student *current = head;
    if (current == NULL)
    {
        printf("\n No Student Records Found!\n");
        return;
    }

    printf("\n ========= Student Records =========\n");

    while (current != NULL)
    {
        printStudentInfo(current);
        current = current->next;
        printf("\n====================\n");
    }
}

void updateMarks()
{
    int roll;
    printf("\n ========= Update Marks =========\n\n");
    printf(" Enter Student Roll Number: ");
    while (scanInt(&roll, 0) != 1)
        ;
    Student *student = searchStudent(roll);
    if (student)
    {
        printf(" Press Enter to skip..\n\n");
        for (int i = 0; i < SUBJECTS_LEN; i++)
        {
            printf("\n Enter %s marks: ", Subjects[i]);
            scanInt(&student->marks[i], 1);
        }
    }
    else
    {
        printf("\n Record does not exists.\n");
    }
    return;
}

void searchStudentMenu()
{
    int roll;
    printf("\n ========= Student Info =========\n\n");
    printf(" Enter Student Roll Number: ");
    while (scanInt(&roll, 0) != 1)
        ;
    Student *student = searchStudent(roll);
    if (student)
        printStudentInfo(student);
    else
    {
        printf("\n Record does not exists.\n");
    }
    return;
}

void deleteRecord()
{
    int roll;
    char confirmation;

    printf("\n ========= Delete Record =========\n\n");
    printf("Enter Student Roll Number: ");
    while (scanInt(&roll, 0) != 1)
        ;

    if (head == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    Student *current = head;
    Student *prev = NULL;

    while (current != NULL && current->roll != roll)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("\n Record does not exists.\n");
        return;
    }
    printf(" Are you sure (y/n)? ");
    scanf("%c", &confirmation);
    if (confirmation != 'y')
    {
        getchar();
        return;
    }
    getchar();
    if (prev == NULL)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    free(current);
    printf("\nRecord deleted successfully.\n");
}

int main()
{
    int option, validInput;

    do
    {
        printf("\n ========= Student Management =========\n\n");
        printf(" 1. Add a Student Record\n");
        printf(" 2. Display all Student Records\n");
        printf(" 3. Search for a Student Record\n");
        printf(" 4. Update Marks\n");
        printf(" 5. Delete a Student Record\n");
        printf(" 6. Exit\n");

        printf("\nEnter Option: ");
        if (scanInt(&option, 0) != 1)
            continue;

        switch (option)
        {
        case 1:
            addRecord();
            break;
        case 2:
            displayAllRecords();
            break;
        case 3:
            searchStudentMenu();
            break;
        case 4:
            updateMarks();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            printf("Exit\n");
            break;
        default:
            printf("Invalid Choice! Please try again..\n");
            break;
        }
        printf("\n\n");
    } while (option != 6);

    return 0;
}