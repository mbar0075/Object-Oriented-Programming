//
// Created by Matthias on 26/12/2022.
//
//Inclusion of Libraries
#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <ctime>
using namespace std;

/* Resources Utilised:
 *  1. Coins Resource - utilised to Build Buildings
 *  2. Food Resource - utilised to Train Troops
 *  3. Hex Source Resource - utilised to Upgrade Buildings
 *
 * Troops Utilised:
 *  1. Soldier Troop - a troop which has the least stats
 *  2. Warrior Troop - a troop which has medium stats
 *  3. General Troop - a troop which has the best stats
 *
 * Buildings Utilised:
 *  1. Coin Generator Building - utilised to Generate Coins Resource
 *  2. Food Generator Building - utilised to Generate Food Resource
 *  3. Hex Source Generator Building - utilised to Generate Hex Source Resource
 *  4. Soldier Barracks Building - utilised to Train/Make a Soldier Troop
 *  5. Warrior Barracks Building - utilised to Train/Make a Warrior Troop
 *  6. General Barracks Building - utilised to Train/Make a General Troop
 */

//Resource Constants:
//Food Resource Constants:
const string FOODNAME="Food";
const int FOODSTARTINGAMOUNT=30;
const int FOODRESOURCEWEIGHT=2;
//Coins Resource Constants:
const string COINSNAME="Coins";
const int COINSSTARTINGAMOUNT=30;
const int COINSRESOURCEWEIGHT=3;
//Hex Source Resource Constants:
const string HEXSOURCENAME="Hex Source";
const int HEXSOURCESTARTINGAMOUNT=15;
const int HEXSOURCERESOURCEWEIGHT=7;

//Troops Constants:
//Soldier Troop Constants:
const string SOLDIERNAME="Soldier";
const int SOLDIERSTARTINGHEALTH=5;
const int SOLDIERDAMAGE=5;
const int SOLDIERSPEED=1;
const int SOLDIERCARRYWEIGHT=10;
//Warrior Troop Constants:
const string WARRIORNAME="Warrior";
const int WARRIORSTARTINGHEALTH=20;
const int WARRIORDAMAGE=15;
const int WARRIORSPEED=2;
const int WARRIORCARRYWEIGHT=15;
//General Troop Constants:
const string GENERALNAME="General";
const int GENERALSTARTINGHEALTH=30;
const int GENERALDAMAGE=20;
const int GENERALSPEED=3;
const int GENERALCARRYWEIGHT=25;

//Buildings Constants:
//General Buildings Constants (which will be shared by all buildings):
const int STARTINGBUILDINGLEVEL=1;
const int MAXBUILDINGLEVEL=10;
const int UPGRADECOSTAINCREASE=10;
const int UPGRADEBUILDINGHEALTHINCREASE=10;
const int TROOPCOSTINCREASE=2;
//Food Generator Building Constants:
const int FOODGENERATORSTARTINGBUILDCOST=5;
const int FOODGENERATORSTARTINGHEALTH=10;
const int FOODGENERATORUPGRADECOST=5;
const int FOODRESOURCESGPT=5;
//Coins Generator Building Constants:
const int COINSGENERATORSTARTINGBUILDCOST=10;
const int COINSGENERATORSTARTINGHEALTH=15;
const int COINSGENERATORUPGRADECOST=10;
const int COINSRESOURCESGPT=5;
//Hex Source Generator Building Constants:
const int HEXSOURCEGENERATORSTARTINGBUILDCOST=15;
const int HEXSOURCEGENERATORSTARTINGHEALTH=15;
const int HEXSOURCEGENERATORUPGRADECOST=20;
const int HEXSOURCERESOURCESGPT=1;
//Soldier Barracks Building Constants:
const int SOLDIERBARRACKSSTARTINGBUILDCOST=5;
const int SOLDIERBARRACKSSTARTINGHEALTH=15;
const int SOLDIERBARRACKSUPGRADECOST=5;
const int SOLDIERCOST=5;
//Warrior Barracks Building Constants:
const int WARRIORBARRACKSSTARTINGBUILDCOST=10;
const int WARRIORBARRACKSSTARTINGHEALTH=20;
const int WARRIORBARRACKSUPGRADECOST=10;
const int WARRIORCOST=10;
//General Barracks Building Constants:
const int GENERALBARRACKSSTARTINGBUILDCOST=15;
const int GENERALBARRACKSSTARTINGHEALTH=25;
const int GENERALBARRACKSUPGRADECOST=20;
const int GENERALCOST=20;

//Village Constants:
const int VILLAGESTARTINGHEALTH=100;

//GameMapManager Constants
const string CELLCHARACTERINITIAL="_";
const int MAPWIDTH=14;
const int MAPHEIGHT=14;

//Input Validation Constants:
const int MINRANGENORMALPLAYERS=1;
const int MAXRANGENORMALPLAYERS=7;
const int MINRANGEAIPLAYERS=0;
const int MAXRANGEAIPLAYERS=7;


//Resources Class, with its respective class variables and methods:
class Resources{
private:
    string resourceName;
    int resourceAmount;
    int resourceWeight;
    void SetResourceAmount(int newResourceAmount);
    void SetResourceName(string newResourceName);
    void SetResourceWeight(int newResourceWeight);
public:
    Resources()=default;
    Resources(string resourceName,int startingAmount, int resourceWeight);
    void AddResource(int addamount);
    void DecResource(int decamount);
    string GetResourceName();
    int GetResourceAmount();
    int GetResourceWeight();
    ~Resources();
};

//Troops Class, with its respective class variables and methods:
class Troops{
private:
    string troopName;
    int troopHealth;
    int troopSpeed;
    int troopDamage;
    int troopCarryWeight;
    void SetTroopHealth(int newTroopHealth);
    void SetTroopSpeed(int newTroopSpeed);
    void SetTroopDamage(int newTroopDamage);
    void SetTroopCarryWeight(int newTroopCarryWeight);
    void SetTroopName(string newTroopName);
public:
    Troops()=default;
    Troops(string troopName,int startingHealth,int troopSpeed,int troopDamage,int troopCarryWeight);
    string GetTroopName();
    int GetTroopHealth();
    int GetTroopSpeed();
    int GetTroopDamage();
    int GetTroopCarryWeight();
    void TakeDamage(int damage);
    ~Troops();
};

//Buildings Class, with its respective class variables and methods:
class Buildings{
protected:
    int buildingHealth;
    int upgradeCost;
    int maxBuildingLevel;
    int currentBuildingLevel;
    void SetBuildingHealth(int newBuildingHealth);
    void SetUpgradeCost(int newUpgradeCost);
    void SetCurrentBuildingLevel(int newCurrentBuildingLevel);
    void SetMaxBuildingLevel(int newMaxBuildingLevel);
public:
    Buildings()=default;
    Buildings(int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel);
    virtual void UpgradeBuilding();//virtual since it will always need to be overridden
    int GetUpgradeCost();
    int GetBuildingHealth();
    int GetCurrentBuildingLevel();
    int GetMaxBuildingLevel();
    ~Buildings();
};

//Resource Generator Building Class (class is inheriting from Buildings class), with its respective class variables and methods:
class ResourceGenerator : public Buildings{
private:
    int resourcesGPT;
    string resourceName;
    void SetResourcesGPT(int newResourceGPT);
    void SetResourceName(string newResourceName);
public:
    ResourceGenerator()=default;
    ResourceGenerator(string resourceName,int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel,int resourcesGPT);
    void UpgradeBuilding() override;
    int GetResourceGPT();
    string GetResourceName();
    ~ResourceGenerator();
};

//Barracks Building Class (class is inheriting from Buildings class), with its respective class variables and methods:
class Barracks : public Buildings{
private:
    string troopName;
    int startingTroopHealth;
    int troopSpeed;
    int troopDamage;
    int troopCarryWeight;
    int troopCost;
    void SetTroopHealth(int newTroopHealth);
    void SetTroopSpeed(int newTroopSpeed);
    void SetTroopDamage(int newTroopDamage);
    void SetTroopCarryWeight(int newTroopCarryWeight);
    void SetTroopName(string newTroopName);
    void SetTroopCost(int newTroopCost);
public:
    Barracks()=default;
    Barracks(int startingHealth,int upgradeCost,int maxBuildingLevel,int currentBuildingLevel,string troopName,int startingTroopHealth,int troopSpeed,int troopDamage,int troopCarryWeight, int troopCost);
    void UpgradeBuilding() override;
    string GetTroopName();
    int GetTroopHealth();
    int GetTroopSpeed();
    int GetTroopDamage();
    int GetTroopCost();
    int GetTroopCarryWeight();
    unique_ptr<Troops> CreateTroop();
    ~Barracks();
};

//Army Class, with its respective class variables and methods:
class Army{
private:
    int armyHealth;
    string playerTarget;
    string playerOwner;
    string armyLabel;
    int armyCarryWeight;
    int armySpeed;
    int armyDamage;
    int xPosition;
    int yPosition;
    int initialxPosition;
    int initialyPosition;
    int TroopCount;
    list< unique_ptr<Troops>> armyTroops;
    unique_ptr<Resources> HexSource=make_unique<Resources>(HEXSOURCENAME,0,HEXSOURCERESOURCEWEIGHT);
    unique_ptr<Resources> Food=make_unique<Resources>(FOODNAME,0,FOODRESOURCEWEIGHT);
    unique_ptr<Resources> Coins=make_unique<Resources>(COINSNAME,0,COINSRESOURCEWEIGHT);
    void SetArmyHealth(int newArmyHealth);
    void SetPlayerTarget(string newplayerTarget);
    void SetPlayerOwner(string newplayerOwner);
    void SetArmyCarryWeight(int newArmyCarryWeight);
    void SetArmySpeed(int newArmySpeed);
    void SetArmyDamage(int newArmyDamage);
    void SetArmyXPosition(int xPosition);
    void SetArmyYPosition(int yPosition);
    void SetArmyInitialXPosition(int xPosition);
    void SetArmyInitialYPosition(int yPosition);
    void SetTroopCount(int TroopCount);
    void SetArmyLabel(string armyLabel);

public:
    Army()=default;
    Army(string playerOwner,string playerTarget, int xPosition, int yPosition,int xInitialPosition, int yInitialPosition,string armyLabel);
    int GetArmyHealth();
    string GetPlayerTarget();
    string GetPlayerOwner();
    int GetArmyCarryWeight();
    int GetArmySpeed();
    int GetArmyDamage();
    void TakeDamage(int damage);
    int GetArmyXPosition();
    int GetArmyYPosition();
    int GetArmyInitialXPosition();
    int GetArmyInitialYPosition();
    int GetTroopCount();
    int GetFoodAmount();
    int GetCoinsAmount();
    int GetHexSourceAmount();
    string GetArmyLabel();
    void UpdateArmyXPosition(int xPosition);
    void UpdateArmyYPosition(int yPosition);
    void AddTroop(unique_ptr<Troops> troop);
    void ChangePlayerTarget(string playerTarget);
    void AddFoodAmount(int addamount);
    void AddHexSourceAmount(int addamount);
    void AddCoinsAmount(int addamount);
    void GetNewMarchingSpeed();
    unique_ptr<Troops> GetTroop();
    ~Army();
};

//Village Class, with its respective class variables and methods:
class Village{
private:
    int villageHealth;
    int xPosition;
    int yPosition;
    string playerOwnerName;
    string villageChar;
    unique_ptr<Resources> HexSource=make_unique<Resources>(HEXSOURCENAME,HEXSOURCESTARTINGAMOUNT,HEXSOURCERESOURCEWEIGHT);
    unique_ptr<Resources> Food=make_unique<Resources>(FOODNAME,FOODSTARTINGAMOUNT,FOODRESOURCEWEIGHT);
    unique_ptr<Resources> Coins=make_unique<Resources>(COINSNAME,COINSSTARTINGAMOUNT,COINSRESOURCEWEIGHT);
    list< unique_ptr<ResourceGenerator>> resourceGeneratorBuildings;
    list<unique_ptr<Barracks>> barracksBuildings;
    list<unique_ptr<Troops>> troopsInVillage;
    void SetPlayerOwnerName(string newName);
    void SetVillageHealth(int newHealth);
    void SetVillageChar(string villageChar);
    void SetXPosition(int xPosition);
    void SetYPosition(int yPosition);

public:
    Village()=default;
    Village(string playerOwnerName, int xPosition, int yPosition,string villageChar);
    string GetPlayerOwnerName();
    int GetVillageHealth();
    int GetXPosition();
    int GetYPosition();
    string GetVillageChar();
    void BuildResourceGeneratorBuilding(string BuildingTypeName);
    void BuildBarracksBuilding(string BuildingTypeName);
    void UpgradeBarracksBuilding(string BuildingTypeName);
    void UpgradeResourceGeneratorBuilding(string BuildingTypeName);
    void CreateTroops();
    void RandomCreateTroops();
    void DisplayResources();
    void GenerateResources();
    int GetVillageHexSourceAmount();
    int GetVillageFoodAmount();
    int GetVillageCoinsAmount();
    void DecVillageHexSourceAmount(int amount);
    void DecVillageFoodAmount(int amount);
    void DecVillageCoinsAmount(int amount);
    unique_ptr<Army>  RandomSendAttackingArmy(string playerTarget, int xPosition, int yPosition, string armyLabel);
    unique_ptr<Army> SendAttackingArmy(string playerTarget, int xPosition, int yPosition, string armyLabel);
    bool CheckResourceGeneratorUpgrade(string BuildingTypeName);
    bool CheckBarracksUpgrade(string BuildingTypeName);
    int Fight(int attackingArmyDamage);
    void RetrieveResources(unique_ptr<Army> friendlyArmy);
    void DisplayTroops();
    void DisplayBuildings();
    void TakeDamage(int damage);
    int GetResourceGeneratorSize();
    int GetBarracksSize();
    ~Village();

};

//Cell Class, with its respective class variables and methods:
class Cell{
private:
    string cellState;
    void SetCellState(string State);
public:
    Cell();
    ~Cell();
    string GetCellState();
    void ChangeCellState(string State);
};

//GameMapManager Class, with its respective class variables and methods:
class GameMapManager{
private:
    int mapWidth;
    int mapHeight;
    int noOfAIPlayers;
    int noOfNormalPlayers;
    string alphabet={"abcdefghijklmnopqrstuvwxyz"};
    list<list<unique_ptr<Cell>>> BoardMap;
    list<unique_ptr<Village>> villages;
    list<unique_ptr<Army>> movingArmies;
    void SetMapWidth(int mapWidth);
    void SetMapHeight(int mapHeight);
    void SetNormalPlayers(int playerAmount);
    void SetAIPlayers(int aiPlayerAmount);
    string toLower(string input);
    int GetMapWidth();
    int GetMapHeight();
    bool isCellValid(int x, int y);
    void GenerateArmy(int playerIndex, int opponentIndex,int playerBit);
    int GetPlayerToAttack(int playerIndex);
    void DestroyVillageOnMap(int playerIndex);
    void DestroyPlayerArmies(string playerOwner);
    void MoveArmy(int playerIndex,string villageChar);
    bool ResolveFight(int playerIndex,int playerBit);
    void ResolveFriendlyArmy(int playerIndex);
    void ChangeArmyTarget(string playerName);
public:
    GameMapManager()=default;
    GameMapManager(int mapWidth, int mapHeight,int playerAmount,int aiPlayerAmount);
    void DisplayMap();
    void GenerateVillage(string ownerName);
    int GetNormalPlayers();
    int GetAIPlayers();
    void PlayerTurn(int playerIndex);
    void AIPlayerTurn(int playerIndex);
    string GetPlayerName(int playerIndex);
    ~GameMapManager();
};

//Input Validation Class, with its respective class variables and methods:
class InputValidation{
public:
    InputValidation()=default;
    int GetValidInput(int minrange, int maxrange);
    ~InputValidation()=default;
};