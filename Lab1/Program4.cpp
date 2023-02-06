/*
Author: Marianne Yamazaki Dorr
Program Description: This program asks the user to think of a number between 1 and
    20. It will then proceed to guess the user's number while keeping track of previous
    guesses in an array. If it guesses all 20 numbers without the user saying yes, it 
    will end the program. If the user says yes to one of the guesses, the program will
    print out a statement saying how many steps it took for the program to find the number.
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <vector>
using namespace std;

//Boolean function that checks if the program guessed wrong.
bool wrong_guess(string in) {
    if( in == "n" || in == "N" || in == "no" || in == "No") {
            return true;
        }
    return false;
}

//Boolean function that checks if the input is valid. Either yes or no, in differing
//string formats.
bool valid_input(string in) {
    if( in == "n" || in == "N" || in == "no" || in == "No"
        || in == "y" || in == "Y" || in == "yes" || in == "Yes") {
            return true;
        }
    return false;
}

//Boolean function that checks if the number the program is guessing has already been
//guessed beforehand.
bool match_guess(vector<int> arr, int guess) {
    for (int i = 0; i < arr.size(); i++) {
        if(arr[i] == guess) {
            return true;
        }
    }
    return false;
}

int main() {

    //Asks the user to think of a number and to press enter when ready.
    cout << "Think of a number between 1 and 20. Press enter when you are ready.\n";
    //sets the counter to 0 to keep track of the # of steps 
    int counter = 0;
    //sets the input string to no so that the program starts guessing
    string input = "N";
    //initialize the vector array of guesses
    vector<int> guesses;
    //ignore the cin when user presses enter.
    cin.ignore();

    //checks if the input is no and all numbers havent been guessed yet, keeps guessing
    while (wrong_guess(input) && guesses.size() < 20) {
        //initializes a random number
        srand((unsigned) time(0));
        int number = rand()%20;
        //as long as the program hasn't guessed all 20 numbers, it will keep guessing.
        if(guesses.size() <= 20) {
            //regenarates a random number if it has already been guessed.
            while(match_guess(guesses, number)) {
                number = rand()%20;
            }
            //adds the new guess to the array of guesses
            guesses.push_back(number);
            //prints out if the number is correct
            cout << "Is the number " << number << "? Y or N\n";
            //receives the new input
            getline (cin, input);

            //if input is invalid, asks user to reinput until a valid one has been received.
            while(!valid_input(input)) {
                cout << "Please enter a valid input. Either Y or N.\n";
                getline (cin, input);
            }
            //increase the counter to add another step   
            counter++;
        }

        //if user says yes, program prints out in how many steps it found the number in.
        if (input == "Y" || input == "y" || input == "yes" || input == "Yes") {
            cout << "I found the number in " << counter << " steps.\n";
        }
    }
    //if user keeps saying no, but all numbers have been guessed, program ends. 
    cout << "All numbers between 0-20 have been guessed. Ending program.\n";
}