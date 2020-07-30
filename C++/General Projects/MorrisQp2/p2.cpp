//Quentin Morris
//CSE 1342 
//program 2

#include <iostream>
using namespace std;


//getStock() is the introductory function that reads off the initial
//prompts for how much of each denomination of cash there are 
int getStock(int& Q, int& D, int& N, int& M)//pass by reference
{
		//Introduction Statements
	cout << "Welcome to the SMU vending machine program." << "\n" << endl;
	
	cout<< "How many dollar bills are in the machine?" << "\n" << endl;
	cin >> M; 
	cout << "\n";

	cout << "How many quarters are in the machine?" << "\n" << endl;
	cin >> Q; 
	cout << "\n";
	
	cout << "How many dimes are there in the machine?" << "\n" << endl;
	cin >> D;
	cout << "\n";
	
	cout << "How many nickels are there in the machine?" << "\n" << endl;
	cin >> N;
	cout << "\n";
	

	cout << "Thank you. The machine contains" << endl;
	cout << M << " dollars, " << Q << " quarters, " << D << " dimes and " << N << " nickels. \n" << endl;
}


//getChoice() gets passed the value of userChoice and 
//determines what the balance will be, then returns that balance 
int getChoice(char userChoice)//pass by value
{
	//Requests Loop
	//Will ask the customer what they want, ask for payment, calculate their change and return the stock before looping again
	
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

		if(userChoice == 'q' || userChoice == 'Q')
		{
			return 0;
		}
		else if(userChoice == 'a' || userChoice == 'A')
		{
			cout << "You have chosen a twix bar. Please enter payment of 0.50." << endl;
			return balance = 50;
		}	
		else if(userChoice == 'b' || userChoice == 'B')
		{
			cout << "You have chosen skittles. Please enter payment of 0.75." << endl;
			return balance = 75;
		}
		else if(userChoice == 'c' || userChoice == 'C')
		{
			cout << "You have chosen doritos. Please enter payment of 1.20." << endl;
			return balance = 120;
		}
		else if(userChoice == 'd' || userChoice == 'D')
		{
			cout << "You have chosen hot cheetos. Please enter payment of 1.10." << endl;
			 return balance = 110;
		}
		else if(userChoice == 'e' || userChoice == 'E')
		{
			cout << "You have chosen gum. Please enter payment of 0.40." << endl;
			return balance = 40;
		}
		else
		{
			cout << "That is not a valid choice." << endl;
			cin >> userChoice;
		}

	}

}


//makeChange() takes in the balance along with totals of each denomination of money
//(passed by reference)
//the function takes deposits until change needs to be rendered, creates change
void makeChange(int r, int& w, int& x, int& y, int& z)
{
	
	int money;
	char deposit;
	int difference = r;
	int totalValue = (w * 100) + (x * 25) + (y * 10) + (z * 5);
	while(true)

			{
				cout << "\n" << "Menu for payment: " << endl;
				cout << "n - deposit a nickel" << endl;
				cout << "d - deposit a dime" << endl;
				cout << "q - deposit a quarter" << endl;
				cout << "m - deposit a dollar" << "\n" << endl;
				cout << "Indicate your deposit: " << "\n";
				cin >> deposit; 

					if(deposit == 'n' || deposit == 'N')
					{
						money = 5;
						z += 1;
					}
					else if(deposit == 'd' || deposit == 'D')
					{
						money = 10;
						y += 1;
					}
					else if(deposit == 'q' || deposit == 'Q')
					{
						money = 25;
						x += 1;
					}
					else if(deposit == 'm' || deposit == 'M')
					{
						money = 100;
						w += 1;
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

					int a;
					int b;
					int c;
					int t;
					//algorithm to figure out change
					for(a = 0; (difference - 100) >= 0; a++)
					{
						difference -= 100;
						w -= 1;
					}

					for(b = 0; (difference - 25) >= 0; b++)
					{
						difference -= 25;
						x -= 1;
					}

					for(c = 0; (difference - 10) >= 0; c++)
					{
						difference -= 10;
						y -= 1;
					}

					for(t = 0; (difference - 5) >= 0; t++)
					{
						difference -= 5;
						z -= 1;
					}

					cout << "\n" << "Thank you. Here is your item." << endl;
					cout << "Please take your change below." << "\n" << endl;
					cout << a << " dollars" << endl;
					cout << b << " quarters" << endl;
					cout << c << " dimes" << endl;
					cout << t << " nickels" << "\n" << endl;

				}

			if((totalValue - difference) < 0)
			{
				cout << "Not enough change in machine, please see the manager to get your remaining balance of " << -(((w * 1) + (x * .25) + (y * .1) + (z * .05)) - r) << " cents." << endl;
				w = 0;
				x = 0;
				y = 0;
				z = 0;
			}
	
			cout << "Stock contains: " << endl
				 << w << " dollars" << endl
				 << x << " quarters" << endl
				 << y << " dimes" << endl
				 << z << " nickels" << "\n" << endl;
}

int main()
{

	int q;
	int d;
	int n;
	int m;
	char snackChoice;
	
	//method getStock() gives beginning prompts to program

	getStock( q, d, n, m);//think this method is fine, but do i need && in these paremeters
	while(snackChoice != 'q' || snackChoice != 'Q')
	{
		int x = getChoice(snackChoice);//send program to getChoice() next
		if(x == 0)//I set my Q to 0 to make it quit on Q
		{
			break;
		}
		else//if they do not quit, make them change for their purchase and deposits
		{
			makeChange(x, m, q, d, n);
		}
		
	}

	double totalValue = (m * 100) + (q * 25) + (d * 10) + (n * 5);
	cout << "Machine contains a  total of $" << totalValue * 0.01 << endl; //a total variable that updates throughout.. 
	//int quarters;
	//int dimes;
	//int nickels;
 


	return 0;
}


