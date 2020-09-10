/* PlayListTester.h tests the PlayList class.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Lab: 01
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef PLAYLISTTESTER_
#define PLAYLISTTESTER_

class PlayListTester {
public:
   void runTests();
   void testConstructors();
   void testSearchByArtist();

   void testSearchByYear();
   void testSearchByTitlePhrase();
   void testAddRemoveSong();
   void testSave();
};

#endif /*PLAYLISTTESTER_*/
