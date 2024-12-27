#include <stdio.h>

#define MAX_OPERATIONS 100 


typedef struct Account account;


//functions that we are implementing on bank.c
int addAccount(Account *acount);
int updateAccount(long accountNumber, const char *newName);
int deleteAccount(long accountNumber);
int deleteHolderAccounts(const char *holderName);
Account *searchAccount(int accountNumber);
void displayAllAccounts();
int AddOperation(long accountNumber,char type,double amount);


int nameValidation(char holderName[50]);
int emailAddressValidation(char email[50]);
int amountValidation(double amount);


