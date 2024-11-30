#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LEN 100

const char file_name[100] = "users.txt";

// User structure
typedef struct {
    int id;
    char name[50];
    int age;
} User;

User users[MAX_USERS];
int userCount = 0;

// will load all users into memory
void loadUsers() {
    FILE *file = fopen(file_name, "r");
    userCount = 0;

    if (file == NULL) {
        printf("No existing user file found. Creating a new one.\n");
        return;
    }

    while (userCount < MAX_USERS && 
           fscanf(file, "%d,%[^,],%d\n", 
                  &users[userCount].id, 
                  users[userCount].name, 
                  &users[userCount].age) == 3) {
        userCount++;
    }

    fclose(file);
}

// writes all users from memory into file
void saveUsers() {
    FILE *file = fopen(file_name, "w");
    
    if (file == NULL) {
        printf("Error saving users to file!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%d,%s,%d\n", 
                users[i].id, 
                users[i].name, 
                users[i].age);
    }

    fclose(file);
}

int findUserById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) {
            return i;
        }
    }
    return -1;
}

void createFile() {
    FILE *file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(file);
    loadUsers();
}

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached!\n");
        return;
    }

    User newUser;
    int existingIndex;

    printf("Enter User ID: ");
    scanf("%d", &newUser.id);

    existingIndex = findUserById(newUser.id);
    if (existingIndex != -1) {
        printf("User ID %d already exists!\n", newUser.id);
        return;
    }
    
    printf("Enter Name: ");
    scanf(" %[^\n]s", newUser.name);
    
    printf("Enter Age: ");
    scanf("%d", &newUser.age);

    users[userCount] = newUser;
    userCount++;

    saveUsers();
    printf("User added successfully!\n");
}

void displayUsers() {
    if (userCount == 0) {
        printf("No users found!\n");
        return;
    }
    printf("\n");
    printf("ID\tName\t\tAge\n");
    printf("------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("%d\t%-15s\t%d\n", 
               users[i].id, 
               users[i].name, 
               users[i].age);
    }
}

void updateUser() {
    int searchId, index;

    printf("Enter User ID to update: ");
    scanf("%d", &searchId);

    index = findUserById(searchId);
    if (index == -1) {
        printf("User with ID %d not found!\n", searchId);
        return;
    }

    printf("Current Name: %s\n", users[index].name);
    printf("Current Age: %d\n", users[index].age);
    
    printf("Enter new Name: ");
    scanf(" %[^\n]s", users[index].name);
    
    printf("Enter new Age: ");
    scanf("%d", &users[index].age);

    saveUsers();
    printf("User updated successfully!\n");
}

void deleteUser() {
    int searchId, index;

    printf("Enter User ID to delete: ");
    scanf("%d", &searchId);

    index = findUserById(searchId);
    if (index == -1) {
        printf("User with ID %d not found!\n", searchId);
        return;
    }

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    saveUsers();
    printf("User deleted successfully!\n");
}

int main() {
    int choice;
    createFile();

    while (1) {
        printf("\n-------------------\n");
        printf("1. Add New User\n");
        printf("2. Display All Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addUser(); break;
            case 2: displayUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: 
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
