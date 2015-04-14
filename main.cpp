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
#include <algorithm>
#include <ctime>
#include <fstream>
#include "hashtable.h"
#include "pair.h"

using namespace std;

#define TOTAL_RUNS 100

/* === MAIN === */
int main(void) {

	/* Get the number of factors and levels from the user so we can generate a table that's FACTORS * LEVELS big. */
	int factors, levels;
	cout << "Enter number of factors: ";
	cin >> factors;
	cout << "Enter number of levels: ";
	cin >> levels;

	/* Start our timer for calculating how long it takes the entire program to run. */
	clock_t begin = clock();
	
	/* Create the pairs and put them in our hashtable. */
	HashTable pair_table(factors, levels);
	
	/* Set up our variables to be used in generating test candidates and test suites. */
	int possible_pairs = 0, best_pairs = 0, total_candidates = 0,
	candidate_total_pairs = 0, candidate_best_pairs = 0, best_total_candidates = 0, worst_total_candidates = 0, candidates_sum = 0;
	vector<int> possible_options, candidate;
	vector<vector<int> > possible_candidates, best_candidates, final_suite;
	
	candidate.resize(factors);
	fill(candidate.begin(), candidate.end(), -1); // Set all candidate values to -1 so we can easily check against existing values.
	
	/* Randomize the order of the factors to be selected. */
	int factor_order[factors];
	for (int i = 0; i < factors; i++) {
		factor_order[i] = i; // Fill in each value in order first
	}
	random_shuffle(&factor_order[0],&factor_order[factors-1]); // This is where the randomization happens
	
	/* Seed our random generator to be used in breaking ties when options/candidates are equally good. */
	srand(time(NULL));
	
	// begin test suite creation ->
	/* === GENERATE 100 TEST SUITES === */
	for (int g = 0; g < 1; g++) {
	
		/* Reset the test suite vector. */
		best_candidates.clear();
		
		// begin while-loop ->
		/* Continue to generate candidates for the test suite until all pairs are covered. */
		while (pair_table.getCoveredPairs() < pair_table.getTotalPairs()) {
		
			/* Reset our variables for picking candidates for the test suite. */
			candidate_best_pairs = -1;
			possible_candidates.clear();
			
			// begin candidate creation ->
			/* === GENERATE 50 CANDIDATES === */
			for (int a = 0; a < 1; a++) {
			
				/* Reset our variables for this candidate. */
				fill(candidate.begin(), candidate.end(), -1);
				candidate_total_pairs = 0;
				
				// begin option select ->
				/* === GENERATE A SINGLE CANDIDATE BY PICKING THE OPTIONS THAT COVER THE MOST NEW PAIRS === */
				/* Loop through each factor (in a random order) until we've generated a potential candidate. */
				for (int b = 0; b < factors; b++) {
				
					/* Reset our variables for this factor. */
					possible_pairs = 0;
					best_pairs = -1;
					possible_options.clear();
					//cout << "Testing factor #: " << factor_order[b] << endl;
					
					/* Loop through each option for this factor, checking to see which option is involved in the most new pairs. */
					/* If this is the first factor we're testing for this candidate, we don't need to check it against other values. Just check which one has the most pairs by itself. */
					if (b == 0) {
						/* Count how many pairs are left for this option by itself. */
						int start = factor_order[b] * levels, end = start + levels;
						for (int o = start; o < end; o++) {
							possible_pairs = 0;
							for (int m = 0; m < start; m++) {
								if (pair_table.searchPairs(o, m)) {
									possible_pairs++;
								}
							}
							for (int m = start + levels; m < factors * levels; m++) {
								if (pair_table.searchPairs(o, m)) {
									possible_pairs++;
								}
							}
							
							/* Push the option that has the most new pairs to a group of potential options for this factor. */
							if (possible_pairs > best_pairs) {
								possible_options.clear();
								possible_options.push_back(o);
								best_pairs = possible_pairs;
								//cout << "New best pairs: " << best_pairs << endl;
								//cout << "New best option: " << o << endl;
							}
							else if (possible_pairs == best_pairs && possible_options.back() != o) {
								//cout << "Additional option: " << o << endl;
								possible_options.push_back(o);
							}
						}
					}
						
					/* If this is NOT the first factor we're testing for this candidate, we'll need to check this factor's options against what we've already selected for this candidate. */
					else {
						int start = factor_order[b] * levels, end = start + levels;
						for (int o = start; o < end; o++) {
							possible_pairs = 0;
							for (int d = 0; d < factors; d++) {
								if (candidate[d] != -1) { // Check the options against only the factors we've already picked options for
									if (pair_table.searchPairs(o, candidate[d])) {
										possible_pairs++;
									}
									if (possible_pairs > best_pairs) {
										possible_options.clear();
										possible_options.push_back(o);
										best_pairs = possible_pairs;
										//cout << "New best pairs: " << best_pairs << endl;
										//cout << "New best option: " << o << endl;
									}
									else if (possible_pairs == best_pairs && possible_options.back() != o) {
										possible_options.push_back(o);
										//cout << "Additional option: " << o << endl;
									}
								}
							}
						}
					}
							
					/* If there are multiple possible options for this factor, randomly pick one. */
					int random_option = rand() % possible_options.size();
					candidate[factor_order[b]] = possible_options[random_option];
						
				} // <- end option select
						
					/* Shuffle the order of the factors for the next candidate test. */
					random_shuffle(&factor_order[0],&factor_order[factors-1]);
					
					/* Count the pairs for this potential candidate. */
					for (int i = 0; i < factors-1; i++) {
						for (int j = i+1; j < factors; j++) {
							if (pair_table.searchPairs(candidate[i], candidate[j])) {
								candidate_total_pairs++;
							}
						}
					}
					
					/* Collect the candidates that cover the most new pairs. */
					if (candidate_total_pairs > candidate_best_pairs) {
						possible_candidates.clear();
						possible_candidates.push_back(candidate);
						candidate_best_pairs = candidate_total_pairs;
					}
					
					else if (candidate_total_pairs == candidate_best_pairs) {
						possible_candidates.push_back(candidate);
					}
					
				} // <- end candidate select
				
				/* If there are multiple possible best candidates that cover the same amount of best new pairs, randomly pick one. */
				int random_option = rand() % possible_candidates.size();
				best_candidates.push_back(possible_candidates[random_option]);
				
				/* Delete the pairs for the best candidate we just added to the test suite. */
				for (int i = 0; i < factors-1; i++) {
					for (int j = i+1; j < factors; j++) {
						pair_table.deletePair(possible_candidates[random_option][i], possible_candidates[random_option][j]);
					}
				}
			} // <- end while-loop
		
		/* Get the number of candidates in the completed test suite. */
		total_candidates = best_candidates.size();
		
		/* If this test suite has fewer candidates in it, set it to be the best one. */
		if (g == 0) {
			final_suite.resize(best_candidates.size());
			final_suite = best_candidates;
			best_total_candidates = total_candidates;
		}
		
		else if (total_candidates < best_total_candidates) {
			final_suite.resize(best_candidates.size());
			final_suite = best_candidates;
			best_total_candidates = total_candidates;
		}
		
		else if (total_candidates > worst_total_candidates) {
			worst_total_candidates = total_candidates;
		}
		
		/* Once we've covered all of the pairs and generated a test suite, reset all of the pairs by marking them uncovered again. */
		pair_table.resetTable();
		
		candidates_sum += total_candidates;
		
	} // <- end test suite generation
	
	/* End our timer for checking the run time of the program and calculate how long it took to run. */
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	
	/* Output information about this program execution to the console. */
	cout << endl << "Total time to run: " << elapsed_secs << " s" << endl;
	// cout << "Average time per test suite: " << elapsed_secs / TOTAL_RUNS << " s" << endl;
	cout << "Best result: " << final_suite.size() << endl;
	cout << "Worst result: " << worst_total_candidates << endl;
	cout << "Average result: " << candidates_sum / TOTAL_RUNS << endl;
	
	/* Write the best test suite to a file. */
	cout << endl << "Writing best test suite to file..." << endl;
	string filename = "results.txt";
	ofstream output;
	output.open(filename.c_str());
	output << best_total_candidates << endl;
	output << endl;
	for (int i = 0; i < final_suite.size(); i++) {
		for (int j = 0; j < factors; j++) {
			output << final_suite[i][j] << " ";
		}
		output << endl;
	}
	output.close();
	cout << "Test suite is in file: " << filename << endl << endl;

	return 0;
}