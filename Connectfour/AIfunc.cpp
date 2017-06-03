//
//  AIfunc.cpp
//  Connectfour
//
//  Created by Yufeng Chen on 27/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "AIfunc.hpp"

using namespace std;

int AIplay(Board board, int player) {
    int column = 7;
    srand((unsigned)time(NULL));
    int oppn = 0;
    Board boardcopy = board;//copy board
    
    if (player == 1) {
        oppn = 2;
    }
    if (player == 2) {
        oppn = 1;
    }

        for (column = 0; column < 7; column++) {//look for a winning drop
            boardcopy=board;
            if (boardcopy.getnode(0, column) == 0) {//make sure it is a valid column to drop
                boardcopy.drop(column, player);//make a virtual drop
                if (boardcopy.whoswin(column, player) == player) {//check winning drop
                    return column;
                    break;
                }
            }
        }

        for (column = 0; column < 7; column++) {//check whether opponent has any winning drop
            boardcopy=board;
            if (boardcopy.getnode(0, column) == 0) {
                boardcopy.drop(column, oppn);
                if (boardcopy.whoswin(column, oppn) == oppn) {//check opponent's winning drop
                    return column;
                    break;
                }
            }
        }
    
    boardcopy=board;//initialize
    
    if (boardcopy.getnode(5, 3) == 0) {//use many if to make robot draw in mid blocks
        column=3;
    }
    else if (boardcopy.getnode(4, 3) == 0) {
        column=3;
    }
    else if (boardcopy.getnode(5, 2) == 0 || boardcopy.getnode(5, 4) == 0){
        while(true){
        int i = rand() % 2;
        if (i == 0 && boardcopy.getnode(5, 2) == 0) {
            column = 2;
            break;
        }
        else if (i == 1 && boardcopy.getnode(5, 4) == 0) {
            column = 4;
            break;
        }
        }
    }
    else if (boardcopy.getnode(3, 3) == 0) {
        column = 3;
    }
    else if (boardcopy.getnode(4, 2 )== 0 || boardcopy.getnode(5, 1) == 0 || boardcopy.getnode(4, 4) == 0 || boardcopy.getnode(5, 5) == 0) {
        while (true) {
            int i = rand() % 4;
            if (i == 0 && boardcopy.getnode(4, 2) == 0) {
                column = 2;
                break;
            }
            else if (i == 1 && boardcopy.getnode(5, 1) == 0) {
                column = 1;
                break;
            }
            else if (i == 2 && boardcopy.getnode(4, 4) == 0) {
                column = 4;
                break;
            }
            else if (i == 3 && boardcopy.getnode(5, 5) == 0) {
                column = 5;
                break;
            }
        }
    }
    else if (boardcopy.getnode(2, 3) == 0) {
        column = 3;
    }
    else if (boardcopy.getnode(5, 0) == 0 || boardcopy.getnode(4, 1) == 0 || boardcopy.getnode(3, 2) == 0 || boardcopy.getnode(3, 4) == 0 || boardcopy.getnode(4, 5) == 0 || boardcopy.getnode(5, 6) == 0) {
        while (true) {
            int i = rand() % 6;
            if (i == 0 && boardcopy.getnode(5, 0) == 0) {
                column = 0;
                break;
            }
            else if (i == 1 && boardcopy.getnode(4, 1) == 0) {
                column = 1;
                break;
            }
            else if (i == 2 && boardcopy.getnode(3, 2) == 0) {
                column = 2;
                break;
            }
            else if (i == 3 && boardcopy.getnode(3, 4) == 0) {
                column = 4;
                break;
            }
            else if (i == 4 && boardcopy.getnode(4, 5) == 0) {
                column = 5;
                break;
            }
            else if (i == 5 && boardcopy.getnode(5, 6) == 0) {
                column = 6;
                break;
            }
        }
    }
    else if (boardcopy.getnode(1, 3) == 0){
        column = 3;
    }
    else if (boardcopy.getnode(4, 0) == 0 || boardcopy.getnode(3,1)==0||boardcopy.getnode(2,2)==0||boardcopy.getnode(2,4)==0||boardcopy.getnode(3,5)==0||boardcopy.getnode(4,6)==0){
        while(true){
        int i=rand()%6;
        if (i==0 && boardcopy.getnode(4,0)==0) {
            column= 0;
            break;
        }
        else if (i==1 && boardcopy.getnode(3,1)==0){
            column= 1;
            break;
        }
        else if (i==2 && boardcopy.getnode(2,2)==0){
            column= 2;
            break;
        }
        else if (i==3 && boardcopy.getnode(2,4)==0){
            column= 4;
            break;
        }
        else if (i==4&&boardcopy.getnode(3,5)==0){
            column= 5;
            break;
        }
        else if(i==5&&boardcopy.getnode(4,6)==0){
            column= 6;
            break;
        }
        }
    }
    else if (boardcopy.getnode(0,3)==0){
        column= 3;
    }
    else if (boardcopy.getnode(3,0)==0||boardcopy.getnode(2,1)==0||boardcopy.getnode(1,2)==0||boardcopy.getnode(1,4)==0||boardcopy.getnode(2,5)==0||boardcopy.getnode(3,6)==0){
        while(true){
        int i=rand()%6;
        if (i==0 && boardcopy.getnode(3,0)==0) {
            column= 0;
            break;
        }
        else if (i==1 && boardcopy.getnode(2,1)==0){
            column= 1;
            break;
        }
        else if (i==2 && boardcopy.getnode(1,2)==0){
            column= 2;
            break;
        }
        else if (i==3 && boardcopy.getnode(1,4)==0){
            column= 4;
            break;
        }
        else if (i==4 && boardcopy.getnode(2,5)==0){
            column= 5;
            break;
        }
        else if(i==5&&boardcopy.getnode(3,6)==0){
            column= 6;
            break;
        }
        }
    }
    else {
        while (true) {
        column=rand()%10;
        if (column<7&&boardcopy.checkdrop(column)) {
            break;
        }
    }
    }
//    if (boardcopy.checkdrop(column)) {
//        break;
//    }
//    }
    cout<<"AI is going to drop on clumn "<<column<<endl;
    return column;
}
