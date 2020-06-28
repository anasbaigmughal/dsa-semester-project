#include "date.h"
#include<iostream>
using namespace std;

date::date(void)
{
}

void date::getInput()
{
	cout<<endl<<"Enter Date:-"<<endl;
	cout<<"Day:"<<endl;
	cin>>day;
	cout<<"Month:"<<endl;
	cin>>month;
	cout<<"Year:"<<endl;
	cin>>year;
}

void date::displayDate()
{
	cout<<day<<"/"<<month<<"/"<<year;
}