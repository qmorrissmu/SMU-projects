#include <iostream>
#include <fstream>
#include <string>
#include "SocialNetwork.h"
using namespace std;

int main()
{
	string choice;
	int user_id;
	SocialNetwork myNetwork;
	myNetwork.readFile();

	while(choice.compare("no") != 0 || choice != "no" || choice != "No" || choice != "NO"|| choice != "nO")//compare chars not strings
	{
		cout << "Enter an integer in the range 0 to " << myNetwork.getSize() - 1 << " : ";
		cin >> user_id;
		
		while(user_id > myNetwork.getSize() - 1 || user_id < 0)
		{
			cout << "Error, enter another integer";
			cin >> user_id;
		}
		
		myNetwork.calc_similarity_scores();
		myNetwork.recommend(user_id);
		cout << "Do you want to continue (yes/no)? ";
		cin >> choice;
	} 



}//end main