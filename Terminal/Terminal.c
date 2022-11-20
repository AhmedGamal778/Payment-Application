#include <stdio.h>
#include <string.h>
#include"Terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	printf("Please enter the transaction date");
	fflush(stdout);
	scanf("%s", termData->transactionDate);
	if(termData->transactionDate[2]!='/' || termData->transactionDate[5]!='/'||(strlen(termData->transactionDate)!=10))
		return WRONG_DATE ;
	return OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (cardData.cardExpirationDate[4]>= termData.transactionDate[9] )
		if (cardData.cardExpirationDate[4]> termData.transactionDate[9])
			return OK;
		else
			if (cardData.cardExpirationDate[0]>= termData.transactionDate[3] )
				if (cardData.cardExpirationDate[0]> termData.transactionDate[3] )
					return OK;
				else
					if (cardData.cardExpirationDate[1]>= termData.transactionDate[4] )
							return OK;
	return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{

	printf("Please enter the transaction amount");
	fflush(stdout);
	scanf("%d", &termData->transAmount);
	if ((termData->transAmount) <= 0)
		return INVALID_AMOUNT;
	return OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	printf("Please enter the transaction amount");
	fflush(stdout);
	scanf("%d", &termData->transAmount);
	printf("Please enter the max transaction amount");
	fflush(stdout);
	scanf("%d", &termData->maxTransAmount);
	if (termData->transAmount > termData->maxTransAmount )
		return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	printf("Please enter the max amount");
	fflush(stdout);
	scanf("%d", &termData->maxTransAmount);
	if(termData->maxTransAmount<=0)
		return INVALID_MAX_AMOUNT ;
	return TERMINAL_OK;

}
void getTransactionDateTest(void)
{
	ST_terminalData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  getTransactionDate \n");
	printf("Test Case 1: \n");
	EN_terminalError_t state =getTransactionDate (&trial);
	printf("Input Data: %s \n" , trial.transactionDate);
	printf("Expected Result: WRONG_DATE \n");
	if (state==1)
		printf("Actual Result: WRONG_DATE \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	state =getTransactionDate (&trial);
	printf("Input Data: %s \n" , trial.transactionDate);
	printf("Expected Result: TERMINAL_OK\n");
	if (state==1)
		printf("Actual Result: WRONG_DATE \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");

	printf("Test Case 3: \n");
	state =getTransactionDate (&trial);
	printf("Input Data: %s \n" , trial.transactionDate);
	printf("Expected Result: WRONG_DATE\n");
	if (state==1)
		printf("Actual Result: WRONG_DATE \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
}
void isCardExpriedTest(void)
{
	ST_cardData_t cardData; ST_terminalData_t termData;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  isCardExpried \n");
	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);
	printf("Test Case 1: \n");
	EN_terminalError_t state =isCardExpired (cardData,termData);
	printf("Input Data: %s   %s \n" ,cardData.cardExpirationDate,termData.transactionDate);
	printf("Expected Result: EXPIRED_CARD\n");
	if (state==2)
		printf("Actual Result: EXPIRED_CARD \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");
	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);
	printf("Test Case 2: \n");
	 state =isCardExpired (cardData,termData);
	printf("Input Data: %s   %s \n" ,cardData.cardExpirationDate,termData.transactionDate);
	printf("Expected Result: TERMINAL_OK\n");
	if (state==2)
		printf("Actual Result: EXPIRED_CARD \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");
	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);
	printf("Test Case 3: \n");
	state =isCardExpired (cardData,termData);
	printf("Input Data: %s   %s \n" ,cardData.cardExpirationDate,termData.transactionDate);
	printf("Expected Result: EXPIRED_CARD\n");
	if (state==2)
		printf("Actual Result: EXPIRED_CARD \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
}
void getTransactionAmountTest(void)
{
	ST_terminalData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  getTransactionAmount \n");
	printf("Test Case 1: \n");
	EN_terminalError_t state =getTransactionAmount (&trial);
	printf("Input Data: %d \n" , trial.transAmount);
	printf("Expected Result: INVALID_AMOUNT\n");
	if (state==4)
		printf("Actual Result: INVALID_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	state =getTransactionAmount (&trial);
	printf("Input Data: %d \n" , trial.transAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (state==4)
		printf("Actual Result: INVALID_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
}
void isBelowMaxAmountTest(void)
{
	ST_terminalData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  isBelowMaxAmount \n");
	printf("Test Case 1: \n");
	EN_terminalError_t state =isBelowMaxAmount (&trial);
	printf("Input Data: %d   %d\n" , trial.transAmount,trial.maxTransAmount);
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	if (state==5)
		printf("Actual Result: EXCEED_MAX_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	state =isBelowMaxAmount (&trial);
	printf("Input Data: %d   %d\n" , trial.transAmount,trial.maxTransAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (state==5)
		printf("Actual Result: EXCEED_MAX_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");}
void setMaxAmountTest(void)
{
	ST_terminalData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name:  setMaxAmount \n");
	printf("Test Case 1: \n");
	EN_terminalError_t state =setMaxAmount (&trial);
	printf("Input Data: %d   \n" ,trial.maxTransAmount);
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	if (state==6)
		printf("Actual Result: INVALID_MAX_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	state =setMaxAmount (&trial);
	printf("Input Data: %d   \n" ,trial.maxTransAmount);
	printf("Expected Result: TERMINAL_OK\n");
	if (state==6)
		printf("Actual Result: INVALID_MAX_AMOUNT \n");
	if (state==0)
		printf("Actual Result: TERMINAL_OK \n");}

