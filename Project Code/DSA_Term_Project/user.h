#pragma once
#include "string.h"
#include <iostream>
using namespace std;

class user
{
public:
	string username, password; //to store login credentials
public:
	user(void);
	void getData(int); //to get login credentials rom user
	string getUsername(); //get username function
	string getPassword(); //get password function
};

