/* SongTester.h declares a test-class for class Song.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Lab: 01
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef SONGTESTER_H_
#define SONGTESTER_H_

class SongTester {
   public:
      void runTests();
      void testConstructors();
      void testReadFrom();
      void testWriteTo();

      void testSongOperator();
};

#endif /*SONGTESTER_H_*/
