//
//  main.cpp
//  Connectfour
//
//  Created by Yufeng Chen on 07/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include "robot.hpp"
#include "connectfour.h"
using namespace std;

Board board;//initialize gameboard

Reinforce RLagent1(board, 1, "firstvallist", "firstrecord");
Reinforce RLagent2(board, 2, "secondvallist", "secondrecord");

int main() {
    int col = 0;
    char startgame;
    int player;
    int player1 = 1;
    int player2 = 2;
    int type = 0;
    int sequence = 0;
    int counter = 0;
    int limitgames = 10;
    
    cout << "Enter Y/y to start a new game." << endl;
    cin >> startgame;
    
    while (startgame == 'y' || startgame == 'Y') {//start game
        player = 1;//initialize these members to remove last game's effects
        if (counter == 0) {
            type = 0;
            sequence = 0;
            board.gametype(type, sequence);//choose game type and playing sequence
        }
        
        board.printboard();//show an empty board
        
        
        while (!board.checkfull()) {//make sure the board is not full
            while (true) {
                whoseturn(board, type, sequence, player, col);//check current player and get drop
                if (board.checkdrop(col) == 1) {//make sure the drop is legal
                    break;
                }
            }
            
            board.drop(col, player);
            board.printboard();//show the drop
            
            if (board.whoswin(col, player) != 0) {//check anyone win to break the while
                break;
            }
            
            board.playerswitch(player, player1, player2);//take turns to drop
        }

        outputwinner(board, type, sequence, col,player);
        //should be devided into 2 parts,winner and outputwinner,so that function winner could be reused by RLAI
        
        if ((type == 3 || type == 5) && counter <= limitgames) {
            counter ++;
            cout << counter << endl;
            
            if (sequence == 1) {
                RLagent1.update(board.whoswin(col, player));
            }
            
            else if (sequence == 2) {
                int winner = board.whoswin(col, player);
                RLagent2.update(winner);
            }
            
            else {
                RLagent1.update(board.whoswin(col, player));
                RLagent2.update(board.whoswin(col, player));
            }
            
            startgame = 'y';
            if (counter == limitgames) {
                counter = 0;
            }
        }
        
        else {
            if (type == 4 && sequence == 1) {
                RLagent2.update(board.whoswin(col, player));
            }
            
            if (type == 4 && sequence == 2) {
                RLagent1.update(board.whoswin(col, player));
            }
            
            cout << "Play again?" << endl;
            cin >> startgame;
        }
        
        if (startgame == 'y' || startgame == 'Y') {
            board.resetboard();
        }
    }
}

void outputwinner(Board board, int type, int sequence, int col, int player) {
    if (board.whoswin(col, player) == 1) {//first player wins
        switch (type) {
            case 1://human vs human
                cout << "Player1 wins." << endl;
                break;
            case 2://human vs AI
                if (sequence == 1) {//human first
                    cout << "You win." << endl;
                }
                else if (sequence == 2) {//AI first
                    cout << "You lose." << endl;
                }
                break;
            case 3://Heuristic AI vs RL AI
            case 4://Human vs RL AI
            case 5://RL AI vs RL AI
                cout << "x wins." << endl;
                break;
                
            default:
                break;
        }
    }
    else if (board.whoswin(col, player) == 2) {//second player wins
        switch (type) {
            case 1:
                cout << "Player2 wins." << endl;
                break;
            case 2:
                if (sequence == 1) {
                    cout << "You lose." << endl;
                }
                else if (sequence == 2) {
                    cout << "You win." << endl;
                }
                break;
            case 3:
            case 4:
            case 5:
                cout << "o wins." << endl;
                break;
                
            default:
                break;
        }
    }
    else cout << "Draw." << endl;//no one wins
}

void whoseturn(Board board, int type, int sequence, int player, int &col) {
    char column;

    if (type == 1) {//multiplayer
    cout << "player" << player << "'s turn,please choose a correct column." << endl;
    cin >> column;
    col = column - 97;
    }
    else if (type == 2 && sequence == 1) {//vsAI,play first
        switch (player) {
            case 1:
                cout << "your turn,please choose a correct column." << endl;
                cin >> column;
                col = column - 97;
                break;
                
            case 2:
                col = AIplay(board, player);
                break;
        }
    }
    else if (type == 2 && sequence == 2) {//vsAI,play second
        switch (player) {
            case 1:
                col = AIplay(board, player);
                break;
                
            case 2:
                cout << "your turn,please choose a correct column." << endl;
                cin >> column;
                col = column - 97;
                break;
        }
    }
    else if (type == 3 && sequence == 1) {//Heuristic AI vs RL AI
        switch (player) {
            case 1:
                col = RLagent1.RLplay(board);
                break;
                
            case 2:
                col = AIplay(board, player);
                break;
        }
    }
    else if (type ==3 && sequence == 2){
        switch (player) {
            case 1:
                col = AIplay(board, player);
                break;
                
            case 2:
                col = RLagent2.RLplay(board);
                break;
        }
    }
    else if (type == 4 && sequence == 1) {
        switch (player) {
            case 1:
                cout << "your turn,please choose a correct column." << endl;
                cin >> column;
                col = column - 97;
                break;
                
            case 2:
                col = RLagent2.RLplay(board);
                break;
        }
    }
    else if (type == 4 && sequence == 2) {
        switch (player) {
            case 1:
                col = RLagent1.RLplay(board);
                break;
                
            case 2:
                cout << "your turn,please choose a correct column." << endl;
                cin >> column;
                col = column - 97;
                break;
        }
    }
    else if (type == 5) {
        switch (player) {
            case 1:
                col = RLagent1.RLplay(board);
                break;
                
            case 2:
                col = RLagent2.RLplay(board);
                break;
        }
    }
}