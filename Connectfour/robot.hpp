//
//  robot.hpp
//  Connectfour
//
//  Created by Yufeng Chen on 27/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#ifndef robot_hpp
#define robot_hpp

#include "AIfunc.hpp"
#include "connectfour.h"
#include <iostream>
#include <cstdlib>
//#include <time.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Reinforce{
private:
    double alpha = 0.05;
    
    string filestore;
    string resultrecord;
    
    Board copyboard;
    
    int player;

    int droprd = -1;
    int exprd = -1;
    
    int countgames = 0;
    
    double valuekeeper;
    string movelistkeeper;
public:
//    Reinforce();
    Reinforce(Board board, int getplayer, string filename, string resultfilename);
    int RLplay(Board board);
    bool chooseActType();
    int random();
    int exploit();
    int explore();
    int countline();
    
    double getvalue(int col, string mvlist);
    double reward(int winner);
    
    void update(int winner);
    void write(string array, double value);
    
    vector<double> valuelist;
    vector<string> boardlist;
    string getarray();
};

#endif /* robot_hpp */
