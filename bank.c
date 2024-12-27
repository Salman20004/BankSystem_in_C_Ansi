#include <stdio.h>
#include <string.h>
#define MAX_OPERATIONS 100

typedef struct 
{
    char type;
    double amount;
}Operation;
typedef struct {
    long accountNumber;
    double balance;
    char holderName[50];
    char email[50];

    int numOfOperations;
    Operation operations[MAX_OPERATIONS];

}Account;








//method to add a acount 
int addAccount(){
   Account newAccount;

   printf("enter holderName");
   scanf("%s",&newAccount.holderName);  // note that fgets keeps the \n
   printf("enter email : ");
   scanf("%s",&newAccount.email); 
   
   printf("enter account number : ");
   scanf("%d",&newAccount.accountNumber);
   
   newAccount.balance = 0;
   newAccount.numOfOperations = 0;
    
  

    FILE* f;
    if(f = fopen("accounts.dat","ab+")){
        fseek(f,0,SEEK_END);
        if(fwrite(&newAccount,sizeof(Account),1,f)){
            fclose(f);     
            return 1;
        }else{
            perror("problem accured appending to the file");
            fclose(f);

            return -2;
            
        }

    }else{
        perror("file could not be opened");
        return -1;
    }
}

// we will find the account number specified and update the holder name 
int updateAccount(long accountNumber, const char *newName){
    FILE* f;
    
    Account account;
    
    

    if(f = fopen("accounts.dat","rb+")){
        if(!f){
            return -1;
            perror("empy file");
        }
        
        long size = ftell(f);
        fseek(f,0,SEEK_SET);

        while(fread(&account,sizeof(Account),1,f) == 1){


            if(account.accountNumber == accountNumber ){

                fseek(f,-sizeof(Account),SEEK_CUR); // because fread after reading it goes to next index.... so we have to return back an index
                strncpy(account.holderName,newName,49);
                fwrite(&account,sizeof(Account),1,f);
                fclose(f);
                return 1;
            }
            fseek(f,sizeof(Account),SEEK_CUR);

        }


    }else{
        perror("couldnt open file");
        return -1;
    }

}


void displayAllAccounts(){
    FILE* f;
    
    Account account;

    if(f = fopen("accounts.dat","rb")){
         if(!f){
        
        perror("empy file");
    }
        fseek(f,0,SEEK_SET);
        while(fread(&account,sizeof(Account),1,f) == 1){
            printf("account.holderName : %s  ",account.holderName);
            printf("account.accountNumber : %d  ",account.accountNumber);
            printf("account.email : %s  ",account.email);
            printf("account.balance : %d  ",account.balance);
            printf("account.numOfOperations : %d  ",account.numOfOperations);
        }

        fclose(f);

    }else{
        perror("open file error");
       
    }
    int nameValidation(char holder_name[50]) {

    int i = 0 ; 
    while (holder_name[i] != '\0') {
        if (!isalpha(holder_name[i])) { 
            return 0 ; // if not alpha 
        }
        i++; 
    }
    i = 0 ;
    while (holder_name[i] != '\0')
    holderName[i] = holder_name[i] ; 
     //aplha then intilaize it
    return 1; 
}
    int  emailAddressValidation(char user_email[50]){
int at = 0 ; //@
int dot = 0 ; //.
int i = 0 ; 
        while(user_email[i] != '\0'){
            if(user_email[i] == '@') {
                if(at == 0)
                at = 1; 
                else return 0 ; //if @ was spotted again 

            }
            if(user_email[i] == '.' && at) { // at here confirms that the dot is after the @ 
                dot = 1 ; 
            }
            if((at && dot) && (user_email[i] == '.' || user_email[i] == '@') ) // here if @ and . already in the email then its impossible to have them again in the same mail 
            // example salman@gmail.c@om or salman@gmail.c.om which is not valid but you can have dots in the email like sa.l.ma.n@gamil.com this is acceptable
                return 0 ; 


        }
        if(at && dot ){ // outside the loop , it checks if its valid 
        i = 0 ; 
           while (user_email[i] != '\0')
            email[i] = user_email[i] ; 
            return 1 ; 
        }
        return 0 ; 
    }
 int amountValidation(double user_amount ){
    if(user_amount < 1) return 0 ;  //negative 
    else amount = user_amount ; //positive 

    return 1 ; 
 }

}

