/* Selection.java computes the letter grade given a student's average grade
 *
 * Input: percent grade
 * Precondition: percent grade is nonnegative and not above 100
 * Output: letter grade
 *
 * Begun by: Dr. Adams, for CS 214, at Calvin College.
 * Completed by: Jacob Brink
 * Date: 2/26/2020
 * Project: 03
 **********************************************************/


import java.util.Scanner;  // include class for Scanner

public class Selection {

     /* function getLetter computes the letter grade
      * Parameter: average, an integer
      * Precondition: average is nonnegative and not above 100
      * Returns: letter in string format
      */
     public static String getLetter(int average) {
	 switch(average / 10) {
	 case 10:
	     return "A";
	 case 9:
	     return "A";
	 case 8:
	     return "B";
	 case 7:
	     return "C";
	 case 6:
	     return "D";
	 default:
	     return "F";
	 }
     }


     /* function testGetLetter outputs clearly what is being tested and whether or not the test passed
      * Parameter: inputAverage (integer), expectedOutput (String)
      * Precondition: inputAverage is not negative and not greater than 100
      * Returns: void
      */
    public static void testGetLetter(int inputAverage, String expectedOutput) {
	System.out.println("Asserting getLetter(" + inputAverage + ") equals " + expectedOutput);
	if (getLetter(inputAverage) == expectedOutput)
	    System.out.println("Success");
	else
	    System.out.println("Fail");
    }

     /* function runTests runs tests on getLetter method
      * Parameter: none
      * Precondition: none
      * Returns: void
      */
    public static void runTests() {
	System.out.println("Running tests...");
	testGetLetter(100, "A");
	testGetLetter(95, "A");
	testGetLetter(90, "A");
	testGetLetter(85, "B");
	testGetLetter(80, "B");
	testGetLetter(75, "C");
	testGetLetter(70, "C");
	testGetLetter(65, "D");
	testGetLetter(60, "D");
	testGetLetter(55, "F");
	testGetLetter(30, "F");
    }
	
  // main program
  public static void main(String[] args) {
      runTests();
  } // main method

} // class CircleArea

