//
// Created by Matthias on 30/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Method, which returns a valid user input, in a specified range
int InputValidation::GetValidInput(int minrange, int maxrange){
    //Declaring variable, which will be used for loop
    bool Loop=true;
    //Declaring variable, which hold the user input
    int userinput;
    //Looping until a valid user input is entered
    while(Loop==true) {
        //Getting user input, and storing in variable
        cout << "\nEnter Choice (Input needs to be in range of "<<minrange<<"-"<<maxrange<<"):"<< endl;
        cin >> userinput;
        //Checking if cin failed, and whether user input is in incorrect range, if so, will enter if statement
        if (cin.fail() || (userinput < minrange || userinput > maxrange)) {
            //Printing out relevant message to the user, and clearing cin
            cout << "\nInvalid Option"<< endl;
            cin.clear();
            //Storing incorrect input, in string buffer, to allow the user to re-enter a choice
            string incorrectInput;
            getline(cin,incorrectInput);
            //Resetting user input and loop condition
            userinput=0;
            Loop = true;
        } else {
            //Setting appropriate condition, to terminate loop
            Loop = false;
        }
    }
    //Returning user input
    return userinput;
}