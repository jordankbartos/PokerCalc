/*******************************************************************************
** Author: Jordan K Bartos
** Date: August 10, 2019
** Description: Header file for the PlayerGraph class. The PlayerGraph class
**              is used to implement the graph algorithm that solves the poker
**              problem
*******************************************************************************/
#ifndef PLAYERGRAPH_HPP
#define PLAYERGRAPH_HPP

#include "Game.hpp"
#include <vector>
#include "Structs.hpp"

class PlayerGraph
{
    private:
        std::vector<struct Node*> adjList;
        void initializeGraph(std::vector<Player*>);

    public:
        //constructor
        PlayerGraph(Game*);
        ~PlayerGraph();
        std::vector<struct Node*> getAdjList();
        void printGraph();
        void solveGraph();
};

#endif
