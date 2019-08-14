/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: This class turns a Game object's vector of player's - given 
 *              their final stacks and total buy-ins - and generates a graph as
 *              an adjacency list. Each node in the graph represents a player.
 *              Each node also has a value representing how much the player owes
 *              or is owed. At first, there are no edges in the graph. The
 *              PlayerGraph then solves the graph by a greedy algorithm that
 *              runs in O(n * log(n)) time where n is the number of players.
*******************************************************************************/
#include "helperFunctions.hpp"
#include <iostream>
#include "PlayerGraph.hpp"
#include "Player.hpp"
#include <cassert>
#include <algorithm>


/*******************************************************************************
**                            PlayerGraph(Game*)
** Description: Constructor for a player graph. Takes a pointer to a game 
**              object, ensures the game is balanced - that is that al of the 
**              players' stacks sum to the game's purse, then it initializes the
**              graph.
*******************************************************************************/
PlayerGraph::PlayerGraph(Game* game){
    std::vector<Player*> players = game->getPlayers();

    //ensure the game is balanced
    int playerFinalStackSum = 0;
    for(int i = 0; i < players.size(); ++i){
        playerFinalStackSum += players.at(i)->getFinalStack();
    }
    assert(game->getTotalPurse() == playerFinalStackSum);

    //initialize the graph
    this->initializeGraph(players);
}


/*******************************************************************************
**                               ~PlayerGraph()
** Description: Player Graph destructor. Frees dynamically allocated memory.
*******************************************************************************/
PlayerGraph::~PlayerGraph(){
    //deallocate adjacencey list for each Player
    for(int i = 0; i < this->adjList.size(); ++i){

        //deallocate adjcacent nodes for each player node in the graph
        for(int j = 0; j < adjList.at(i)->adjacentNodes.size(); j++){
            delete this->adjList.at(i)->adjacentNodes.at(j);
        }

        delete this->adjList.at(i);
    }
}


/*******************************************************************************
**                           getAdjList()
** Description: returns the adjacency list, which is represented by a vector of
**              pointers to nodes
*******************************************************************************/
std::vector<struct Node*> PlayerGraph::getAdjList()
{
    return this->adjList;
}

/*******************************************************************************
**                              initializeGraph
** input: - a vector of Player objects
**        - an int, the total pot of the game
** description: initializes the graph by determining the value of each node
**              (the playerOwed field). This value is determined by taking the
**              player's totalStack and subtracting the player's finalStack.
**              Thus, negative values represent money owed to the player, and
**              positive values represent a debt the player owes. More like a 
**              money pressure system than traditional bookkeeping, I guess.
**              Negative values "pull" money torwards them until the field is
**              in equilibrium (all 0)
** preconditions: The game must be balanced before this function executes. That
**                is, the sum of the player's finalStacks must equal the total
**                pot for the game.
*******************************************************************************/
void PlayerGraph::initializeGraph(std::vector<Player*> players){

    for(int i = 0; i < players.size(); i++){
        Player* currPlayer = players.at(i);
        struct Node* newNode = new struct Node;
        newNode->player = currPlayer;

        //node's value = initial buy-in - final stack
        newNode->playerOwed = currPlayer->getBuyIn() - 
                              currPlayer->getFinalStack();

        this->adjList.push_back(newNode);
    }
}

/*******************************************************************************
**                                  printGraph()
** Description: Prints a representation of the adjacency list that represents
**              the Player Graph.
*******************************************************************************/
void PlayerGraph::printGraph(){
    std::cout << "The graph:\n";

    /* iterate through each node, printing the name of the player at that node
    followed by the name of the player at each adjacent node and the weight of
    the edge to that node */
    for(int i = 0; i < this->adjList.size(); ++i){
        Node* currNode = this->adjList.at(i);
        std::cout << currNode->player->getName() << " -";

        for(int j = 0; j < currNode->adjacentNodes.size(); ++j){
            std::cout << currNode->adjacentNodes.at(j)->edgeWeight << "->"
                      << currNode->adjacentNodes.at(j)->node->player->getName() 
                      << "-";
        }
        std::cout << "\n";
    }

    std::cout << std::flush;
}

/*******************************************************************************
**                       compMin(struct Node*, struct Node*)
**                       compMax(struct Node*, struct Node*)
** Description: comparators for struct Node* used to compare pointers to Nodes
**              for the heap functions in solveGraph()
*******************************************************************************/
bool compMin(const struct Node* first, struct Node* second){
    if(first->playerOwed < second->playerOwed){
        return true;
    }
    else{
        return false;
    }
}


bool compMax(const struct Node* first, struct Node* second){
    if(first->playerOwed > second->playerOwed){
        return true;
    }
    else{
        return false;
    }
}


/*******************************************************************************
**                         solveGraph()
** Description: determines the correct edgeweights such that the minimum number
**              of payments are made such that each player receives as much
**              money as they are owed and each player pays as much as they owe.
** Prereqs: The graph must be correctly initialized with the node values. The
**          sum of the negative node values plus the sum of the positive node
**          values must equal 0
** Input: An initialized PlayerGraph which consists of a set of nodes - one per
**        player. Each node's value represents the amount owed to that player
**        (negative values) or the amount owed by that player (positve values).
** Output: The member varaible adjacency list is filled out by this function
**         such that each node's value is 0 with as few edges made as possible.
**         Each edge represents a transfer of money from a node to another.
*******************************************************************************/
void PlayerGraph::solveGraph(){

    //heapify the players with negative balances into a min heap
    //heapify the players iwth a positive balance into a max heap
    std::vector<struct Node*> winners;
    std::vector<struct Node*> losers;

    //go though the adjacencey list. Put the winners into one vector, put the
    //losers into the other
    for(int i = 0; i < this->adjList.size(); i++){
        struct Node* currNode = this->adjList.at(i);
        if(currNode->playerOwed < 0) {
            winners.push_back(currNode);
        }
        else if(currNode->playerOwed > 0){
            losers.push_back(currNode);
        }
    }

    //make a heap out of the losers and winners vectors
    std::make_heap(winners.begin(), winners.end(), compMax);
    std::make_heap(losers.begin(), losers.end(), compMin);
    //if there are no losers/winners, there is no graph. Leave it set to null
    if(losers.size() == 0){
        return;
    }

    /* The following lines of code may be un-commented out to print the heaps
       of winners and losers for debugging purposes if necessary
    //---------------------------------------------------------------------------
    std::cout << "\n---winners---" << std::endl;
    for(int i = 0; i < winners.size(); i++){
        std::cout << winners.at(i)->player->getName() << " -- " 
                  << winners.at(i)->playerOwed << std::endl;
    }

    std::cout << "\n---losers---" << std::endl;
    for(int i = 0; i < losers.size(); i++){
        std::cout << losers.at(i)->player->getName() << " -- " 
                  << losers.at(i)->playerOwed << std::endl;
    }
    //-----------------------------------------------------------------------------
    */

    //get the current loser from the losers heap
    struct Node* currentLoser = losers.front();
    std::pop_heap(losers.begin(), losers.end(), compMin);
    struct Node* currentWinner = NULL;

    //solve the graph
    //while the current loser's playerOwed value does not equal 0, there are
    //edges that need to be added to the graph. This loop determines the value
    //of the next edge that needs to be added, adds it, adjusts the playerOwed
    //values, and gets the next current loser from the losers heap
    while(currentLoser->playerOwed != 0){
        //currWinner <-- getMin from the minHeap
        currentWinner = winners.front();
        std::pop_heap(winners.begin(), winners.end(), compMax);

        //transfer = min(currLoser, -(currWinnter))
        int loserOwes = currentLoser->playerOwed;
        int winnerOwes = -(currentWinner->playerOwed);
        int transfer;

        if(loserOwes > winnerOwes){
            transfer = winnerOwes;
        }
        else{
            transfer = loserOwes;
        }
        
        //Create a new edge to add to the Player Node's adjacency List
        //Set the value of the edge from the current loser to the current winner
        //such that it equals the transfer amount. Also adjust the playerOwed
        //variable of each player node affected
        struct adjNode* newEdge = new adjNode;
        newEdge->edgeWeight = transfer;
        newEdge->node = currentWinner;
        currentLoser->adjacentNodes.push_back(newEdge);
        currentLoser->playerOwed -= transfer;
        currentWinner->playerOwed += transfer;

        //add current loser and current winner back into their respective heaps
        push_heap(losers.begin(), losers.end(), compMin);
        push_heap(winners.begin(), winners.end(), compMax);

        assert(std::is_heap(losers.begin(), losers.end(), compMin));
        assert(std::is_heap(winners.begin(), winners.end(), compMax));

        //get next loser
        currentLoser = losers.front();
        pop_heap(losers.begin(), losers.end(), compMin);
    }
}
