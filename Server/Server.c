#include "Server.h"
#include <string.h>
static uint8_t sequence=0;
ST_accountsDB_t accountsDB[255] = { { 4000.0, RUNNING,"4847352989263094" },
{ 15000.0, RUNNING, "3379513561108795" }, {
    9000.0, BLOCKED, "5181975718047403" }, { 2000.0, RUNNING,
    "8989374615436851" }, { 100000.0, BLOCKED, "5807007076043875" }
,{5000.0,RUNNING,"5807007076043875"},{5000.0,BLOCKED,"9009997076043875"},
{9800.0,BLOCKED,"2307007076044444"},{8900.0,RUNNING,"8956997076043875"}};
ST_transaction_t trans [255] ;

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	uint8_t counter;
	for(counter=0 ; counter<255 ; counter++)
	{
		if (strcmp(accountsDB[counter].primaryAccountNumber,cardData->primaryAccountNumber)==0)
		{
			accountRefrence->balance=accountsDB[counter].balance;
			strcpy(accountRefrence->primaryAccountNumber,accountsDB[counter].primaryAccountNumber);
			accountRefrence->state=accountsDB[counter].state;
			return SERVER_OK ;
		}
	}
	accountRefrence=(void*)0;
	return ACCOUNT_NOT_FOUND ;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	uint8_t counter;
		for(counter=0 ; counter<255 ; counter++)
		{
			if (strcmp(accountsDB[counter].primaryAccountNumber,accountRefrence->primaryAccountNumber)==0)
			{
				if(accountsDB[counter].state== BLOCKED)
					return BLOCKED_ACCOUNT;
				return SERVER_OK;
			}
		}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
		return LOW_BALANCE;
	return SERVER_OK;
}


static void copyTransaction(ST_transaction_t *destin,
        ST_transaction_t *sourceTrans) {
    strcpy(destin->cardHolderData.cardExpirationDate,
            sourceTrans->cardHolderData.cardExpirationDate);

    strcpy(destin->cardHolderData.cardHolderName,
            sourceTrans->cardHolderData.cardHolderName);

    strcpy(destin->cardHolderData.primaryAccountNumber,
            sourceTrans->cardHolderData.primaryAccountNumber);

    strcpy(destin->terminalData.transactionDate,
            sourceTrans->terminalData.transactionDate);

    destin->terminalData.maxTransAmount =
            sourceTrans->terminalData.maxTransAmount;

    destin->terminalData.transAmount =
            sourceTrans->terminalData.transAmount;

    destin->transactionSequenceNumber =
            sourceTrans->transactionSequenceNumber;

   destin->transState = sourceTrans->transState;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
	if(sequence>=255)
		return SAVING_FAILED;
	copyTransaction( &trans[sequence], transData);
	sequence++;
	return SERVER_OK;
}
void printTransaction(ST_transaction_t *transData) {
		printf("#########################");
		printf("%s%d\n", "Transaction Sequence Number: ",
	    transData->transactionSequenceNumber);
	    printf("%s%s\n", "Transaction date: ",
	    transData->terminalData.transactionDate);
	    printf("%s%.2f\n", "Transaction amount: ",
	    transData->terminalData.transAmount);
	    switch (transData->transState)
	    {
	    	    case APPROVED:
	    	        printf("%s%s\n", "Transaction State: ", "Approved");
	    	        break;
	    	   case DECLINED_STOLEN_CARD:
	    	        printf("%s%s\n", "Transaction State: ", "Declined stolen card");
	    	        break;
	    	   case DECLINED_INSUFFECIENT_FUND:
	    	        printf("%s%s\n", "Transaction State: ", "Insufficient fund");
	    	        break;
	    	    case FRAUD_CARD:
	    	        printf("%s%s\n", "Transaction State: ", "Fraud Card");
	    	        break;
	     }
	    printf("%s%.2f\n", "Terminal Max Amount: ",
	    transData->terminalData.maxTransAmount);
	    printf("%s%s\n", "Card holder name: ",
	            transData->cardHolderData.cardHolderName);
	    printf("%s%s\n", "Card PAN: ",
	   	      transData->cardHolderData.primaryAccountNumber);
	    printf("%s%s\n", "Card expiration date: ",
	            transData->cardHolderData.cardExpirationDate);
	}
void listSavedTransactions(void)
{
	uint8_t counter;
	for(counter=0 ; counter<sequence ; counter++)
		printTransaction(&trans[counter]);
}
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	uint8_t state , counter;
	ST_accountsDB_t accountRefrence;
	state= isValidAccount(&(transData->cardHolderData), &accountRefrence);
	if (state==ACCOUNT_NOT_FOUND)
		return FRAUD_CARD;
	state= isAmountAvailable(&transData->terminalData, &accountRefrence);
	if (state==LOW_BALANCE)
		return DECLINED_INSUFFECIENT_FUND;

	state= isBlockedAccount(&accountRefrence);
	if(BLOCKED_ACCOUNT==state)
		return DECLINED_STOLEN_CARD;
	state=saveTransaction(transData);
	if(SAVING_FAILED==state)
		return INTERNAL_SERVER_ERROR ;
	for (counter=0;counter<255;counter++)
		if(strcmp(accountsDB[counter].primaryAccountNumber,transData->cardHolderData.primaryAccountNumber) ==0)
			accountsDB[counter].balance-=transData->terminalData.transAmount;
	return APPROVED;
}
void isValidAccountTest(void)
{
	ST_cardData_t cardData , dummy;

	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  isValidAccount \n");
	printf("Test Case 1: \n");
	getCardPAN(&cardData);
	EN_serverError_t state =isValidAccount (&cardData,&dummy);
	printf("Input Data: %s  \n" ,cardData.primaryAccountNumber);
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	if (state==3)
		printf("Actual Result: ACCOUNT_NOT_FOUND \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	getCardPAN(&cardData);
	 state =isValidAccount (&cardData,&dummy);
	printf("Input Data: %s  \n" ,cardData.primaryAccountNumber);
	printf("Expected Result: SERVER_OK \n");
	if (state==3)
		printf("Actual Result: ACCOUNT_NOT_FOUND \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");}
void isBlockedAccountTest(void)
{
	ST_accountsDB_t data;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  isBlockedAccount \n");
	printf("Test Case 1: \n");
	/*which this pan for running account */
	strcpy(data.primaryAccountNumber,"3379513561108795");
	EN_serverError_t state =isBlockedAccount (&data);
	printf("Input Data: %s  \n" ,data.primaryAccountNumber);
	printf("Expected Result: SERVER_OK \n");
	if (state==5)
		printf("Actual Result: BLOCKED_ACCOUNT \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	/*which this pan for Blocked account */
	strcpy(data.primaryAccountNumber,"2307007076044444");
	 state =isBlockedAccount (&data);
	printf("Input Data: %s  \n" ,data.primaryAccountNumber);
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	if (state==5)
		printf("Actual Result: BLOCKED_ACCOUNT \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");}
void isAmountAvailableTest(void)
{
	ST_terminalData_t termDat ; ST_accountsDB_t accountRefrence;


	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  isAmountAvailable \n");
	printf("Test Case 1: \n");
	/*giving some values for trial*/
	termDat.transAmount=1000;
	accountRefrence.balance=2000;
	EN_serverError_t state =isAmountAvailable (&termDat,&accountRefrence);
	printf("Input Data: %d   %f \n" ,termDat.transAmount,accountRefrence.balance);
	printf("Expected Result: SERVER_OK\n");
	if (state==4)
		printf("Actual Result: LOW_BALANCE \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
		/*giving some values for trial*/
		termDat.transAmount=3000;
		accountRefrence.balance=2000;
		state =isAmountAvailable (&termDat,&accountRefrence);
		printf("Input Data: %d   %f \n" ,termDat.transAmount,accountRefrence.balance);
		printf("Expected Result: LOW_BALANCE\n");
		if (state==4)
			printf("Actual Result: LOW_BALANCE \n");
		if (state==0)
			printf("Actual Result: SERVER_OK  \n");}
void saveTransactionTest(void)
{
	ST_transaction_t transData;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  saveTransaction \n");
	printf("Test Case 1: \n");
	sequence=255;
	EN_serverError_t state =saveTransaction (&transData);
	printf("Input Data: sequence = %d \n",sequence );
	printf("Expected Result: SAVING_FAILED\n");
	if (state==1)
		printf("Actual Result: SAVING_FAILED \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	sequence=12;
	state =saveTransaction (&transData);
	printf("Input Data: sequence = %d \n",sequence );
	printf("Expected Result: SERVER_OK\n");
	if (state==1)
		printf("Actual Result: SAVING_FAILED \n");
	if (state==0)
		printf("Actual Result: SERVER_OK  \n");}
void listSavedTransactionsTest(void)
{
	/*which the list is empty at the begging
	so no data will be printed*/
	listSavedTransactions();
	printf("nothing\n");
	ST_transaction_t transData;
	 saveTransaction(&transData);
	 /* here we added data so the function will
	  work and print */
	listSavedTransactions();
}

