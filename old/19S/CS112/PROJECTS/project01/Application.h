/* Application.h declares a class for user input handling.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Project: 01
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "PlayList.h"

class Application
{
    public:
        Application();
        void run();
    private:
        void printOptions();
        void printSongs(vector<Song> &sVec);
        Song inputToSong();
        //I couldn't figure out how to declare but not initialize playlist so I followed this stack overflow suggestion
        //https://stackoverflow.com/questions/800368/declaring-an-object-before-initializing-it-in-c
        PlayList* pList;

};

#endif // APPLICATION_H
