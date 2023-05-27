#include "funcs.h"

//Ufxx|twi

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
        printf("\t\t4. Sort Data by Balance\n");
        printf("\t\t5. Search Customer by Account Number\n");
        printf("\t\t6. Delete Customer by Account Number\n");
        printf("\t\t7. Edit Customer Information\n");
        printf("\t\t8. Change Password\n");
        printf("\t\t9. Transfer Money\n");
        printf("\t\t10. Sort and Generate Text File\n");
        printf("\t\t11. Generate List of Customers by Service Region\n");
        printf("\t\t12. Show all accounts\n");
        printf("\t\t0. Exit\n\n");
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

                    //char pinInput[10];
                    printf("Set a PIN: ");
                    scanf("%s", customers[count].pin);
                    //customers[count].pin = atoi(pinInput);

                    customers[count].accountNumber = 1070000 + count + 1;
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
                sortDataByDeposit(customers, count);
                break;
            case 5:
                printf("Enter account number: ");
                int accountNumber;
                scanf("%d", &accountNumber);
                searchData(customers, count, accountNumber);
                break;
            case 6:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                deleteData(customers, &count, accountNumber);
                break;
            case 7:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                editData(customers, count, accountNumber);
                break;
            case 8:
                changePassword();
                break;
            case 9:
                printf("Enter sender account number: ");
                int senderAccountNumber;
                scanf("%d", &senderAccountNumber);
                printf("Enter receiver account number: ");
                int receiverAccountNumber;
                scanf("%d", &receiverAccountNumber);
                transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                break;
            case 10:
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
            case 11:
                printf("Enter service region: ");
                char serviceRegion[100];
                scanf("%s", serviceRegion);
                generateListByServiceRegion(customers, count, serviceRegion);
                break;
            case 12:
                printAllAccounts(customers, count);
                break;
            case 0:
                printf("*********Exiting the program............!!!\n");
                writeData(customers, count);
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
