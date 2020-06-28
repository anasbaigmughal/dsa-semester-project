#include "string.h"
#include "date.h"

#pragma once
class transactionNode
{
public:
	int amount; //transaction amount
	int balance; //final balance
	string category; //type of transaction
	string paymentType; //paymentType where transaction made
	date d; //to store date of transaction
	transactionNode *next;
public:
	transactionNode(void);
};