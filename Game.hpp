/*******************************************************************************
 * Author: Jordan K Bartos
 * Date: August 10, 2019
 * Description: header file for the Game class. The Game class is used to 
 *              represent a game of poker. It maintains a vector of pointers to
 *              player objects, keeps track of the game's purse, and has member
 *              functions to add a player, print the players' informations, end
 *              the game - calculating the necessary payments to satisfy the
 *              game.
*******************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Player.hpp"
#include "Structs.hpp"


class Game {
    private:
        std::vector<Player*> players;
        int totalPurse;
        //helper functions
        void inputFinalStacks();
        void checkStacks();
        void printResults(std::vector<Node*>) const;
        
    public:
        //constructor/destructor
        Game();
        ~Game();

        //getters/setters
        std::vector<Player*> getPlayers() const;
        int getTotalPurse() const;
        int getPlayersStacks() const;
        

        //other functions
        void showPlayers(bool) const;
        void addPlayer(Player*);
        void endGame();
        int getTotalStacks() const;
        void addBuyInToPlayer(int player, int amount);
};

#endif
