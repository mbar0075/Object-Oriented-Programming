#include <iostream>
#include <string>
#include "headerFile.h"
using namespace std;

int main() {
    //Creating Input Validation Instance
    unique_ptr<InputValidation> input= make_unique<InputValidation>();
    //Prompting user to Input number of Normal Players
    cout << "\nChoose, the number of Normal Players"<< endl;
    int normalPlayerAmount=0;
    //Retrieving Valid Normal Players Amount Input, based on valid number of players range
    normalPlayerAmount=input->GetValidInput(MINRANGENORMALPLAYERS,MAXRANGENORMALPLAYERS);
    //Prompting user to Input number of AI Players
    cout << "\nChoose, the number of AI Players"<< endl;
    int aiPlayerAmount=0;
    //Retrieving Valid AI Players Amount Input, based on valid number of AI players range
    aiPlayerAmount=input->GetValidInput(MINRANGEAIPLAYERS,MAXRANGEAIPLAYERS);

    //Creating GameMapManager Instance
    unique_ptr<GameMapManager> gameMapManagerInstance=make_unique<GameMapManager>(MAPWIDTH,MAPHEIGHT,normalPlayerAmount,aiPlayerAmount);
    //Creating Villages, for the Normal Players
    for(int i=0;i<gameMapManagerInstance->GetNormalPlayers();i++) {
        gameMapManagerInstance->GenerateVillage("Player "+to_string((i+1)));
    }
    //Creating Villages, for the AI Players
    for(int i=0;i<gameMapManagerInstance->GetAIPlayers();i++) {
        gameMapManagerInstance->GenerateVillage("AI Player "+to_string((i+1)));
    }

    //Declaring Variables, which will be used for Game Loop
    int playerAmount=gameMapManagerInstance->GetNormalPlayers();
    int newplayerAmount=playerAmount;
    int aiplayerAmount=playerAmount+gameMapManagerInstance->GetAIPlayers();
    int newaiplayerAmount=aiplayerAmount;

    //Looping until there is only 1 player left playing
    while((gameMapManagerInstance->GetNormalPlayers()+gameMapManagerInstance->GetAIPlayers())>1){
        //Declaring counter, and setting it to 0
        int counter=0;
        //Looping for the indexes of the Normal Players
        while(counter<playerAmount){
            //Calling the Player Turn method for the current Normal Player
            gameMapManagerInstance->PlayerTurn(counter);
            //Getting the amount of Normal Players
            newplayerAmount = gameMapManagerInstance->GetNormalPlayers();
            //Checking if a Normal Player has Surrendered or if a Normal Player lost, and if so, will update relevant variables
            if (newplayerAmount < playerAmount) {
                counter--;
                playerAmount = newplayerAmount;
            }
            //Checking whether, there is only, 1 player left  playing, and if so, will exit Loop
            if((gameMapManagerInstance->GetNormalPlayers()+gameMapManagerInstance->GetAIPlayers())==1){
                break;
            }
            //Incrementing counter
            counter++;
        }
        //Checking whether, there is only, 1 player left  playing, and if so, will exit Loop
        if((gameMapManagerInstance->GetNormalPlayers()+gameMapManagerInstance->GetAIPlayers())==1){
            break;
        }
        //Setting counter to the playerAmount
        counter=playerAmount;
        //Skipping AI Player Turns, if there are no AI Players
        if(aiPlayerAmount==0){
            continue;
        }
        //Looping for the indexes of the AI Players
        while(counter<aiplayerAmount){
            //Calling the AI Player Turn method for the current AI Player
            gameMapManagerInstance->AIPlayerTurn(counter);
            //Getting the amount of AI Players
            newaiplayerAmount = playerAmount+ gameMapManagerInstance->GetAIPlayers();
            //Checking if an AI Player has Surrendered or if an AI Player lost, and if so, will update relevant variables
            if (newaiplayerAmount < aiplayerAmount) {
                counter--;
                aiplayerAmount = newaiplayerAmount;
            }
            //Checking whether, there is only, 1 player left  playing, and if so, will exit Loop
            if((gameMapManagerInstance->GetNormalPlayers()+gameMapManagerInstance->GetAIPlayers())==1){
                break;
            }
            //Incrementing counter
            counter++;
        }
    }
    //Showing Game Map
    gameMapManagerInstance->DisplayMap();
    //Displaying Player who won the Game, and Game End Message
    cout<<"\n"<<gameMapManagerInstance->GetPlayerName(0)<<" Won the Game and Bested the other Players!"<<endl;
    cout<<"\nThank you for playing ;)"<<endl;

    //Freeing Input Validation Pointer
    input.reset();
    //Freeing GameMapManager Pointer
    gameMapManagerInstance.reset();
    return 0;
}