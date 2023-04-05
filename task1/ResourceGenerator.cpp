//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Resource Generator Building Instance
ResourceGenerator::ResourceGenerator(string resourceName,int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel,int resourcesGPT)
    : Buildings(startingHealth,upgradeCost,maxBuildingLevel,currentBuildingLevel){
    SetResourcesGPT(resourcesGPT);
    SetResourceName(resourceName);
    cout<<"\nCreated "<<resourceName<<" Resource Generator\n";
}
//Method, which will be utilised to upgrade a Resource Generator Building
void ResourceGenerator::UpgradeBuilding() {
    //Checking if Current Building Level is smaller, than Max Building Level, if so
    //will proceed to upgrade, else, and output is shown to the user
    if (GetMaxBuildingLevel()>GetCurrentBuildingLevel()){
        //Setting the new Upgraded Building stats for the Building
        SetCurrentBuildingLevel(GetCurrentBuildingLevel()+1);
        SetResourcesGPT(GetResourceGPT()*2);
        SetUpgradeCost(GetUpgradeCost()+UPGRADECOSTAINCREASE);
        SetBuildingHealth(GetBuildingHealth()+UPGRADEBUILDINGHEALTHINCREASE);
        cout << "\nUpgraded "<<GetResourceName()<<" Resource Generator\n";
    }
    else{
        cout << "\nYour building exceeded the Max level, you cannot upgrade it further\n";
    }
}
//Setter for Building Resources Generated Per Turn
void ResourceGenerator::SetResourcesGPT(int newResourceGPT){
    this->resourcesGPT=newResourceGPT;
}
//Getter for Building Resources Generated Per Turn
int ResourceGenerator::GetResourceGPT(){
    return resourcesGPT;
}
//Getter for Building Resource Name
string ResourceGenerator::GetResourceName(){
    return resourceName;
}
//Setter for Building Resource Name
void ResourceGenerator::SetResourceName(string newResourceName) {
    this->resourceName=newResourceName;
}
//Destructor for Resource Generator Building Instance
ResourceGenerator::~ResourceGenerator(){
    //Statement below, used to check, if instance was destroyed
    //cout<< "\n"<<GetResourceName()<<" Resource Generator has been destroyed"<< endl;
}