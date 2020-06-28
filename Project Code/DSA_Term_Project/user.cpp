#include "user.h"
#include "string"
#include "transaction.h"
#include "string.h"
#include "fstream"
#include <iostream>
using namespace std;

user::user(void)
{
}

void user::getData(int type)
{
	if( type==1 ) //log in
	{
		bool checkpoint; //flag to check credentials accuracy
		string temp_username; //temporary username variable
		string temp_password; //temporary password variable
		do //loop to get input again and again untill correct username is entered
		{
			checkpoint = false; //flag set to false

			cout<<endl;
			cout<<"Enter Username:"<<endl;
			cin>>temp_username; //username input
			
			cout<<endl<<"Enter Password:"<<endl;
			cin>>temp_password; //password input
			
			ifstream read_file("credentials.txt", ios::binary); //read mode file open which contains login credentials of all users

			for( ;!(read_file.eof()); ) //no initialization or increment statements because there we only check loop with EOF
			{
				read_file.read(reinterpret_cast<char *>(this), sizeof(*this)); //reading credentials file
				if((temp_username == this->username) && (temp_password==this->password)) //it checks either username and password are correct or not
				{
					checkpoint = true; //if username and password are entered correctly
				}
			}

			if(checkpoint ==  false) //if username or password is incorrectly typed
			{
				cout<<"Incorrect USERNAME or PASSWORD!!! TRY AGAIN"<<endl<<endl;
			}
			read_file.close(); //file close
		}
		while(checkpoint == false); //let it get input from user unless correct username and password is entered (i.e. checkpoint=true)

		if(checkpoint == true) //condition when username and password are correctly typed
		{
			this->username = temp_username; //stores username 
			this->password = temp_password; //stores password 
		}
	}
	if( type == 2) //sign up
	{
		bool checkpoint; //flag to check credentials uniqueness
		string temp_username; //stores username temporarily
		string temp_password; //stores password temporarily
		
		do //asks user for username and password untill he enters unique username(i.e. no two users can have similar usernames)
		{
			checkpoint = true; //set flag to false

			cout<<endl;
			cout<<"Enter Username:"<<endl;
			cin>>temp_username; //username input
			
			cout<<endl<<"Enter Password:"<<endl;
			cin>>temp_password; //password input

			ifstream read_file("credentials.txt", ios::binary); //file open read mode to check either entered username is already registered or not
			for( ;!(read_file.eof()); ) //checks for EOF, no intialization or increment statements necassary
			{
				read_file.read(reinterpret_cast<char *>(this), sizeof(*this)); //reads object from file
				if(temp_username == this->username) //if entered username is registered
				{
					cout<<"USERNAME Already Found!!! TRY AGAIN"<<endl<<endl;
					checkpoint = false; //set flag to true
					break;
				}
			}
			read_file.close(); //file close
		}
		while(checkpoint == false); //continues loop till checkpoint is false (i.e. username already registered)

		if(checkpoint == true) //if duplicate username not found
		{
			this->username = temp_username; //stores username
			this->password = temp_password; //stores password
			transaction t; //transaction class object
			t.setZero(this->username, this->password); //this function sets all variables of new user to 0
			ofstream write_file("credentials.txt",ios::binary|ios::app); //file write mode open to save new user login information to file
			write_file.write(reinterpret_cast<char *>(this), sizeof(*this)); //writes object to file
			write_file.close(); //file close
		}
	}
}

string user::getUsername() //get username fucntion
{
	return(username);
}

string user::getPassword() //get password function
{
	return(password);
}