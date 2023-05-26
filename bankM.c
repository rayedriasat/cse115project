#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

//Ufxx|twi
struct Customer {
    char name[100];
    int accountNumber;
    float balance;
    char contactNumber[20];
    char serviceRegion[10];
    int pin;
};

void encrypt(char *str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = str[i] + key;
    }
}

void decrypt(char *str, int key) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = str[i] - key;
    }
}

int writeData(struct Customer customers[], int count) {
    FILE *file = fopen("bankdata.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

//    char password[100] = "Password";
//    encrypt(password, 5);
//    fprintf(file, "%s\n", password);

    for (int i = 0; i < count; i++) {
        encrypt(customers[i].name, 5);
        fprintf(file, "%s %d %.2f %s %s %d\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion, customers[i].pin);
        decrypt(customers[i].name, 5);
    }

    fclose(file);
    printf("Data written to file successfully.\n");
    return 0;
}

int readData(struct Customer customers[], int *count) {
    FILE *file = fopen("bankdata.txt", "r");
    FILE *pass = fopen("pass.txt", "r");
    if (file == NULL || pass == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char input[100];
    printf("Enter password: ");
    scanf("%s", input);

    if (strcmp(input, password) != 0) {
        printf("Incorrect password. Access denied.\n");
        fclose(file);
        fclose(pass);
        exit(0);
    }

    *count = 0;
    int fscworked = 6;
    while (fscworked == 6 && *count < MAX_CUSTOMERS) {
        fscworked = fscanf(file, "%s %d %f %s %s %d", customers[*count].name, &customers[*count].accountNumber, &customers[*count].balance, customers[*count].contactNumber, customers[*count].serviceRegion, &customers[*count].pin);
        if (fscworked != 6)
        {
            break;
        }
        decrypt(customers[*count].name, 5);
        (*count)++;
    }

    fclose(file);
    fclose(pass);
    printf("Data read from file successfully.\n");
    return 0;
}

void sortDataAlphabetically(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(customers[j].name, customers[j + 1].name) > 0) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("Data sorted alphabetically successfully.\n");
}

void sortDataByDeposit(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (customers[j].balance < customers[j + 1].balance) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("Data sorted by deposit successfully.\n");
}

void sortDataByAccountNumber(struct Customer customers[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (customers[j].accountNumber > customers[j + 1].accountNumber) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }
    printf("Data sorted by account number successfully.\n");
}

void searchData(struct Customer customers[], int count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            printf("Customer found:\n");
            printf("Name: %s\n", customers[i].name);
            printf("Account Number: %d\n", customers[i].accountNumber);
            printf("Balance: %.2f\n", customers[i].balance);
            printf("Contact Number: %s\n", customers[i].contactNumber);
            printf("Service Region: %s\n", customers[i].serviceRegion);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Customer with account number %d not found.\n", accountNumber);
    }
}

void deleteData(struct Customer customers[], int *count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                customers[j] = customers[j + 1];
            }
            (*count)--;
            printf("Customer with account number %d deleted.\n", accountNumber);
            break;
        }
    }
    if (!found) {
        printf("Customer with account number %d not found.\n", accountNumber);
    }
}

void editData(struct Customer customers[], int count, int accountNumber) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == accountNumber) {
            printf("Enter new name: ");
            scanf("%s", customers[i].name);
            printf("Enter new balance: ");
            scanf("%f", &customers[i].balance);
            printf("Enter new contact number: ");
            scanf("%s", customers[i].contactNumber);
            printf("Enter new service region: ");
            scanf("%s", customers[i].serviceRegion);
            found = 1;
            printf("Customer information updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Customer with account number %d not found.\n", accountNumber);
    }
}

void changePassword() {
    FILE *pass = fopen("pass.txt", "r+");
    if (pass == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char password[100];
    fscanf(pass, "%s", password);
    decrypt(password, 5);

    char newPassword[100];
    printf("Enter current password: ");
    scanf("%s", newPassword);
    if (strcmp(newPassword, password) != 0) {
        printf("Incorrect password. Password change failed.\n");
        fclose(pass);
        return;
    }

    char newPasswordConfirm[100];
    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Confirm new password: ");
    scanf("%s", newPasswordConfirm);

    if (strcmp(newPassword, newPasswordConfirm) == 0) {
        encrypt(newPassword, 5);
        fseek(pass, 0, SEEK_SET);
        fprintf(pass, "%s\n", newPassword);
        printf("Password changed successfully.\n");
    } else {
        printf("Password confirmation failed. Password change failed.\n");
    }

    fclose(pass);
}

void transferMoney(struct Customer customers[], int count, int senderAccountNumber, int receiverAccountNumber) {
    int senderIndex = -1;
    int receiverIndex = -1;

    for (int i = 0; i < count; i++) {
        if (customers[i].accountNumber == senderAccountNumber) {
            senderIndex = i;
        } else if (customers[i].accountNumber == receiverAccountNumber) {
            receiverIndex = i;
        }

        if (senderIndex != -1 && receiverIndex != -1) {
            break;
        }
    }

    if (senderIndex == -1) {
        printf("Sender with account number %d not found.\n", senderAccountNumber);
        return;
    }

    if (receiverIndex == -1) {
        printf("Receiver with account number %d not found.\n", receiverAccountNumber);
        return;
    }

    int pin;
    printf("Enter your PIN: ");
    scanf("%d", &pin);

    if (customers[senderIndex].pin != pin) {
        printf("Incorrect PIN. Transfer failed.\n");
        return;
    }

    float amount;
    printf("Enter the amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Transfer failed.\n");
        return;
    }

    if (customers[senderIndex].balance < amount) {
        printf("Insufficient balance. Transfer failed.\n");
        return;
    }

    customers[senderIndex].balance -= amount;
    customers[receiverIndex].balance += amount;

    printf("Transfer successful.\n");

    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Sender Account Number: %d, Receiver Account Number: %d, Amount: %.2f\n", senderAccountNumber, receiverAccountNumber, amount);

    fclose(file);
}

void generateSortedTextFile(struct Customer customers[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Name\t\tAccountNumber\tBalance\tContactNumber\tServiceRegion\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%12d\t%7.2f\t%s\t%s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
    }

    fclose(file);
    printf("Text file generated successfully.\nPlease handle it carefully. It contains Sensitive data\n");
}

void generateListByServiceRegion(struct Customer customers[], int count, const char *serviceRegion) {
    FILE *file = fopen("listByServiceRegion.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "Name\t\tAccountNumber\tBalance\tContactNumber\tServiceRegion\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].serviceRegion, serviceRegion) == 0) {
            fprintf(file, "%s\t%12d\t%7.2f\t%s\t%s\n", customers[i].name, customers[i].accountNumber, customers[i].balance, customers[i].contactNumber, customers[i].serviceRegion);
        }
    }

    fclose(file);
    printf("Text file generated successfully.\nPlease handle it carefully. It contains Sensitive data\n");
}
void printAllAccounts(struct Customer customers[], int count) {
    printf("All Customer Accounts:\n");
    printf("Name\t\tAccount Number\tBalance\tContact Number\tService Region\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t%12d\t%7.2f\t%s\t%s\n", customers[i].name, customers[i].accountNumber, customers[i].balance,
               customers[i].contactNumber, customers[i].serviceRegion);
    }
}


int main() {
    struct Customer customers[MAX_CUSTOMERS];
    int count = 0;

    int readStat = readData(customers, &count);
    if (readStat == 1)
    {
        int writeStat = writeData(customers, count);
    }

    while (1) {
        printf("\n****************Bank Management System Menu:****************\n");
        printf("\t\t1. Add Customer\n");
        printf("\t\t2. Sort Data Alphabetically by Name\n");
        printf("\t\t3. Sort Data by Account Number\n");
        printf("\t\t4. Search Customer by Account Number\n");
        printf("\t\t5. Delete Customer by Account Number\n");
        printf("\t\t6. Edit Customer Information\n");
        printf("\t\t7. Change Password\n");
        printf("\t\t8. Transfer Money\n");
        printf("\t\t9. Generate Sorted Text File\n");
        printf("\t\t10. Generate List of Customers by Service Region\n");
        printf("\t\t11. Show all accounts\n");
        printf("\t\t12. Exit\n\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (count >= MAX_CUSTOMERS) {
                    printf("Maximum number of customers reached.\n");
                } else {
                    printf("\tEnter customer name: ");
                    scanf("%s", customers[count].name);
                    printf("\tEnter contact number: ");
                    scanf("%s", customers[count].contactNumber);
                    printf("\tEnter service region: ");
                    scanf("%s", customers[count].serviceRegion);
                    printf("\tEnter initial balance: ");
                    scanf("%f", &customers[count].balance);

                    char pinInput[10];
                    printf("Set a PIN (leave blank to use last 3 digits of contact number): ");
                    scanf("%s", pinInput);
                    customers[count].pin = atoi(pinInput);

                    customers[count].accountNumber = 1070000 + count;
                    count++;

                    printf("Customer added successfully.\n");
                }
                break;
            case 2:
                sortDataAlphabetically(customers, count);
                break;
            case 3:
                sortDataByAccountNumber(customers, count);
                break;
            case 4:
                printf("Enter account number: ");
                int accountNumber;
                scanf("%d", &accountNumber);
                searchData(customers, count, accountNumber);
                break;
            case 5:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                deleteData(customers, &count, accountNumber);
                break;
            case 6:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                editData(customers, count, accountNumber);
                break;
            case 7:
                changePassword();
                break;
            case 8:
                printf("Enter sender account number: ");
                int senderAccountNumber;
                scanf("%d", &senderAccountNumber);
                printf("Enter receiver account number: ");
                int receiverAccountNumber;
                scanf("%d", &receiverAccountNumber);
                transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                break;
            case 9:
                printf("Generate sorted text file by:\n");
                printf("1. Name\n");
                printf("2. Deposit\n");
                printf("3. Service Region\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);

                switch (sortChoice) {
                    case 1:
                        sortDataAlphabetically(customers, count);
                        generateSortedTextFile(customers, count, "sortedByName.txt");
                        break;
                    case 2:
                        sortDataByDeposit(customers, count);
                        generateSortedTextFile(customers, count, "sortedByDeposit.txt");
                        break;
                    case 3:
                        printf("Enter service region: ");
                        char serviceRegion[100];
                        scanf("%s", serviceRegion);
                        generateListByServiceRegion(customers, count, serviceRegion);
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            case 10:
                printf("Enter service region: ");
                char serviceRegion[100];
                scanf("%s", serviceRegion);
                generateListByServiceRegion(customers, count, serviceRegion);
                break;
            case 11:
                printAllAccounts(customers, count);
                break;
            case 12:
                printf("Exiting the program............!!!\n");
                writeData(customers, count);
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
