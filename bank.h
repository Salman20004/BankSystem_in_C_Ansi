#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#define MAX_OPERATIONS 100

typedef struct {
   char type;
   double amount;
} Operation;

typedef struct {
   long accountNumber;
   double balance;
   char holderName[50];
   char email[50];
   int numOfOperations;
   Operation operations[MAX_OPERATIONS];
} Account;

typedef enum {
   dontPrint = 0,
   doPrint = 1
} printStatus;

int addAccount();
int updateAccount(long accountNumber, long newAccountNumber, char *newName);
int deleteAccount(long accountNumber);
int deleteHolderAccounts(char* holder_name);
void displayAllAccounts();

int addOperation(char opType, double amount, long int accountNo);

int nameValidation(char *holder_name);
int emailAddressValidation(char *user_email);
int amountValidation(double user_amount);

Account* searchForAccount(FILE* f, long accountNo, int printStatus);

#endif