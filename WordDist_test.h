/*
  WordDist_test.h
  Unit tests for HW09, WordDist.
  
*/

#include "WordDist.h"
#include <stdexcept>
#include <fstream>
#include <time.h>
#include <iostream>
#include <cxxtest/TestSuite.h>

class WordDistTest : public CxxTest::TestSuite {
public:

	void testSize01() {
    WordDist a;
    a.addToDictionary("word");
    TS_ASSERT_EQUALS(a.size(), 1);
  }
  void testSize02() {
    WordDist a;
    a.addToDictionary("word");
    a.addToDictionary("werd");
    a.addToDictionary("weird");
    a.addToDictionary("wired");
    TS_ASSERT_EQUALS(a.size(), 4);
  }
  void testStored01() {
    WordDist a;
    a.addToDictionary("word");
    TS_ASSERT_EQUALS(a.isStored("word"), 1);
  }
  void testStored02() {
    WordDist a;
    a.addToDictionary("word");
    TS_ASSERT_EQUALS(a.isStored("werd"), 0);
  }
  void testLevenschteinDist01() {
  	WordDist a;
    TS_ASSERT_EQUALS(a.levenDist("word", "werd"), 1);
  }
  void testLevenschteinDist02() {
  	WordDist a;
    TS_ASSERT_EQUALS(a.levenDist("word", "word"), 0);
  }
  void testLevenschteinDist03() {
  	WordDist a;
    TS_ASSERT_EQUALS(a.levenDist("word", "ord"), 1);
  }
  void testLevenschteinDist04() {
  	WordDist a;
    TS_ASSERT_EQUALS(a.levenDist("word", "birdman"), 5);
  }
  void testGetDistSet01() {
  	ifstream read_file("wordswithfriends.txt");
  	string read_in;
  	WordDist wd;
  	while(getline(read_file, read_in)){
   		wd.addToDictionary(read_in);
  	}
  	set<string> distSet = wd.getDistanceSet("apple", 1);
    TS_ASSERT_EQUALS(distSet.size(), 5);
  }
  void testGetDistSet02() {
  	ifstream read_file("wordswithfriends.txt");
  	string read_in;
  	WordDist wd;
  	while(getline(read_file, read_in)){
   		wd.addToDictionary(read_in);
  	}
  	set<string> distSet = wd.getDistanceSet("apple", 2);
    TS_ASSERT_EQUALS(distSet.size(), 67);
  }
  void testGetDistSet03() {
  	ifstream read_file("wordswithfriends.txt");
  	string read_in;
  	WordDist wd;
  	while(getline(read_file, read_in)){
   		wd.addToDictionary(read_in);
  	}
  	set<string> distSet = wd.getDistanceSet("apple", 3);
    TS_ASSERT_EQUALS(distSet.size(), 827);
  }
  void testGetDistSet04() {
  	WordDist a;
    a.addToDictionary("mat");
  	set<string> distSet = a.getDistanceSet("cat", 1);
    TS_ASSERT_EQUALS(distSet.size(), 1);
  }
  void testGetDistSet05() {
  	WordDist a;
  	a.addToDictionary("at");
  	set<string> distSet = a.getDistanceSet("cat", 1);
    TS_ASSERT_EQUALS(distSet.size(), 1);
  }
  void testGetDistSet06() {
  	WordDist a;
  	a.addToDictionary("scat");
  	set<string> distSet = a.getDistanceSet("cat", 1);
    TS_ASSERT_EQUALS(distSet.size(), 1);
  }
  void testGetDistSet07() {
  	WordDist a;
  	a.addToDictionary("cat");
  	set<string> distSet = a.getDistanceSet("cat", 1);
    TS_ASSERT_EQUALS(distSet.size(), 1);
  }
  void testGetDistSet08() {
		WordDist a;
		a.addToDictionary("cat");
		a.addToDictionary("at");
		a.addToDictionary("scat");
		a.addToDictionary("mat");
		a.addToDictionary("fart");
  	set<string> distSet = a.getDistanceSet("cat", 1);
    TS_ASSERT_EQUALS(distSet.size(), 4);
  }
  void testGetDistSet09() {
  	WordDist a;
  	a.addToDictionary("cat");
		a.addToDictionary("at");
		a.addToDictionary("scat");
		a.addToDictionary("mat");
		a.addToDictionary("fart");
  	set<string> distSet = a.getDistanceSet("cat", 2);
    TS_ASSERT_EQUALS(distSet.size(), 5);
  }
  void testGetDistSet10() {
  	WordDist a;
  	a.addToDictionary("cat");
		a.addToDictionary("at");
		a.addToDictionary("scat");
		a.addToDictionary("mat");
		a.addToDictionary("fart");
  	set<string> distSet = a.getDistanceSet("cat", 0);
    TS_ASSERT_EQUALS(distSet.size(), 1);
  }
  void testGetDistSetTime01() {
  	clock_t t;
  	ifstream read_file("wordswithfriends.txt");
  	string read_in;
  	WordDist wd;
  	while(getline(read_file, read_in)){
   		wd.addToDictionary(read_in);
  	}
  	t = clock();
  	set<string> distSet = wd.getDistanceSet("apple", 4);
  	t = clock() - t;
  	cout << "\nOperation time (sec): " << (float)t/CLOCKS_PER_SEC << endl;
    TS_ASSERT_EQUALS(t/CLOCKS_PER_SEC<=300,1);
  }
  void testGetDistSetTime02() {
  	clock_t t;
  	ifstream read_file("wordswithfriends.txt");
  	string read_in;
  	WordDist wd;
  	while(getline(read_file, read_in)){
   		wd.addToDictionary(read_in);
  	}
  	t = clock();
  	set<string> distSet = wd.getDistanceSet("matt", 100);
  	t = clock() - t;
  	cout << "\nOperation time (sec): " << (float)t/CLOCKS_PER_SEC << endl;
    TS_ASSERT_EQUALS(t/CLOCKS_PER_SEC<=300, 1);
  }

};
