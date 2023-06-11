#include "funcs.h"

int main()
{
    struct Customer customers[MAX_CUSTOMERS];
    int count = 0;
    int readStat = 0;

    pheader();
    while (1)
    {
        int option;
        printf("\n\t1 for User\t\n");
        printf("\t2 for Admin\t\n");
        printf("\n\tPlease enter your choice: ");
        scanf("%d", &option);
        if (option == 2)
        {
            printf("\n");
            readStat = readData(customers, &count);  //password check
            if (readStat == 1)
            {
                int writeStat = writeData(customers, count);
            }
            while (1)
            {
                printf("\n");
                printf("\n\t****************Bank Management System Menu:****************\t\n");
                printf("\t\t1. Add Customer\n");
                printf("\t\t2. Search Customer by Account Number\n");
                printf("\t\t3. Delete Customer by Account Number\n");
                printf("\t\t4. Edit Customer Information\n");
                printf("\t\t5. Change Password\n");
                printf("\t\t6. Transfer Money\n");
                printf("\t\t7. Sort and Generate Text File\n");
                printf("\t\t8. Show all accounts\n");
                printf("\t\t9. Add interests to all customers\n");
                printf("\t\t0. Exit\n\n");
                printf("\tEnter your choice: ");
                int choice;
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    clr();
                    if (count >= MAX_CUSTOMERS)
                    {
                        printf("\tMaximum number of customers reached.\t\n");
                    }
                    else
                    {
                        printf("\tEnter customer name: ");
                        scanf("%s", customers[count].name);
                        printf("\tEnter contact number: ");
                        scanf("%s", customers[count].contactNumber);
                        printf("\tEnter service region: ");
                        scanf("%s", customers[count].serviceRegion);
                        printf("\tEnter initial balance: ");
                        scanf("%f", &customers[count].balance);

                        printf("\tSet a PIN: ");
                        scanf("%s", customers[count].pin);

                        customers[count].accountNumber = 1070000 + count + 1;
                        count++;

                        printf("\tCustomer added successfully.\t\n");
                    }
                    break;
                case 2:
                    clr();
                    printf("\tEnter account number: ");
                    int accountNumber;
                    scanf("%d", &accountNumber);
                    searchData(customers, count, accountNumber);
                    break;
                case 3:
                    clr();
                    printf("\tEnter account number: ");
                    scanf("%d", &accountNumber);
                    deleteData(customers, &count, accountNumber);
                    break;
                case 4:
                    clr();
                    printf("\tEnter account number: ");
                    scanf("%d", &accountNumber);
                    editData(customers, count, accountNumber);
                    break;
                case 5:
                    clr();
                    changePassword();
                    break;
                case 6:
                    clr();
                    printf("\tEnter sender account number: ");
                    int senderAccountNumber;
                    scanf("%d", &senderAccountNumber);
                    printf("\tEnter receiver account number: ");
                    int receiverAccountNumber;
                    scanf("%d", &receiverAccountNumber);
                    transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                    break;
                case 7:
                    clr();
                    printf("\tSort by:\t\n");
                    printf("\t1. Name\n");
                    printf("\t2. Deposit\n");
                    printf("\t3. Account Number\n");
                    printf("\t4. Service Region\n");
                    printf("\tEnter your choice: ");
                    int sortChoice;
                    char generate[4] = "";
                    scanf("%d", &sortChoice);

                    switch (sortChoice)
                    {
                    case 1:
                        sortDataAlphabetically(customers, count);
                        printAllAccounts(customers, count);
                        printf("Enter YES to generate file, anything else to skip file output:\n == ");
                        scanf("%s", generate);
                        if (strcmp(generate,"YES") == 0)
                            generateSortedTextFile(customers, count, "sortedByName.txt");
                        break;
                    case 2:
                        sortDataByDeposit(customers, count);
                        printAllAccounts(customers, count);
                        printf("Enter YES to generate file, anything else to skip file output:\n == ");
                        scanf("%s", generate);
                        if (strcmp(generate,"YES") == 0)
                            generateSortedTextFile(customers, count, "sortedByDeposit.txt");
                        break;
                    case 3:
                        sortDataByAccountNumber(customers, count);
                        printAllAccounts(customers, count);
                        printf("Enter YES to generate file, anything else to skip file output:\n == ");
                        scanf("%s", generate);
                        if (strcmp(generate,"YES") == 0)
                            generateSortedTextFile(customers, count, "sortedByAccountNumber.txt");
                        break;
                    case 4:
                        printf("\tEnter service region: ");
                        char serviceRegion[100];
                        scanf("%s", serviceRegion);
                        generateListByServiceRegion(customers, count, serviceRegion);
                        break;
                    default:
                        printf("\tInvalid choice.\t\n");
                        break;
                    }
                    break;
                case 8:
                    clr();
                    printAllAccounts(customers, count);
                    break;
                case 9:
                    clr();
                    addInterest(customers, count);
                    printAllAccounts(customers, count);
                    break;
                case 0:
                    clr();
                    printf("\n\t**************Exiting the program**************\t\n");
                    printf("\n");
                    writeData(customers, count);
                    printf("\n\t===========================================\t\n");
                    printf("\tThank you for your time and have a good day!\t\n");
                    printf("\t=============================================\t\n");
                    return 0;
                    break;
                } // end of switch case
            } // end while
        } // end of if
        else if (option == 1)
        {
            printf("\n\t****************Banking Menu:****************\t\n");
            printf("Enter account number: ");
            int AccountNumber;
            scanf("%d", &AccountNumber);
            int accIndex = -1;
            for (int i = 0; i < count; i++)
            {
                if (customers[i].accountNumber == AccountNumber)
                {
                    accIndex = i;
                }
                if (accIndex != -1)
                {
                    break;
                }
            }
            if (accIndex == -1)
            {
                printf("Account number didn't match any existing accounts!!\n");
            }
            printf("Enter your pin: ");
            char pin[5];
            scanf("%s", pin);
            if (strcmp(pin, customers[accIndex].pin) != 0)
            {
                printf("Wrong pin!!\n");
                break;
            }

            printf("\n\t\t1. Check Balance\n");
            printf("\t\t2. Transfer Money\n");
            printf("\t\t3. Withdraw Money\n");
            printf("\t\t4. Change your pin\n");
            printf("\t\t0. Exit\n");
            printf("\n\tEnter your choice: ");
            int choice2;
            scanf("%d", &choice2);
            printf("\n");

            switch (choice2)
            {
            case 1:
                printf("Your Balance is $%d\n", customers[accIndex].balance);
                break;
            case 2:
                clr();
                printf("Enter receiver account number: ");
                int receiverAccountNumber;
                scanf("%d", &receiverAccountNumber);
                transferMoney(customers, count, AccountNumber, receiverAccountNumber);
                break;
            case 0:
                printf("\t*************Exiting the program*************\t\n");
                break;
            default:
                printf("\n\tError!\t\n");
                break;
            } // end of switch case
        } // end of else if
    } // end of while
    return 0;
}
