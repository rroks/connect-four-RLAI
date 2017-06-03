//
//  connectfour.h
//  Connectfour
//
//  Created by Yufeng Chen on 16/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#ifndef connectfour_h
#define connectfour_h

#include <iostream>
#include "board.hpp"
#include "AIfunc.hpp"

using namespace std;

void outputwinner(Board board, int type, int sequence, int col, int player);
void whoseturn(Board board, int type, int sequence, int player, int &col);

#endif /* connectfour_h */
