//
//  board.hpp
//  Connectfour
//
//  Created by Yufeng Chen on 16/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

class Board{
private:
    int node[6][7];//board info
    bool checkwin(int col, int player);//winning rules
    
public:
    Board();//constructor
    int type();//integer to represent game time
    void resetboard();//reset node allay
    void printboard();//displayer board
    bool drop(int col, int player);//dropping pieces
    
    bool checkdrop(int col);//check drop in legal column
    bool checkfull();//check the column is not full
    int whoswin(int col, int player);//use the private checkwin through this function
    int playerswitch(int &player, int plyaer1, int player2);//change player each turn
    void gametype(int &type, int &sequence);//choos game type
    
    int getnode(int i, int j);//to get private member node[6][7]
    string movelist(int row, int col, int player);//output node node array
    int cpnode[6][7];//copy of node, board information
};

#endif /* board_hpp */
