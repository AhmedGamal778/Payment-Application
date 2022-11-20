/*
 * Card.h
 *
 *  Created on: Oct 18, 2022
 *      Author: Ahmed Gamal
 */


#ifndef CARD_CARD_H_
#define CARD_CARD_H_
#include "../std_types.h"

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
void getCardExpiryDateTest(void);
void getCardPANTest(void);
void getCardHolderNameTest(void);
#endif /* CARD_CARD_H_ */
