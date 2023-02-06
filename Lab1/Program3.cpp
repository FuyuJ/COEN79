/*
Author: Marianne Yamazaki Dorr
Program Description: This program receives a text file as an argument. It will then
    parse through the file line by line. It removes all non-alphabet characters and 
    places the remaining characters into a temporary string variable. It then checks 
    if that string is at least 10 characters long. If it is, it will convert the string
    to uppercase and print that out to the screen.
*/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;


int main(int argc, char* argv[]) {

   //Checks if text file argument has been received.
   if (argc < 1) {
       cout << "No file name entered. Exiting...\n";
       return -1;
   }
   ifstream file(argv[1]); //open the file
   if (file.is_open() && file.good()) {
       // initialize placeholder strings
       string line = "";
       string tempword = "";
       string tempalpha = "";
       //parse through the text file line by line
       while(getline(file, line)) {
           //for each character in a line, add the character to tempword if not a space
           for (int x = 0; x < line.length(); x++) {
               if (!isspace(line[x])) {
                   tempword += line[x];
                //once a space has been encountered, for each character in tempword
                //check if it is an alphabet character then concatenates it to tempalpha
               } else {
                   for (int y = 0; y < tempword.length(); y++) {
                       if (isalpha(tempword[y])) {
                           tempalpha += tempword[y];
                       }
                   }
                   //resets tempword for next word to be processed
                   tempword = "";
                   //checks if tempalpha is at least 10 characters long
                   if (tempalpha.length() >= 10) {
                    //capitalize each letter in tempalpha and prints it
                    for (int z = 0; z < tempalpha.length(); z++) {
                        putchar(toupper(tempalpha[z]));
                    }
                    cout << endl;
                   }
                   //resets tempalpha for next word
                   tempalpha = "";
               }
           }
       }
   }
    file.close();
}