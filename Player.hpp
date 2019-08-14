/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: The Player class represents a player in the poker game. It has
 *              member variables for the Player's buy-in, the player's final 
 *              stack, and for the players name. It has getters/setters for each
 *              member variable, and it has an additional member function for 
 *              adding additional buy-ins to the Player object.
*******************************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>


class Player 
{
    private:
        int buyIn;
        int finalStack;
        std::string name;

    public:
        //constructors destructors
        Player(std::string name, int cents);
        ~Player();
        
        //getters/setters
        int getFinalStack();
        int getBuyIn();
        void setBuyIn(int cents);
        void setFinalStack(int cents);
        std::string getName();
        void setName(std::string name);

        //additional functions
        void addBuyIn(int cents);
};

#endif
