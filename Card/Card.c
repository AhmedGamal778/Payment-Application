#include <stdio.h>
#include <string.h>
#include"Card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	uint8_t temp;
	printf("Please enter your name");
	fflush(stdout);
	scanf("%s", cardData->cardHolderName);
	temp =strlen(cardData->cardHolderName);
	if( temp==0 || temp <20 ||temp>24 )
		return WRONG_NAME ;
	return OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	printf("Please enter card expiry date");
	fflush(stdout);
	scanf("%s", cardData->cardExpirationDate);
	if(cardData->cardExpirationDate[2]!='/' || strlen(cardData->cardExpirationDate)<0 ||strlen(cardData->cardExpirationDate)>5)
		return WRONG_EXP_DATE;
	return OK;
}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	uint8_t temp;
	printf("Please enter card pan");
	fflush(stdout);
	scanf("%s", cardData->primaryAccountNumber);
	temp =strlen(cardData->primaryAccountNumber);
	if (temp<16 || temp>19)
		return WRONG_PAN;
	return OK;

}
void getCardHolderNameTest(void)
{
	ST_cardData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name: getCardHolderName  \n");
	printf("**********************\n");
	printf("Test Case 1: \n");
	EN_cardError_t state =getCardHolderName (&trial);
	printf("Input Data: %s \n" , trial.cardHolderName);
	printf("Expected Result: WRONG_NAME\n");
	if (state==1)
		printf("Actual Result: WRONG_NAME \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");
	printf("**********************\n");
	printf("Test Case 2: \n");
	state =getCardHolderName (&trial);
	printf("Input Data: %s \n" , trial.cardHolderName);
	printf("Expected Result: CARD_OK\n");
	if (state==1)
		printf("Actual Result: WRONG_NAME \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");
	printf("**********************\n");
	printf("Test Case 3: \n");
	state =getCardHolderName (&trial);
	printf("Input Data: %s \n" , trial.cardHolderName);
	printf("Expected Result: WRONG_NAME\n");
	if (state==1)
		printf("Actual Result: WRONG_NAME \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");

}
void getCardExpiryDateTest(void)
{
	ST_cardData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name: getCardExpiryDate \n");
	printf("\n***********************\n");
	printf("Test Case 1: \n");
	EN_cardError_t state =getCardExpiryDate (&trial);
	printf("Input Data: %s \n" , trial.cardExpirationDate);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state==2)
		printf("Actual Result: WRONG_EXP_DATE \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");

	printf("\n***********************\n");

	printf("Test Case 2: \n");
	 state =getCardExpiryDate (&trial);
	printf("Input Data: %s \n" , trial.cardExpirationDate);
	printf("Expected Result: CARD_OK\n");
	if (state==2)
		printf("Actual Result: WRONG_EXP_DATE \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");

	printf("\n***********************\n");

	printf("Test Case 3: \n");
	 state =getCardExpiryDate (&trial);
	printf("Input Data: %s \n" , trial.cardExpirationDate);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (state==2)
		printf("Actual Result: WRONG_EXP_DATE \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");

}
void getCardPANTest(void)
{
	ST_cardData_t trial;
	printf("Tester Name: Ahmed Gamal \n");
	printf("Function Name: getCardPAN \n");
	printf("\n***********************\n");

	printf("Test Case 1: \n");
	EN_cardError_t state =getCardPAN (&trial);
	printf("Input Data: %s \n" , trial.primaryAccountNumber);
	printf("Expected Result: WRONG_PAN\n");
	if (state==3)
		printf("Actual Result: WRONG_PAN \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");
	printf("\n***********************\n");

	printf("Test Case 2: \n");
	state =getCardPAN (&trial);
	printf("Input Data: %s \n" , trial.primaryAccountNumber);
	printf("Expected Result: CARD_OK\n");
	if (state==3)
		printf("Actual Result: WRONG_PAN \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");
	printf("\n***********************\n");

	printf("Test Case 3: \n");
	state =getCardPAN (&trial);
	printf("Input Data: %s \n" , trial.primaryAccountNumber);
	printf("Expected Result: WRONG_PAN\n");
	if (state==3)
		printf("Actual Result: WRONG_PAN \n");
	if (state==0)
		printf("Actual Result: CARD_OK \n");
}
