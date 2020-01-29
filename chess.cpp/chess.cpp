//  chess.cpp
//
//  Created by Sara Pisanelli on 4/21/18.
//  Copyright © 2018 Sara Pisanelli. All rights reserved.
//

#include <iostream>
#include "2PlayerGame.cpp"
#include <string>

using namespace std;

int main() {
  cout << "Welcome to chess!\n";
  cout << "To move a piece, enter commands in \"A1 to A2\" format.\n";
  cout << "To exit, type \"q\" at any time.\n\n";
  cout << "How many players? (Choose 0, 1, or 2).\n";
  
  bool numPlayers = false;
  int playerInput = 3;
  do {
    cin >> playerInput;
    if(playerInput == 0) { numPlayers = 0; cout << endl; }
    else if(playerInput == 1) { numPlayers = 1; cout << endl; }
    else if(playerInput == 2) { numPlayers = 2; cout << endl; }
    else { cout << "Please choose 0, 1, or 2.\n"; }
  } while ((playerInput != 0) && (playerInput != 1) && (playerInput != 2));
  
  if(playerInput == 0) { //0 player mode, CVC
    
  }
  
  if(playerInput == 1) { //1 player mode, PVC
    
  }
  
  if(playerInput == 2) { //2 player mode, PVP
    Board board;
    char justTaken = 'X';
    bool firstTurn = true;
  
    //game loop
    while((justTaken != 'K') && (justTaken != 'k')) {
      if(firstTurn) {
        justTaken = WhiteTurn(board);
        if(justTaken == '0') return 0;
        if(justTaken != '?' && justTaken != '!') firstTurn = false;
      } else {
        justTaken = BlackTurn(board);
        if(justTaken == '0') return 0;
        if(justTaken != '?' && justTaken != '!') firstTurn = true;
      }
    }
    (justTaken == 'K')? cout << "\nBlack Wins!\n" : cout << "\nWhite Wins!\n";
  }
  
  return 0;
}
