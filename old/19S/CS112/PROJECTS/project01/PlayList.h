/* PlayList.h declares class PlayList.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Lab: 01
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Song.h"
#include <vector>	//STL vector
#include <string>
using namespace std;

class PlayList {
public:
  PlayList(const string& fileName);
  unsigned getNumSongs() const;
  vector<Song> searchByArtist(const string& artist) const;

  vector<Song> searchByYear(unsigned year) const;
  vector<Song> searchByTitlePhrase(const string& title) const;
  void addSong(const Song& newSong);
  void removeSong(const Song& aSong);
  void save() const;
private:
  vector<Song> mySongs;
  string fName;

};

#endif /*PLAYLIST_H_*/
