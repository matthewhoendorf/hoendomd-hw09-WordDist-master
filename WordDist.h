#ifndef WORDDIST_H
#define WORDDIST_H 
/**   @file WordDist.h    
      @author Matt Hoendorf <hoendomd@mail.uc.edu>
      @date 10.28.14
      @version 0.01   
      
      This WordDist class allows the addition of words to an internal
      dictionary, and the retrieval of a set of words which have at
      least a certain 'distance' from it.
      
      See assignment document for 'distance' definition.
**/
#include <set>
#include <string>

using namespace std;

class WordDist{

public:
  WordDist();
  
  ~WordDist();
  
  void addToDictionary(string word);
  
  unsigned int size();
  
  bool isStored(string word);
  
  set<string> getDistanceSet(string word, unsigned int dist);

  unsigned int levenDist(string s, string t);

private:

  unsigned int my_size;
  set<string> my_dict;
  set<string> dist_set;
  
  int min(int a, int b, int c);
  int *getCellPt(int *pOrigin, int col, int row, int nCols);
  int getAt(int *pOrigin, int col, int row, int nCols);
  void putAt(int *pOrigin, int col, int row, int nCols, int x);

};

#endif
