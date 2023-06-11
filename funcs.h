#ifdef _WIN32
#define clr() system("cls")
#else
#define clr() system("clear")
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_CUSTOMERS 100

void pheader()
{
    printf("\t=============================================================\t\n");
    printf("\t         Welcome to Bank of North South University\n");
    printf("\t=============================================================\t\n");
}

struct Customer
{
    char name[100];
    int accountNumber;
    float balance;
    char contactNumber[20];
    char serviceRegion[10];
    char pin[5];
};


void encrypt(char *str, int key)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = str[i] + key;
    }
}

void decrypt(char *str, int key)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = str[i] - key;
    }
}

int writeData(struct Customer customers[], int count)
{
    FILE *file = fopen("bankdata.txt", "w");
    if (file == NULL)
    {
        printf("\tError opening file.\t\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        encrypt(customers[i].name, 5);
        encrypt(customers[i].pin, 7);
        fprintf(file, "%s\n%d %.2f %s %s %s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber,customers[i].serviceRegion, customers[i].pin);
        decrypt(customers[i].name, 5);
        decrypt(customers[i].pin, 7);
    }

    fclose(file);
    printf("\t==============Data written to file successfully==============\n\n");
    return 0;
}


int readDataUser(struct Customer customers[], int *count)
{
    FILE *file = fopen("bankdata.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    *count = 0;
    while (*count < MAX_CUSTOMERS)
    {
        if (fgets(customers[*count].name, 100, file) == NULL)
        {
            break;
        }
        customers[*count].name[strlen(customers[*count].name) - 1] = '\0'; // remove newline character
        fscanf(file, " %d %f %s %s %s", &customers[*count].accountNumber, &customers[*count].balance, customers[*count].contactNumber, customers[*count].serviceRegion, customers[*count].pin);
        decrypt(customers[*count].name, 5);
        decrypt(customers[*count].pin, 7);
        (*count)++;

        // Consume remaining characters in the input buffer
        char buffer[10];
        fgets(buffer, 10, file);
    }

    fclose(file);
    printf("\t=============Data read from file successfully================\n");
    return 0;
}


int readData(struct Customer customers[], int *count)
{
    FILE *file = fopen("bankdata.txt", "r");
    FILE *pass = fopen("pass.txt", "r");
    if (file == NULL || pass == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char input[100];
    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp(input, password) != 0)
    {
        printf("Incorrect password. Access denied.\n");
        fclose(file);
        fclose(pass);
        exit(0);
    }

    *count = 0;
    while (*count < MAX_CUSTOMERS)
    {
        if (fgets(customers[*count].name, 100, file) == NULL)
        {
            break;
        }
        customers[*count].name[strlen(customers[*count].name) - 1] = '\0'; // removing newline character
        fscanf(file, " %d %f %s %s %s",
               &customers[*count].accountNumber,
               &customers[*count].balance,
               customers[*count].contactNumber,
               customers[*count].serviceRegion,
               customers[*count].pin);
        decrypt(customers[*count].name, 5);
        decrypt(customers[*count].pin, 7);
        (*count)++;

        // Consume remaining characters in the input buffer
        char buffer[10];
        fgets(buffer, 10, file);
    }

    fclose(file);
    fclose(pass);
    printf("\t=====================Data read from file successfully====================\n");
    return 0;
}

void sortDataAlphabetically(struct Customer customers[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (strcmp(customers[j].name, customers[j + 1].name) > 0)
            {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\tData sorted alphabetically successfully.\t\n");
}

void sortDataByDeposit(struct Customer customers[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (customers[j].balance < customers[j + 1].balance)
            {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\tData sorted by deposit successfully.\t\n");
}

void sortDataByAccountNumber(struct Customer customers[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (customers[j].accountNumber > customers[j + 1].accountNumber)
            {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("\tData sorted by account number successfully.\t\n");
}

void searchData(struct Customer customers[], int count, int accountNumber)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("\tCustomer found:\t\n");
            printf("\tName: %s\t\n", customers[i].name);
            printf("\tAccount Number: %d\t\n", customers[i].accountNumber);
            printf("\tBalance: %.2f\t\n", customers[i].balance);
            printf("\tContact Number: %s\t\n", customers[i].contactNumber);
            printf("\tService Region: %s\t\n", customers[i].serviceRegion);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void deleteData(struct Customer customers[], int *count, int accountNumber)
{
    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            found = 1;
            for (int j = i; j < *count - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            (*count)--;
            printf("\tCustomer with account number %d deleted.\t\n", accountNumber);
            break;
        }
    }
    if (!found)
    {
        printf("\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void editData(struct Customer customers[], int count, int accountNumber)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("\tEnter new name: ");
            fgets(customers[i].name, 100, stdin);
            customers[i].name[strlen(customers[i].name) - 1] = '\0';
            printf("\tEnter new balance: ");
            scanf("%f", &customers[i].balance);
            printf("\tEnter new contact number: ");
            scanf("%s", customers[i].contactNumber);
            printf("\tEnter new service region: ");
            scanf("%s", customers[i].serviceRegion);
            found = 1;
            printf("\tCustomer information updated successfully.\t\n");
            break;
        }
    }
    if (!found)
    {
        printf("\tCustomer with account number %d not found.\t\n", accountNumber);
    }
}

void changePassword()
{
    FILE *pass = fopen("pass.txt", "r+");
    if (pass == NULL)
    {
        printf("\tError opening file.\t\n");
        return;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char newPassword[100];
    printf("\tEnter current password: ");
    scanf("%s", newPassword);
    if (strcmp(newPassword, password) != 0)
    {
        printf("\tIncorrect password. Password change failed.\t\n");
        fclose(pass);
        return;
    }

    char newPasswordConfirm[100];
    printf("\tEnter new password: ");
    scanf("%s", newPassword);
    printf("\tConfirm new password: ");
    scanf("%s", newPasswordConfirm);

    if (strcmp(newPassword, newPasswordConfirm) == 0)
    {
        encrypt(newPassword, 5);
        fseek(pass, 0, SEEK_SET);
        fprintf(pass, "%s\n", newPassword);
        printf("Password changed successfully.\n");
    }
    else
    {
        printf("\tPassword confirmation failed. Password change failed.\t\n");
    }

    fclose(pass);
}

void transferMoney(struct Customer customers[], int count, int senderAccountNumber, int receiverAccountNumber)
{
    int senderIndex = -1;
    int receiverIndex = -1;

    for (int i = 0; i < count; i++)
    {
        if (customers[i].accountNumber == senderAccountNumber)
        {
            senderIndex = i;
        }
        else if (customers[i].accountNumber == receiverAccountNumber)
        {
            receiverIndex = i;
        }

        if (senderIndex != -1 && receiverIndex != -1)
        {
            break;
        }
    }

    if (senderIndex == -1)
    {
        printf("\tSender with account number %d not found.\t\n", senderAccountNumber);
        return;
    }

    if (receiverIndex == -1)
    {
        printf("\tReceiver with account number %d not found.\t\n", receiverAccountNumber);
        return;
    }

    char pin[5];
    printf("\tEnter your PIN: ");
    scanf("%s", pin);

    if (strcmp(customers[senderIndex].pin, pin) != 0)
    {
        printf("\tIncorrect PIN. Transfer failed.\t\n");
        return;
    }

    float amount;
    printf("\tEnter the amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\tInvalid amount. Transfer failed.\t\n");
        return;
    }

    if (customers[senderIndex].balance < amount)
    {
        printf("\tInsufficient balance. Transfer failed.\t\n");
        return;
    }

    customers[senderIndex].balance -= amount;
    customers[receiverIndex].balance += amount;

    printf("Transfer successful.\n");

    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Sender Account Number: %d, Receiver Account Number: %d, Amount: %.2f\n", senderAccountNumber, receiverAccountNumber, amount);

    fclose(file);
}

void generateSortedTextFile(struct Customer customers[], int count, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("\tError opening file.\t\n");
        return;
    }

    fprintf(file, "Name                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
    }

    fclose(file);
    printf("\tText file generated successfully.\nPlease handle it carefully. It contains Sensitive data\t\n");
}

void generateListByServiceRegion(struct Customer customers[], int count, const char *serviceRegion)
{
    printf("For region: %s\n\n", serviceRegion);
    printf("Name                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(customers[i].serviceRegion, serviceRegion) == 0)
        {
            printf("%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
        }
    }
    char generate[4] = "";
    printf("Enter YES to generate file, anything else to skip file output:\n == ");
    scanf("%s", generate);
    if (strcmp(generate,"YES") != 0)
    {
        return;
    }
    FILE *file = fopen("listByServiceRegion.txt", "w");
    if (file == NULL)
    {
        printf("\tError opening file.\t\n");
        return;
    }
    fprintf(file, "For region: %s\n\n", serviceRegion);
    fprintf(file, "Name                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");

    for (int i = 0; i < count; i++)
    {
        if (strcmp(customers[i].serviceRegion, serviceRegion) == 0)
        {
            fprintf(file, "%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
        }
    }

    fclose(file);
    printf("\tText file generated successfully.\nPlease handle it carefully. It contains Sensitive data\t\n");
}

void printAllAccounts(struct Customer customers[], int count)
{
    printf("All Customer Accounts:\n");
    printf("Name                AccountNumber  Balance      ContactNumber   ServiceRegion  \n\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-19s %-14d %-12.2f %-15s %-14s\n", customers[i].name, customers[i].accountNumber, customers[i].balance,
               customers[i].contactNumber, customers[i].serviceRegion);
    }
}

void addInterest(struct Customer customers[], int count)
{
    printf("Enter interest rate (in Percentage): ");
    double rate;
    scanf("%lf", &rate);
    for (int i = 0; i < count; i++)
    {
        customers[i].balance += customers[i].balance * (rate/100.0);
    }
}


