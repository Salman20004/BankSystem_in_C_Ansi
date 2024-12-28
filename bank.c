#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bank.h"

#define MAX_OPERATIONS 100




//method to add a acount 
int addAccount(){
     



   Account *newAccount = (Account*)malloc(sizeof(Account));//refering to a specific memory
   if(newAccount == NULL){
    perror("memmory allocation failed");
    return -1;
   }

   printf("enter holderName : ");
   scanf("%s",newAccount->holderName);
   while(getchar() != '\n'); 
   if(!nameValidation(newAccount->holderName)){
     free(newAccount);
     perror("validation problem ");
     return -1;
   }

   printf("enter email : ");
   scanf("%s",newAccount->email);
   while(getchar() != '\n'); 
   if(!emailAddressValidation(newAccount->email)){
        perror("validation error");
        return -1;

   }
   printf("enter account number : ");
   scanf("%ld", &newAccount->accountNumber);
    
    FILE *d = fopen("accounts.dat","rb");
    
   // cheack if account is already exist, when searchForAccount returns null that means the account does not exist ( not repeated )  
   if(searchForAccount(d , newAccount->accountNumber , dontPrint) != NULL){
        printf("Account is already exist"); 
        fclose(d);
        return -3; }
   
   newAccount->balance = 0;
   newAccount->numOfOperations = 0;
    fclose(d);

    FILE* f;

    
  

    if(f = fopen("accounts.dat","ab+")){

        
        if(fwrite(newAccount,sizeof(Account),1,f) != 1){
            fclose(f);     
            free(newAccount);
            perror("problem writing the account");
            return 1;
        }
        free(newAccount);
        fclose(f);
        printf("account added successfully\n");

    }else{
        perror("file could not be opened");
         free(newAccount);
        fclose(f);
        return -1;
       
    }
}

// we will find the account number specified and update the holder name 
int updateAccount(long accountNumber, long newAccountNumber, char *newName) {
   FILE* f = fopen("accounts.dat","rb+");
    if (!f) {
        perror("Could not open file");
        return -1; 
    }
    if(!nameValidation(newName)){
        perror("wrong name validation");
        fclose(f);
        return -1;
    }
    // cheack if account is already exist, when searchForAccount returns null that means the account does not exist ( not repeated )  
    if(searchForAccount(f,newAccountNumber,dontPrint) != NULL){
        printf("There is another account with %ld as an account number" , newAccountNumber);
        fclose(f);
        return -2;
    }

    Account *account = searchForAccount(f, accountNumber, dontPrint);
    if (account == NULL) {
        printf("Account not found.\n");
        fclose(f);
        return -3; 
    }
    


    // Update account number if a valid new account number is provided
    if (newAccountNumber != -1) {
        account->accountNumber = newAccountNumber;
    }

    // Update holder name if a valid new name is provided
    if (newName != NULL) {
        strncpy(account->holderName, newName, sizeof(account->holderName) - 1);
        account->holderName[sizeof(account->holderName) - 1] = '\0'; // Ensure null-termination
    }

    fwrite(account, sizeof(Account), 1, f);
    printf("Account updated successfully.\n");
    fclose(f);
    
    return 1; 
}
void displayAllAccounts(){
    FILE* f;
    f = fopen("accounts.dat","rb");
    if(f==NULL){
        perror("OPENNING FILE");
        return;
    }
    
    
    Account *account = (Account*)malloc(sizeof(Account));
    if(account == NULL){
        perror("memory allocation failed");
        fclose(f);
        
    }


        printf("============================================================\n");
        printf("==================displaying all accounts===================\n");

    
        fseek(f,0,SEEK_SET);
        while(fread(account,sizeof(Account),1,f) == 1){
            printf("HolderName: %s  ",account->holderName);
            printf("Account Number: %d  ",account->accountNumber);
            printf("Email: %s  ",account->email);
            printf("Balance: %.2lf  ",account->balance);
            printf("Number of operations: %d  \n",account->numOfOperations);
        }
        free(account);
        fclose(f);

  
}



int nameValidation(char *holder_name) {

    int i = 0 ; 
    while (holder_name[i] != '\0') {
        if (!isalpha(holder_name[i])) { 
            perror("invalid format ");

            return 0 ; // if not alpha 
        }
        i++; 
    }
  
    return 1; 
}

int emailAddressValidation(char *user_email) {
    if (user_email == NULL) {
        perror("Email is NULL");
        return 0;
    }

    int at = 0;  // @
    int dot = 0; // .
    int i = 0;

    while (user_email[i] != '\0') {
         if ((at==1 && dot==1) && (user_email[i] == '@' || user_email[i] == '.')) {
            // @ found after we already have both @ and .
            perror("Invalid email format: @ or .  after dot");
            return 0;
        }
        if (user_email[i] == '@') {
            if (at == 0) {
                at = 1;
            } else {
                perror("Multiple @ symbols found");
                return 0;
            }
        }
        
        if (user_email[i] == '.' && at) {
            // Dot after @ found
            dot = 1;
        }



        i++;  // Increment moved outside conditions
    }

    if (!(at && dot)) {
        perror("Email must contain both @ and . symbols");
        return 0;
    }

    return 1;
}

 int amountValidation(double user_amount ){
    if(user_amount <= 0){
        perror("must be positive"); return 0 ;  //negative 
    }else return 1;
    

   
 }


Account* searchForAccount(FILE* f , long int accountNo, int printStatus) {
    Account *account = (Account*)malloc(sizeof(Account));  // Static memory for returning a pointer
    rewind(f);  // Ensure the file pointer starts at the beginning
    while (fread(account, sizeof(Account), 1, f) == 1) {
        if (account->accountNumber == accountNo) {
            // File pointer is positioned correctly for updating
            fseek(f, -(long)sizeof(Account), SEEK_CUR);

            if (printStatus) {
               printf("HolderName: %s  ",account->holderName);
               printf("Account Number: %d  ",account->accountNumber);
               printf("Email: %s  ",account->email);
               printf("Balance: %.2lf  ",account->balance);
               printf("Number of operations: %d  \n",account->numOfOperations);
            }
           
            return account; 
        }
    }
    // Account not found
    return NULL;  
}
int deleteHolderAccounts(char* holder_name){
    FILE* f = fopen("accounts.dat", "rb");
    if (f == NULL) {
        perror("No file found");
        return -1;
    }

    Account *account = (Account*)malloc(sizeof(Account));
    if (account == NULL) {
        printf("Memory allocation failed ");
        fclose(f);
        return -1;
    }

    FILE* tmp = fopen("temp.dat", "wb");
    if (tmp == NULL) {
        perror("Cannot open temporary file");
        free(account);
        fclose(f);
        return -2;
    }
    int found = 0;

    while(fread(account,sizeof(Account),1,f) == 1){


        if(strcmp(account->holderName,holder_name) !=0){
            if(fwrite(account,sizeof(Account),1,tmp) != 1){
                printf("error adding to tmp");
                return -1;
            }

        }else found = 1;
    }
    
    fclose(f);
    fclose(tmp);
    free(account);

    if (!found) {
        printf("Account not found\n");
        remove("temp.dat");  
        return -5;
    }

    // Remove the original file
    if (remove("accounts.dat") != 0) {
        perror("Error deleting original file");
        return -6;
    }

    // Rename the temporary file to the original file name
    if (rename("temp.dat", "accounts.dat") != 0) {
        perror("Error renaming temporary file");
        return -7;
    }

    printf("Accounts deleted successfully!\n");
    return 1;





}



int deleteAccount(long accountNumber) {
    FILE* f = fopen("accounts.dat", "rb");
    if (f == NULL) {
        perror("No file found");
        return -1;
    }
    
    Account *account = (Account*)malloc(sizeof(Account));
    if (account == NULL) {
        printf("Memory allocation failed ");
        fclose(f);
        return -1;
    }
    
    FILE* tmp = fopen("temp.dat", "wb");
    if (tmp == NULL) {
        perror("Cannot open temporary file");
        free(account);
        fclose(f);
        return -2;
    }
    
    int found = 0;

    while (fread(account, sizeof(Account), 1, f) == 1) {
        if (account->accountNumber != accountNumber) {
            // Write to the temporary file
            if (fwrite(account, sizeof(Account), 1, tmp) != 1) {
                printf("Couldn't write to temporary file");
                free(account);
                fclose(tmp);
                fclose(f);
                return -1;
            }
        } else {
            found = 1; // Account found, do not write it to the temp file
        }
    }

    fclose(f);
    fclose(tmp);
    free(account);

    if (!found) {
        printf("Account not found\n");
        remove("temp.dat");  
        return -5;
    }

    // Remove the original file
    if (remove("accounts.dat") != 0) {
        perror("Error deleting original file");
        return -6;
    }

    // Rename the temporary file to the original file name
    if (rename("temp.dat", "accounts.dat") != 0) {
        perror("Error renaming temporary file");
        return -7;
    }

    printf("Account deleted successfully!\n");
    return 1;
}




int addOperation(char opType, double amount, long int accountNo) {
    FILE *f = fopen("accounts.dat", "rb+");
    if (f == NULL) {
        perror("Error opening file");
        return -1;
    }

    if(!amountValidation(amount)){perror("invalid amound "); return -1;}
    

    // Use searchForAccount to get the desired account and make the pointer in the right place for writing
    Account *account = searchForAccount(f,accountNo, dontPrint);  // Don't print account details
    if (account == NULL) {
        printf("Error: Account with number %ld not found.\n", accountNo);
        fclose(f);
        return -6;
    }


    if (opType != 'D' && opType != 'd' && opType != 'W' && opType != 'w') {
        printf("Error: Invalid operation type '%c'. Use 'D' for deposit or 'W' for withdrawal.\n", opType);
        fclose(f);
        return -2;
    }

    if (opType == 'D' || opType == 'd') {
        account->balance += amount;  // Deposit
    } else if (opType == 'W' || opType == 'w') {
        if (account->balance >= amount) {
            account->balance -= amount;  // Withdraw
        } else {
            perror("Error: Insufficient balance.\n");
            fclose(f);
            return -3;
        }
    }

    
    if (account->numOfOperations < 100) { 
        Operation op = {opType, amount};
        account->operations[account->numOfOperations++] = op;
    } else {
        perror("Error: Operation list is full.\n");
        fclose(f);
        return -4;
    }

    // Write the updated account back to the file
    if (fwrite(account, sizeof(Account), 1, f) == 1) {
        printf("Operation successfully added. Updated balance: %.2f\n", account->balance);
    } else {
        return 1;
        perror("Error writing to file");

    }

    fclose(f);
}