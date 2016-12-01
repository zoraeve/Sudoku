//
//  main.cpp
//  Sudoku
//
//  Created by Edmond on 2016/10/26.
//  Copyright © 2016年 Edmond. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


int square[10][10][10];
int solve_square[10][10];

int load()
{
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            for (int cnt = 0; cnt <= 9; ++cnt) {
                square[i][j][cnt] = cnt;
            }
            solve_square[i][j] = 0;
        }
    }
    
    return 0;
}

int input(const unsigned int x, const unsigned int y, const unsigned int v)
{
    if (0 != v) {
        
        cout << "new solve is " << x << "-" << y << ": " << v << endl;

        // 目标单元格
        for (int cnt = 0; cnt <= 9; ++cnt) {
            square[x][y][cnt] = 0;
        }
        
        // hang
        for (int cnt = 1; cnt <= 9; ++cnt) {
            square[x][cnt][v] = 0;
        }
        
        // lie
        for (int cnt = 1; cnt <= 9; ++cnt) {
            square[cnt][y][v] = 0;
        }
        
        int h = (x-1) - (x - 1) % 3;
        int s = (y-1) - (y - 1) % 3;
        for (int i = h + 1; i <= h + 3; ++i) {
            for (int j = s + 1; j <= s + 3; ++j) {
                square[i][j][v] = 0;
            }
        }
    }
    square[x][y][v] = v;

    solve_square[x][y] = v;
    
    return 0;
}

int output()
{
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            cout << i << "-" << j << ": ";
            for (int cnt = 1; cnt <= 9; ++cnt) {
                if (0 != square[i][j][cnt]) {
                    cout << square[i][j][cnt] << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    cout << endl;
    
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            cout << solve_square[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

int logic()
{
    // number
    // h
    // s
    // block
    
    for (int cnt = 1; cnt <= 9; ++cnt) { // all possible values
        
        for (int x = 1; x <= 9; ++x) { // hang
            
            bool bEnable = true;
            
            for (int y = 1; y <= 9; ++y) {
                if (cnt == solve_square[x][y]) { // already has this value
                    bEnable = false; // not enable
                    break;
                }
            }
            
            if (true == bEnable) { // this hang does not have this value
                
                int pos_count = 0; // index_x_y
                int pos_y = 0;
                
                for (int y = 1; y <= 9; ++y) { // check every cell of this hang
                
                    bool bEmpty = true;
                    
                    if (0 == solve_square[x][y]) { // get an empty pos
                        
                        for (int i = 0; i <= 9; ++i) { // check if this lie has same value
                            if (cnt == solve_square[i][y]) { // not a valid empty pos
                                bEmpty = false;
                                break;
                            }
                        }
                        
                        if (true == bEmpty) { // this pos is OK : x-y
                            
                            bool bAvailable = true;
                            
                            int h = (x-1) - (x - 1) % 3;
                            int s = (y-1) - (y - 1) % 3;
                            for (int i = h + 1; i <= h + 3; ++i) { // check block if has same value
                                for (int j = s + 1; j <= s + 3; ++j) {
                                    if (cnt == solve_square[i][j]) {
                                        bAvailable = false;
                                        break;
                                    }
                                }
                            }
                            if (true == bAvailable) { // the empty can set this value
                                ++pos_count; // add a pos
                                pos_y = y;
                            }
                        }
                    }
                }
                if (1 == pos_count) { // only can be set here
                    input(x, pos_y, cnt);
                }
            }
            
        }
    }
    
    // number in line 1
    // if has
    // to next line
    // else
    // get all empty
    // if shuzhede has number
    // to next empty
    // else
    // if block has number
    // to next empty
    // else set number
    //
    
    return 0;
}

int guess()
{
//    bool bSolved = true;
//    bool bValid = true;
//    
//    for (int i = 1; i <= 9; ++i) {
//        for (int j = 1; j <= 9; ++j) {
//            
//            if (0 == solve_square[i][j]) {
//                for (int k = 1; k <= 9; ++k) {
//                    if (0 != square[i][j][j]) {
//                        input(i, j, k);
//                        
//                        if (!bSolved) {
//                            if (!bValid) { // error
//                                ; // try an other value
//                            } else {
//                                guess();
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    
    return 0;
}

int solve()
{
    cout << endl;
    
    bool bFound = true;
    
    do {
        logic();
        
        bFound = false;
        
        for (int i = 1; i <= 9; ++i) {
            for (int j = 1; j <= 9; ++j) {
                
                int cnt = 0;
                int slot = 0;
                for (int k = 1; k <= 9; ++k) {
                    if (square[i][j][k] != 0) {
                        ++cnt;
                        slot = k;
                    }
                }
                if (1 == cnt && 0 == solve_square[i][j]) {
                    
                    cout << "found new " << i << "-" << j << ": " << square[i][j][slot] << endl;

                    input(i, j, square[i][j][slot]);
                    bFound = true;
                }
            }
        }
        
    } while (bFound);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    load();
    
    cout << "pls input square: " << endl;
//    while (1) {
//        int x = 0; int y = 0; int v = 0;
//        scanf("%d %d %d", &x, &y, &v);
//        if (0 == x == y == v) {
//            break;
//        }
//        input(x, y, v);
//    }
    
    input(1, 1, 3);
    input(1, 5, 1);
    input(1, 9, 2);
  
    input(2, 2, 1);
    input(2, 3, 9);
    input(2, 7, 8);
    input(2, 8, 5);
    
    input(3, 4, 5);
    input(3, 6, 2);
    
    input(4, 3, 5);
    input(4, 5, 7);
    input(4, 7, 4);
    
    input(5, 1, 1);
    input(5, 3, 6);
    input(5, 7, 3);
    input(5, 9, 9);
    
    input(6, 3, 3);
    input(6, 5, 4);
    input(6, 7, 1);
    
    input(7, 4, 1);
    input(7, 6, 6);
    
    input(8, 2, 9);
    input(8, 3, 8);
    input(8, 7, 2);
    input(8, 8, 6);
    
    input(9, 1, 4);
    input(9, 5, 9);
    input(9, 9, 8);

//    input(1, 2, 2);
//    input(1, 4, 4);
//    input(1, 5, 3);
//    input(1, 6, 6);
//    
//    input(2, 1, 5);
//    input(2, 3, 6);
//    input(2, 8, 3);
//    
//    input(3, 2, 7);
//    input(3, 5, 2);
//    
//    input(4, 1, 3);
//    input(4, 4, 9);
//    input(4, 6, 7);
//    input(4, 9, 6);
//    
//    input(5, 1, 4);
//    input(5, 3, 7);
//    input(5, 7, 8);
//    input(5, 9, 2);
//    
//    input(6, 1, 9);
//    input(6, 4, 2);
//    input(6, 6, 1);
//    input(6, 9, 5);
//    
//    input(7, 5, 5);
//    input(7, 8, 4);
//    
//    input(8, 2, 8);
//    input(8, 7, 6);
//    input(8, 9, 9);
//    
//    input(9, 4, 7);
//    input(9, 5, 9);
//    input(9, 6, 4);
//    input(9, 8, 2);
    
    solve();
    
    output();
    
    return 0;
}
