#include"Application.h"
#include"../Card/Card.h"
#include"../Server/Server.h"
#include"../Terminal/Terminal.h"
#include <stdio.h>

void appStart(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t terminalData;
	ST_transaction_t transactionData;
	EN_transState_t transactionState;

	if (getCardHolderName(&cardData)==WRONG_NAME)
	{
		printf("Wrong name");
		printf("%s\n", "Transaction Failed");
		return;
	}
	if (getCardExpiryDate(&cardData)==WRONG_EXP_DATE)
		{
			printf("Wrong Expire date");
			printf("%s\n", "Transaction Failed");
			return;
		}
	if (getCardPAN(&cardData)==WRONG_PAN)
			{
				printf("Wrong Pan");
				printf("%s\n", "Transaction Failed");
				return;
			}
	if ( getTransactionDate(&terminalData)==WRONG_DATE)
				{
					printf("Wrong Date");
					printf("%s\n", "Transaction Failed");
					return;
				}
	if ( (isCardExpired(cardData,terminalData))==EXPIRED_CARD)
					{
						printf("Expired card");
						printf("%s\n", "Transaction Failed");
						return;
					}
	if ( setMaxAmount(&terminalData)==INVALID_MAX_AMOUNT)
						{
							printf("INVALID_MAX_AMOUNT");
							printf("%s\n", "Transaction Failed");
							return;
						}
	if ( getTransactionAmount(&terminalData)==INVALID_AMOUNT)
							{
								printf("INVALID_AMOUNT");
								printf("%s\n", "Transaction Failed");
								return;
							}
	if ( isBelowMaxAmount(&terminalData)==EXCEED_MAX_AMOUNT)
								{
									printf("EXCEED_MAX_AMOUNT");
									printf("%s\n", "Transaction Failed");
									return;
								}
	transactionData.cardHolderData = cardData;
	transactionData.terminalData = terminalData;
	transactionState=recieveTransactionData(&transactionData);
	switch(transactionState)
	{
	case FRAUD_CARD:
		printf("%s\n", "This is a Fraud Card.");
					printf("%s\n", "Transaction Failed");
					break;
	case DECLINED_STOLEN_CARD:
					printf("%s\n", "This account is blocked.");
					printf("%s\n", "Transaction Failed");
					break;
	case DECLINED_INSUFFECIENT_FUND:
					printf("%s\n", "Transaction amount is unavailable");
					printf("%s\n", "Transaction Failed");
					break;
	case INTERNAL_SERVER_ERROR:
					printf("%s\n", "Transaction can't be received");
					printf("%s\n", "Transaction Failed");
					break;
	case APPROVED:
					printf("%s\n", "Transaction is done successfully");
					break;


	}


}
