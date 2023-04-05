//
// Created by Matthias on 28/12/2022.
//
#include "headerFile.h"
//Constructor for Cell Instance
Cell::Cell() {
    SetCellState(CELLCHARACTERINITIAL);
}
//Setter for Cell State
void Cell::SetCellState(string State) {
    this->cellState=State;
}
//Getter for Cell State
string Cell::GetCellState() {
    return cellState;
}
//Method to change the Cell State, by a specified parameter
void Cell::ChangeCellState(string State) {
    SetCellState(State);
}
//Destructor for Cell Instance
Cell::~Cell() {
    //Statement below, used to check, if instance was destroyed
    //cout<<"\nCell has been destroyed"<< endl;
}