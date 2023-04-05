//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Resource Instance
Resources::Resources(string resourceName,int startingAmount, int resourceWeight) {
    SetResourceName(resourceName);
    SetResourceAmount(startingAmount);
    SetResourceWeight(resourceWeight);
}
//Method to Increase the Resource Amount, by a specified parameter
void Resources::AddResource(int addamount) {
    SetResourceAmount(GetResourceAmount()+addamount);
}
//Method to Decrease the Resource Amount, by a specified parameter
void Resources::DecResource(int decamount) {
    SetResourceAmount(GetResourceAmount()-decamount);
}
//Getter for Resource Name
string Resources::GetResourceName(){
    return resourceName;
}
//Getter for Resource Amount
int Resources::GetResourceAmount(){
    return resourceAmount;
}
//Getter for Resource Weight
int Resources::GetResourceWeight(){
    return resourceWeight;
}
//Setter for Resource Amount
void Resources::SetResourceAmount(int newResourceAmount){
    this->resourceAmount=newResourceAmount;
}
//Setter for Resource Name
void Resources::SetResourceName(string newResourceName){
    this->resourceName=newResourceName;
}
//Setter for Resource Weight
void Resources::SetResourceWeight(int newResourceWeight){
    this->resourceWeight=newResourceWeight;
}
//Destructor for Resource Instance
Resources::~Resources() {
    //Statement below, used to check, if instance was destroyed
    //cout<<"\n"<<this->resourceName<<" has been destroyed"<< endl;
}