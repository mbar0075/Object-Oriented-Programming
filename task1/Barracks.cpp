//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Barracks Building Instance
Barracks::Barracks(int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel,string troopName,int startingTroopHealth,int troopSpeed,int troopDamage,int troopCarryWeight,int troopCost)
        : Buildings(startingHealth,upgradeCost,maxBuildingLevel,currentBuildingLevel){
    SetTroopName(troopName);
    SetTroopDamage(troopDamage);
    SetTroopCarryWeight(troopCarryWeight);
    SetTroopSpeed(troopSpeed);
    SetTroopHealth(startingTroopHealth);
    SetTroopCost(troopCost);
    cout<<"\nCreated "<<this->troopName <<" Barracks\n";
}
//Method, which will be utilised to upgrade a Barracks Building
void Barracks::UpgradeBuilding() {
    //Checking if Current Building Level is smaller, than Max Building Level, if so
    //will proceed to upgrade, else, and output is shown to the user
    if (GetMaxBuildingLevel()>GetCurrentBuildingLevel()){
        //Setting the new Upgraded Building stats for the Building
        SetCurrentBuildingLevel(GetCurrentBuildingLevel()+1);
        SetUpgradeCost(GetUpgradeCost()+UPGRADECOSTAINCREASE);
        SetBuildingHealth(GetBuildingHealth()+UPGRADEBUILDINGHEALTHINCREASE);
        SetTroopCost(GetTroopCost()+TROOPCOSTINCREASE);
        cout << "\nUpgraded "<<GetTroopName()<<" Barracks\n";
    }
    else{
        cout << "\nYour building exceeded the Max level, you cannot upgrade it further";
    }
}
//Method which Creates and Returns a new Troop
unique_ptr<Troops> Barracks::CreateTroop(){
    return make_unique<Troops>(GetTroopName(),GetTroopHealth()*GetCurrentBuildingLevel(),GetTroopSpeed(),GetTroopDamage()*GetCurrentBuildingLevel(),GetTroopCarryWeight());
}
//Getter for Building Troop Name
string Barracks::GetTroopName(){
    return troopName;
}
//Getter for Building Troop Health
int Barracks::GetTroopHealth(){
    return startingTroopHealth;
}
//Getter for Building Troop Speed
int Barracks::GetTroopSpeed(){
    return troopSpeed;
}
//Getter for Building Troop Damage
int Barracks::GetTroopDamage(){
    return troopDamage;
}
//Getter for Building Troop Carry Weight
int Barracks::GetTroopCarryWeight(){
    return troopCarryWeight;
}
//Getter for Building Troop Cost
int Barracks::GetTroopCost() {
    return troopCost;
}
//Setter for Building Troop Cost
void Barracks::SetTroopCost(int newTroopCost) {
    this->troopCost=newTroopCost;
}
//Setter for Building Troop Health
void Barracks::SetTroopHealth(int newTroopHealth){
    this->startingTroopHealth=newTroopHealth;
}
//Setter for Building Troop Speed
void Barracks::SetTroopSpeed(int newTroopSpeed){
    this->troopSpeed=newTroopSpeed;
}
//Setter for Building Troop Damage
void Barracks::SetTroopDamage(int newTroopDamage){
    this->troopDamage=newTroopDamage;
}
//Setter for Building Troop Carry Weight
void Barracks::SetTroopCarryWeight(int newTroopCarryWeight){
    this->troopCarryWeight=newTroopCarryWeight;
}
//Setter for Building Troop Name
void Barracks::SetTroopName(string newTroopName){
    this->troopName=newTroopName;
}
//Destructor for Barracks Building Instance
Barracks::~Barracks() {
    //Statement below, used to check, if instance was destroyed
    //cout<< "\n"<<GetTroopName()<<" Barracks has been destroyed"<< endl;
}