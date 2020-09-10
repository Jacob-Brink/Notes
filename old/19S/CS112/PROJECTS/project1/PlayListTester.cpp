/* PlayListTester.cpp defines the PlayList test-methods.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Lab: 01
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "PlayListTester.h"
#include "PlayList.h"
#include <cassert>
#include <iostream>
using namespace std;

void PlayListTester::runTests() {
  cout << "\nTesting class PlayList..." << endl;
  testConstructors();
  testSearchByArtist();

  testSearchByYear();
  testSearchByTitlePhrase();
  testAddRemoveSong();
  testSave();
  cout << "All tests passed!" << endl;
}

void PlayListTester::testConstructors() {
	cout << "- constructors..." << flush;
	PlayList pList("testSongs.txt");
	assert( pList.getNumSongs() == 4 );
	cout << " 0 " << flush;

	cout << " Passed! " << endl;
}

void PlayListTester::testSearchByArtist() {
	cout << "- searchByArtist()... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	// empty case (0)
	vector<Song> searchResult = pList.searchByArtist("Cream");
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// case of 1
	searchResult = pList.searchByArtist("Baez");
	assert( searchResult.size() == 1 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	cout << " 1 " << flush;

	// case of 2
	searchResult = pList.searchByArtist("Beatles");
	assert( searchResult.size() == 2 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	assert( searchResult[1].getTitle() == "Penny Lane" );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testSearchByYear() {
	cout << "- searchByYear... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	// empty case (0)
	vector<Song> searchResult = pList.searchByYear(2015);
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// 1 returned case
	searchResult = pList.searchByYear(2012);
	assert( searchResult.size() == 1);
	cout << " 1 " << flush;

	// 2 returned case
	searchResult = pList.searchByYear(1967);
	assert( searchResult.size() == 2);
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}

void PlayListTester::testSearchByTitlePhrase() {
	cout << "- searchByTitlePhrase... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	// empty case (0)
	vector<Song> searchResult = pList.searchByTitlePhrase("non-existent title");
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// 1 returned case
	searchResult = pList.searchByTitlePhrase("Penny Lane");
	assert( searchResult.size() == 1);
	cout << " 1 " << flush;

	// 2 returned case
	searchResult = pList.searchByTitlePhrase("Let It Be");
	assert( searchResult.size() == 2);
	cout << " 2 " << flush;

	// only part of the title case
	searchResult = pList.searchByTitlePhrase("Penny");
	assert( searchResult.size() == 1);
	cout << " 3 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testAddRemoveSong() {
	cout << "- AddRemoveSong... " << flush;
	Song s1("Title", "Artist", 2019);
	PlayList pList("testSongs.txt");

	// add song and check if length of list increases and song is included
	pList.addSong(s1);

	assert( pList.getNumSongs() == 5);
	cout << " 0 " << flush;
	assert( pList.searchByYear(2019).size() == 1);


	// remove added song and check if length and list are same to original
	pList.removeSong(s1);

	assert(pList.getNumSongs() == 4);
	assert(pList.searchByYear(2019).size() == 0);
	cout << " 1 " << flush;

	cout << " Passed!" << endl;
}


void PlayListTester::testSave() {
	cout << "- Save... " << flush;

}

