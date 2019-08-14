/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: The Game class implementation file. The game class manages the 
 *              a vector of players, and tracks the total purse of the poker
 *              game. It also has functions for getting the final player stacks
 *              and ending the game. It uses the PlayerGraph class to carry out
 *              the algorithm for determining payments.
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cassert>
#include "Game.hpp"
#include "PlayerGraph.hpp"
#include "helperFunctions.hpp"

/*******************************************************************************
 *                               Game()
 * Description: Default constructor
*******************************************************************************/
Game::Game() {
    this->totalPurse = 0;
}


/*******************************************************************************
 *                               ~Game()
 * Description: Deconstructor. Deallocates dynamically allocated memory in 
 *              vector of players.
*******************************************************************************/
Game::~Game() {
    //deallocate all of the dynamically allocated Player objects
    for(int i = 0; i < this->players.size(); i++) {
        delete players.at(i);
    }
    //empty the vector of players
    this->players.clear();
}


/*******************************************************************************
 *                        void addPlayer(Player* p)
 * Description: takes a pointer to a Player object and appends it to the Game's
 *              vector of Players and updates the game's total purse with the
 *              player's buy-in amount
*******************************************************************************/
void Game::addPlayer(Player* p) {
    this->players.push_back(p);
    this->totalPurse += p->getBuyIn();
}


/*******************************************************************************
 *                   vector<Player*> getPlayers()
 * Description: returns a reference to the vector of player objects
*******************************************************************************/
std::vector<Player*> Game::getPlayers() const {
    return this->players;
}


/*******************************************************************************
 *                       int getTotalPurse()
 * Description: returns the Game's total purse
*******************************************************************************/
int Game::getTotalPurse() const {

    //--------------------------------------------------------
    //This can be removed once the totalPurse is known to keep track
    //correctly
    int purse = 0;
    for(int i = 0; i < this->players.size(); i++) {
        purse += this->players.at(i)->getBuyIn();
    }
    assert(this->totalPurse == purse);
    //----------------------------------------------------------

    return this->totalPurse;
}

/*******************************************************************************
**                              getTotalStacks()
** Description: Returns the current total of the player's final stack counts
** this function is for ending the game and making sure everything adds up right
*******************************************************************************/
int Game::getTotalStacks() const{
    int totalStacks = 0;
    for(int i = 0; i < this->players.size(); ++i){
        totalStacks += this->players.at(i)->getFinalStack();
    }
    return totalStacks;
}


/*******************************************************************************
 *                          void showPlayers()
 * Description: Prints a list of players, their buy-ins, and optionally their
 *              stacks as well
 * Input: a bool variable that determines whether the stacks will be printed 
 *        or not.
*******************************************************************************/
void Game::showPlayers(bool withStacks) const {
    Player* currPlayer;

    //print table header
    std::cout << "---#--|--Name-----------|------Buy-in------";
    if(withStacks){
        std::cout << "|-----Stack----";
    }
    std::cout << "\n";

    //print each row of table
    for(int i = 0; i < this->players.size(); i++) {
        currPlayer = this->players.at(i);
        
        std::cout << std::setw(2) << i+1 
                  << std::setw(18) << currPlayer->getName() 
                  << std::setw(19) << currPlayer->getBuyIn();

        if(withStacks) {
            std::cout << std::setw(14) << currPlayer->getFinalStack();
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
    return;
}


/*******************************************************************************
 *                           void endGame()
 * Description: Ends the poker game. Gets the final stack count for each player,
 *              generates a graph where each node is a player with a value 
 *              representing how much the player owes or is owed. Then, the
 *              PlayerGraph object is used to solve the graph, and the resulting
 *              adjacency list is used to display the results
*******************************************************************************/
void Game::endGame(){
    //get the final stack for each player and make sure it's right
    inputFinalStacks();
    checkStacks();
    //generate a graph of the players such that each node represents a player
    //and the value of each node is equal to how much that player is owed 
    //(negative value) or how much that player owes (positive value)
    PlayerGraph graph(this);
    graph.solveGraph();
    std::vector<Node*> graphSolution = graph.getAdjList();
    printResults(graphSolution);
    return;
}


/*******************************************************************************
 *                              printResults()
 * Description: Prints the results of the graph solution to the console window
*******************************************************************************/
void Game::printResults(std::vector<Node*> graphSolution) const {
    clearTheScreen();

    std::cout << "---------------------FINAL RESULTS---------------------------"
              << "\n" << std::endl;
 
    //for each node in the adjacencey list, print each adjacent node and the 
    //edge weight associated with it. Each edge represents a payment from a
    //the node to each of its adjacent nodes
    for(int i = 0; i < graphSolution.size(); ++i) {
        struct Node* currNode = graphSolution.at(i);

        //iterate through each adjacent node, printing name and weight of edge
        for(int j = 0; j < currNode->adjacentNodes.size(); ++j) {
            std::cout << currNode->player->getName() 
                      << " owes " 
                      << currNode->adjacentNodes.at(j)->node->player->getName()
                      << " " << currNode->adjacentNodes.at(j)->edgeWeight
                      << "." << std::endl;
        }
    }
}

/*******************************************************************************
 *                               checkStacks()
 * Description: Determines whether the sum of the players' stacks adds up to the
 *              game's purse. This is a precondition for generating and solving
 *              a PlayerGraph.
*******************************************************************************/
void Game::checkStacks(){
     //make sure it adds up, let user adjust players' chip counts until it does
    int totalStacks = this->getTotalStacks();
    while(totalStacks != this->getTotalPurse()){
        clearTheScreen();
        std::cout << "The player's stacks don't add up to the " <<
                      "game's total purse.\n"
                  << "The total purse is  " << this->getTotalPurse() << "\n" 
                  << "The stacks total is " << totalStacks << "\n" << std::endl;
        std::cout << "Please choose a player to adjust their stack.\n";
        this->showPlayers(true);
        std::cout << "\nEnter player number to adjust ->" << std::flush;

        int choice = getIntFromUser(1, this->players.size() + 1);

        clearTheScreen();
        std::cout << "Adjusting " << this->players.at(choice - 1)->getName() 
                  << "'s chip count.\n"
                  << "New final stack ->";

        this->players.at(choice -1)->setFinalStack(getIntFromUser(0,1000000));
        totalStacks = this->getTotalStacks();
    }   
}
/*******************************************************************************
 *                             inputFinalStacks()
 * Description: gets user input for the ending stack for each player in the game
*******************************************************************************/
void Game::inputFinalStacks() {

    //get chip count for each user
    for(int i = 0; i < this->players.size(); ++i){
        clearTheScreen();
        std::cout << "Enter the final chip count for " 
                  << this->players.at(i)->getName()
                  << "\n-->" << std::flush;
        this->players.at(i)->setFinalStack(getIntFromUser(0,1000000));
    }
    
}


/*******************************************************************************
 *                        addBuyInToPlayer(int, int)
 * Description: adds a buy-in amount to an existing Player object.
*******************************************************************************/
void Game::addBuyInToPlayer(int playerNumber, int amount){
    //assert that the playerNumber is valid
    assert(playerNumber < this->players.size());
    Player* player = players.at(playerNumber);

    //add amount to player's buy-in and to game's purse
    int currentStack = player->getBuyIn();
    player->setBuyIn(currentStack + amount);
    this->totalPurse += amount;
}

