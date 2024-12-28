#include <stdio.h>
#include <string.h>
#include "bank.h"





int main(){
    
   int choice;
   long int accountNo; char newName[100]; char opType; double amount; long int newAccountNo;
    do {
        printf("\n--- Bank Account Management System ---\n");
        printf("1. Add Account\n");
        printf("2. Update Account\n");
        printf("3. Delete Account\n");
        printf("4. Delete Holder Accounts\n");
        printf("5. Search Account\n");
        printf("6. Add Operation\n");
        printf("7. Display All Accounts\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // Clear the newline character left by scanf
        while (getchar() != '\n');

        switch (choice) {
            case 1:         
                addAccount(); 
                break;
            case 2:
                printf("Enter the account number: ");
                scanf("%ld", &accountNo);
                 // Clear the newline character left by scanf
                while (getchar() != '\n');
                printf("1. Change the holder name only\n");
                printf("2. Change the account number only\n");
                printf("3. Both \n");
                printf("your choice: ");
                int updateChoice;

                scanf("%d", &updateChoice);
                 // Clear the newline character left by scanf
                while (getchar() != '\n');


                switch (updateChoice)
                {
                case 1:
                    printf("Enter the new holder name: ");
                    fgets(newName, sizeof(newName), stdin);

                    // Remove the trailing newline character from the input
                    size_t len = strlen(newName);
                    if (len > 0 && newName[len - 1] == '\n') {
                        newName[len - 1] = '\0';
                    }


                    updateAccount(accountNo, -1 , newName); // change only the holder name 
                    break;
                case 2:
                    printf("Enter the new account number: ");
                    scanf("%ld", &newAccountNo);

                    // Clear the newline character left by scanf
                    while (getchar() != '\n');
                    updateAccount(accountNo, newAccountNo , NULL); // change only the account number
                    break;
                case 3: 
                    printf("Enter the new account number: ");
                    scanf("%ld", &newAccountNo);
                    while(getchar() != '\n');
                    printf("Enter the new holder name: ");
                    fgets(newName, sizeof(newName), stdin);

                    // Remove the trailing newline character from the input
                    len = strlen(newName);
                    if (len > 0 && newName[len - 1] == '\n') {
                        newName[len - 1] = '\0';
                    }
                    updateAccount(accountNo, newAccountNo , newName); // change both
                    break; 
                default:
                    printf("Invalid choice.");
                    break;
                }
                break;
            case 3: 
                printf("Enter the account number: ");
                scanf("%ld", &accountNo);
                while (getchar() != '\n');
                deleteAccount(accountNo); 
                break;
            case 4:
                printf("Enter the holder name: ");
                fgets(newName, sizeof(newName), stdin);

                // Remove the trailing newline character from the input
                size_t len = strlen(newName);
                if (len > 0 && newName[len - 1] == '\n') {
                    newName[len - 1] = '\0';
                }
                deleteHolderAccounts(newName);
                break;
            case 5: 
                {
                    FILE* f = fopen("accounts.dat","rb");
                    printf("Enter the account number: ");
                    scanf("%ld", &accountNo);
                    if(searchForAccount(f, accountNo , doPrint) == NULL){
                        printf("Account not found.");
                    }
                }
                
                break;
            case 6: 
                printf("Enter the account number: ");
                scanf("%ld", &accountNo);
                while (getchar() != '\n');
                printf("Enter the Operation type (W for withdraw , D for deposit): ");
                opType = getchar();
                printf("Enter the amount number: ");
                scanf("%lf", &amount);
                while (getchar() != '\n');
                addOperation(opType,amount,accountNo); 
                break; 
            case 7: displayAllAccounts(); break;
            case 0: printf("Exiting the program.\n"); break; 
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);






    return 0;
}