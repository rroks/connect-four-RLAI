//
//  board.cpp
//  Connectfour
//
//  Created by Yufeng Chen on 16/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include "board.hpp"

using namespace std;

Board::Board() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            node[i][j] = 0;
            cpnode[i][j] = node[i][j];
        }
    }
}

void Board::resetboard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            node[i][j] = 0;
            cpnode[i][j] = node[i][j];
        }
    }
}

void Board::printboard() {
    char move;
    
    cout << " ";
    for (int i = 0; i < 7; i++)
        cout << " " << char (i + 97) << " ";
    cout << endl;
    
    for (int i = 0; i < 6; i ++) {
        cout << 6 - i;

        for (int j=0; j<7; j++) {
            //           cout<<" X ";
            if (node[i][j] == 1) {
                move = 'x';
                cout << " " << move << " ";
            }
            else if (node[i][j] == 2) {
                move = 'o';
                cout << " " << move << " ";
            }
            else cout << "   ";
        }
        cout << '\n';
        for (int k = 0; k < 7; k++) {
            cout << "    ";
        }
        cout << '\n';
    }
}

bool Board::checkdrop(int col) {
    if (col < 0 || col > 6) {
        return false;
    }
    
    if (node[0][col] != 0) {
        return false;
    }
    
    return true;
}

bool Board::drop(int col, int player) {
    for (int i = 5; i >= 0; i--){
        if (node[i][col] == 0) {
            node[i][col] = player;
            cpnode[i][col] = node[i][col];
            return true;
        }
    }
    return true;
}

bool Board::checkfull() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (node[i][j] == 0)
            return false;
        }
    }
    return true;
}

bool Board::checkwin(int col, int player) {
    int vertical = 1;
    int horizontal = 1;
    int diagonal1 = 1;
    int diagonal2 = 1;
    int row;
    int i;
    int j;
    
    for (row = 0; row < 6; row++) {
        if (node[row][col] != 0) {
            break;
        }
    }
    
    for (i = row+1; node[i][col] == player && i < 6; i++,vertical++);
    for (i = row-1; node[i][col] == player && i >= 0; i--,vertical++);
    if (vertical >= 4) {
        return true;
    }
    
    for (j = col -1; node[row][j] == player && j >= 0; j--, horizontal++);
    for (j = col +1; node[row][j] == player && j < 7; j++, horizontal++);
    if (horizontal >= 4) {
        return true;
    }
    
    for (i = row-1, j = col-1; node[i][j] == player && i >= 0 && j >= 0; diagonal1++, i--, j--);
    for (i = row+1, j = col+1; node[i][j] == player && i < 6 && j < 7; diagonal1++, i++, j++);
    if (diagonal1 >= 4) {
        return true;
    }
    
    for (i = row-1, j= col+1; node[i][j] == player && i >= 0 && j < 7; diagonal2++, i--, j++);
    for (i = row+1, j= col-1; node[i][j] == player && i < 6 && j >= 0; diagonal2++, i++, j--);
    if (diagonal2 >= 4) {
        return true;
    }
    
    return false;
    
}

int Board::whoswin(int col,int player) {
    if (checkwin(col, player)) {
        return player;
    }
    else return 0;
}

int Board::getnode(int i, int j) {
    return node[i][j];
}

int Board::playerswitch(int &player, int player1, int player2) {
    if (player == player1) {
        player = player2;
    }
    else if (player == player2) {
        player = player1;
    }
    return player;
}

void Board::gametype(int &type, int &sequence) {
    cout << "Enter a number to choose an opponent:" << endl << "1:Multiplayer\n2:vs Heuristic AI\n3:RL AI vs  Heuristic AI\n4:vs RL AI\n5:RL AI vs RL AI" << endl;
    cin >> type;
//    while (true) {
//        switch (type) {
//            case 1:
//                cout<<"Let's begin!"<<endl;
//                break;
//            case 2: case 4:
//                cout<<"Enter 1 to play first, 2 to play second."<<endl;
//                cin>>sequence;
//                break;
//            case 3:
//                cout<<"AI vs AI."<<endl;
//                break;
//                
//            default:
//                break;
//        }
//    }
    if (type == 1) {
        cout << "Let's begin!" << endl;
    }
    else if (type == 2 || type == 4) {
        cout << "Enter 1 to play first, 2 to play second." << endl;
        cin >> sequence;
    }
    else if (type == 3) {
        cout << "RL AI vs Heuristic AI.\n1:RL first.\n2:RL second." << endl;
        cin >> sequence;
    }
    else if (type == 5) {
        cout << "RL AI vs RL AI." << endl;
    }
}
string Board::movelist(int row, int col, int player) {
    string mvlist;
    int fakedrop = player;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            stringstream s;
            if (row == i && j == col) {
                int &b = fakedrop;
//                cout<<fakedrop<<"fd"<<endl;
                s << b;
            }
            else {
                int &b = node[i][j];
                s<<b;
//                cout<<node[i][j]<<"nd"<<endl;
            }
            mvlist += s.str();
//            cout<<mvlist<<" mvlist "<<endl;
        }
    }
//    cout<<mvlist<<" mvlist "<<endl;
    return mvlist;
}