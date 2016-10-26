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

int n, match[N], rmatch[N];
bool mfree[N], ffree[N], vis[N][N];
string group1[N], group2[N];
map<string, int> midx, fidx;
vector<int> mv[N], fv[N];

bool ifFreeG1Available(){
    for ( int i = 0 ; i < n ; i ++ ){
        if ( mfree[i] == true ){
            return true;
        }
    }
    return false;
}

int findFreeG1(){
    for ( int i = 0 ; i < n ; i ++ ){
        if ( mfree[i] == true ){
            return i;
        }
    }
}

bool ifG2Prefer(int w, int x, int y){
    int id1 = 0, id2 = 0;
    for ( int i = 0 ; i < n - 1 ; i ++ ){
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
    
    cin >> n;
    
    int i, j;
    for ( i = 0 ; i < n ; i ++ ){
        cin >> group1[i];
        midx[group1[i]] = i;
    }
    
    for ( i = 0 ; i < n ; i ++ ){
        cin >> group2[i];
        fidx[group2[i]] = i;
    }
    
    for ( i = 0 ; i < n ; i ++ ){
        for ( j = 0 ; j < n - 1 ; j ++ ){
            string choice;
            cin >> choice;
            mv[i].push_back(fidx[choice]);
        }
    }
    
    for ( i = 0 ; i < n ; i ++ ){
        for ( j = 0 ; j < n - 1 ; j ++ ){
            string choice;
            cin >> choice;
            fv[i].push_back(midx[choice]);
        }
    }

    for ( i = 0 ; i < n ; i ++ ) for ( j = 0 ; j < n ; j ++ ) vis[i][j] = false;
    
    // Group1 Favourable Algorithm
    
    for ( i = 0 ; i < n ; i ++ ){
        mfree[i] = true;
        ffree[i] = true;
    }
    
    int sel;
    
    while(ifFreeG1Available()){
        int fel = findFreeG1();
        for ( i = 0 ; i < n - 1 ; i ++ ){
            sel = mv[fel][i];
            if ( vis[fel][sel] == false ){
                vis[fel][sel] = true;
                break;
            }
        }
        if ( ffree[sel] == true ){
            match[fel] = sel;
            rmatch[sel] = fel;
            mfree[fel] = false;
            ffree[sel] = false;
        }
        else{
            if(ifG2Prefer(sel, fel, rmatch[sel])){
                mfree[rmatch[sel]] = true;
                match[fel] = sel;
                mfree[fel] = false;
                rmatch[sel] = fel;
            }
        }
    }
    
    for ( i = 0 ; i < n ; i ++ ){
        cout << i << " matched to " << match[i] << "\n";
    }
    
    return 0;
}
