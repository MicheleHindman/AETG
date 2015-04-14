/*
	CSCE 4444 - Homework #01
	Author:		Michele Hindman (Michele.Hindman@unt.edu)
	Date: 	 	January 20th, 2015
	Purpose: 	AETG algorithm implementation to generate combinatorial test suites				
*/

#include <cstdlib>

#ifndef PAIR_H
#define PAIR_H

using namespace std;

class Pair {
	public:
		/* Data */
		int y; // Stores the Y value of the pair
		bool covered; // Flags if it's been covered
	
		/* Methods */
		Pair(int value_y);
};

#endif