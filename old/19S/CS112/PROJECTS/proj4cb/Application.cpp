/* Application.cpp contains the application definitions yeah
 * Student Name: Jacob Brink
 * Date: 3/4/2019
 */

#include "Application.h"
#include "Matrix.h"
#include <string>

/* Default Constructor
 * Postcondition: Nothing
 */
Application::Application()
{

}

/* Return Matrix from User Input
 * @params: none
 * Precondition: file exists
 * Returns: Matrix<int> read from given file
 */
Matrix<int> returnMatrixFromFile() {
    cout << "Choose file to read matrix: " << endl;
    string stringInput;
    getline(cin, stringInput);
    Matrix<int> m1;
    m1.readFrom(stringInput);
    return m1;
}

/* Command Line User Interface
 * @params: none
 * Precondition: none
 * Returns: none
 */
void Application::run() {

    cout << "Choose one of the following matrix operations" << endl;
    cout << "0: Add, 1: Subtract, 2: Transpose, 3: Quit" << endl;

    int input = 0;
    string inputString;

    //Unless quitting, ask user for input and then do appropriate matrix operation
    while (input != 3) {
        cout << "Enter Command: " << flush;
        getline(cin, inputString);
        input = atoi(inputString.c_str());

        switch(input) {
            case 0: {
                Matrix<int> sum;
                sum = returnMatrixFromFile() + returnMatrixFromFile();
                cout << "Matrix Sum" << endl;
                sum.writeTo(cout);
                break;
            }

            case 1: {
                Matrix<int> difference;
                difference = returnMatrixFromFile() - returnMatrixFromFile();
                cout << "Matrix Difference" << endl;
                difference.writeTo(cout);
                break;
            }

            case 2: {
                Matrix<int> transposed;
                transposed = returnMatrixFromFile().getTranspose();
                cout << "Matrix Transposed" << endl;
                transposed.writeTo(cout);
            }

        }
    }
}
