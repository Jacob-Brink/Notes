#include "Application.h"


Application::Application()
{
    //ctor
}

void Application::run() {
    string input;
    unsigned numDimensions;

    cout << "Enter number of dimensions: " << flush;

    getline(cin, input);
    numDimensions = stoi(input);

    Vec sum(numDimensions);
    bool invalid = false;


    while (true) {

        //create and fill vector array
        Vec newVector(numDimensions);
        cout << "Enter Coordinate: " << endl;

        //Populate vector array
        for (unsigned i = 0; i < numDimensions; ++i) {

            //Ask at least one time, unless invalid input is given
            do {

                cout << "Dimension " << i << ": ";
                getline(cin, input);
                if (input == "") {
                    invalid = true;
                } else {
                    invalid = false;
                }

            } while (invalid == true);

            newVector.setItem(i, stoi(input));
        }

        //Add vector to sum vector
        sum = sum + newVector;

        //Exit if n is pressed
        cout << "Discontinue adding positions? (q/quit) (Press any other key to continue): " << flush;
        getline(cin, input);
        if (input == "q") {
            break;
        }

    }

    cout << "Sum of vectors: " << flush;
    sum.writeTo(cout);


}
