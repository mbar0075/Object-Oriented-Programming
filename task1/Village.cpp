//
// Created by Matthias on 26/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for Village Instance
Village::Village(string playerOwnerName, int xPosition, int yPosition,string villageChar){
    SetPlayerOwnerName(playerOwnerName);
    SetVillageHealth(VILLAGESTARTINGHEALTH);
    SetXPosition(xPosition);
    SetYPosition(yPosition);
    SetVillageChar(villageChar);
    cout<<"\n"<<this->playerOwnerName <<" Created a Village"<<endl;
}
//Method which builds a Resource Generator Building, given Building type
void Village::BuildResourceGeneratorBuilding(string BuildingTypeName){
    //Based on Resource Generator Building type, method, will check if Village has enough Coins Resource,
    //to build Building, if not, no Resource Generator is created, and message is shown.
    //If Village has Sufficient Coins, then cost to build Building, will be reduced from Village Coins Resource
    if(BuildingTypeName==HEXSOURCENAME && Coins->GetResourceAmount()>=HEXSOURCEGENERATORSTARTINGBUILDCOST){
        Coins->DecResource(HEXSOURCEGENERATORSTARTINGBUILDCOST);
    }else if(BuildingTypeName==FOODNAME && Coins->GetResourceAmount()>=FOODGENERATORSTARTINGBUILDCOST){
        Coins->DecResource(FOODGENERATORSTARTINGBUILDCOST);
    }else if(BuildingTypeName==COINSNAME && Coins->GetResourceAmount()>=COINSGENERATORSTARTINGBUILDCOST){
        Coins->DecResource(COINSGENERATORSTARTINGBUILDCOST);
    }else{
        cout <<"\nNot enough Coins, to create "<<BuildingTypeName <<" Resource Generator";
        return;
    }

    //Based on Resource Generator Building type, method, will build the respective building, and add to the village health
    //New Resource Generator building, will be added to the resourceGeneratorBuildings, dynamic list
    if(BuildingTypeName==FOODNAME){
        resourceGeneratorBuildings.push_back(make_unique<ResourceGenerator>(FOODNAME,FOODGENERATORSTARTINGHEALTH,FOODGENERATORUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,FOODRESOURCESGPT));
        SetVillageHealth(GetVillageHealth()+FOODGENERATORSTARTINGHEALTH);
    }
    else if(BuildingTypeName==COINSNAME){
        resourceGeneratorBuildings.push_back(make_unique<ResourceGenerator>(COINSNAME,COINSGENERATORSTARTINGHEALTH,COINSGENERATORUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,COINSRESOURCESGPT));
        SetVillageHealth(GetVillageHealth()+COINSGENERATORSTARTINGHEALTH);
    }
    else if(BuildingTypeName==HEXSOURCENAME){
        resourceGeneratorBuildings.push_back(make_unique<ResourceGenerator>(HEXSOURCENAME,HEXSOURCEGENERATORSTARTINGHEALTH,HEXSOURCEGENERATORUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,HEXSOURCERESOURCESGPT));
        SetVillageHealth(GetVillageHealth()+HEXSOURCEGENERATORSTARTINGHEALTH);
    }
}
//Method which builds a Barracks Building, given Building type
void Village::BuildBarracksBuilding(string BuildingTypeName){
    //Based on Barracks Building type, method, will check if Village has enough Coins Resource,
    //to build Building, if not, no Barrack is created, and message is shown.
    //If Village has Sufficient Coins, then cost to build Building, will be reduced from Village Coins Resource
    if(BuildingTypeName==SOLDIERNAME && Coins->GetResourceAmount()>=SOLDIERBARRACKSSTARTINGBUILDCOST){
        Coins->DecResource(SOLDIERBARRACKSSTARTINGBUILDCOST);
    }else if(BuildingTypeName==WARRIORNAME && Coins->GetResourceAmount()>=WARRIORBARRACKSSTARTINGBUILDCOST){
        Coins->DecResource(WARRIORBARRACKSSTARTINGBUILDCOST);
    }else if(BuildingTypeName==GENERALNAME && Coins->GetResourceAmount()>=GENERALBARRACKSSTARTINGBUILDCOST){
        Coins->DecResource(GENERALBARRACKSSTARTINGBUILDCOST);
    }else{
        cout <<"\nNot enough Coins, to create "<<BuildingTypeName <<" Barracks";
        return;
    }

    //Based on Barracks Building type, method, will build the respective building, and add to the village health
    //New Barracks building, will be added to the barracksBuildings, dynamic list
    if(BuildingTypeName==SOLDIERNAME){
        barracksBuildings.push_back(make_unique<Barracks>(SOLDIERBARRACKSSTARTINGHEALTH,SOLDIERBARRACKSUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,SOLDIERNAME,SOLDIERSTARTINGHEALTH,SOLDIERSPEED,SOLDIERDAMAGE,SOLDIERCARRYWEIGHT,SOLDIERCOST));
        SetVillageHealth(GetVillageHealth()+SOLDIERBARRACKSSTARTINGHEALTH);
    }
    else if(BuildingTypeName==WARRIORNAME){
        barracksBuildings.push_back(make_unique<Barracks>(WARRIORBARRACKSSTARTINGHEALTH,WARRIORBARRACKSUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,WARRIORNAME,WARRIORSTARTINGHEALTH,WARRIORSPEED,WARRIORDAMAGE,WARRIORCARRYWEIGHT,WARRIORCOST));
        SetVillageHealth(GetVillageHealth()+WARRIORBARRACKSSTARTINGHEALTH);
    }
    else if(BuildingTypeName==GENERALNAME){
        barracksBuildings.push_back(make_unique<Barracks>(GENERALBARRACKSSTARTINGHEALTH,GENERALBARRACKSUPGRADECOST,MAXBUILDINGLEVEL,STARTINGBUILDINGLEVEL,GENERALNAME,GENERALSTARTINGHEALTH,GENERALSPEED,GENERALDAMAGE,GENERALCARRYWEIGHT,GENERALCOST));
        SetVillageHealth(GetVillageHealth()+GENERALBARRACKSSTARTINGHEALTH);
    }
}
//Method which upgrades a Barracks Building, given Building type
void Village::UpgradeBarracksBuilding(string BuildingTypeName){
    //Based on Barracks Building type, method, will check if Village has enough HexSource Resource,
    //to build Building, if not, no Barrack is upgraded, and message is shown.
    //If Village has Sufficient HexSource, then cost to build Building, will be reduced from Village HexSource Resource
    if(BuildingTypeName==SOLDIERNAME && HexSource->GetResourceAmount()>=SOLDIERBARRACKSUPGRADECOST){
        HexSource->DecResource(SOLDIERBARRACKSUPGRADECOST);
    }else if(BuildingTypeName==WARRIORNAME && HexSource->GetResourceAmount()>=WARRIORBARRACKSUPGRADECOST){
        HexSource->DecResource(WARRIORBARRACKSUPGRADECOST);
    }else if(BuildingTypeName==GENERALNAME && HexSource->GetResourceAmount()>=GENERALBARRACKSUPGRADECOST){
        HexSource->DecResource(GENERALBARRACKSUPGRADECOST);
    }else{
        cout <<"\nNot enough Hex Source, to upgrade "<<BuildingTypeName <<" Barracks";
        return;
    }

    //Based on Barracks Building type, method, will iterate through all the barracksBuildings, dynamic list, and proceed to upgrade,
    //the barrack building, with the lowest level
    list <unique_ptr<Barracks>> :: iterator it1;
    list <unique_ptr<Barracks>> :: iterator lowestLevel;
    lowestLevel=barracksBuildings.begin();
    for(it1 = barracksBuildings.begin(); it1 != barracksBuildings.end(); it1++) {
        if (((*it1)->GetTroopName() == BuildingTypeName)&&((*it1)->GetCurrentBuildingLevel()<(*lowestLevel)->GetCurrentBuildingLevel())) {
            lowestLevel=it1;
        }

    }
    (*lowestLevel)->UpgradeBuilding();
    //Adding to the Village Health
    SetVillageHealth(GetVillageHealth()+UPGRADEBUILDINGHEALTHINCREASE);
}
//Method which upgrades a Resource Generator Building, given Building type
void Village::UpgradeResourceGeneratorBuilding(string BuildingTypeName){
    //Based on Resource Generator Building type, method, will check if Village has enough HexSource Resource,
    //to build Building, if not, no Resource Generator is upgraded, and message is shown.
    //If Village has Sufficient HexSource, then cost to build Building, will be reduced from Village HexSource Resource
    if(BuildingTypeName==HEXSOURCENAME && HexSource->GetResourceAmount()>=HEXSOURCEGENERATORUPGRADECOST){
        HexSource->DecResource(HEXSOURCEGENERATORUPGRADECOST);
    }else if(BuildingTypeName==FOODNAME && HexSource->GetResourceAmount()>=FOODGENERATORUPGRADECOST){
        HexSource->DecResource(FOODGENERATORUPGRADECOST);
    }else if(BuildingTypeName==COINSNAME && HexSource->GetResourceAmount()>=COINSGENERATORUPGRADECOST){
        HexSource->DecResource(COINSGENERATORUPGRADECOST);
    }else{
        cout <<"\nNot enough Hex Source, to upgrade "<<BuildingTypeName <<" Resource Generator";
        return;
    }

    //Based on Resource Generator Building type, method, will iterate through all the resourceGeneratorBuildings, dynamic list, and proceed to upgrade,
    //the Resource Generator building, with the lowest level
    list <unique_ptr<ResourceGenerator>> :: iterator it1;
    list <unique_ptr<ResourceGenerator>> :: iterator lowestLevel;
    lowestLevel=resourceGeneratorBuildings.begin();
    for(it1 = resourceGeneratorBuildings.begin(); it1 != resourceGeneratorBuildings.end(); it1++) {
        if (((*it1)->GetResourceName() == BuildingTypeName)&&((*it1)->GetCurrentBuildingLevel()<(*lowestLevel)->GetCurrentBuildingLevel())) {
            lowestLevel=it1;
        }

    }
    (*lowestLevel)->UpgradeBuilding();
    //Adding to the Village Health
    SetVillageHealth(GetVillageHealth()+UPGRADEBUILDINGHEALTHINCREASE);
}
//Method which checks if a Resource Generator Building is present in the resourceGeneratorBuildings dynamic list, given Building type
bool Village::CheckResourceGeneratorUpgrade(string BuildingTypeName){
    //Based on Resource Generator Building type, method, will iterate through all the resourceGeneratorBuildings, dynamic list, and checks
    //if the specified Resource Generator Building type is present in said list, if so true is returned, else, false is returned
    list <unique_ptr<ResourceGenerator>> :: iterator it1;
    it1=resourceGeneratorBuildings.begin();
    for(it1 = resourceGeneratorBuildings.begin(); it1 != resourceGeneratorBuildings.end(); it1++) {
        if ((*it1)->GetResourceName() == BuildingTypeName) {
            return true;
        }
    }
    return false;
}
//Method which checks if a Barracks Building is present in the barracksBuildings dynamic list, given Building type
bool Village::CheckBarracksUpgrade(string BuildingTypeName){
    //Based on Barracks Building type, method, will iterate through all the barracksBuildings, dynamic list, and checks
    //if the specified Barracks Building type is present in said list, if so true is returned, else, false is returned
    list <unique_ptr<Barracks>> :: iterator it1;
    it1=barracksBuildings.begin();
    for(it1 = barracksBuildings.begin(); it1 != barracksBuildings.end(); it1++) {
        if ((*it1)->GetTroopName() == BuildingTypeName) {
            return true;
        }
    }
    return false;
}
//Getter for Village Label/Village Character represented on Map
string Village::GetVillageChar() {
    return villageChar;
}
//Setter for Village Label/Village Character represented on Map
void Village::SetVillageChar(string villageChar) {
    this->villageChar=villageChar;
}
//Getter for Village Health
int Village::GetVillageHealth() {
    return villageHealth;
}
//Getter for Village Player Owner
string Village::GetPlayerOwnerName(){
    return playerOwnerName;
}
//Setter for Village Health
void Village::SetVillageHealth(int newHealth) {
    this->villageHealth=newHealth;
}
//Setter for Village Player Owner
void Village::SetPlayerOwnerName(string newName) {
    this->playerOwnerName=newName;
}
//Setter for Village's x Position on the Map
void Village::SetXPosition(int xPosition) {
    this->xPosition=xPosition;
}
//Setter for Village's y Position on the Map
void Village::SetYPosition(int yPosition) {
    this->yPosition=yPosition;
}
//Setter for Village's x Position on the Map
int Village::GetXPosition() {
    return xPosition;
}
//Setter for Village's y Position on the Map
int Village::GetYPosition() {
    return yPosition;
}
//Method, which Displays, the Village's Resources
void Village::DisplayResources(){
    cout <<"\nVillage Resources:"<<endl;
    cout <<"1.HexSource \t Resource Amount:"<<HexSource->GetResourceAmount()<<endl;
    cout <<"2.Food \t\t Resource Amount:"<<Food->GetResourceAmount()<<endl;
    cout <<"3.Coins \t Resource Amount:"<<Coins->GetResourceAmount()<<endl;

}
//Method, which allows a Player to Create Troops, based on user input
void Village::CreateTroops() {
    string userinput;
    list <unique_ptr<Barracks>> :: iterator it1;
    //Checking, if there are sufficient Barracks Buildings, to Create/Train Troops, if not, message is shown
    if(barracksBuildings.empty()){
        cout<<"\nNo Barracks to Train Troops"<<endl;
        return;
    }
    //Iterating, through the barracksBuildings, and asking user whether to Create/Train a Troop, from a specific Barrack
    for(it1 = barracksBuildings.begin(); it1 != barracksBuildings.end(); it1++) {
        cout <<"\nDo you wish to create Troop: "<<(*it1)->GetTroopName()<<endl;
        cout <<"From: "<<(*it1)->GetTroopName()<<" Barracks \t Level : "<<(*it1)->GetCurrentBuildingLevel()<<endl;
        cout <<"Troop Cost: "<<(*it1)->GetTroopCost()<<endl;
        cout <<"Food Resource Amount: "<<Food->GetResourceAmount()<<endl;
        cout <<"EnterChoice:\n 1.Yes\n 2.No"<<endl;
        //User Input
        cin>>userinput;
        if(userinput[0]=='1'){
            //Based on Barrack Building type and user input, method, will check if Village has enough Food Resource,
            //to train Troop, if not, no Troop is created, and message is shown.
            //If Village has Sufficient Food, then cost to train Troop, will be reduced from Village Food Resource
            if(Food->GetResourceAmount()>=(*it1)->GetTroopCost()){
                Food->DecResource((*it1)->GetTroopCost());
                //Creating troop, and appending troop, to the troopsInVillage, dynamic list
                troopsInVillage.push_back((*it1)->CreateTroop());
            }else {
                cout <<"\nNot enough Food, to create Troop "<<endl;
            }
        }else if(userinput[0]!='2'){
            //Proper Input Validation, for Invalid User Input
            cout <<"\nInvalid Option"<<endl;
            it1--;
        }
    }
}
//Method, which allows a Player to Create Troops, based on random choice
void Village::RandomCreateTroops(){
    list <unique_ptr<Barracks>> :: iterator it1;
    //Checking, if there are sufficient Barracks Buildings, to Create/Train Troops, if not, message is shown
    if(barracksBuildings.empty()){
        cout<<"\nNo Barracks to Train Troops"<<endl;
        return;
    }
    //Iterating, through the barracksBuildings, and generating a random choice, to check whether
    //to Create/Train a Troop, from a specific Barrack
    for(it1 = barracksBuildings.begin(); it1 != barracksBuildings.end(); it1++) {
        //Generating random choice
        int choice=rand() % (3);
        if(choice==1){
            //Based on Barrack Building type and random choice, method, will check if Village has enough Food Resource,
            //to train Troop, if not, no Troop is created.
            //If Village has Sufficient Food, then cost to train Troop, will be reduced from Village Food Resource
            if(Food->GetResourceAmount()>=(*it1)->GetTroopCost()){
                cout<<"\nTroop was Created"<<endl;
                Food->DecResource((*it1)->GetTroopCost());
                //Creating troop, and appending troop, to the troopsInVillage, dynamic list
                troopsInVillage.push_back((*it1)->CreateTroop());
            }
        }
    }
}
//Method, which allows a Player to append Troops to an Army, based on user input, and Send mentioned Army, to Attack another Village
unique_ptr<Army> Village::SendAttackingArmy(string playerTarget, int xPosition, int yPosition, string armyLabel){
    //Creating Army Instance
    unique_ptr<Army> attackingArmy= make_unique<Army>(GetPlayerOwnerName(),playerTarget,xPosition,yPosition,GetXPosition(),GetYPosition(),armyLabel);

    string userinput;
    //Iterating, through the troopsInVillage, and asking user whether to append a specific Troop to the Attacking Army
    list <unique_ptr<Troops>> :: iterator it1;
    it1= troopsInVillage.begin();
    while(it1!=troopsInVillage.end()){
        cout <<"\nDo you wish to add Troop to army: "<<(*it1)->GetTroopName()<<endl;
        cout <<"\nTroop: "<<(*it1)->GetTroopName()<<endl;
        cout <<"Troop Health :"<<(*it1)->GetTroopHealth()<<" \t\t Troop Speed:"<<(*it1)->GetTroopSpeed()<<endl;
        cout <<"Troop Carry Weight:"<<(*it1)->GetTroopCarryWeight()<<" \t\t Troop Damage:"<<(*it1)->GetTroopDamage()<<endl;
        cout <<"EnterChoice:\n 1.Yes\n 2.No"<<endl;
        //User Input
        cin>>userinput;
        if(userinput[0]=='1'){
            cout<<"\nTroop was added to army"<<endl;
            //Appending Troop to Attacking Army
            attackingArmy->AddTroop(move(*it1));
            //Erasing Troop, from troopsInVillage, dynamic list
            it1=troopsInVillage.erase(it1);
        }
        else if(userinput[0]!='2'){
            //Proper Input Validation, for Invalid User Input
            cout <<"\nInvalid Option"<<endl;
        }
        else{
            ++it1;
        }
    }
    //Returning Attacking Army Instance
    return attackingArmy;
}
//Method, which allows a Player to append Troops to an Army, based on random choice, and Send mentioned Army, to Attack another Village
unique_ptr<Army> Village::RandomSendAttackingArmy(string playerTarget, int xPosition, int yPosition, string armyLabel){
    //Creating Army Instance
    unique_ptr<Army> attackingArmy= make_unique<Army>(GetPlayerOwnerName(),playerTarget,xPosition,yPosition,GetXPosition(),GetYPosition(),armyLabel);

    //Iterating, through the troopsInVillage, and generating a random choice, to check whether to append a specific Troop to the Attacking Army
    list <unique_ptr<Troops>> :: iterator it1;
    it1= troopsInVillage.begin();
    while(it1!=troopsInVillage.end()){
        //Generating random choice
        int choice=rand() % (3);
        if(choice==1){
            cout<<"\nTroop was added to army"<<endl;
            //Appending Troop to Attacking Army
            attackingArmy->AddTroop(move(*it1));
            //Erasing Troop, from troopsInVillage, dynamic list
            it1=troopsInVillage.erase(it1);
        }
        else{
            ++it1;
        }
    }
    //Returning Attacking Army Instance
    return attackingArmy;
}
//Method, which Retrieves Resources and Troops, from an Army, unique pointer of mentioned Army is passed as a parameter
void Village::RetrieveResources(unique_ptr<Army> friendlyArmy){
    //Retrieving Army Resources, and appending Resources, to the Village's Resources
    Food->AddResource(friendlyArmy->GetFoodAmount());
    Coins->AddResource(friendlyArmy->GetCoinsAmount());
    HexSource->AddResource(friendlyArmy->GetHexSourceAmount());
    //Retrieving all Troops from Army, and appending Troops, to troopsInVillage, dynamic list
    int troopCount=friendlyArmy->GetTroopCount();
    while(troopCount>=1){
        troopsInVillage.push_back(friendlyArmy->GetTroop());
        troopCount=friendlyArmy->GetTroopCount();
    }
    //Freeing Army pointer
    friendlyArmy.reset();
}
//Method, which Generates Resources, from the Resource Generator Buildings
void Village::GenerateResources(){
    list <unique_ptr<ResourceGenerator>> :: iterator it2;
    //Generated Resource Variables, will be used, to hold, the Generated Resource Amount
    int generatedFood=0;
    int generatedCoins=0;
    int generatedHexSource=0;
    //Iterating through all the resourceGeneratorBuildings, dynamic list, and based on Building Type, method will append
    //Generated Resource Amounts, to the Generated Resource Variables
    for(it2 = resourceGeneratorBuildings.begin(); it2 != resourceGeneratorBuildings.end(); it2++) {
        if((*it2)->GetResourceName()==FOODNAME){
            generatedFood+=(*it2)->GetResourceGPT();
        }
        if((*it2)->GetResourceName()==COINSNAME){
            generatedCoins+=(*it2)->GetResourceGPT();
        }
        if((*it2)->GetResourceName()==HEXSOURCENAME){
            generatedHexSource+=(*it2)->GetResourceGPT();
        }
    }
    //Adding amounts, to Village Resources
    Food->AddResource(generatedFood);
    Coins->AddResource(generatedCoins);
    HexSource->AddResource(generatedHexSource);
}
//Method to Decrease the Village Health, by a specified parameter
void Village::TakeDamage(int damage){
    //Creating variable remaining damage, and initialising it to damage
    int remainingDamage=damage;
    //Iterating through all the troops in the troopsInVillage, dynamic list
    list <unique_ptr<Troops>> :: iterator it;
    it = troopsInVillage.begin();
    while(it != troopsInVillage.end()){
        //Creating a variable troopHealth, and getting Troop Health, through Troop Getter
        int troopHealth=(*it)->GetTroopHealth();
        //Reducing, the remaining damage from the troop
        (*it)->TakeDamage(remainingDamage);
        //Reducing the troopHealth, from the remaining damage
        remainingDamage-=troopHealth;
        //Checking if new Troop Health is smaller or equal to 0, if so, will enter if statement
        if((*it)->GetTroopHealth()<=0){
            //Erasing troop from armyTroops, dynamic list
            it=troopsInVillage.erase(it);
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
    //Decreasing the total damage, from the Village Health
    if(remainingDamage>0) {
        SetVillageHealth(GetVillageHealth() - remainingDamage);
    }
}
//Method, which simulates a Fight between an Attacking Army, and a Village, the Attacking Army Damage, is passed as a parameter
int Village::Fight(int attackingArmyDamage) {
    //Variable, will hold the total Village Damage
    int villageDamage = 0;
    //Iterating through all the Troops in troopsInVillage, dynamic list, and appending Troop Damage, to the total Village Damage
    list<unique_ptr<Troops>>::iterator it;
    for (it = troopsInVillage.begin(); it != troopsInVillage.end(); it++){
        villageDamage += (*it)->GetTroopDamage();
    }
    //Calling the TakeDamage method, to reduce the Army Damage, from the Village Health
    TakeDamage(attackingArmyDamage);
    //Returning the Village Damage
    return villageDamage;
}
//Method, which Displays, all the Village's Troops
void Village::DisplayTroops(){
    //Iterating through all the troopsInVillage, dynamic list, and printing out Troop Information for every Troop
    list <unique_ptr<Troops>> :: iterator it1;
    for(it1 = troopsInVillage.begin(); it1 != troopsInVillage.end(); it1++) {
        cout <<"\nTroop: "<<(*it1)->GetTroopName()<<endl;
        cout <<"Troop Health :"<<(*it1)->GetTroopHealth()<<" \t\t Troop Speed:"<<(*it1)->GetTroopSpeed()<<endl;
        cout <<"Troop Carry Weight:"<<(*it1)->GetTroopCarryWeight()<<" \t\t Troop Damage:"<<(*it1)->GetTroopDamage()<<endl;
    }
    //Respective Message, if Village, has no Troops
    if(troopsInVillage.begin()==troopsInVillage.end()){
        cout <<"--Village has no troops to show--"<<endl;
    }
}
//Method, which Displays, all the Village's Buildings
void Village::DisplayBuildings(){
    //Iterating through all the barracksBuildings, dynamic list, and printing out Barrack Information for every Barrack
    list <unique_ptr<Barracks>> :: iterator it1;
    for(it1 = barracksBuildings.begin(); it1 != barracksBuildings.end(); it1++) {
        cout <<"\n"<<(*it1)->GetTroopName()<<" Barracks "<<endl;
        cout<<"Building Level: "<<(*it1)->GetCurrentBuildingLevel()<<endl;
    }
    //Iterating through all the resourceGeneratorBuildings, dynamic list, and printing out Resource Generator Information for every ResourceGenerator
    list <unique_ptr<ResourceGenerator>> :: iterator it2;
    for(it2 = resourceGeneratorBuildings.begin(); it2 != resourceGeneratorBuildings.end(); it2++) {
        cout <<"\n"<<(*it2)->GetResourceName()<<" Resource Generator "<<endl;
        cout<<"Building Level: "<<(*it2)->GetCurrentBuildingLevel()<<endl;
    }
    //Respective Message, if Village, has no Buildings
    if(barracksBuildings.begin()==barracksBuildings.end()&&resourceGeneratorBuildings.begin()==resourceGeneratorBuildings.end()){
        cout <<"--Village has no buildings to show--"<<endl;
    }
}
//Getter for Village Food Resource Amount
int Village::GetVillageFoodAmount(){
    return Food->GetResourceAmount();
}
//Getter for Village Coins Resource Amount
int Village::GetVillageCoinsAmount(){
    return Coins->GetResourceAmount();
}
//Getter for Village HexSource Resource Amount
int Village::GetVillageHexSourceAmount(){
    return HexSource->GetResourceAmount();
}
//Method, which decrements, the Village Coins Resource Amount
void Village::DecVillageCoinsAmount(int amount) {
    Coins->DecResource(amount);
}
//Method, which decrements, the Village HexSource Resource Amount
void Village::DecVillageHexSourceAmount(int amount) {
    HexSource->DecResource(amount);
}
//Method, which decrements, the Village Food Resource Amount
void Village::DecVillageFoodAmount(int amount) {
    Food->DecResource(amount);
}
//Getter for Resource Generator, dynamic list size
int Village::GetResourceGeneratorSize(){
    return resourceGeneratorBuildings.size();
}
//Getter for Barracks, dynamic list size
int Village::GetBarracksSize(){
    return barracksBuildings.size();
}
//Destructor for Village Instance
Village::~Village() {
    //Freeing Resource Pointers
    HexSource.reset();
    Food.reset();
    Coins.reset();
    //Clearing all Troops, in the troopsInVillage, dynamic list
    troopsInVillage.clear();
    //Clearing all Barracks buildings, in the barracksBuildings, dynamic list
    barracksBuildings.clear();
    //Clearing all Resource Generator Buildings, in the resourceGeneratorBuildings, dynamic list
    resourceGeneratorBuildings.clear();
    //Statement below, used to check, if instance was destroyed
    //cout<< "\nVillage has been destroyed"<< endl;
}