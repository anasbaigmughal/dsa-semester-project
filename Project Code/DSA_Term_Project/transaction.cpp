#include "transaction.h"
#include "fstream"
#include "string"
#include "conio.h"
#include "iomanip"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

transaction::transaction(void) //constructor
{
	head = new transactionNode;
}

void transaction::setZero(string username, string password)
{
	head->amount = 0; //set to zero
	head->balance = 0; //set to zero
	head->d.day = head->d.month = head->d.year = 0;
	head->next = NULL;

	//below are empty file creation for new user with its username to store final balance
	ofstream username_write(username.c_str(), ios::binary); //file write mode open to store final balance 
	username_write.write(reinterpret_cast<char *>(head), sizeof(*head)); //writes object to file
	username_write.close(); //file close
	
	//below are empty file creation for new user with its password to store all transactions
	ofstream password_write(password.c_str(), ios::binary); //file write mode open to store all transactions
	password_write.write(reinterpret_cast<char *>(head), sizeof(*head)); //writes object to file
	password_write.close(); //file close
}

void transaction::getAmount(string username, string password, int type) //function to get input from user
{
	if( type == 1 ) //income
	{
		transactionNode *ptr = new transactionNode; //node created to add new transaction
		int temp_amount; //temporary amount storing variable

		cout<<"Enter Income Amount:"<<endl;
		cin>>temp_amount; //income amount input
		
		ifstream username_read(username.c_str(), ios::binary); //file open read mode to get final balance
		username_read.read(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //reads object from file
		ptr->balance = ptr->balance + temp_amount; //adds amount to final balance (i.e. updating final balance)
		username_read.close(); //file close

		ptr->amount = temp_amount; //sets amount
		
		cout<<endl<<"Enter Income Category(e.g. gift, holiday, shopping etc.):"<<endl;
		cin>>ptr->category; //transaction type
		
		cout<<endl<<"Enter Income Payment Method:"<<endl;
		cin>>ptr->paymentType; //transaction location
		
		ptr->d.getInput(); //date input
		
		ofstream username_write(username.c_str(), ios::binary); //file write mode open to write final balance reading
		username_write.write(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //writes object to file
		username_write.close(); //file close
		
		//-----------------------Above is work with username.txt file which only has 1 record for final balance------
		//-----------------------Below is work with password.txt file which contains transactions list------
			
		ofstream password_write(password.c_str(), ios::binary|ios::app); //file write mode open to write transactions details
		password_write.write(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //writes object to file
		password_write.close(); //file close
	}
	if(type ==2) //expense
	{
		transactionNode *ptr = new transactionNode; //node created to add new transaction
		int temp_amount; //temporary amount storing variable

		cout<<"Enter Expense Amount:"<<endl;
		cin>>temp_amount; //expense amount input

		temp_amount = (temp_amount * (-1)); //set debit amount to -ve so that when all transactions are displayed user could identify which one is income and which one is expense

		ifstream username_read(username.c_str(), ios::binary); //file read mode open to get final balance
		username_read.read(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //reads object form file

		ptr->balance = ptr->balance + temp_amount; //adds amount to final balance (i.e. updates final balance)
		username_read.close(); //file close

		ptr->amount = temp_amount; //amount set

		cout<<endl<<"Enter Exoense Category(e.g. gift, holiday, shopping etc.):"<<endl;
		cin>>ptr->category; //gets transaction type

		cout<<endl<<"Enter Expense Payment Method:"<<endl;
		cin>>ptr->paymentType; //gets transaction location
		
		ptr->d.getInput(); //gets date input
		
		ofstream username_write(username.c_str(), ios::binary); //file write mode open to store final balance
		username_write.write(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //writes object to file
		username_write.close(); //file close
		
		//-----------------------Above is work with username.txt file which only has 1 record for final balance------
		//-----------------------Below is work with password.txt file which contains transactions list---------------

		ofstream password_write(password.c_str(), ios::binary|ios::app); //file write mode open to store transaction details
		password_write.write(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //writes object to file
		password_write.close(); //file close
		}
}

void transaction::finalBalance(string filename) //to display final balance in account
{
	transactionNode *ptr = new transactionNode;

	ifstream file_read(filename.c_str(), ios::binary); //file read mode open to read final balance
	file_read.read(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //reads object form file

	cout<<endl<<"Account Balance: "<<ptr->balance<<endl; 

	file_read.close(); //file close
}

transactionNode* transaction::fileToList(string filename) //converts file data to linked list
{
	transactionNode *ptr = new transactionNode;
	transactionNode *temp = new transactionNode;
	transactionNode *list = new transactionNode;

	ifstream file_read(filename.c_str(), ios::binary); //file read mode open to read transactions
	
	file_read.read(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //reads object form file
	temp = ptr;
	list = temp;
	
	while(!file_read.eof())
	{
		file_read.read(reinterpret_cast<char *>(ptr), sizeof(*ptr)); //reads object form file
		temp->next = ptr; //connecting each file read data (node) to linked list
		ptr = new transactionNode;
		temp = temp->next;
	}
	temp->next = NULL;

	return list;
}

void transaction::displayTransaction(string filename) //to display transactions  with respect to user's choice time period
{
	int duration;

	cout<<"Select Time Period"<<endl;
	cout<<"1. Last 7 Days."<<endl;
	cout<<"2. Last Month."<<endl;
	cout<<"3. Last 6 Months."<<endl;
	cout<<"4. All."<<endl;
	cin>>duration;


	system("CLS");
	cout<<endl<<"================================================================================";
	HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (  m_hConsole, 
                              BACKGROUND_RED |
                              BACKGROUND_GREEN |
                              BACKGROUND_BLUE );
	std::cout <<"      B A H R I A - U N I V E R S I T Y - S P E N D I N G - T R A C K E R       ";
    SetConsoleTextAttribute ( m_hConsole,
                              FOREGROUND_RED |
                              FOREGROUND_GREEN |
                              FOREGROUND_BLUE );
	cout<<"================================================================================"<<endl;
	transactionNode *temp = fileToList(filename);

	cout<<"================================================================================";
	cout<<"  "<<setw(20)<<left<<"TRANSACTION AMOUNT";
	cout<<setw(16)<<left<<"CATEGORY";
	cout<<setw(14)<<left<<"paymentType";
	cout<<setw(18)<<left<<"FINAL BALANCE";
	cout<<"DATE"<<endl;
	cout<<"================================================================================"<<endl;

	if( duration == 1 ) //1 is specified for last 7 days(week)
	{
		int sevenDay = (temp->d.day) - 7;
		int thisDay = temp->d.day; //last transaction's day
		int thisMonth = temp->d.month; //last transaction's month 
		int thisYear = temp->d.year; //last transaction's year

		temp = fileToList(filename); //converts file data to linked list

		while( temp->next != NULL )
		{
			if( temp->d.day >= sevenDay && temp->d.day <= thisDay && temp->d.month == thisMonth && temp->d.year == thisYear ) //condition for last 7 days transactions
			{
				cout<<"  "<<setw(20)<<left<<temp->amount<<setw(16)<<left<<temp->category<<setw(14)<<left<<temp->paymentType<<setw(18)<<left<<temp->balance;
				temp->d.displayDate();
				cout<<endl;
			}
			else
			{
			}
			temp = temp->next;
		}
	}
	else if( duration == 2 ) //2 is specified for last 30 days(month)
	{
		int thirtyDay = (temp->d.day) - 30;
		int thisDay = temp->d.day; //last transaction's day
		int thisMonth = temp->d.month; 
		int thisYear = temp->d.year;

		temp = fileToList(filename); //converts file data to linked list

		while( temp->next != NULL )
		{
			if( temp->d.day >= thirtyDay && temp->d.day <= thisDay && temp->d.month == thisMonth && temp->d.year == thisYear ) //condition for last 30 days transactions
			{
				cout<<"  "<<setw(20)<<left<<temp->amount<<setw(16)<<left<<temp->category<<setw(14)<<left<<temp->paymentType<<setw(18)<<left<<temp->balance;
				temp->d.displayDate();
				cout<<endl;
			}
			else
			{
			}
			temp = temp->next;
		}
	}
	else if( duration == 3 ) //3 is specified for last 6 months
	{
		int month = (temp->d.month) - 6;
		//int thisDay = temp->d.day; //last transaction's day
		int thisMonth = temp->d.month; 
		int thisYear = temp->d.year;

		temp = fileToList(filename);

		while( temp->next != NULL )
		{
			if( temp->d.month >= month && temp->d.month <= thisMonth && temp->d.year == thisYear ) //condition for last year transactions
			{
				cout<<"  "<<setw(20)<<left<<temp->amount<<setw(16)<<left<<temp->category<<setw(14)<<left<<temp->paymentType<<setw(18)<<left<<temp->balance;
				temp->d.displayDate();
				cout<<endl;
			}
			else
			{
			}
			temp = temp->next;
		}
	}
	else //display all transactions
	{
		while( temp->next != NULL )
			{
				cout<<"  "<<setw(20)<<left<<temp->amount<<setw(16)<<left<<temp->category<<setw(14)<<left<<temp->paymentType<<setw(18)<<left<<temp->balance;
				temp->d.displayDate();
				cout<<endl;
				temp = temp->next;
			}
	}
	cout<<"================================================================================"<<endl;
}

void transaction::generateReport( string filename ) //to generate textual report of transactions
{
	transactionNode *temp = fileToList(filename); //converts file data to linked list

	ofstream report_write("C:\\Users\\MABM\\Desktop\\Transactions_Report.txt"); //file write mode open to write report
	
	report_write<<"================================================================================";
	report_write<<endl;
	report_write<<"  "<<setw(20)<<left<<"TRANSACTION AMOUNT";
	report_write<<setw(16)<<left<<"CATEGORY";
	report_write<<setw(14)<<left<<"paymentType";
	report_write<<setw(18)<<left<<"FINAL BALANCE";
	report_write<<"DATE";
	report_write<<endl;
	report_write<<"================================================================================";
	report_write<<endl;

	while( temp->next != NULL )
	{
				report_write<<"  "<<setw(20)<<left<<temp->amount<<setw(16)<<left<<temp->category<<setw(14)<<left<<temp->paymentType<<setw(18)<<left<<temp->balance;
				report_write<<temp->d.day<<"/"<<temp->d.month<<"/"<<temp->d.year;
				report_write<<endl;
				temp = temp->next;
	}
	
	report_write<<endl;
	report_write<<"================================================================================";

	cout<<endl;
	cout<<"DONE!!! Report Saved To Desktop."<<endl;

	report_write.close(); //file close
}

void transaction::summary(string filename)
{
	//cout<<"================================================================================"<<endl;
	//cout<<"                 S     U     M     M     A     R     Y                          "<<endl;
	//cout<<"================================================================================"<<endl;
	
	system("CLS");
	cout<<endl<<"================================================================================";
	HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (  m_hConsole, 
                              BACKGROUND_RED |
                              BACKGROUND_GREEN |
                              BACKGROUND_BLUE );
	std::cout <<"                 S     U     M     M     A     R     Y                          ";
    SetConsoleTextAttribute ( m_hConsole,
                              FOREGROUND_RED |
                              FOREGROUND_GREEN |
                              FOREGROUND_BLUE );
	cout<<"================================================================================"<<endl;

	cout<<setw(10)<<left<<"CATEGORY"<<"";
	cout<<setw(3)<<left<<"%AGE";
	cout<<left<<"                            PERCENTAGE GRAPH"<<endl;
	cout<<"--------------------------------------------------------------------------------"<<endl;

	transactionNode *temp1 = fileToList( filename );

	int incomeSum = 0; //to store sum of incomes
	int expenseSum = 0; //to store sum of expenses
	
	while(temp1->next != NULL)
	{
		if(temp1->amount >= 0)
		{
			incomeSum = ( temp1->amount + incomeSum ); //to calculate total income of user
		}
		else
		{
			int amount = ( temp1->amount * (-1) ); //to make expense positive
			expenseSum = ( amount + expenseSum ); //to calculate total income of user
		}
		temp1 = temp1->next;
	}
	
	temp1 = fileToList( filename ); //renewing head again to start of linked list

	while( temp1->next != NULL ) //loop to make sum of transactions of similar category and then determining their graph
	{
		int expenseCategory = 0; //to calculate sum of the transations of same category

		transactionNode *temp2 = fileToList(filename); //converts file data to list
		
		while( temp2->next != NULL ) //compares each item of list to the remaining list
		{
			if( temp1->category == temp2->category && temp2->amount < 0 ) //if category is same and expense amount only(amount>0)
			{
				expenseCategory = ( expenseCategory + ( -1 * temp2->amount ) );
			}
			temp2 = temp2->next;
		}

		int percentage = ( ( (expenseCategory*1.0) / (expenseSum*1.0) ) * 65.0 ); //calculating percentage 65 is just taken on my own choice to make 65 ']' brackets for 100% and vice versa

		cout<<setw(10)<<left<<temp1->category<<":";
		cout<<setw(3)<<left<<percentage<<"% ";

		while( percentage ) //displaying ']' brackets according to percentage of expenses of category
		{
			percentage--;
			cout<<"]";
		}
		cout<<endl;
		
		temp1 = temp1->next;
	}
	cout<<"--------------------------------------------------------------------------------"<<endl;

	cout<<"Total Income:   "<<incomeSum<<endl;
	cout<<"Total Expense:   "<<expenseSum<<endl;
}
