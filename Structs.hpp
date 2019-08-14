/*******************************************************************************
** Name: Jordan K Bartos
** Date: August 10, 2019
** Description: Defines structs used in the PlayerGraph and Graph classes.
*******************************************************************************/
#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include "Player.hpp"

struct Node{
    Player* player;
    std::vector<struct adjNode*> adjacentNodes;
    int playerOwed;
};

struct adjNode{
    struct Node* node;
    int edgeWeight;
};

#endif
