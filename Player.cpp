/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: The Player class holds information about each player, including
 *              their name, the the sum of their buy-ins, and the value of their
 *              final stack - for the end of the game. It has member functions 
 *              to set/get each of these member variables as well a function to
 *              add an additional buy-in to the player.
*******************************************************************************/
#include "Player.hpp"


/*******************************************************************************
 *                           Player(std::string, int)
 * Description: Constructor that takes a string and an int. Sets the player's
 *              name to the string, and sets the initial buy-in to the integer.
 *              Sets final stack count to -1, which is a flag value for an 
 *              un-set final stack.
*******************************************************************************/
Player::Player(std::string name, int cents) {
    this->name = name;
    this->buyIn = cents;
    this->finalStack = -1;
}


/*******************************************************************************
 *                            ~Player()
 * Description: Player object deconstructor
*******************************************************************************/
Player::~Player() {
}


/*******************************************************************************
 *                     getters and setters for Player class
 * Description: Return or set member variables for the Player object
*******************************************************************************/
int Player::getBuyIn() {
    return this->buyIn;
}


std::string Player::getName() {
    return this->name;
}


void Player::setBuyIn(int cents) {
    this->buyIn = cents;
}


void Player::setFinalStack(int cents) {
    this->finalStack = cents;
}


int Player::getFinalStack() {
    return this->finalStack;
}


void Player::setName(std::string name) {
    this->name = name;
}


/*******************************************************************************
 *                             addBuyIn(int)
 * Description: Adds a buy-in amount to the player's buy-in
*******************************************************************************/
void Player::addBuyIn(int cents) {
    this->buyIn += cents;
}

