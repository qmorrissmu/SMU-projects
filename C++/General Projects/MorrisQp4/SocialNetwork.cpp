#include "SocialNetwork.h"
#include <fstream>
#include <iostream>
using namespace std;

SocialNetwork::SocialNetwork(){
	
	string fileName;

	cout << "Facebook friend recommendation.\n" << endl;
	cout << "Enter a filename:";
	cin >> fileName;
	infile.open(fileName);

	//to handle an error in entering the filename
	while(!infile.is_open())
	{
		cout << "Error in filename." << endl;
		cout << "Enter a filename:";
		cin >> fileName;
		infile.open(fileName);

	}

	//grab the first line of the text file, the number of users
	infile >> size;
	
	
	network_data = new vector<int>[size];

	init_matrix();

}

int SocialNetwork::getSize()
{
	return size;
}

void SocialNetwork::readFile()
{
	int u;
	int v;

	//while: the file is still good(has not reached end)
	while(infile.good())
	{
		//each charachter that is read is assigned to u and v, pairings of friends
		//in vector netword_data, the friend pairs go to each other's matrix index

		infile >> u;
		infile >> v;

		network_data[u].push_back(v);
		network_data[v].push_back(u);

	}
}

//FIX ME
void SocialNetwork::display()
{
	for(int i = 0; i < size; i++)
	{
		cout << i << " : " << "[";

		for(int j = 0; j < network_data[i].size() - 1; j++)
		{
			cout << network_data[i].at(j) << ", ";
		}
	}

	cout << "]";
}

void SocialNetwork::init_matrix()
{
	//creates and initializes the similarity_matrix to all 0s

	similarity_matrix = new int*[size];
	for(int i = 0; i < size; i++)
	{
		similarity_matrix[i] = new int[size];
	}
	
	int j;
	for(int i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			similarity_matrix[i][j] = 0;
		}
	}
}

void SocialNetwork::calc_similarity_scores()
{
	
	//records the number of friends in common and puts it into the similarity_matrix
	//copies entries across the diagonal
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			similarity_matrix[i][j] = num_in_common_between_vectors(network_data[i], network_data[j]);
			similarity_matrix[j][i] = similarity_matrix[i][j];
		}   

	}

}

int SocialNetwork::num_in_common_between_vectors(vector<int> vector1,vector<int> vector2)
{
	int num_in_common;
	
	//iterates through rows and columns of vectors in network data and if any entries in the rows match, num_in_common incriments
	//to keep track of how many friends each person has in common with each other
	for(int i = 0; i < vector1.size(); i++)
	{
		for(int j = 0; j < vector2.size(); j++)
		{
			if(vector1.at(i) == vector2.at(j))
				num_in_common++;
		}
	}
	return num_in_common;
}



int SocialNetwork::recommend(int user_id)
{
	int recommendedUser;
	int maxScore = 0;
	
	//iterates through the row of the similarity matrix of the user that a recommendation is being searched for 
	for(int i = 0; i < size; i++)
	{

		//if: ensures you are not recommended to be friends with yourself
		if (user_id != i)
		{
			//if: the highest similarity score in the row user_id is higher than the score previosly highest 
			if(similarity_matrix[user_id][i] > maxScore)
			{
			
				//updates the recommendedUser to the column that has the highest similarity score
				//updates the maxScore to the highest score in the row
				recommendedUser = i;
				maxScore = similarity_matrix[user_id][i];



			}
	}

	}
	cout << "The suggested friend for " << user_id << " is " << recommendedUser << endl << "\n";

	return 0;
}


