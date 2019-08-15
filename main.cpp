/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: Implements the PokerCalc program. This program is used to 
 *              calculate the minimum number of payments necessary to settle a
 *              game of poker such that all player's that have winnings are paid
 *              by all players that owe money.
*******************************************************************************/
#include "Player.hpp"
#include "Game.hpp"
#include "helperFunctions.hpp"
#include "PlayerGraph.hpp"
#include <iostream>

const int MIN_NAME_LENGTH = 2;
const int MAX_NAME_LENGTH = 20;
const int MIN_STACK = 0;
const int MAX_STACK = 1000000;


//function prototypes
int mainMenu(Game*);
void addPlayer(Game*);
void addBuyInToPlayer(Game*);
bool splashScreen();


/*******************************************************************************
 *                          main()
 * Description: main function for PokerCalc execution. Creates a Game object,
 *              manages user input for the main menu of the game
*******************************************************************************/
int main() {

    while(splashScreen()){
        Game* game = new Game;
        while(mainMenu(game));
        pause();
        delete game;
    }

    return 0;
}


/*******************************************************************************
 *                                  int mainMenu()
 * Description: displays the main menu for the game, gets user input for running
 *              the game.
*******************************************************************************/
int mainMenu(Game* game) {

    //display the menu
    clearTheScreen();
    std::cout << "---------------------------------------------------------\n";
    std::cout << "Options:\n";
    std::cout << "1. Add a player\n";
    std::cout << "2. Show players\n";
    std::cout << "3. Add buy-in to existing player\n";
    std::cout << "4. End game\n" << std::endl;
      
    std::cout << "Your choice ->" << std::flush;

    //get a choice
    int choice = getIntFromUser(1,4);
    bool continueGame = true;

    
    switch(choice){
        //add a player
        case 1:
            clearTheScreen();
            addPlayer(game);
            break;
        //show the players
        case 2:
            clearTheScreen();
            game->showPlayers(false);
            pause();
            break;
        //add a buy-in to a player
        case 3:
            clearTheScreen();
            addBuyInToPlayer(game);
            break;
        //end the game
        case 4:
            clearTheScreen();
            game->endGame();
            continueGame = false;
            break;
    };
    return continueGame;
}


/*******************************************************************************
 *                                 void addPlayer(Game*)
 * Gets user input for adding a player to the game
*******************************************************************************/
void addPlayer(Game* game){
    std::string userName;
    int userStack;
    
    //get player name
    std::cout << "Enter new player's name ->" << std::flush;
    userName = getStringFromUser(MIN_NAME_LENGTH, MAX_NAME_LENGTH);

    //get player amount
    std::cout << "Enter new player's stack ->" << std::flush;
    userStack = getIntFromUser(MIN_STACK, MAX_STACK);

    //add the player
    Player* newPlayer = new Player(userName, userStack);
    game->addPlayer(newPlayer);
    return;
}


/*******************************************************************************
 *                                 addBuyInToPlayer(Game*)
 * gets user input for adding an additional buy-in to an existing player.
*******************************************************************************/
void addBuyInToPlayer(Game* game){
    //clear the screen
    clearTheScreen();

    //get the vector of players from the game
    std::vector<Player*> players = game->getPlayers();

    //make sure there are players entered in the game
    if(players.size() == 0){
        std::cout << "There are no players in the game yet." << std::endl;
        pause();
        return;
    }

    //display prompt and players
    std::cout << "Select a player to add to their total buy-in.\n";
    std::cout << "Enter 0 to cancel action.\n";
    game->showPlayers(false);
    std::cout << "Player # ->" << std::flush;

    //get player choice
    int choice = getIntFromUser(0, players.size());

    //if choice is 0, cancel adding
    if(choice == 0){
        std::cout << "Update buy-in cancelled." << std::endl;
        pause();
        return;
    }

    //get amount to add
    std::cout << "How much is the player buying back in for?\n";
    std::cout << "Amount ->" << std::flush;
    int amount = getIntFromUser(MIN_STACK, MAX_STACK);
    
    //update player amount
    game->addBuyInToPlayer(choice-1, amount);
    
    //display confirmation message
    clearTheScreen();
    std::cout << amount << " cents added to " << players.at(choice-1)->getName() 
              << "'s stack.\nHere is the updated list of players.\n\n";
    game->showPlayers(false);
    pause();
    return;
}

bool splashScreen() {
    clearTheScreen();

    std::ifstream printFile;
    printFile.open("./views/titleScreen.txt");
    printFileContents(printFile);
    printFile.close();

    int input = getIntFromUser(1,2);
    if(input == 1) {
        return true;
    }
    else {
        return false;
    }
}
