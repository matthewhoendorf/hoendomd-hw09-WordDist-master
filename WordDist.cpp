/*    @file WordDist.cpp   
      @author Matt Hoendorf <hoendomd@mail.uc.edu>
      @date 10.28.14

			@description Implements the WordDist class
*/
#include <set>
#include <string.h>
#include <malloc.h>
#include <math.h>

#include "WordDist.h"

using namespace std;

WordDist::WordDist(){}

WordDist::~WordDist(){}

void WordDist::addToDictionary(string word){
	my_dict.insert(word);
}

unsigned int WordDist::size(){
	return my_dict.size();
}

bool WordDist::isStored(string word){
	if(my_dict.count(word) == 0){
		return false;
	}
	return true;
}

// Get set of words that are within given distance
set<string> WordDist::getDistanceSet(string word, unsigned int dist){
	set<string>::iterator it;
	for(it = my_dict.begin(); it != my_dict.end(); ++it){
  	string test = *it;
  	/*
  	unsigned int distance = 0;
		if(word.size() == test.size()){
			for(unsigned int i = 0; i < word.size(); i++){
				if(word.at(i) != test.at(i)){
					distance++;
				}
			}
			if(distance == dist){
				dist_set.insert(test);
			}
		}
		*/
		if(levenDist(word,test) <= dist){
			dist_set.insert(test);
		}
	}
	return dist_set;
}

// Get min of 3 values
int WordDist::min (int a, int b, int c)
{
	int val;
  val = a;
  if (b < val) {
    val = b;
  }
  if (c < val) {
    val = c;
  }
  return val;
}

// Get a pointer to the specified cell of the matrix
int *WordDist::getCellPt (int *pO, int col, int row, int nCols)
{
  return pO + col + (row * (nCols + 1));
}

// Get the contents of the specified cell in the matrix 
int WordDist::getAt (int *pO, int col, int row, int nCols)
{
	int *pCell;
  pCell = getCellPt (pO, col, row, nCols);
  return *pCell;
}

// Fill the specified cell in the matrix with the value x
void WordDist::putAt (int *pO, int col, int row, int nCols, int x)
{
	int *pCell;
  pCell = getCellPt (pO, col, row, nCols);
  *pCell = x;
}

unsigned int WordDist::levenDist(string s, string t){
	int *d; // pointer to matrix
	int n, m; // length of s, t respectively
	int i, j; // iterates through s, t respectively
	char s_i, t_j; // ith char of s, jth char of t
	int cell, up_cell, left_cell, diag_cell, num_cells; // cell initializations
	int cost;
	int result;

	// Set n, m to string length
	n = s.size();
	m = t.size();
	
	// If s is NULL, result is length of t - and vice versa
	if(n == 0){
		return m;
	}
	if(m == 0){
		return n;
	}

	// Create matrix n x m
	num_cells = (n+1)*(m+1)*sizeof(int);
  d = (int*)malloc(num_cells);

  // Make first row 0..n and first col 0..m
  for (i = 0; i <= n; i++) {
    putAt(d, i, 0, n, i);
  }
  for (j = 0; j <= m; j++) {
    putAt(d, 0, j, n, j);
  }

  // Assemble Levenschtein matrix
  for(i = 1; i <= n; i++){
    s_i = s[i-1]; // Examine each char of s
    for(j = 1; j <= m; j++){
      t_j = t[j-1]; //Examine each char of t
      
      if (s_i == t_j){
        cost = 0; // If chars are equal, cost is zero
      }
      else {
        cost = 1; // If equal, cost is one
      }
      // Place Levenschtein Matrix values
      up_cell = getAt(d, i-1, j, n);
      left_cell = getAt(d, i, j-1, n);
      diag_cell = getAt(d, i-1, j-1, n);
      cell = min(up_cell + 1, left_cell + 1, diag_cell + cost);
      putAt(d, i, j, n, cell);
    }
	}

  result = getAt(d, n, m, n); // Result is the bottom right of the matrix
  free(d); // Free pointer to matrix
  return result; // Return result (Levenschtein dist)
}