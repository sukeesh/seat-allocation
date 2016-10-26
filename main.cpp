/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sukeesh
 *
 * Created on October 26, 2016, 9:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
 * 
 */

#define N 1000

int members, match[N], rmatch[N];
bool mfree[N], ffree[N], vis[N][N];
string male[N], female[N];
map<string, int> midx, fidx;
vector<int> mv[N], fv[N];

bool ifFreeManAvailable(){
    for ( int i = 0 ; i < members ; i ++ ){
        if ( mfree[i] == true ){
            return true;
        }
    }
    return false;
}

int findFreeMan(){
    for ( int i = 0 ; i < members ; i ++ ){
        if ( mfree[i] == true ){
            return i;
        }
    }
}

bool ifWomenPrefer(int w, int x, int y){
    int id1 = 0, id2 = 0;
    for ( int i = 0 ; i < members - 1 ; i ++ ){
        if(fv[w][i] == x){
            id1 = i;
        }
        if(fv[w][i] == y){
            id2 = i;
        }
    }
    if ( id1 < id2 ){
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    
    cin >> members;
    
    int i, j;
    for ( i = 0 ; i < members ; i ++ ){
        cin >> male[i];
        midx[male[i]] = i;
    }
    
    for ( i = 0 ; i < members ; i ++ ){
        cin >> female[i];
        fidx[female[i]] = i;
    }
    
    for ( i = 0 ; i < members ; i ++ ){
        for ( j = 0 ; j < members - 1 ; j ++ ){
            string choice;
            cin >> choice;
            mv[i].push_back(fidx[choice]);
        }
    }
    
    for ( i = 0 ; i < members ; i ++ ){
        for ( j = 0 ; j < members - 1 ; j ++ ){
            string choice;
            cin >> choice;
            fv[i].push_back(midx[choice]);
        }
    }

    for ( i = 0 ; i < members ; i ++ ) for ( j = 0 ; j < members ; j ++ ) vis[i][j] = false;
    
    // Male Favourable Algorithm
    
    for ( i = 0 ; i < members ; i ++ ){
        mfree[i] = true;
        ffree[i] = true;
    }
    
    int woman;
    
    while(ifFreeManAvailable()){
        int man = findFreeMan();
        for ( i = 0 ; i < members - 1 ; i ++ ){
            woman = mv[man][i];
            if ( vis[man][woman] == false ){
                vis[man][woman] = true;
                break;
            }
        }
        if ( ffree[woman] == true ){
            match[man] = woman;
            rmatch[woman] = man;
            mfree[man] = false;
            ffree[woman] = false;
        }
        else{
            if(ifWomenPrefer(woman, man, rmatch[woman])){
                mfree[rmatch[woman]] = true;
                match[man] = woman;
                mfree[man] = false;
                rmatch[woman] = man;
            }
        }
    }
    
    for ( i = 0 ; i < members ; i ++ ){
        cout << i << " Engaged to " << match[i] << "\n";
    }
    
    return 0;
}
