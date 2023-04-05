//
// Created by Matthias on 27/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Army Instance
Army::Army(string playerOwner,string playerTarget, int xPosition, int yPosition,int xInitialPosition, int yInitialPosition,string armyLabel) {
    SetPlayerTarget(playerTarget);
    SetPlayerOwner(playerOwner);
    SetArmySpeed(GENERALSPEED);
    SetArmyInitialYPosition(yInitialPosition);
    SetArmyInitialXPosition(xInitialPosition);
    SetArmyXPosition(xPosition);
    SetArmyYPosition(yPosition);
    SetArmyLabel(armyLabel);
    SetTroopCount(0);
    SetArmyCarryWeight(0);
    SetArmyHealth(0);
    SetArmyDamage(0);
}
//Getter for Army Player Target
string Army::GetPlayerTarget() {
    return playerTarget;
}
//Getter for Army Label/Army Character represented on Map
string Army::GetArmyLabel() {
    return armyLabel;
}
//Getter for Army Player Owner
string Army::GetPlayerOwner() {
    return playerOwner;
}
//Getter for Army Health
int Army::GetArmyHealth(){
    return armyHealth;
}
//Getter for Army Carry Weight
int Army::GetArmyCarryWeight(){
    return armyCarryWeight;
}
//Getter for Army Speed
int Army::GetArmySpeed(){
    return armySpeed;
}
//Getter for Army Damage
int Army::GetArmyDamage(){
    return armyDamage;
}
//Method which updates the Army's x Position on the Map, by a specified parameter
void Army::UpdateArmyXPosition(int xPosition){
    SetArmyXPosition(xPosition);
}
//Method which updates the Army's y Position on the Map, by a specified parameter
void Army::UpdateArmyYPosition(int yPosition){
    SetArmyYPosition(yPosition);
}
//Setter for Army Speed
void Army::SetArmySpeed(int newArmySpeed) {
    this->armySpeed=newArmySpeed;
}
//Setter for Army Player Target
void Army::SetPlayerTarget(string newplayerTarget) {
    this->playerTarget=newplayerTarget;
}
//Setter for Army Player Owner
void Army::SetPlayerOwner(string newplayerOwner) {
    this->playerOwner=newplayerOwner;
}
//Setter for Army Health
void Army::SetArmyHealth(int newArmyHealth) {
    this->armyHealth=newArmyHealth;
}
//Setter for Army Carry Weight
void Army::SetArmyCarryWeight(int newArmyCarryWeight) {
    this->armyCarryWeight=newArmyCarryWeight;
}
//Setter for Army Damage
void Army::SetArmyDamage(int newArmyDamage) {
    this->armyDamage=newArmyDamage;
}
//Setter for Army's x Position on the Map
void Army::SetArmyXPosition(int xPosition) {
    this->xPosition=xPosition;
}
//Setter for Army's y Position on the Map
void Army::SetArmyYPosition(int yPosition) {
    this->yPosition=yPosition;
}
//Setter for Army's initial x Position on the Map
void Army::SetArmyInitialXPosition(int xPosition) {
    this->initialxPosition=xPosition;
}
//Setter for Army's initial y Position on the Map
void Army::SetArmyInitialYPosition(int yPosition) {
    this->initialyPosition=yPosition;
}
//Setter for Army Label/Army Character represented on Map
void Army::SetArmyLabel(string armyLabel) {
    this->armyLabel=armyLabel;
}
//Setter for Army Troop Count
void Army::SetTroopCount(int TroopCount) {
    this->TroopCount=TroopCount;
}
//Getter for Army Troop Count
int Army::GetTroopCount() {
    return TroopCount;
}
//Getter for Army's x Position on the Map
int Army::GetArmyXPosition() {
    return xPosition;
}
//Getter for Army's y Position on the Map
int Army::GetArmyYPosition() {
    return yPosition;
}
//Getter for Army's initial x Position on the Map
int Army::GetArmyInitialXPosition() {
    return initialxPosition;
}
//Getter for Army's initial y Position on the Map
int Army::GetArmyInitialYPosition() {
    return initialyPosition;
}
//Method to Increase the Army Food Amount, by a specified parameter
void Army::AddFoodAmount(int addamount){
    Food->AddResource(addamount);
}
//Method to Increase the Army Hex Source Amount, by a specified parameter
void Army::AddHexSourceAmount(int addamount){
    HexSource->AddResource(addamount);
}
//Method to Increase the Army Coins Amount, by a specified parameter
void Army::AddCoinsAmount(int addamount){
    Coins->AddResource(addamount);
}
//Method, which adds a troop to the Army, method takes a Troops unique pointer as a parameter
void Army::AddTroop(unique_ptr<Troops> troop) {
    //Utilising relevant Setter, to Update, the Army's variables
    SetArmyCarryWeight(GetArmyCarryWeight()+troop->GetTroopCarryWeight());
    SetArmyHealth(GetArmyHealth()+troop->GetTroopHealth());
    SetArmyDamage(GetArmyDamage()+troop->GetTroopDamage());
    SetTroopCount(GetTroopCount()+1);
    //Pushing troop onto armyTroops dynamic List, by utilising move command
    armyTroops.push_back(move(troop));
    //Calling  Function, to calculate, the new Marching Speed, for the Army
    GetNewMarchingSpeed();
}
//Method, which calculates, the new Marching Speed, for the Army
void Army::GetNewMarchingSpeed(){
    //Iterating through all the troops in the armyTroops, dynamic list, to obtain the minimum troop speed
    list <unique_ptr<Troops>> :: iterator it1;
    for(it1 = armyTroops.begin(); it1 != armyTroops.end(); it1++) {
        if ((*it1)->GetTroopSpeed() < armySpeed) {
            //Setting minimum troop speed to Army Speed
            SetArmySpeed((*it1)->GetTroopSpeed());
        }
    }
}
//Method, which returns the first troop in the Army
unique_ptr<Troops> Army::GetTroop() {
    //Retrieving, the first troop in the armyTroops, dynamic list
    list <unique_ptr<Troops>> :: iterator it1;
    it1 = armyTroops.begin();
    //Creating a new unique pointer of Troops, and through move function, setting it2 to point to the first troop
    unique_ptr<Troops> it2=move(*it1);
    //Erasing first troop form armyTroops, dynamic list
    armyTroops.erase(it1);
    //Returning pointer, through move function
    //Setting the Troop Count to the armyTroops, dynamic list size
    SetTroopCount(armyTroops.size());
    return it2;
}
//Method to Decrease the Army Health, by a specified parameter
void Army::TakeDamage(int damage){
    //Creating variable remaining damage, and initialising it to damage
    int remainingDamage=damage;
    //Iterating through all the troops in the armyTroops, dynamic list
    list <unique_ptr<Troops>> :: iterator it;
    it = armyTroops.begin();
    while(it != armyTroops.end()){
        //Creating a variable troopHealth, and getting Troop Health, through Troop Getter
        int troopHealth=(*it)->GetTroopHealth();
        //Reducing, the remaining damage from the troop
        (*it)->TakeDamage(remainingDamage);
        //Reducing the troopHealth, from the remaining damage
        remainingDamage-=troopHealth;
        //Checking if new Troop Health is smaller or equal to 0, if so, will enter if statement
        if((*it)->GetTroopHealth()<=0){
            //Utilising relevant Setters and Getters, to Update, the Army's variables
            SetArmyDamage(GetArmyDamage()-(*it)->GetTroopDamage());
            SetArmyCarryWeight(GetArmyCarryWeight()-(*it)->GetTroopCarryWeight());
            GetNewMarchingSpeed();
            //Erasing troop from armyTroops, dynamic list
            it=armyTroops.erase(it);
        }
        else{
            //Incrementing iterator
            ++it;
        }
        //Checking if remaining damage is smaller than or equal to 0, if so, will break from loop
        if(remainingDamage<=0){
            break;
        }
    }
    //Decreasing the total damage, from the Army Health
    SetArmyHealth(GetArmyHealth() - damage);
}
//Getter for Army Food Amount
int Army::GetFoodAmount(){
    return Food->GetResourceAmount();
}
//Getter for Army Coins Amount
int Army::GetCoinsAmount(){
    return Coins->GetResourceAmount();
}
//Getter for Army Hex Source Amount
int Army::GetHexSourceAmount(){
    return HexSource->GetResourceAmount();
}
//Method, which changes the Army's Player Target, by a specified parameter
void Army::ChangePlayerTarget(string playerTarget){
    SetPlayerTarget(playerTarget);
}
//Destructor for Army Instance
Army::~Army() {
    //Freeing Resource Pointers
    HexSource.reset();
    Food.reset();
    Coins.reset();
    //Clearing all Troops, in the armyTroops, dynamic list
    armyTroops.clear();
    //Statement below, used to check, if instance was destroyed
    //cout<< "\nArmy has been destroyed"<< endl;
}