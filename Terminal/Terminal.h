/*
 * Terminal.h
 *
 *  Created on: Oct 18, 2022
 *      Author: Ahmed Gamal
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_
#include "../std_types.h"
#include"../Card/Card.h"
#include <float.h>

typedef struct ST_terminalData_t
{
uint32_t transAmount;
uint32_t maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isBelowMaxAmountTest(void);

#endif /* TERMINAL_TERMINAL_H_ */
