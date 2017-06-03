//
//  robot.cpp
//  Connectfour
//
//  Created by Yufeng Chen on 27/03/2016.
//  Copyright © 2016 Yufeng Chen. All rights reserved.
//

#include <iostream>
#include <cstdlib>
//#include <time.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <random>
#include "robot.hpp"

using namespace std;

Reinforce::Reinforce(Board board, int getplayer, string filename, string resultfilename) {
    copyboard = board;
    filestore = filename;
    resultrecord = resultfilename;
    player = getplayer;
    
    fstream currfile(filestore.c_str(), fstream::out|fstream::in);
    currfile.close();
    fstream resultfile(resultrecord.c_str(), fstream::out|fstream::in);
    resultfile.close();
    
//initialize the data file
//    ofstream learfile(filestore.c_str(),ofstream::out);
//    learfile.close();
//    ofstream outcometfile(resultrecord.c_str(),ofstream::out);
//    learfile.close();
}

int Reinforce::RLplay(Board board) {
//    srand((unsigned)time(NULL));
    copyboard = board;
    int drop;
    int exploredrop;
    drop = exploit();
    
    int colcount = 0;
    for (int i = 0; i < 7; i++) {
        if (copyboard.getnode(0, i) != 0) {
            colcount++;
        }
    }
    
    if (chooseActType() && colcount < 6 && valuekeeper != 1) {
        while (true) {
            exploredrop = explore();
            if (drop != exploredrop) {
                drop = exploredrop;
                break;
            }
        }
    }
    
    valuelist.push_back(valuekeeper);
    boardlist.push_back(movelistkeeper);

    return drop;
}

bool Reinforce::chooseActType() {
    int rdAT;
    
    random_device randomnumber;
    rdAT = randomnumber() % 100;
    
    //random possibility
    if (rdAT < 1) {
        return true;
    }
    else {
        return false;
    }
}

int Reinforce::explore() {

    int rddrop;
    
    
    while (!false) {
        random_device randomnumber;
        rddrop = randomnumber() % 7;
        
        if (copyboard.checkdrop(rddrop)) {
            break;
        }
    }
    
    for (int i = 5; i >= 0; i--) {
        if (copyboard.cpnode[i][rddrop] == 0) {
            string cpmovelsit;
            cpmovelsit=copyboard.movelist(i,rddrop,player);
            double value;
            value = getvalue(rddrop, cpmovelsit);
            valuekeeper = value;
            movelistkeeper = cpmovelsit;
            break;
        }
    }
    
    return rddrop;
}

int Reinforce::exploit() {
    double value = -1;
    double maxvalue = -1;
    int possibledrop = 0;
    int samevalcounter = 0;
    int samerd = -1;
    vector<int> samevaldroplist;
    vector<string> samearraylist;
    string restorearray;
    
    while (true) {
        for (int j = 0; j < 7; j++) {
            for (int i = 4; i >= 0; i--) {
                if (copyboard.cpnode[0][j]!=0) {
                    break;
                }
                if ((copyboard.cpnode[5][j] == 0) || (copyboard.cpnode[i][j] == 0 && copyboard.cpnode[i+1][j] != 0)) {
                    string cpmovelsit;
                    if (copyboard.cpnode[5][j] == 0) {
                        cpmovelsit=copyboard.movelist(5,j,player);
                    }
                    else {
                        cpmovelsit=copyboard.movelist(i,j,player);
                    }
                    value = getvalue(j, cpmovelsit);
                    
                
                    if (value>maxvalue) {
                        samevalcounter = 1;
                        maxvalue = value;
                        samevaldroplist.clear();
                        samevaldroplist.push_back(j);
                        samearraylist.clear();
                        samearraylist.push_back(cpmovelsit);
                        break;
                    }
                    
                    else if (value == maxvalue){
                        samevalcounter++;
                        samevaldroplist.push_back(j);
                        samearraylist.push_back(cpmovelsit);
                        break;
                    }
                }
            }
        }
        
        if (samevalcounter == 1) {
            possibledrop = samevaldroplist[0];
            if (copyboard.checkdrop(possibledrop)) {
                possibledrop = samevaldroplist[0];
                restorearray = samearraylist[0];
                break;
            }
        }
        
        else if (samevalcounter > 1) {

            random_device randomnumber;
            samerd = randomnumber() % samevalcounter;
            
            possibledrop = samevaldroplist[samerd];
            
            if (copyboard.checkdrop(possibledrop)) {
                possibledrop = samevaldroplist[samerd];
                restorearray = samearraylist[samerd];
                break;
            }
        }
    }
    
    valuekeeper = maxvalue;
    movelistkeeper = restorearray;
    
    return possibledrop;
}

double Reinforce::getvalue(int col, string cpmvlist) {
    double value;
    value = -2;
    
    Board tryboard;
    tryboard = copyboard;
    tryboard.drop(col, player);
    if (tryboard.whoswin(col, player) == player) {
        value = 1;//Truncation
    }
    else {
        ifstream currfile;
        string stagename;
        string stgval;
        int lines;
        lines = countline();
    
        currfile.open(filestore.c_str());
        if (currfile.is_open()) {
            for (int i = 0;i < lines;i++){
                currfile >> stagename>>stgval;
                if (cpmvlist == stagename) {
                    value = atof(stgval.c_str());
                    break;
                }
            }
        }
        if (value == -2) {
            value = 0.5;
        }
        currfile.close();
    }
    
    return value;
}

void Reinforce::update(int winner){
    
    fstream resultfile(resultrecord.c_str(), fstream::out|fstream::in);
    if (resultfile.is_open()) {
        int winlosedraw;
        if (winner == 0) {
            winlosedraw = 0;
        }
        
        else if (player == winner) {
            winlosedraw = 1;
        }
        
        else if (player != winner) {
            winlosedraw = 2;
        }
        resultfile.seekp(0,ios::end);
        resultfile<<winlosedraw;
        
        countgames++;
        cout<<countgames<<endl;
    }
    resultfile.close();
    
    for (int i = 0; i < valuelist.size(); i++) {
        string array = boardlist[i];
        double val = valuelist[i];
        double improvement = alpha * (reward(winner) - val);
        val += improvement;
        write(array,val);
    }

    valuelist.clear();
    boardlist.clear();
}

void Reinforce::write(string array, double value) {
    int lines;
    long position[2];
    position[0] = -1;
    position[1] = -1;
    string blank = " ";
    string stagename;
    lines = countline();
    
    stringstream ss;
    string trans;
    ss << value;
    trans += ss.str();
    
    //symmetry
    string symmetry;
    for (int m = 0; m < 6; m++) {
        for (int n = 6; n >= 0; n--) {
            symmetry += array[7 * m + n];
        }
    }
    
    int countsymt;
    if (array == symmetry) {
        countsymt = 1;
    }
    else countsymt = 0;
    
    string orivalue;
    
    fstream currfile;
    currfile.open(filestore.c_str(),fstream::out|fstream::in);
    if (currfile.is_open()) {
        for (int i = 0; i <= lines; i++) {
            currfile >> stagename;
            
            if (array == stagename || symmetry == stagename) {
                position[countsymt] = currfile.tellp();
                countsymt++;
            }
            if (countsymt == 2) {
                break;
            }
        }
    }
    currfile.close();
    
    fstream into;
    into.open(filestore.c_str(),fstream::out|fstream::in);
    if (into.is_open()) {
        if (position[1] == -1) {
            into.seekp(0,ios::end);
            into << array.c_str() << blank.c_str() << trans.c_str();
            for (int i = 0; i < (50-sizeof(trans)); i ++) {
                into << blank.c_str();
            }
            into << endl;
            if (countsymt == 0){
                into << symmetry.c_str() << blank.c_str() << trans.c_str();
                for (int i = 0; i < (50-sizeof(trans)); i ++) {
                    into << blank.c_str();
                }
                into << endl;
            }
        }
        else if (position[0] == -1) {
            into.seekp(position[1]);
            into << blank.c_str() << trans.c_str();
        }
        else {
            for (int k = 0; k < 2; k++) {
                into.seekp(position[k]);
                into << blank.c_str() << trans.c_str();
            }
        }
    }
    into.close();
}

string Reinforce::getarray() {
    string s;
    
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            int &b = copyboard.cpnode[i][j];
            stringstream ss;
            ss << b;
            s += ss.str();
        }
    }
    return s;
}
int Reinforce::countline() {
    int n = 0;
    string tmp;
    
    ifstream currfile;
    currfile.open(filestore.c_str(),fstream::in);
    if (currfile.is_open()) {
        while (getline(currfile,tmp,'\n')) {
            n++;
        }
    }
    currfile.close();
    
    return n;
}
double Reinforce::reward(int winner) {
    if (winner == 0) {
        return 0.5;
    }
    
    if (player == winner) {
        return 1;
    }
    
    else return 0;
}