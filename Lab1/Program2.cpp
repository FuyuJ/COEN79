/*
Author: Marianne Yamazaki Dorr
Program Description: The program asks the user to input a string of 10 digits
    with no spaces in between. It will then print out the input number and its
    reverse 5 times with incrementing width using setw().
*/
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

//Boolean method to check if the string is of size 10 and contains only numbers.
bool is_valid(string input) {

    if (input.size() != 10) {
        return false;
    }
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "Input String of 10 digits (no spaces)" << endl;
    string input;
    cin >> input;
    //check if input is valid
    if (is_valid(input)){
        //Initialize new string reversed to hold the reversed version of the input
        string reversed;
        //use for loop to go through the input from the end to the beginning
        for (int i = input.size() - 1; i > -1; i--) {
            reversed += input[i];
        }
        //print out the output 5 times with incrementing width using setw()
        int s = 20; //space between input string and reversed string
        int inc = 12; //whitespace increment for setw()
        int c = 0; // count of while loop
        while (c < 5) {
            cout << std::setw(inc) << input << setw(s) << reversed << endl;
            inc = inc + 2;
            c++;
        } 

    //if invalid, print error message
    } else {
        printf("Invalid input, please run the program again. \n");
    }
}