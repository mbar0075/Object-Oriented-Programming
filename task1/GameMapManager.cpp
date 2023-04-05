//
// Created by Matthias on 28/12/2022.
//
//Inclusion of headerFile instance
#include "headerFile.h"

//Constructor for GameMapManager Instance
GameMapManager::GameMapManager(int mapWidth, int mapHeight,int playerAmount,int aiPlayerAmount) {
    SetMapHeight(mapHeight);
    SetMapWidth(mapWidth);
    SetAIPlayers(aiPlayerAmount);
    SetNormalPlayers(playerAmount);
    //Initialising Board Map, to unique pointer of Cells
    for(int j=0;j<mapHeight;j++){
        list<unique_ptr<Cell>> row;
        for (int i = 0; i < mapWidth; i++) {
            row.push_back(make_unique<Cell>());
        }
        BoardMap.push_back(move(row));
    }
}
//Method, which Displays the Board Map
void GameMapManager::DisplayMap(){
    //Displaying column numbers
    cout<<"\n\t";
    for (int i=0;i<GetMapWidth();i++) {
        cout<<i<<"\t";
    }
    cout<<endl;
    int counter=0;
    //Displaying Board Contents and row numbers
    list <list<unique_ptr<Cell>>> :: iterator it1;
    for(it1=BoardMap.begin();it1!=BoardMap.end();it1++){
        list <unique_ptr<Cell>> :: iterator it2;
        cout<<counter<<"\t";
        for (it2=(*it1).begin();it2!=(*it1).end();it2++) {
            cout<<(*it2)->GetCellState()<<"\t";
        }
        cout<<"\n"<<endl;
        counter++;
    }
}
//Setter for Map Height
void GameMapManager::SetMapHeight(int mapHeight) {
    this->mapHeight=mapHeight;
}
//Setter for Map Width
void GameMapManager::SetMapWidth(int mapWidth) {
    this->mapWidth=mapWidth;
}
//Getter for Map Width
int GameMapManager::GetMapWidth() {
    return mapWidth;
}
//Getter for Map Height
int GameMapManager::GetMapHeight() {
    return mapHeight;
}
//Setter for the amount of Normal Players
void GameMapManager::SetNormalPlayers(int playerAmount){
    this->noOfNormalPlayers=playerAmount;
}
//Setter for the amount of AI Players
void GameMapManager::SetAIPlayers(int aiPlayerAmount){
    this->noOfAIPlayers=aiPlayerAmount;
}
//Getter for the amount of AI Players
int GameMapManager::GetAIPlayers() {
    return noOfAIPlayers;
}
//Getter for the amount of Normal Players
int GameMapManager::GetNormalPlayers() {
    return noOfNormalPlayers;
}
//Method, which given and x and y position, determines, whether Cell is Valid
bool GameMapManager::isCellValid(int x, int y) {
    //Checking, whether x position falls in the board MapWidth, if not, false is returned
    if(x>GetMapWidth()-1||x<0)
        return false;
    //Checking, whether y position falls in the board MapWidth, if not, false is returned
    if(y>GetMapHeight()-1||y<0)
        return false;
    //Returning true
    return true;
}
//Method, which Generates a Village, given a Village Owner Name
void GameMapManager::GenerateVillage(string ownerName) {
    //Variable will be used to continue looping
    bool Loop = true;
    //Variables will be used, to hold the Village position on the Board Map
    int xpos=0;
    int ypos=0;

    //Setting Random Seed, based on Current Time
    srand(time(0));
    //Looping until a Valid Village Position is found
    while(Loop){
        //If Statements, being used, to spawn the first 4 Villages in the corners of the Board Map, and
        //spawn the remaining Villages, at a random position on the Board Map
        if((int)villages.size()>3){
             xpos= rand() % (GetMapWidth()-GetMapWidth()/3);
             ypos = rand() % (GetMapHeight()-GetMapHeight()/3);
        }
        else if ((int)villages.size()==0){
            xpos= 0;
            ypos = 0;
        }
        else if ((int)villages.size()==1){
            xpos= GetMapWidth()-1;
            ypos = GetMapHeight()-1;
        }
        else if ((int)villages.size()==2){
            xpos= 0;
            ypos = GetMapHeight()-1;
        }
        else if (villages.size()==3){
            xpos= GetMapWidth()-1;
            ypos = 0;
        }
        //Utilising iterators, and advance, to obtain current Cell State of the Board Map, for the generated x and y positions
        list<list<unique_ptr<Cell>>>::iterator it1;
        it1 = BoardMap.begin();
        advance(it1, ypos);
        list<unique_ptr<Cell>>::iterator it2;
        it2 = (*it1).begin();
        advance(it2, xpos);
        //Checking if, aforementioned Cell State is an empty State, if so, it will enter if statement, else, it will continue looping
        if ((*it2)->GetCellState() == CELLCHARACTERINITIAL) {
            //Retrieving, the first letter, from the alphabets list
            string newCellState=alphabet.substr(0,1);
            //Setting, Character to UpperCase, to signify a Village Position
            for (int x=0; x<(int)newCellState.length(); x++)
                newCellState[x]=toupper(newCellState[x]);
            //Erasing character from alphabet list
            alphabet=alphabet.erase(0,1);
            //Creating a Village, Instance, and appending it, to the villages, dynamic list
            villages.push_back(make_unique<Village>(ownerName, xpos, ypos,newCellState));
            //Changing the current Board Map, Cell State to the Village Character
            (*it2)->ChangeCellState(newCellState);
            //Setting Loop condition to false, and breaking from loop
            Loop = false;
            break;
        }
    }
}
//Method, which Generates an Army, given the playerIndex, opponentIndex, and playerBit
void GameMapManager::GenerateArmy(int playerIndex, int opponentIndex,int playerBit) {
    //Utilising iterators, and advance, to obtain the name of the Target Village
    list <unique_ptr<Village>> :: iterator it;
    it=villages.begin();
    advance(it,opponentIndex);
    string targetName=(*it)->GetPlayerOwnerName();
    //Utilising iterators, and advance, to obtain the Village Character/Label
    it=villages.begin();
    advance(it,playerIndex);
    string villageChar = (*it)->GetVillageChar();
    //Getting the current Village, x and y position, and storing in variables
    int ypos = (*it)->GetYPosition();
    int xpos = (*it)->GetXPosition();
    //Variables, will be used to hold the Army's position on the Board Map
    int newypos = 0;
    int newxpos = 0;
    list<list<unique_ptr<Cell>>>::iterator it1;
    list<unique_ptr<Cell>>::iterator it2;
    //Looping through the 8 adjacent Cells of the Village
    for (int row = -1; row < 2; row++) {
        for (int col = -1; col < 2; col++) {
            //Calculating Army's x and y position
            newypos = ypos + col;
            newxpos = xpos + row;
            //Checking if Army's position is not the Village position, and that Army's position is Valid
            if (!(row == 0 && col == 0) && isCellValid(newxpos, newypos)) {
                //Utilising iterators, and advance, to obtain current Cell State of the Board Map, for the generated x and y positions
                it1 = BoardMap.begin();
                advance(it1, newypos);
                it2 = (*it1).begin();
                advance(it2, newxpos);
                //Checking, that the Cell State is empty, and if so, will enter if statement
                if ((*it2)->GetCellState() == CELLCHARACTERINITIAL) {
                    //Creating Army Instance
                    unique_ptr<Army> attackingArmy;
                    //Based on PlayerBit, relevant Attack Army is sent
                    //playerBit 1, signifies, Normal Player
                    if(playerBit==1){
                        attackingArmy=(*it)->SendAttackingArmy(targetName,newxpos,newypos, toLower((*it)->GetVillageChar()));
                    }
                    //playerBit is anything else, signifies, AI Player
                    else{
                        attackingArmy=(*it)->RandomSendAttackingArmy(targetName,newxpos,newypos, toLower((*it)->GetVillageChar()));
                    }
                    //Checking if the Troop Count of the attackingArmy is larger than 0, if so, it will enter if statement, else
                    //it will display a message, that an empty Army cannot be created
                    if(attackingArmy->GetTroopCount()>0){
                        //Appending Army, to the movingArmies, dynamic list
                        movingArmies.push_back(move(attackingArmy));
                        //Changing the current Board State, to have the Army Character/Label
                        villageChar= toLower(villageChar);
                        (*it2)->ChangeCellState(villageChar);
                        cout << "\nCommencing Army Attack" << endl;
                    }
                    else{
                        //Cannot Create an Empty Army
                        cout << "\nEmpty Army, cannot be created" << endl;
                    }
                    //Freeing Army pointer
                    attackingArmy.reset();
                    //Returning
                    return;
                }
            }
        }
    }
    //Displaying appropriate message, since, Army could not be created, as surrounding Cells, were not empty
    cout << "\nUnable to Create Army" << endl;
}
//Method, which Destroys Village on Map, given the playerIndex
void GameMapManager::DestroyVillageOnMap(int playerIndex){
    //Utilising iterators, and advance, to obtain the Village Character/Label
    list <unique_ptr<Village>> :: iterator it;
    it=villages.begin();
    advance(it,playerIndex);
    string villageCharacter=(*it)->GetVillageChar();
    //Obtaining Army Character/Label, by Invoking toLower method, on the Village Character/Label
    string armyCharacter= toLower(villageCharacter);

    //Looping, through all the Cells in the Board Map
    list<list<unique_ptr<Cell>>>::iterator it1;
    list<unique_ptr<Cell>>::iterator it2;
    for(it1=BoardMap.begin();it1!=BoardMap.end();it1++){
        for (it2=(*it1).begin();it2!=(*it1).end();it2++) {
            //Obtaining, Cell State
            string cellState=(*it2)->GetCellState();
            //Removing all Instances of the Army Character/Label from the cellState
            size_t pos = std::string::npos;
            while ((pos  = cellState.find(armyCharacter) )!= std::string::npos){
                (*it2)->ChangeCellState(cellState.erase(pos, armyCharacter.length()));
            }
            //Removing all Instances of the Village Character/Label from the cellState
             pos = std::string::npos;
            while ((pos  = cellState.find(villageCharacter) )!= std::string::npos){
                (*it2)->ChangeCellState(cellState.erase(pos, villageCharacter.length()));
            }
            //If Cell State, is an empty String, then setting CellState to initial Character
            if((*it2)->GetCellState()==""){
                (*it2)->ChangeCellState(CELLCHARACTERINITIAL);
            }
        }
    }
}
//Method, which transforms, a given string to LowerCase
string GameMapManager::toLower(string input){
    //Looping, through all characters in the string, and changing character to lowercase
    for (int x = 0; x < (int)input.length(); x++) {
        input[x] = tolower(input[x]);
    }
    //Returning updated string
    return input;
}
//Method, which determines, which Player to Attack, given a player index
int GameMapManager::GetPlayerToAttack(int playerIndex){
    //Variable, will be used, to hold user input
    int userinput=-1;
    //Variable, will be used to continue to Loop
    bool Loop=true;
    //Iterating through all the Villages, in the villages, dynamic list, and displaying all villages to the user,
    //accompanied, by a numeric index
    list<unique_ptr<Village>>::iterator it;
    it = villages.begin();
    int counter = 1;
    cout << "\nChoose from the following Villages to Attack:" << endl;
    cout << "\nAvailable Villages:" << endl;
    while (it != villages.end()) {
        cout << counter << ". " << (*it)->GetPlayerOwnerName() << " Village" << endl;
        it++;
        counter++;
    }
    //Continuing to Loop until user entered, a valid Input
    while(Loop==true) {
        //Getting user input, and storing in variable
        cout << "\nEnter Choice (Input needs to be in range of "<<1<<"-"<<villages.size() <<"):"<< endl;
        cin >> userinput;
        //Checking if cin failed, and whether user input is in incorrect range, if so, will enter if statement
        if (cin.fail() || (userinput < 1 || userinput > (int)villages.size())) {
            //Printing out relevant message to the user, and clearing cin
            cout << "\nInvalid Option"<< endl;
            cin.clear();
            //Storing incorrect input, in string buffer, to allow the user to re-enter a choice
            string incorrectInput;
            getline(cin,incorrectInput);
            //Resetting user input and loop condition
            userinput=0;
            Loop = true;
        //Displaying appropriate message, if user, chose to attack, his own village
        } else if ((userinput-1) == playerIndex) {
            cout << "\nOne does not simply attack One's Own Village" << endl;
            //Resetting user input and loop condition
            userinput=0;
            Loop = true;
        } else {
            //Setting appropriate condition, to terminate loop
            Loop = false;
            //Decrementing user input, since, playerIndex starts from 0, and not 1
            userinput--;
        }
    }
    //Returning user input
    return userinput;
}
//Method, which will Move all the Armies, of a specified Player, on the Map, given a playerIndex, and a Village Character/Label
void GameMapManager::MoveArmy(int playerIndex,string villageChar){
    //Utilising iterators, and advance, to obtain the Player Village
    list<unique_ptr<Village>>::iterator it;
    it = villages.begin();
    advance(it,playerIndex);
    //Obtaining Army Character/Label, by Invoking toLower method, on the Village Character/Label
    string armyCharacter= toLower(villageChar);

    //Looping through, all the movingArmies, dynamic list
    list<unique_ptr<Army>>::iterator it1;
    it1 = movingArmies.begin();
    while (it1 != movingArmies.end()) {
        //Checking, if Army, Player Owner, is the same as the Player Village, Player Owner, if so, will enter If statement
        if((*it1)->GetPlayerOwner()==(*it)->GetPlayerOwnerName()){
            //Retrieving, Army x and y positions
            int armyxpos=(*it1)->GetArmyXPosition();
            int armyypos=(*it1)->GetArmyYPosition();
            //Creating 2 other variables to hold said position
            int initialxpos=armyxpos;
            int initialypos=armyypos;
            //Retrieving, Army Speed
            int armyspeed=(*it1)->GetArmySpeed();

            //Utilising iterators, and advance, to obtain current Cell State of the Board Map, for the Army's x and y positions
            list<list<unique_ptr<Cell>>>::iterator it3;
            list<unique_ptr<Cell>>::iterator it4;
            it3 = BoardMap.begin();
            advance(it3, initialypos);
            it4 = (*it3).begin();
            advance(it4, initialxpos);
            string cellState=(*it4)->GetCellState();
            //If Cell State, has a length of 1, then setting CellState to initial Character
            if((int)cellState.length()==1){
                (*it4)->ChangeCellState(CELLCHARACTERINITIAL);
            }
            //Else removing Army, Character, from Cell State
            else{
                size_t startIndex=cellState.find(armyCharacter);
                (*it4)->ChangeCellState(cellState.erase(startIndex,armyCharacter.length()));
            }
            //Retrieving the Player Target Name
            string targetName=(*it1)->GetPlayerTarget();

            //Looping, through all the village, in the villages, dynamic list
            list<unique_ptr<Village>>::iterator it2;
            it2 = villages.begin();
            bool exit=true;
            while(it2!=villages.end()){
                //If Village Player Owner, is equivalent to the target Name, then exit loop, else continue looping
                if((*it2)->GetPlayerOwnerName()==targetName){
                    exit=false;
                    break;
                }
                it2++;
            }
            if(exit==true){
                return;
            }
            //Retrieving the Target Village, x and y position
            int targetxpos=(*it2)->GetXPosition();
            int targetypos=(*it2)->GetYPosition();
            //Calculating the Manhattan distance, on the Target Village and Current Army Position
            int xdistance=targetxpos-armyxpos;
            int ydistance=targetypos-armyypos;
            //Checking if xdistance is larger than 0
            if(xdistance>0){
                //Continuing, to loop until Cell is Valid, and armyspeed is larger than 0
                while(isCellValid(armyxpos+1,armyypos)&&armyspeed>0){
                    //Incrementing armyxpos, and Decrementing armyspeed
                    armyxpos++;
                    armyspeed--;
                }
            }
            //Checking if xdistance is smaller than 0
            else if (xdistance<0){
                //Continuing, to loop until Cell is Valid, and armyspeed is larger than 0
                while(isCellValid(armyxpos-1,armyypos)&&armyspeed>0){
                    //Decrementing armyxpos, and Decrementing armyspeed
                    armyxpos--;
                    armyspeed--;
                }
            }
            //Checking if ydistance is larger than 0
            if (ydistance > 0) {
                //Continuing, to loop until Cell is Valid, and armyspeed is larger than 0
                while (isCellValid(armyxpos, armyypos + 1) && armyspeed > 0) {
                    //Incrementing armyypos, and Decrementing armyspeed
                    armyypos++;
                    armyspeed--;
                }
            }
            //Checking if ydistance is smaller than 0
            else if (ydistance < 0) {
                //Continuing, to loop until Cell is Valid, and armyspeed is larger than 0
                while (isCellValid(armyxpos, armyypos - 1) && armyspeed > 0) {
                    //Decrementing armyypos, and Decrementing armyspeed
                    armyypos--;
                    armyspeed--;
                }
            }
            //Updating, the Army x and y position
            (*it1)->UpdateArmyXPosition(armyxpos);
            (*it1)->UpdateArmyYPosition(armyypos);

            //Utilising iterators, and advance, to obtain the Cell State on the Board Map, for the calculated x and y positions
            it3 = BoardMap.begin();
            advance(it3, armyypos);
            it4 = (*it3).begin();
            advance(it4, armyxpos);
            //If Cell State, is an empty state, then CellState, will be changed to hold, the armyCharacter
            //Else, appending, the armyCharacter to the CellState
            if((*it4)->GetCellState()==CELLCHARACTERINITIAL){
                (*it4)->ChangeCellState(armyCharacter);
            }
            else{
                (*it4)->ChangeCellState((*it4)->GetCellState()+armyCharacter);
            }
        }
        //Incrementing iterator
        it1++;
    }
}
//Method, which will Resolve a Fight, given a playerIndex, and a playerBit
bool GameMapManager::ResolveFight(int playerIndex,int playerBit){
    //Variables, will be used, to determine, if entities are destroyed
    bool villagedestroyed=false;
    bool armydestroyed=false;
    //Utilising iterators, and advance, to obtain the Player Village
    list <unique_ptr<Village>> :: iterator it;
    it=villages.begin();
    advance(it,playerIndex);
    //Looping through, all the movingArmies, dynamic list
    list <unique_ptr<Army>> :: iterator it1;
    it1=movingArmies.begin();
    while(it1!=movingArmies.end()){
        //Checking, if Army, Player Target, is the same as the Player Village, Player Owner, if so, will enter if statement
        if((*it1)->GetPlayerTarget()==(*it)->GetPlayerOwnerName()){
            //Variables, to hold, Army x and y positions
            int armyxpos=(*it1)->GetArmyXPosition();
            int armyypos=(*it1)->GetArmyYPosition();
            //Variables, to hold, the Player Village x and y positions
            int enemyvxpos=(*it)->GetXPosition();
            int enemyvypos=(*it)->GetYPosition();

            //Checking, whether, the Army and Player Village, have the same position
            if(armyxpos==enemyvxpos&&armyypos==enemyvypos) {
                //Retrieving Army Character/Label
                string armyCharacter=(*it1)->GetArmyLabel();
                //Retrieving, the total Army Damage
                int attackingArmyDamage = (*it1)->GetArmyDamage();
                //Invoking Fight method, in the Village class, and retrieving, villageDamage
                int villageDamage = (*it)->Fight(attackingArmyDamage);
                //Invoking TakeDamage method, in the Army class, and passing villageDamage as a parameter
                (*it1)->TakeDamage(villageDamage);

                //If Army Health is smaller or equal to 0, thus, Army has lost, and enter if statement
                if ((*it1)->GetArmyHealth() <= 0) {
                    //Displaying relevant message
                    cout << "\n" << (*it1)->GetPlayerOwner() << " Army has lost the Battle\n" << endl;
                    //Utilising iterators, and advance, to obtain the Cell State on the Board Map, for the Army's x and y positions
                    list<list<unique_ptr<Cell>>>::iterator it3;
                    list<unique_ptr<Cell>>::iterator it4;
                    it3 = BoardMap.begin();
                    advance(it3, (*it1)->GetArmyYPosition());
                    it4 = (*it3).begin();
                    advance(it4, (*it1)->GetArmyXPosition());
                    string cellState = (*it4)->GetCellState();

                    //Removing the first armyCharacter from CellState
                    size_t pos = cellState.find(armyCharacter);
                    if (pos != string::npos) {
                        (*it4)->ChangeCellState(cellState.erase(pos, armyCharacter.length()));
                    }
                    //Erasing, the current Army, from the movingArmies, dynamic list
                    it1=movingArmies.erase(it1);
                    //Decrementing iterator
                    --it1;
                    //Setting armydestroyed flag to true
                    armydestroyed=true;
                }
                //If Village Health is smaller or equal to 0, thus, Village has lost, and enter if statement
                if ((*it)->GetVillageHealth() <= 0) {
                    //Invoking method, which changes, all the Armies, which are Targeting, the current Village
                    ChangeArmyTarget((*it)->GetPlayerOwnerName());
                    //Retrieving, Army Carry Weight
                    int armycarryweight=(*it1)->GetArmyCarryWeight();
                    //Variable, will be used to continue to Loop
                    bool Loop =true;
                    //Continuing to Loop, until Loop flag is set to false
                    while(Loop==true){
                        //Setting Loop to false
                        Loop=false;
                        //Checking if the armycarryweight is larger, than HexSource Weight, and checking, that Player Village has enough HexSource Resources
                        if(armycarryweight>=HEXSOURCERESOURCEWEIGHT&&(*it)->GetVillageHexSourceAmount()>0){
                            //Decrementing, the armycarryweight by the HexSource Weight
                            armycarryweight-=HEXSOURCERESOURCEWEIGHT;
                            //Adding 1, to the Army HexSource Resource
                            (*it1)->AddHexSourceAmount(1);
                            //Deducting 1, from the Village HexSource Resource
                            (*it)->DecVillageHexSourceAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                        //Checking if the armycarryweight is larger, than Coins Weight, and checking, that Player Village has enough Coins Resources
                        if(armycarryweight>=COINSRESOURCEWEIGHT&&(*it)->GetVillageCoinsAmount()>0){
                            //Decrementing, the armycarryweight by the Coins Weight
                            armycarryweight-=COINSRESOURCEWEIGHT;
                            //Adding 1, to the Army Coins Resource
                            (*it1)->AddCoinsAmount(1);
                            //Deducting 1, from the Village Coins Resource
                            (*it)->DecVillageCoinsAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                        //Checking if the armycarryweight is larger, than Food Weight, and checking, that Player Village has enough Food Resources
                        if(armycarryweight>=FOODRESOURCEWEIGHT&&(*it)->GetVillageFoodAmount()>0){
                            //Decrementing, the armycarryweight by the Food Weight
                            armycarryweight-=FOODRESOURCEWEIGHT;
                            //Adding 1, to the Army Food Resource
                            (*it1)->AddFoodAmount(1);
                            //Deducting 1, from the Village Food Resource
                            (*it)->DecVillageFoodAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                    }
                    //Displaying relevant message
                    cout << "\n" << (*it)->GetPlayerOwnerName() << " has lost the Battle\n" << endl;
                    //Invoking method, which Destroys, all the Armies, owned by the Player
                    DestroyPlayerArmies((*it)->GetPlayerOwnerName());
                    //Invoking method, which Destroys, all the Village, and Army Characters/Labels, from the Board Map
                    DestroyVillageOnMap(playerIndex);
                    //Based on PlayerBit, relevant Player Amount is decremented
                    //playerBit 1, signifies, Normal Player
                    if(playerBit==1){
                        SetNormalPlayers(GetNormalPlayers() - 1);
                    }
                    //playerBit is anything else, signifies, AI Player
                    else{
                        SetAIPlayers(GetAIPlayers() - 1);
                    }
                    //Erasing Current Village, from villages, dynamic list
                    it = villages.erase(it);
                    //Setting villagedestroyed flag to true, and returning flag
                    villagedestroyed=true;
                    return villagedestroyed;
                }
                //Checking, whether both army, and village, were not destroyed
                if(armydestroyed==false&&villagedestroyed==false){
                    //Invoking method, which changes, all the Armies, which are Targeting, the current Village
                    (*it1)->ChangePlayerTarget((*it1)->GetPlayerOwner());
                    //Retrieving, Army Carry Weight
                    int armycarryweight=(*it1)->GetArmyCarryWeight();
                    //Variable, will be used to continue to Loop
                    bool Loop =true;
                    //Continuing to Loop, until Loop flag is set to false
                    while(Loop==true){
                        //Setting Loop to false
                        Loop=false;
                        //Checking if the armycarryweight is larger, than HexSource Weight, and checking, that Player Village has enough HexSource Resources
                        if(armycarryweight>=HEXSOURCERESOURCEWEIGHT&&(*it)->GetVillageHexSourceAmount()>0){
                            //Decrementing, the armycarryweight by the HexSource Weight
                            armycarryweight-=HEXSOURCERESOURCEWEIGHT;
                            //Adding 1, to the Army HexSource Resource
                            (*it1)->AddHexSourceAmount(1);
                            //Deducting 1, from the Village HexSource Resource
                            (*it)->DecVillageHexSourceAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                        //Checking if the armycarryweight is larger, than Coins Weight, and checking, that Player Village has enough Coins Resources
                        if(armycarryweight>=COINSRESOURCEWEIGHT&&(*it)->GetVillageCoinsAmount()>0){
                            //Decrementing, the armycarryweight by the Coins Weight
                            armycarryweight-=COINSRESOURCEWEIGHT;
                            //Adding 1, to the Army Coins Resource
                            (*it1)->AddCoinsAmount(1);
                            //Deducting 1, from the Village Coins Resource
                            (*it)->DecVillageCoinsAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                        //Checking if the armycarryweight is larger, than Food Weight, and checking, that Player Village has enough Food Resources
                        if(armycarryweight>=FOODRESOURCEWEIGHT&&(*it)->GetVillageFoodAmount()>0){
                            //Decrementing, the armycarryweight by the Food Weight
                            armycarryweight-=FOODRESOURCEWEIGHT;
                            //Adding 1, to the Army Food Resource
                            (*it1)->AddFoodAmount(1);
                            //Deducting 1, from the Village Food Resource
                            (*it)->DecVillageFoodAmount(1);
                            //Setting Loop to true
                            Loop=true;
                        }
                    }
                }
            }
        }
        //Incrementing iterator
        it1++;
    }
    //Returning villagedestroyed flag
    return villagedestroyed;
}
//Method, which changes, the Army Target, given a Player name
void GameMapManager::ChangeArmyTarget(string playerName){
    //Iterating, through, all the Armies, in the movingArmies, dynamic list
    list <unique_ptr<Army>> :: iterator it1;
    it1=movingArmies.begin();
    while(it1!=movingArmies.end()) {
        //If Army's Player Target, is equal to the given Player name, then setting the Army's Player Target to the Army's Player Owner
        if((*it1)->GetPlayerTarget()==playerName){
            (*it1)->ChangePlayerTarget((*it1)->GetPlayerOwner());
        }
        it1++;
    }
}
//Method, which will Resolve, a Friendly Army, given a playerIndex
void GameMapManager::ResolveFriendlyArmy(int playerIndex){
    //Utilising, iterators, to obtain, the Player Village
    list <unique_ptr<Village>> :: iterator it;
    it=villages.begin();
    advance(it,playerIndex);
    //Looping through all the Armies, in the movingArmies, dynamic list
    list <unique_ptr<Army>> :: iterator it1;
    it1=movingArmies.begin();
    while(it1!=movingArmies.end()) {
        //Retrieving, the Village x and y position
        int villageXPos=(*it)->GetXPosition();
        int villageYPos=(*it)->GetYPosition();
        //Retrieving, the Army x and y position
        int armyXPos=(*it1)->GetArmyXPosition();
        int armyYPos=(*it1)->GetArmyYPosition();
        //Checking if Army position, is the same as the Village position
        if(armyXPos==villageXPos&&armyYPos==villageYPos) {
            //Checking whether Army, has the same Player Target, as the Player Owner, and that the Army Player Owner is the
            //same, as the Player Village Owner
            if ((*it1)->GetPlayerTarget() == (*it)->GetPlayerOwnerName() &&
                (*it1)->GetPlayerTarget() == (*it1)->GetPlayerOwner()) {
                //Utilising iterators, and advance, to obtain the Cell State on the Board Map, for the Army's x and y positions
                list<list<unique_ptr<Cell>>>::iterator it3;
                list<unique_ptr<Cell>>::iterator it4;
                it3 = BoardMap.begin();
                advance(it3, (*it1)->GetArmyYPosition());
                it4 = (*it3).begin();
                advance(it4, (*it1)->GetArmyXPosition());
                //Retrieving CellState, and armyCharacter
                string cellState = (*it4)->GetCellState();
                string armyCharacter = toLower((*it)->GetVillageChar());
                //Relevant message is shown
                cout << "\nArmy has Arrived back to the Village "<< endl;
                //Removing, armycharacter, from Village Cell
                size_t pos = cellState.find(armyCharacter);
                if (pos != string::npos) {
                    (*it4)->ChangeCellState(cellState.erase(pos, armyCharacter.length()));
                }
                //Invoking method from Village Class, to Retrieve Army Resources, and Troops
                (*it)->RetrieveResources(move(*it1));
                //Erasing Army, from movingArmies, dynamic list, and decrementing iterator
                it1=movingArmies.erase(it1);
                it1--;
            }
        }
        //Incrementing iterator
        it1++;
    }
}
//Method, which Destroys all Player Armies, given a Player Owner Name
void GameMapManager::DestroyPlayerArmies(string playerOwner){
    //Iterating, through, all the Armies, in the movingArmies, dynamic list
    list<unique_ptr<Army>>::iterator it1;
    it1 = movingArmies.begin();
    while (it1 != movingArmies.end()) {
        //If Army's Player Owner, is equivalent, to the given Player Owner, then erase Army from movingArmies, dynamic list
        if((*it1)->GetPlayerOwner()==playerOwner){
            it1=movingArmies.erase(it1);
            it1--;
        }
        it1++;
    }
}
//Method, which Initiates, a Normal Player's Turn, given a playerIndex
void  GameMapManager::PlayerTurn(int playerIndex) {
    //Variable will hold, user input
    string userinput;
    //Utilising iterators, and advance, to obtain the Player Village
    list<unique_ptr<Village>>::iterator it;
    it = villages.begin();
    advance(it, playerIndex);
    //Invoking method, to Resolve Friendly Army, arrival
    ResolveFriendlyArmy(playerIndex);
    //Invoking method, to Resolve Attacking Army, arrival
    bool villageDestroyed=ResolveFight(playerIndex,1);
    //If Village is destroyed, then return, from method
    if(villageDestroyed==true){
        return;
    }
    //Invoking method, to Move Armies, of the current Player Village, on the Board Map
    MoveArmy(playerIndex,(*it)->GetVillageChar());
    //Invoking method, which Generates Resources, from the Player Village's Resource Generators
    (*it)->GenerateResources();
    //Displaying Map
    DisplayMap();
    //Retrieving, Village, Player Owner
    string playerOwner=(*it)->GetPlayerOwnerName();
    //Continue to Loop, until userinput is not 8
    while(userinput[0]!='8'){
        //Displaying Player Village Information, and Menu of Player Actions
        cout << "\n" << playerOwner << " turn ("<<(*it)->GetVillageChar()<<")\n" << endl;
        cout << "Village Health: " << (*it)->GetVillageHealth()<< endl;
        (*it)->DisplayResources();
        cout << "\nChoose from the following options:" << endl;
        cout << "1. Build Buildings" << endl;
        cout << "2. Upgrade Buildings" << endl;
        cout << "3. Train Troops" << endl;
        cout << "4. Attack another village with an Army" << endl;
        cout << "5. Display Troops" << endl;
        cout << "6. Display Buildings" << endl;
        cout << "7. Surrender" << endl;
        cout << "8. Pass the turn" << endl;
        cin >> userinput;
        string buildingChoice;
        int enemyIndex;
        switch (userinput[0]) {
            case '1'://Displaying Menu, of Build Options, which, the Player, can choose to build specific Buildings
                cout << "Choose from the following Buildings to build:" << endl;
                cout << "1. Build " << FOODNAME << " Resource Generator Building" << endl;
                cout << "2. Build " << COINSNAME << " Resource Generator Building" << endl;
                cout << "3. Build " << HEXSOURCENAME << " Resource Generator Building" << endl;
                cout << "4. Build " << SOLDIERNAME << " Barracks Building" << endl;
                cout << "5. Build " << WARRIORNAME << " Barracks Building" << endl;
                cout << "6. Build " << GENERALNAME << " Barracks Building" << endl;
                cin >> buildingChoice;
                switch (buildingChoice[0]) {
                    case '1':
                        (*it)->BuildResourceGeneratorBuilding(FOODNAME);
                        break;
                    case '2':
                        (*it)->BuildResourceGeneratorBuilding(COINSNAME);
                        break;
                    case '3':
                        (*it)->BuildResourceGeneratorBuilding(HEXSOURCENAME);
                        break;
                    case '4':
                        (*it)->BuildBarracksBuilding(SOLDIERNAME);
                        break;
                    case '5':
                        (*it)->BuildBarracksBuilding(WARRIORNAME);
                        break;
                    case '6':
                        (*it)->BuildBarracksBuilding(GENERALNAME);
                        break;
                    default:
                        cout << "\nInvalid Option" << endl;
                        break;
                }
                break;
            case '2'://Displaying Menu, of Upgrade Options, which, the Player, can choose to upgrade specific Buildings
                     //For each option, the method, checks whether Building, already exists, if not, message is shown.
                cout << "Choose from the following Buildings to upgrade:" << endl;
                cout << "1. Upgrade " << FOODNAME << " Resource Generator Building" << endl;
                cout << "2. Upgrade " << COINSNAME << " Resource Generator Building" << endl;
                cout << "3. Upgrade " << HEXSOURCENAME << " Resource Generator Building" << endl;
                cout << "4. Upgrade " << SOLDIERNAME << " Barracks Building" << endl;
                cout << "5. Upgrade " << WARRIORNAME << " Barracks Building" << endl;
                cout << "6. Upgrade " << GENERALNAME << " Barracks Building" << endl;
                cin >> buildingChoice;
                switch (buildingChoice[0]) {
                    case '1':
                        if((*it)->CheckResourceGeneratorUpgrade(FOODNAME)) {
                            (*it)->UpgradeResourceGeneratorBuilding(FOODNAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    case '2':
                        if((*it)->CheckResourceGeneratorUpgrade(COINSNAME)) {
                            (*it)->UpgradeResourceGeneratorBuilding(COINSNAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    case '3':
                        if((*it)->CheckResourceGeneratorUpgrade(HEXSOURCENAME)) {
                            (*it)->UpgradeResourceGeneratorBuilding(HEXSOURCENAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    case '4':
                        if((*it)->CheckBarracksUpgrade(SOLDIERNAME)) {
                            (*it)->UpgradeBarracksBuilding(SOLDIERNAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    case '5':
                        if((*it)->CheckBarracksUpgrade(WARRIORNAME)) {
                            (*it)->UpgradeBarracksBuilding(WARRIORNAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    case '6':
                        if((*it)->CheckBarracksUpgrade(GENERALNAME)) {
                            (*it)->UpgradeBarracksBuilding(GENERALNAME);
                        }
                        else{
                            cout<<"\nBuilding does not exist, need to create Building to upgrade"<<endl;
                        }
                        break;
                    default:
                        cout << "\nInvalid Option" << endl;
                        break;
                }
                break;
            case '3'://Invoking respective method, to Create Troops
                (*it)->CreateTroops();
                break;
            case '4'://Invoking respective methods, to Determine, which enemy, to attack, and to Generate and Army
                enemyIndex=GetPlayerToAttack(playerIndex);
                GenerateArmy(playerIndex,enemyIndex,1);
                break;
            case '5'://Invoking respective method, to Display, the Village Troops
                cout<<"Village has the Following Troops:"<<endl;
                (*it)->DisplayTroops();
                break;
            case '6'://Invoking respective method, to Display, the Village Buildings
                cout<<"Village has the Following Buildings:"<<endl;
                (*it)->DisplayBuildings();
                break;
            case '7'://Relevant message is shown
                cout << "\n" << playerOwner << " has lost the will to Battle\n" << endl;
                //Invoking method, which Destroys, all the Armies, owned by the Player
                DestroyPlayerArmies(playerOwner);
                //Invoking method, which changes, all the Armies, which are Targeting, the current Village
                ChangeArmyTarget((*it)->GetPlayerOwnerName());
                //Invoking method, which Destroys, all the Village, and Army Characters/Labels, from the Board Map
                DestroyVillageOnMap(playerIndex);
                //Erasing Current Village, from villages, dynamic list
                villages.erase(it);
                //Decreasing the amount of Normal Players
                SetNormalPlayers(GetNormalPlayers()-1);
                //Return statement
                return;
                break;
            case '8'://Relevant message is shown
                cout << "\nTurn Over" << endl;
                return;
            default://Proper Input Validation, for Invalid Option
                cout << "\nInvalid Option" << endl;
                break;
        }
    }
}
//Method, which Initiates, an AI Player's Turn, given a playerIndex
void GameMapManager::AIPlayerTurn(int playerIndex){
    //Utilising iterators, and advance, to obtain the Player Village
    list<unique_ptr<Village>>::iterator it;
    it = villages.begin();
    advance(it, playerIndex);
    //Invoking method, to Resolve Friendly Army, arrival
    ResolveFriendlyArmy(playerIndex);
    //Invoking method, to Resolve Attacking Army, arrival
    bool villageDestroyed=ResolveFight(playerIndex,0);
    //If Village is destroyed, then return, from method
    if(villageDestroyed==true){
        return;
    }
    //Invoking method, to Move Armies, of the current Player Village, on the Board Map
    MoveArmy(playerIndex,(*it)->GetVillageChar());
    //Invoking method, which Generates Resources, from the Player Village's Resource Generators
    (*it)->GenerateResources();
    //Displaying Map
    DisplayMap();
    //Retrieving, Village, Player Owner
    string playerOwner=(*it)->GetPlayerOwnerName();
    //Displaying Player Village Information
    cout << "\n" << playerOwner << " turn ("<<(*it)->GetVillageChar()<<")\n" << endl;
    cout << "Village Health: " << (*it)->GetVillageHealth()<< endl;
    (*it)->DisplayResources();

    //Declaring 4 Variables, which will generate random indexes, which will be used, to determine, which actions, to perform
    int choosebuilding=rand()%(9);
    int chooseupgradebuilding=rand()%(3);
    int choosetraintroop=rand()%(3);
    int chooseattackvillage=rand()%(3);

    //For the first, AI Player turn, a Coins Generator, is built, so that AI Player, will always have incoming Coins, to build Buildings
    if((*it)->GetResourceGeneratorSize()==0){
        (*it)->BuildResourceGeneratorBuilding(COINSNAME);
    }
    //Building, and Upgrading Buildings Turn:
    //Based on choosebuilding random index, a type of Building is built, and based on the chooseupgradebuilding random index,
    //the same type of building is upgraded
    if(choosebuilding==1){
        (*it)->BuildResourceGeneratorBuilding(FOODNAME);
        if(chooseupgradebuilding==1&&(*it)->CheckResourceGeneratorUpgrade(FOODNAME)) {
            (*it)->UpgradeResourceGeneratorBuilding(FOODNAME);
        }
    }
    else if(choosebuilding==2){
        (*it)->BuildResourceGeneratorBuilding(COINSNAME);
        if(chooseupgradebuilding==1&&(*it)->CheckResourceGeneratorUpgrade(COINSNAME)) {
            (*it)->UpgradeResourceGeneratorBuilding(COINSNAME);
        }
    }
    else if(choosebuilding==3){
        (*it)->BuildResourceGeneratorBuilding(HEXSOURCENAME);
        if(chooseupgradebuilding==1&&(*it)->CheckResourceGeneratorUpgrade(HEXSOURCENAME)) {
            (*it)->UpgradeResourceGeneratorBuilding(HEXSOURCENAME);
        }
    }
    else if(choosebuilding==4){
        (*it)->BuildBarracksBuilding(SOLDIERNAME);
        if(chooseupgradebuilding==1&&(*it)->CheckBarracksUpgrade(SOLDIERNAME)) {
            (*it)->UpgradeBarracksBuilding(SOLDIERNAME);
        }
    }
    else if(choosebuilding==5){
        (*it)->BuildBarracksBuilding(WARRIORNAME);
        if(chooseupgradebuilding==1&&(*it)->CheckBarracksUpgrade(WARRIORNAME)) {
            (*it)->UpgradeBarracksBuilding(WARRIORNAME);
        }
    }
    else if(choosebuilding==6){
        (*it)->BuildBarracksBuilding(GENERALNAME);
        if(chooseupgradebuilding==1&&(*it)->CheckBarracksUpgrade(GENERALNAME)) {
            (*it)->UpgradeBarracksBuilding(GENERALNAME);
        }
    }

    //Training Troops Turn:
    //If choosetraintroop random index is 1, then RandomCreateTroop method, is invoked
    if(choosetraintroop==1){
        (*it)->RandomCreateTroops();
    }

    //Choosing a Village, and Attacking Village Turn:
    //If chooseattackvillage random index is 1, then a random enemy index is Generated (which is not the current AI Player's index),
    //and the GenerateArmy method, is invoked, with the relevant parameters
    if(chooseattackvillage==1){
        int enemyIndex=rand() % (GetNormalPlayers()+GetAIPlayers());
        while(enemyIndex==playerIndex){
            enemyIndex=rand() % (GetNormalPlayers()+GetAIPlayers());
        }
        GenerateArmy(playerIndex,enemyIndex,0);
    }

    //Pass Turn:
    //Relevant message is shown
    cout << "\nTurn Over" << endl;
}
//Method, which will Retrieve a Player Name, fo a given playerIndex
string GameMapManager::GetPlayerName(int playerIndex){
    //Utilising iterator, and advance to obtain and return Village Player Name
    list <unique_ptr<Village>> :: iterator it;
    it=villages.begin();
    advance(it,playerIndex);
    return (*it)->GetPlayerOwnerName();
}
//Destructor for GameMapManager Instance
GameMapManager::~GameMapManager() {
    //Clearing all Armies, in the movingArmies, dynamic list
    movingArmies.clear();
    //Clearing all Villages, in the villages, dynamic list
    villages.clear();
    //Clearing all Cells, in the BoardMap, 2d dynamic list
    BoardMap.clear();
    //Statement below, used to check, if instance was destroyed
    //cout<<"\nMap has been destroyed"<< endl;
}