/*
	CSCE 4444 - Homework #01
	Author:		Michele Hindman (Michele.Hindman@unt.edu)
	Date: 	 	January 20th, 2015
	Purpose: 	AETG algorithm implementation to generate combinatorial test suites				
*/

#include <cstdlib>
#include "pair.h"

using namespace std;

/* FUNCTION: Pair() */
/* Pair constructor with parameters. */
Pair::Pair(int value_y) {
	y = value_y;
	covered = false;
}
