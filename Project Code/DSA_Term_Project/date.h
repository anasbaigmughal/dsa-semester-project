#pragma once

#include<iostream>
using namespace std;
class date
{
public:
	int day, month, year; //date variables
public:
	date(void);
	void getInput(); //to get input date
	void displayDate(); //to display date
};