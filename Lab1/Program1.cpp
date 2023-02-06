/*
Author: Marianne Yamazaki Dorr
Program Description: The program asks the user to enter a string. It will then
    count and print the number of alphanumeric and non-alphanumeric characters 
    in the user input.
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
using namespace std;

//A program that counts the number of alphanumeric and non-alphanumeric
//characters in the user input.
int main() {
    //initialize input as a string
    string input;
    //print message to user
    cout << "Please type something. \n";
    //retrieve user input into string input
    getline (cin, input);

    //get length of input and place into integer n
    int n = input.size();
    //initialize integer num_alpha which will hold the # of alphanumeric characters
    int num_alpha = 0;
    //initialize integer num_non_alpha which will hold the # of non-alphanumeric characters
    int num_non_alpha = 0;
    //Go through the input string with a for loop and increment num_alpha if the character is alphanumeric
    //same for num_non_alpha
    for (int i = 0; i < n; i++) {
        if (isalnum(input[i])) {
            num_alpha++;
        }
        if (!isspace(input[i]) && !isalnum(input[i]))
        {
            num_non_alpha++;
        }
    }

    //print result to console
    cout << '"' << input << '"' << " has " << num_alpha << " alphanumeric characters and ";
    cout << num_non_alpha << " non-alphanumeric characters.\n";  
}