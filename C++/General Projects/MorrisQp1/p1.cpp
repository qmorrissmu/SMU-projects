//Quentin Morris
//CSE 1342 
//program 1

#include <iostream>
using namespace std;


int main()
{


	int q;
	int d;
	int n;
	
	int quarters;
	int dimes;
	int nickels;

	//Introduction Statements
	cout << "Welcome to the SMU vending machine program." << "\n" << endl;
	cout << "How many quarters are in the machine?" << "\n" << endl;
	cin >> quarters; 
	cout << "\n";
	
	cout << "How many dimes are there in the machine?" << "\n" << endl;
	cin >> dimes;
	cout << "\n";
	
	cout << "How many nickels are there in the machine?" << "\n" << endl;
	cin >> nickels;
	cout << "\n";
	

	cout << "Thank you. The machine contains" << endl;
	cout << quarters << " quarters, " << dimes << " dimes and " << nickels << " nickels. \n" << endl;

	double totalValue = (quarters * 25) + (dimes * 10) + (nickels * 5);
	

	//Requests Loop
	//Will ask the customer what they want, ask for payment, calculate their change and return the stock before looping again

	char userChoice;
	char deposit;

	while (userChoice != 'q' || userChoice != 'Q')
	{
	
		//vending machine prompts
		//do I declare variables as int's or char's?

		cout << "From the items below, select your food choice or enter q to quit: " << endl;
		cout << "a. twix bar 0.50" << endl
			 << "b. skittles 0.75" << endl 
			 << "c. doritos 1.20" << endl 
			 << "d. hot cheetos 1.10" << endl 
			 << "e. gum 0.40" << endl 
			 << "q. quit" << "\n" << endl;
		
		cin >> userChoice;
		int balance;

		if(userChoice == 'a' || userChoice == 'A')
		{
			cout << "You have chosen a twix bar. Please enter payment of 0.50." << endl;
			balance = 50;
		}	
		else if(userChoice == 'b' || userChoice == 'B')
		{
			cout << "You have chosen skittles. Please enter payment of 0.75." << endl;
			balance = 75;
		}
		else if(userChoice == 'c' || userChoice == 'C')
		{
			cout << "You have chosen doritos. Please enter payment of 1.20." << endl;
			balance = 120;
		}
		else if(userChoice == 'd' || userChoice == 'D')
		{
			cout << "You have chosen hot cheetos. Please enter payment of 1.10." << endl;
			balance = 110;
		}
		else if(userChoice == 'e' || userChoice == 'E')
		{
			cout << "You have chosen gum. Please enter payment of 0.40." << endl;
			balance = 40;
		}
		else if(userChoice != 'q' || userChoice != 'Q')
		{
			break;
		}
		else
		{
			cout << "That is not a valid choice." << endl;
			cin >> userChoice;
		}
	//after else if loops..

		
		int money;

		
		
	
		int difference = balance;
		//while loop to figure out if change or payment is needed or not
		
			while(true)
			{
				cout << "\n" << "Menu for payment: " << endl;
				cout << "n - deposit a nickel" << endl;
				cout << "d - deposit a dime" << endl;
				cout << "q - deposit a quarter" << "\n" << endl;
				cout << "Indicate your deposit: " << "\n";
				cin >> deposit; 

					if(deposit == 'n' || deposit == 'N')
					{
						money = 5;
					}
					else if(deposit == 'd' || deposit == 'D')
					{
						money = 10;
					}
					else if(deposit == 'q' || deposit == 'Q')
					{
						money = 25;
					}

					difference -= money;

					if(difference <= 0)
						break;

					cout << "Payment due:" << difference << " cents" << endl;

					
			}

			difference *= -1;
			
			if(difference == 0)
			{
				cout << "Thank you. Here is your item." << endl;
			}
			else if(difference > 0)
				{

						

					for(q = 0; (difference - 25) >= 0; q++)
					{
						difference -= 25;
						quarters = quarters - 1;
					}

					for(d = 0; (difference - 10) >= 0; d++)
					{
						difference -= 10;
						dimes = dimes - 1;
					}

					for(n = 0; (difference - 5) >= 0; n++)
					{
						difference -= 5;
						nickels = nickels - 1;
					}

					cout << "Thank you. Here is your item." << endl;
					cout << "Please take your change below." << "\n" << endl;
					cout << q << " quarters" << endl;
					cout << d << " dimes" << endl;
					cout << n << " nickels" << endl;

				}

			

			if(totalValue - balance < 0)
			{
				cout << "Not enough change in machine, please see the manager to get your remaining balance of " << -(totalValue - balance) << " cents." << endl;
				quarters = 0;
				dimes = 0;
				nickels = 0;
			}
	
			cout << "Stock contains: " << endl
				 << quarters << endl
				 << nickels << endl
				 << dimes << endl;
	
	
	cout << "Machine contains a  total of $" << totalValue * 0.01 << endl; //a total variable that updates throughout.. 


	}
	


	return 0;
}


