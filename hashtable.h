/*
	CSCE 4444 - Homework #01
	Author:		Michele Hindman (Michele.Hindman@unt.edu)
	Date: 	 	January 20th, 2015
	Purpose: 	AETG algorithm implementation to generate combinatorial test suites				
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "pair.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

class HashTable {
	private:
		/* Data */
		vector<vector<Pair> > pairs;
		int factors;
		int levels;
		int total_pairs;
		int covered_pairs;
	public:
		/* Methods */
		HashTable(int factors_value, int levels_value);
		void printTable();
		void resetTable();
		bool searchPairs(int x, int y);
		bool deletePair(int x, int y);
		int getTotalPairs();
		int getCoveredPairs();
};

#endif