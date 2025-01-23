#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 30

typedef struct Account
{
    int accountNumber;
    char accountHolder[100];
    char dob[12]; // dd/mm/yyyy
    char aadhar[13];
    char pan[11];
    char accountType[10]; // saving or current
    char branch[50];
    float balance;
    char password[20];
    struct Account *next;
} Account;

void accountMenu(Account *);
// global variables
Account *head = NULL;
Account *tail = NULL;
int accountCounter = 1232; // base random account number, to generate further account numbers

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
            printf("Invalid input! Please enter a valid integer.\n");
        }
    }

    return 0;
}

void readString(char *string, size_t size)
{
    fgets(string, size, stdin);
    string[Strcspn(string, '\n')] = '\0';
    printf("\n");
}

void createAccount()
{
    Account *newAccount = (Account *)malloc(sizeof(Account));
    if (newAccount == NULL)
    {
        printf("\n Error creating account");
        return;
    }
    newAccount->accountNumber = accountCounter++;

    printf("\n ========== Create Account ==========\n\n");

    printf("Enter your full name: ");
    readString(newAccount->accountHolder, sizeof(newAccount->accountHolder));
    printf("Enter your date of birth (DD/MM/YYYY): ");
    readString(newAccount->dob, sizeof(newAccount->dob));
    printf("Enter your Aadhar number: ");
    readString(newAccount->aadhar, sizeof(newAccount->aadhar));
    printf("Enter your PAN number: ");
    readString(newAccount->pan, sizeof(newAccount->pan));
    printf("Enter account type (Saving/Current): ");
    readString(newAccount->accountType, sizeof(newAccount->accountType));
    printf("Enter branch name: ");
    readString(newAccount->branch, sizeof(newAccount->branch));
    printf("Set a password for your account: ");
    readString(newAccount->password, sizeof(newAccount->password));
    printf("Enter initial deposit amount: ");
    scanf("%f", &newAccount->balance);

    if (head == NULL)
    {
        head = newAccount;
        tail = newAccount;
    }
    else
    {
        tail->next = newAccount;
        tail = newAccount;
    }
    newAccount->next = NULL;

    if (tail != NULL)
    {
        printf("\n === Account Created Successfully! ===\n");
        printf("\n Your account number is: %d\n", newAccount->accountNumber);
        printf("\n Logging you in...\n");
    }
    else
    {
        printf("\n Not able to create Account!\n");
        free(newAccount);
    }
    accountMenu(newAccount);
}

Account *findAccount(int accountNumber)
{
    Account *current = head;

    while (current != NULL)
    {
        if (accountNumber == current->accountNumber)
            return current;
        current = current->next;
    }
    return NULL;
}

void login()
{
    int accountNumber;
    char password[20];
    printf("\n ========== Login Account ==========\n\n");
    printf("Enter your account number: ");
    while (readInt(&accountNumber, 0) != 1)
        ;
    printf("Enter your password: ");
    readString(password, sizeof(password));

    Account *accountToLogin = findAccount(accountNumber);

    if (accountToLogin != NULL)
    {
        if (strcmp(accountToLogin->password, password) == 0)
        {
            printf("\n Login Successfull!\n");
            accountMenu(accountToLogin);
            return;
        }
    }

    printf("\n Account Number or Password Incorrect.\n");
}

void showAccountDetails(Account *account)
{
    printf("\n ======= Account Details =======\n\n");
    printf(" Account Number: %d\n", account->accountNumber);
    printf(" Account Holder: %s\n", account->accountHolder);
    printf(" DOB: %s\n", account->dob);
    printf(" Aadhar: %s\n", account->aadhar);
    printf(" PAN: %s\n", account->pan);
    printf(" Account Type: %s\n", account->accountType);
    printf(" Branch: %s\n", account->branch);
    printf(" Balance: %.2f\n", account->balance);
}

void depositMoney(float *accountBalance)
{
    printf("\n ======= Money Deposit =======\n\n");
    float amount;
    printf(" Enter deposit amount: ");
    scanf("%f", &amount);
    *accountBalance += amount;
    printf(" Deposit successful. Current Balance: %.2f\n", *accountBalance);
}

void withdrawMoney(float *accountBalance)
{
    printf("\n ======= Money Withdrawal =======\n\n");
    float amount;
    printf(" Enter withdrawal amount: ");
    scanf("%f", &amount);
    if (amount > *accountBalance)
    {
        printf(" Insufficient balance.\n");
    }
    else
    {
        *accountBalance -= amount;
        printf(" Withdrawal successful. Current Balance: %.2f\n", *accountBalance);
    }
}

void transferMoney(float *accountBalance)
{

    int targetAccountNumber;
    float amount;
    printf("\n\n ======= Account Menu =======\n\n");
    printf("Enter target account number: ");
    scanf("%d", &targetAccountNumber);
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    Account *targetAccount = findAccount(targetAccountNumber);

    if (!targetAccount)
    {
        printf("Beneficiary account not found.\n");
    }
    else if (amount > *accountBalance)
    {
        printf("Insufficient balance.\n");
    }
    else
    {
        *accountBalance -= amount;
        targetAccount->balance += amount;
        printf("Transfer successful. Current balance: %.2f\n", *accountBalance);
    }
}

void closeAccount(int accountNumber)
{
    Account *prev = NULL;
    Account *current = head;
    char confirmation;

    if (head == NULL)
    {
        printf("\n No Accounts Found.\n");
        return;
    }

    while (current != NULL && current->accountNumber != accountNumber)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("\n Account does not exists.\n");
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
    printf("\n Account Closed Successfully.\n");
    free(current);
}
void accountMenu(Account *account)
{

    if (!account)
    {
        printf(" Account not found!\n");
        return;
    }

    int choice;
    do
    {
        printf("\n\n ======= Account Menu =======\n\n");
        printf(" 1. Display account details\n");
        printf(" 2. Deposit money\n");
        printf(" 3. Withdraw money\n");
        printf(" 4. Transfer money\n");
        printf(" 5. Close account\n");
        printf(" 6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            showAccountDetails(account);
            break;
        case 2:
            depositMoney(&account->balance);
            break;
        case 3:
            withdrawMoney(&account->balance);
            break;
        case 4:
            transferMoney(&account->balance);
            break;
        case 5:
            closeAccount(account->accountNumber);
            return;
        case 6:
            printf("Logging out...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
        printf("\n\n");
    } while (choice != 6);
}

void freeAll()
{
    Account *account;
    while (account != NULL)
    {
        Account *temp = account;
        account = account->next;
        free(temp);
    }
}
int main()
{
    int choice;
    do
    {
        printf("\n ========== Banking System ==========\n\n");
        printf("1. Create a new account\n");
        printf("2. Login to an account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        while (readInt(&choice, 0) != 1)
            ;

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            login();
            break;
        case 3:
            freeAll();
            printf("Exiting the system. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
        printf("\n\n");
    } while (choice != 3);

    return 0;
}
