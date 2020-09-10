/*
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Project: 01
 *
 * Song default constructor
 * Postcondition: myTitle and myArtist are empty strings
 *            && myYear == 0.
 */

#include "Application.h"
#include <climits>

/* getter method for retreiving integer input in a safe way
 * Return: -1 if invalid input, else integer provided
 */
int returnInputPositiveInt() {
    int integerInput;
    cin >> integerInput;

    // handle invalid input
    if(!cin) {
        // clear cin stream error
        cin.clear();
        // ignore or remove bad input
        cin.ignore(INT_MAX, '\n');

        cout << "Expected postive integer, received string..." << endl;
        return -1;
    }
    // Ignore \n character left in stream
    cin.ignore();

    if (integerInput < 0) {
        cout << "Enter Positive Integer" << endl;
    }
    return integerInput;
}

/* getter method for retreiving year
 * Return: unsigned value for year
 */
unsigned returnYearInput() {
    int yearInput;

    // Get year input until valid input is given
    do {
        cout << "Enter year of song: ";
        yearInput = returnInputPositiveInt();
    }
    while (yearInput < 0);

    //When yearInput is finally valid, return song
    unsigned year = yearInput;

    return year;
}

/* Application default constructor
 * Postcondition: pList is initialized with songList.txt
 */
Application::Application()
{
    //initialize pList to open songList.txt
    pList = new PlayList("songList.txt");
}

/* Main run function, inputting, interpreting, and executing user commands
 * Postcondition: User controls pList
 */
void Application::run() {
    int input;
    string testString;
    cout << "Welcome to the PlayList Manager" << endl;
    while ( true ) {
        // Print list of command options, then retreive command
        printOptions();
        cout << ":";
        //input = returnInputPositiveInt();
        cin >> input;

        // If input is 0, break out of loop and end
        if (input == 0) {
            cout << "Goodbye!";
            break;
        }
        // If input is an a search command, search and print returned songs
        else if (input == 1) {
            string artist;
            cout << "Enter Artist: ";
            //cin >> artist;
            getline(cin, artist);

            vector<Song> searchResults = pList->searchByArtist(artist);
            printSongs(searchResults);

        } else if (input == 2) {
            vector<Song> searchResults = pList->searchByYear(returnYearInput());
            printSongs(searchResults);

        } else if (input == 3) {
            string titlePhrase;
            cout << "Enter a title phrase: ";
            getline(cin, titlePhrase);

            vector<Song> searchResults = pList->searchByTitlePhrase(titlePhrase);
            printSongs(searchResults);

        }
        // If input is adding or removing a song from the playlist
        else if (input == 4) {
            Song addedSong = inputToSong();
            pList->addSong(addedSong);
            cout << "Song added..." << endl;

        } else if (input == 5) {
            Song removedSong = inputToSong();
            pList->removeSong(removedSong);
            cout << "Song removed..." << endl;

        }
        // If input is 6, save playlist to file
        else if (input == 6) {
            pList->save();
            cout << "Saved" << endl;
        }
        else {
            cout << "Please enter an integer corresponding to one of the commands..." << endl;
        }

    }
}

/* Returns Song defined by user
 * Return: Song
 */
Song Application::inputToSong() {
    string title, artist;
    int yearInput;
    cout << "Enter song title: ";
    getline(cin, title);
    cout << "Enter artist of song: ";
    getline(cin, artist);

    unsigned year = returnYearInput();

    return Song(title, artist, year);
}

/* Prints Songs
 * @params: vector reference of type Song
 * Postcondition: out contains description of each song found in search or a message informing of no results
 */
void Application::printSongs(vector<Song> &sVec) {
    cout << "Search Results" << endl;
    if (sVec.size() == 0) {
        cout << "No songs found matching your search..." << endl;
    } else {
        cout << "Number\tTitle\tArtist\tYear" << endl;
        for (unsigned i = 0; i < sVec.size(); ++i) {
            cout << i << "\t" << sVec[i].getTitle() << "\t" << sVec[i].getArtist() << "\t" << sVec[i].getYear() << endl;
        }
    }
}

/* Prints Options
 * Postcondition: out contains list of all commands
 */
void Application::printOptions() {
    cout << "Options..." << endl;
    cout << "1 - search playlist for songs by a given artist" << endl;
    cout << "2 - search playlist for songs from a given year" << endl;
    cout << "3 - search playlist for songs with a given phrase in their title" << endl;
    cout << "4 - add a song to the playlist" << endl;
    cout << "5 - remove a song from the playlist" << endl;
    cout << "6 - save playlist" << endl;
    cout << "0 - to quit" << endl;
}
