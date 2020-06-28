#pragma once
#include "fstream"
#include "date.h"
#include "string"
#include "transactionNode.h"
#include "string.h"
#include <iostream>
using namespace std;

class transaction
{
public:
	transactionNode *head;
public:
	transaction(void); //constructor
	void setZero(string username, string password); //set all values of new user to zero
	void getAmount(string, string, int); //function to get input about transaction details from user
	void displayTransaction(string); //to display transactions  with respect to user's choice time period
	void finalBalance(string); //to display final balance in account
	transactionNode* fileToList(string);  //converts file data to linked list
	void generateReport(string); //to generate textual report of transactions
	void summary(string);
};

