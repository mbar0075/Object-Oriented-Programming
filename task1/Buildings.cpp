//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Building Instance
Buildings::Buildings(int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel) {
    SetBuildingHealth(startingHealth);
    SetUpgradeCost(upgradeCost);
    SetCurrentBuildingLevel(currentBuildingLevel);
    SetMaxBuildingLevel(maxBuildingLevel);
}
//Method, which will be utilised to upgrade a Building
void Buildings::UpgradeBuilding() {
    //Statement below, used to check, if method was overridden
    cout << "Method needs to be overridden";
}
//Getter for Building Upgrade Cost
int Buildings::GetUpgradeCost(){
    return upgradeCost;
}
//Getter for Building Health
int Buildings::GetBuildingHealth(){
    return buildingHealth;
}
//Getter for Current Building Level
int Buildings::GetCurrentBuildingLevel(){
    return currentBuildingLevel;
}
//Getter for Max Building Level
int Buildings::GetMaxBuildingLevel(){
    return maxBuildingLevel;
}
//Setter for Building Health
void Buildings::SetBuildingHealth(int newBuildingHealth){
    this->buildingHealth=newBuildingHealth;
}
//Setter for Building Upgrade Cost
void Buildings::SetUpgradeCost(int newUpgradeCost){
    this->upgradeCost=newUpgradeCost;
}
//Setter for Current Building Level
void Buildings::SetCurrentBuildingLevel(int newCurrentBuildingLevel){
    this->currentBuildingLevel=newCurrentBuildingLevel;
}
//Setter for Max Building Level
void Buildings::SetMaxBuildingLevel(int newMaxBuildingLevel){
    this->maxBuildingLevel=newMaxBuildingLevel;
}
//Destructor for Building Instance
Buildings::~Buildings() {
    //Statement below, used to check, if instance was destroyed
    //cout<< "\nBuilding has been destroyed"<< endl;
}