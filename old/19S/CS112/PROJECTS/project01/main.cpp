/* main.cpp tests the classes in our project.
 * Student Name: jpb34
 * Date: Feb 5, 2019
 * Lab: 01
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "SongTester.h"
#include "PlayListTester.h"
#include "Application.h"

int main() {
	SongTester sTester;
	sTester.runTests();
	PlayListTester plTester;
	plTester.runTests();

    Application mainApp;
    mainApp.run();

}
