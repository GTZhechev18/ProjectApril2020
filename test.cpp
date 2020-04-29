#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
using namespace std;

// deposit 
struct Deposit{
	int number;
	string name, family, currency;
	float amount;
};

//auxilliary function, returning the last present number of the depositor
int last_num_depositors(Deposit arr[], int num_dep) 
{ if (num_dep==0) return 1;
  int max_num=0;
  for (int i=0; i<num_dep; i++)
    if (arr[i].number>max_num) max_num= arr[i].number;
  return max_num+1;  
}

//converts currency number into a string
string scurrency(int currency){
  string result;
  switch (currency){
   case	1: result="BGN"; break;
   case 2: result="USD"; break;
   case 3: result="EUR"; break;
   default: result="BGN";
 }	
  return result;
}

//New depositor
void input_depositor(Deposit arr[], int& num_dep) 
{
 if (num_dep==100) { cout<<"The array is full!\n";
                     return;
                   }
 
 Deposit d;
 d.number=last_num_depositors(arr, num_dep);
 cout<<"\nInput depositor's data:\n\n";
 cout<<"Name: ";
 cin>>d.name;
 cout<<"Family: ";
 cin>>d.family; 
 cout<<"Choose currency: 1-BGN, 2-USD, 3-EUR: ";
 int currency;
 cin>>currency;
 cout<<"Amount: ";
 cin>>d.amount;
 d.currency=scurrency(currency);
 
 arr[num_dep]=d;
 num_dep++; 
}

void view(Deposit arr[], int& num_dep)             // List of depositors
{
  system("cls");
  if (num_dep==0) { cout<<"\nNo Depositors!\n";
                     return;
                   }
  cout<<"LIST OF DEPOSITORS:\n";

  for (int i=0; i<num_dep; i++)
  { 
    cout<<setw(3)<<arr[i].number<<setw(15)<<arr[i].name<<setw(15)<<arr[i].family<<setw(5)<<arr[i].currency<<setw(8)<<arr[i].amount<<endl;
  }
 
}

//search for a depositor with certain currency

int find_depositor_currency(Deposit arr[], int num_dep, int depositor, string money)
{
	for (int i=0; i<num_dep; i++)
       if (arr[i].number==depositor and arr[i].currency==money) return i;
	return -1;
}

//search for a depositor
int find_depositor(Deposit arr[], int num_dep, int depositor)
{
	for (int i=0; i<num_dep; i++)
       if (arr[i].number==depositor) return i;
	return -1;
}

//New deposit
void input_deposit(Deposit arr[], int& num_dep)
{ int num, currency, amount;
  cout<<"\nEnter depositor number:";
  cin>>num;
  
  int index=find_depositor(arr,num_dep,num);
  if (index<0) { cout<<"\n No such depositor!\n";
                 return; 
                }
  
  cout<<"Choose currency: 1-BGN, 2-USD, 3-EUR: ";
  cin>>currency;
  cout<<"Enter amount: ";
  cin>>amount;
  
  string smoney=scurrency(currency);
  int index1=find_depositor_currency(arr,num_dep,num,smoney);
  if (index1>=0) arr[index1].amount=arr[index1].amount+amount;
   else { arr[num_dep].number=num;
          arr[num_dep].name=arr[index].name;
          arr[num_dep].family=arr[index].family;
   	      arr[num_dep].currency=smoney;
   	      arr[num_dep].amount=amount;
   	      num_dep++;
   }
  }

//Withdraw a deposit
void withdraw_deposit(Deposit arr[], int& num_dep)
{ int num,choice, currency;
  float amount;
  system("cls");
  cout<<"\nEnter depositor number:";
  cin>>num;
  
  int index=find_depositor(arr,num_dep,num);
  if (index<0) { cout<<"\n No such depositor!\n";
                 return; 
                }
  
  cout<<"Choose currency: 1-BGN, 2-USD, 3-EUR: ";
  cin>>currency;
  
  string smoney=scurrency(currency);
  int index1=find_depositor_currency(arr,num_dep,num,smoney);
  if (index1<0) { cout<<"\n No such deposit!\n";
                 return; 
                }
  
  cout<<"Enter amount: ";
  cin>>amount;
  if (amount>arr[index1].amount) { cout<<"\n No enough amount!\n";
                                   return; 
                                 }
  if (amount<arr[index1].amount) arr[index1].amount=arr[index1].amount-amount;
  else {  for (int i=index1; i<num_dep; i++)  //delete deposit
              {  arr[i].number=arr[i+1].number;
                 arr[i].name  =arr[i+1].name;
                 arr[i].family=arr[i+1].family;
   	             arr[i].currency=arr[i+1].currency;
   	             arr[i].amount=arr[i+1].amount;
   	     
			  }
    	 num_dep--;
  }
}


void show_menu(Deposit arr[], int& num_dep)
{ 
  int c;
  do{ 
  	
  cout<<"\nMain menu\n\n";
  cout<<"1 - Enter depositor\n";
  cout<<"2 - Enter list of depositors\n";
  cout<<"3 - View depositors\n";
  cout<<"4 - Enter deposit\n";
  cout<<"5 - Withdraw a deposit\n";
  cout<<"6 - Quit program\n";
  cout<<"Your choice:";
  cin>>c;
  switch(c){
  	 case 1: input_depositor(arr, num_dep); break;
  	 case 2: int n;
  	         cout<<"Enter number of depositors: ";
  	         cin>>n;
	         for (int i=1; i<=n; i++) input_depositor(arr, num_dep); 
			 break;
  	 case 3: view(arr, num_dep); break;
  	 case 4: input_deposit(arr, num_dep); break;
  	 case 5: withdraw_deposit(arr, num_dep); break;
  	 default: "Error! Try again!";
  }
  } while (c!=6);
}

int main()	//main function
{ 
 Deposit arr[100];
 int num_dep=0;
  
 show_menu(arr, num_dep);
   
  cout<<"\nEnd of program";
}


void swap_deposits(Deposit& a, Deposit& b)
{ Deposit temp=a;
  a=b;
  b=temp;
}


