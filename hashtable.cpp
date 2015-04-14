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
#include "hashtable.h"
#include "pair.h"

using namespace std;

/* FUNCTION: HashTable() */
/* Hash table constructor. */
HashTable::HashTable(int factors_value, int levels_value) {

	total_pairs = 0;
	covered_pairs = 0;
	factors = factors_value;
	levels = levels_value;
	
	pairs.resize((factors*levels)-levels);
	int key = 0, current_factor = 0;
	for (int i = factors; i > 1; i--) {
		for (int j = 0; j < levels; j++) {
			//cout << key << ": ";
			int value = levels + (levels*current_factor);
			for (int k = 0; k < (i*levels)-levels; k++) {
				Pair new_pair(value);
				pairs[key].push_back(new_pair);
				//cout << pairs[key].back().y << " ";
				value++;
			}
			//cout << "(size: " << pairs[key].size() << ")";
			//cout << endl;
			key++;
		}
		total_pairs += (i*levels)-levels;
		current_factor++;
	}
	total_pairs *= levels;
	//cout << "Total pairs: " << total_pairs << endl;
}

/* FUNCTION: printTable() */
/* Prints the hash table in an easy to read manner. Only prints values that have not been covered. Used for debugging purposes. */
void HashTable::printTable() {
	int value = levels, key = 0, current_factor = 0;
	for (int i = factors; i > 1; i--) {
		for (int j = 0; j < levels; j++) {
			cout << key << ": ";
			for (int k = 0; k < pairs[key].size(); k++) {
				if (pairs[key][k].covered == false) {
					cout << pairs[key][k].y << "[" << k << "]" << " ";
				}
				value++;
			}
			cout << endl;
			key++;
		}
		//total_pairs += (i*levels)-levels;
		current_factor++;
	}
}

/* FUNCTION: getTotalPairs() */
/* Return the total number of pairs. */
int HashTable::getTotalPairs() {
	return total_pairs;
}

/* FUNCTION: getCoveredPairs() */
/* Return the number of pairs that have been covered. */
int HashTable::getCoveredPairs() {
	return covered_pairs;
}

/* FUNCTION: resetTable() */
/* Resets all of the pairs so they're marked as uncovered again. To be used once all pairs have been covered and we want to make a new test suite. */
void HashTable::resetTable() {
	covered_pairs = 0;
	for (int i = 0; i < (factors * levels) - levels; i++) {
		for (int j = 0; j < pairs[i].size(); j++) {
			pairs[i][j].covered = false;
		}
	}
}

/* FUNCTION: searchPairs() */
/* Checks to see if a pair exists in the table. */
bool HashTable::searchPairs(int x, int y) {

	if (x > y) {
		int temp = x;
		x = y;
		y = temp;
	}
	
	//cout << "Checking " << x << ", " << y << "..." << endl;
	
	int key = x; // Get the hash key.
	int current_factor = key/levels;
	int lookup = y - ((current_factor + 1) * levels);
	//cout << "(checking pairs[" << key << "][" << lookup << "]) & current_factor is " << current_factor << endl;
	if (!pairs[key][lookup].covered) {
		//cout << "Found." << endl;
		return true;
	}
	
	//cout << "Not found." << endl;
	return false;
}

/* FUNCTION: deletePair() */
/* Marks a pair as covered in the table, if it exists. Returns true if there was a pair to cover. */
bool HashTable::deletePair(int x, int y) {

	if (x > y) {
		int temp = x;
		x = y;
		y = temp;
	}
	
	int key = x; // Get the hash key
	int current_factor = key/levels;
	int lookup = y - ((current_factor + 1) * levels);
	if (pairs[key][lookup].covered == false) {
		pairs[key][lookup].covered = true;
		covered_pairs++;
		//cout << "Deleting " << x << ", " << y << "..." << endl;
		return true;
	}
	
	//cout << "Can't delete, doesn't exist." << endl;
	return false;
}