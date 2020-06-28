#include "iomanip"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "transaction.h"
#include "user.h"
#include "string"
#include "string.h"
#include "conio.h"
#include "fstream"
#include <iostream>
using namespace std;

int main()
{
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
	
	int choice1, choice2, choice3; //variables to get user choices
	user *u; //pointer to user class
	u = new user; //user object
	transaction *t = new transaction; //dynamic memory allocation to pointer of transaction class
	
	cout<<"Enter Mode:"<<endl; 
	cout<<"1. Log In."<<endl;
	cout<<"2. Sign Up."<<endl;
	cin>>choice1; //gets mode input
	u->getData(choice1); //gets login or sign up credentials from user
	
	do
	{
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
		
		cout<<"Enter Operation:"<<endl;
		cout<<"1. Add Income."<<endl;
		cout<<"2. Add Expense."<<endl;
		cout<<"3. Display Account Balance."<<endl;
		cout<<"4. Display All Transactions."<<endl;
		cout<<"5. Genrate Text File Report."<<endl;
		cout<<"6. Show Summary(Graph)."<<endl;
		cout<<"7. Exit."<<endl;
		cin>>choice2; //gets operation choice
	
		if(choice2 == 1)
		{
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
			t->getAmount(u->getUsername(), u->getPassword(), 1); //files of the user will be created on its username.txt(final balance) and password.txt(transactions details)
		}
		else if (choice2 == 2)
		{
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
		
			t->getAmount(u->getUsername(), u->getPassword(), 2); //files of the user will be created on its username.txt(final balance) and password.txt(transactions details)
		}
		else if(choice2 == 3)
		{
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
		
			t->finalBalance(u->getUsername()); //to display final balance in account
		}
		else if(choice2 == 4)
		{
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
		
			t->displayTransaction(u->getPassword());
		}
		else if(choice2 == 5)
		{
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
		
			t->generateReport(u->getPassword());
		}
		else if(choice2 == 6)
		{
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
		
			t->summary(u->getPassword());
		}
		else if(choice2 == 7)
		{
			break;
		}
		else
		{
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
		
			cout<<"SORRY!!! INVALID CHOICE SELECTED."<<endl;
		}

	cout<<endl;
	cout<<endl<<"Do you want to do operation again?"<<endl;
	cout<<"1. YES."<<endl;
	cout<<"2. NO."<<endl;
	cin>>choice3;
	}
	while(choice3 == 1);
	
	getch();
}