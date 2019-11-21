#include <iostream>
#include <cstdlib>
#include <ctime>
#include "markhov.h"

typedef Markhov<int> markhov;	

int main ()
{
	//Generates a seed for you random number generator
	srand(time(NULL));
	markhov nodes;	

	for(int i = 1; i < 11; i++) 
	{
		nodes.push_back(i);
	}
	

	//Generates a random number between 0 and 100
	int prob = rand() % 100;
	
	int sim = 10000;
	
	unsigned int array[sim] = {0};
	
	for(int i = 0; i < sim; i++) 
	{	

		while (nodes.state() != 10)
		{
			nodes.test(prob);
			prob = (rand() % 100);
		}

		unsigned int n = nodes.steps();
		array[i] = n;
		nodes.reset();
	}

//-------------------------------------------------------------		

	int resultsMax = 0;
	int resultsMin = array[0];
	int mean = 0;

	for (int n = 0; (n + 1) <= sim; n++)
	{
		int ind = array[n];
		mean += array[n];
		
		if(ind > resultsMax)
		{
			resultsMax = ind;
		}
		
		if(ind < resultsMin)
		{
			resultsMin = ind;
		}
		
	
	}

	int resultsMean = (mean/sim);
	
	std::cout << "Max: " << resultsMax << std::endl;
	std::cout << "Min: " << resultsMin << std::endl;
	std::cout << "Mean: " << resultsMean << std::endl;
	
	
	return 0;
}
