/*    @file generate.cpp    
      @author Matt Hoendorf <hoendomd@mail.uc.edu>
      @date 10.28.14
			@description Given a dictionary file (one word per line), and a starter word,
			this prints out all the (simplified) distance 1 words from the given word.
			
			Simplified distance 1 words are all words in the dictionary file that has
			one letter changed from the given word.
			Ex: ape -> aps
			
			./generate wordswithfriends.txt apple
			
			Execution time should be under 1 second.
*/

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <WordDist.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char* argv[]){
  
  // Check the number of arguments given, return usage if invalid
  if(argc != 4){
  	cerr << "\nUsage: " << argv[0] << " <file_name>.txt <word> <distance>\n" << endl;
  	return 1;
  }

  // Open file
  ifstream read_file(argv[1]);
  string read_in;
  
  // Check that txt file was successfully opened
  if(!read_file.is_open()){
    cerr << "\nError reading file. Please provide a valid filename.\n" << endl;
    return 1;
  }

  clock_t start = clock();

  WordDist wd;

  while(getline(read_file, read_in)){
    wd.addToDictionary(read_in);
  }

  set<string> distSet = wd.getDistanceSet(argv[2], atoi(argv[3]));
  clock_t end = clock();
  double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
  
  stringstream ss;
  set<string>::iterator it = distSet.begin();
  int count = 1;
  while(it != distSet.end()){
     ss << count << ":" << *it << "\n";
     it++;
     count++;
  }
  cout << ss.str();
  
  cout << "\ngetDistanceSet time (ms): " << time << "\n" << endl;

  return 0;
}
