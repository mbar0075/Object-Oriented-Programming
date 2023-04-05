//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Troop Instance
Troops::Troops(string troopName,int startingHealth,int troopSpeed,int troopDamage,int troopCarryWeight) {
    SetTroopName(troopName);
    SetTroopHealth(startingHealth);
    SetTroopSpeed(troopSpeed);
    SetTroopCarryWeight(troopCarryWeight);
    SetTroopDamage(troopDamage);
}
//Getter for Troop Name
string Troops::GetTroopName(){
    return troopName;
}
//Getter for Troop Health
int Troops::GetTroopHealth(){
    return troopHealth;
}
//Getter for Troop Speed
int Troops::GetTroopSpeed(){
    return troopSpeed;
}
//Getter for Troop Damage
int Troops::GetTroopDamage(){
    return troopDamage;
}
//Getter for Troop Carry Weight
int Troops::GetTroopCarryWeight(){
    return troopCarryWeight;
}
//Setter for Troop Health
void Troops::SetTroopHealth(int newTroopHealth){
    this->troopHealth=newTroopHealth;
}
//Setter for Troop Speed
void Troops::SetTroopSpeed(int newTroopSpeed){
    this->troopSpeed=newTroopSpeed;
}
//Setter for Troop Damage
void Troops::SetTroopDamage(int newTroopDamage){
    this->troopDamage=newTroopDamage;
}
//Setter for Troop Carry Weight
void Troops::SetTroopCarryWeight(int newTroopCarryWeight){
    this->troopCarryWeight=newTroopCarryWeight;
}
//Setter for Troop Name
void Troops::SetTroopName(string newTroopName){
    this->troopName=newTroopName;
}
//Method to Decrease the Troop Health, by a specified parameter
void Troops::TakeDamage(int damage){
    SetTroopHealth(GetTroopHealth()-damage);
}
//Destructor for Troop Instance
Troops::~Troops() {
    //Statement below, used to check, if instance was destroyed
    //cout<< "\nTroop has been destroyed"<< endl;
}