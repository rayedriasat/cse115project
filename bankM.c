// All the useful functions are added in a separate header file funcs.h
// for better code management
#include "funcs.h"

int main()
{
    struct Customer customers[MAX_CUSTOMERS]; // declaring a struct variable to operate on the data
    int count = 0; // initially before reading from file, setting count to 0
    int readStat = 0; // for tracking if the file was read successfully or not

    pheader(); // for style purpose, this function is called in many lines, avoiding repeating same code again and again
    while (1)
    {
        int option;
        printf("\n\t1 for User\t\n");
        printf("\t2 for Admin\t\n");
        printf("\n\tPlease enter your choice: ");
        scanf("%d", &option);
        if (option == 2)
        {
            // ADMIN mode
            printf("\n");
            readStat = readData(customers, &count);  // password check & reading all data from file
            if (readStat == 1)
            {
                int writeStat = writeData(customers, count);
            }
            while (1)
            {
                // clear previous things on console and print a beautiful header
                clr();
                pheader();

                // The menu options for admin mode
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
                    pheader();
                    if (count >= MAX_CUSTOMERS)
                    {
                        printf("\tMaximum number of customers reached.\t\n");
                    }
                    else
                    {
                        // used fflush for avoiding issues with newline characters in input stream
                        fflush(stdin);
                        printf("\tEnter customer name: ");

                        // used fgets to take name input
                        fgets(customers[count].name, 100, stdin);
                        // replacing the newline character at the end with null character
                        customers[count].name[strlen(customers[count].name) - 1] = '\0';

                        printf("\tEnter contact number: ");
                        fflush(stdin);
                        scanf("%s", customers[count].contactNumber);
                        printf("\tEnter service region: ");
                        fflush(stdin);
                        scanf("%s", customers[count].serviceRegion);
                        printf("\tEnter initial balance: ");
                        fflush(stdin);
                        scanf("%f", &customers[count].balance);
                        fflush(stdin);
                        printf("\tSet a PIN: ");
                        scanf("%s", customers[count].pin);
                        fflush(stdin);

                        /*
                        tracking last added Account number and incrementing that to
                        generate an unique Account number for new customer.
                        Couldn't rely on count variable for this, Cause we need to generate new
                        AC no, if we delete a user, then the count variable becomes unusable
                        for generating unique AC no.
                        */
                        int maxACno = 1070000, i;
                        for (i = 0; i < count; i++)
                        {
                            if (customers[i].accountNumber > maxACno)
                            {
                                maxACno = customers[i].accountNumber;
                            }
                        }
                        customers[count].accountNumber = maxACno + 1;
                        count++;

                        printf("\tCustomer added successfully.\t\n");
                    }
                    getch(); // used getch() to hold the screen content before refreshing
                    break;
                case 2:
                    clr();
                    pheader();
                    printf("\tEnter account number: ");
                    int accountNumber;
                    scanf("%d", &accountNumber);
                    searchData(customers, count, accountNumber);
                    getch();
                    break;
                case 3:
                    clr();
                    pheader();
                    printf("\tEnter account number: ");
                    scanf("%d", &accountNumber);
                    deleteData(customers, &count, accountNumber);
                    getch();
                    break;
                case 4:
                    clr();
                    pheader();
                    printf("\tEnter account number: ");
                    scanf("%d", &accountNumber);
                    fflush(stdin);
                    editData(customers, count, accountNumber);
                    getch();
                    break;
                case 5:
                    clr();
                    pheader();
                    changePassword();
                    getch();
                    break;
                case 6:
                    clr();
                    pheader();
                    printf("\tEnter sender account number: ");
                    int senderAccountNumber;
                    scanf("%d", &senderAccountNumber);
                    printf("\tEnter receiver account number: ");
                    int receiverAccountNumber;
                    scanf("%d", &receiverAccountNumber);
                    transferMoney(customers, count, senderAccountNumber, receiverAccountNumber);
                    getch();
                    break;
                case 7:
                    clr();
                    pheader();
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
                    getch();
                    break;
                case 8:
                    clr();
                    pheader();
                    printAllAccounts(customers, count);
                    getch();
                    break;
                case 9:
                    clr();
                    pheader();
                    addInterest(customers, count);
                    printAllAccounts(customers, count);
                    getch();
                    break;
                case 0:
                    clr();
                    pheader();
                    printf("\n\t=/===================Exiting the program===================/=\t\n");
                    printf("\n");
                    writeData(customers, count);
                    printf("\n\n\n\n\n\n\n\n\t=+=========================================================+=\t\n");
                    printf("\t\tThank you for your time and have a good day!\n");
                    printf("\t=+=========================================================+=\t\n");
                    return 0;
                    break;
                }
            }
        }
        else if (option == 1)
        {
            // USER mode
            clr();
            pheader();
            readDataUser(customers, &count); // only reading data, not asking for passwords
            printf("\n\n\t************************Banking Menu:************************\t\n");
            printf("\n\tEnter account number: ");
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
                break;
            }
            printf("\tEnter your pin: ");
            char pin[5];
            scanf("%s", pin);
            if (strcmp(pin, customers[accIndex].pin) != 0)
            {
                printf("Wrong pin!!\n");
                break;
            }
            while (1)
            {
                clr();
                pheader();
                printf("\n\t\t1. Check Balance\n");
                printf("\t\t2. Transfer Money\n");
                printf("\t\t3. Add money\n");
                printf("\t\t4. Withdraw Money\n");
                printf("\t\t5. Change your pin\n");
                printf("\t\t0. Exit\n");
                printf("\n\tEnter your choice: ");
                int choice2;
                scanf("%d", &choice2);
                printf("\n");

                switch (choice2)
                {
                case 1:
                    clr();
                    pheader();
                    printf("\n\tYour Balance is $%.2f\n", customers[accIndex].balance);
                    getch();
                    break;
                case 2:
                    clr();
                    pheader();
                    printf("\n\tEnter receiver account number: ");
                    int receiverAccountNumber;
                    scanf("%d", &receiverAccountNumber);
                    transferMoney(customers, count, AccountNumber, receiverAccountNumber);
                    getch();
                    break;
                case 3:
                    clr();
                    pheader();
                    float add;
                    printf("\tEnter amount you wanna add: ");
                    scanf("%f", &add);
                    customers[accIndex].balance += add;
                    printf("\n\tAdd Money Successful!\n\n\tYour new balance is: $%.2f\n\n", customers[accIndex].balance);
                    getch();
                    break;
                case 4:
                    clr();
                    pheader();
                    float withdraw;
                    printf("\tEnter amount to withdraw: ");
                    scanf("%f", &withdraw);
                    printf("\tEnter pin: ");
                    scanf("%s", pin);
                    if (strcmp(pin, customers[accIndex].pin) == 0)
                    {
                        if (customers[accIndex].balance >= withdraw) // check if the account has enough balance for withdrawal
                        {
                            customers[accIndex].balance -= withdraw;
                            printf("\n\tWithdrawal Successful!\n\nYour new balance is: $%.2f\n\n", customers[accIndex].balance);
                        }
                        else
                        {
                            printf("\n\tNot enough balance!\n\n\tBalance: %.2f\n", customers[accIndex].balance);
                        }
                    }
                    else
                    {
                        printf("\n\tWrong pin!! Withdrawal denied!!!\n\n");
                    }
                    getch();
                    break;
                case 5:
                    clr();
                    pheader();
                    printf("Enter current pin: ");
                    scanf("%s", pin);
                    if (strcmp(pin, customers[accIndex].pin) == 0)
                    {
                        printf("Enter new pin: ");
                        scanf("%s", customers[accIndex].pin);
                        printf("\n\n\tPin changed successfully!\n\n");
                    }
                    else
                    {
                        printf("Wrong pin!!\n\n");
                    }
                    getch();
                    break;
                case 0:
                    clr();
                    pheader();
                    printf("\n\t=/===================Exiting the program===================/=\t\n");
                    printf("\n");
                    writeData(customers, count); // Saving data before quitting
                    printf("\n\n\n\n\n\n\n\n\t=+=========================================================+=\t\n");
                    printf("\t\tThank you for your time and have a good day!\n");
                    printf("\t=+=========================================================+=\t\n");
                    return 0;
                    break;
                default:
                    printf("\n\tError!\t\n");
                    break;
                }
            }
        }
    }
    return 0;
}
