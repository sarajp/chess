//  2PlayerGame.cpp
//
//  Created by Sara Pisanelli on 4/21/18.
//  Copyright © 2018 Sara Pisanelli. All rights reserved.
//

#include <iostream>
#include "board.h"
#include "pieces.h"
#include <string>

using namespace std;

//reads in inputted move and converts to array coordinates
void inputMove(int &fromX, int &fromY, int &toX, int &toY) {
  char x;
  int y;
  string junk;
  
  cin >> x;
  if(x == 'q') {
    fromX = -1;
    return;
  }
  cin >> y >> junk;
  fromX = x - 'A' + 1;
  fromY = 8 - y;
  
  cin >> x;
  if(x == 'q') {
    fromX = -1;
    return;
  }
  cin >> y;
  toX = x - 'A' + 1;
  toY = 8 - y;
  cout << "\n";
}

void movedPiece(char tag) {
  switch (tag) {
    case 'p':
    case 'P' :
      cout << "a pawn from ";
      break;
    case 'r':
    case 'R' :
      cout << "a rook from ";
      break;
    case 'h':
    case 'H' :
      cout << "a horse from ";
      break;
    case 'b':
    case 'B' :
      cout << "a bishop from ";
      break;
    case 'q':
    case 'Q' :
      cout << "their queen from ";
      break;
    case 'k':
    case 'K' :
      cout << "their king from ";
      break;
    default:
      cout << "Error: invalid piece\n";
      break;
  }
}

void takenPiece(char tag) {
  switch (tag) {
    case 'p':
    case 'P' :
      cout << "pawn";
      break;
    case 'r':
    case 'R' :
      cout << "rook";
      break;
    case 'h':
    case 'H' :
      cout << "horse";
      break;
    case 'b':
    case 'B' :
      cout << "bishop";
      break;
    case 'q':
    case 'Q' :
      cout << "queen";
      break;
    case 'k':
    case 'K' :
      cout << "king";
      break;
    default:
      cout << "Error: invalid piece\n";
      break;
  }
}

bool exitGame() {
  cout << "Are you sure you wish to exit? y/n\n";
  char response;
  cin.ignore(INT_MAX,'\n');
  //clear buffer
  cin >> response; //why won't this execute
  while(response != 'y' && response != 'n') {
    cout << "Please enter y or n\n";
    cin >> response; //dsfgjkjhksadf
  }
  if(response == 'y') {
    cout << "Thanks for playing!\n";
    return true;
  } else {
    return false;
  }
}

char WhiteTurn(Board &board) {
  //setup
  int fromX, fromY, toX, toY;
  cout << "White Player's move.\n";
  //read in player input
  inputMove(fromX, fromY, toX, toY);
  if(fromX < 0) {
    if(exitGame()) {
      return '0';
    } else {return '!';}
  }
  //store move data
  char origin = board.checkSpace(fromX, fromY).getSymbol();
  char dest = board.checkSpace(toX, toY).getSymbol();
  //move
  if(!board.move(true, fromX, fromY, toX, toY)) return '?';
  //display info
  cout << "White Player moved ";
  movedPiece(origin);
  cout << char(fromX+'A'-1) << 8-fromY << " to " <<
  char(toX+'A'-1) << 8-toY << ".\n";
  if(dest != 'X') {
    cout << "Black's ";
    takenPiece(dest);
    cout << " was taken.\n\n";
  }
  board.printBoard();
  return dest;
}

char BlackTurn(Board &board) {
  //setup
  int fromX, fromY, toX, toY;
  cout << "Black Player's move.\n";
  //read in player input
  inputMove(fromX, fromY, toX, toY);
  if(fromX < 0) {
    if(exitGame()) {
      return '0';
    } else {return '!';}
  }
  //store move data
  char origin = board.checkSpace(fromX, fromY).getSymbol();
  char dest = board.checkSpace(toX, toY).getSymbol();
  //move
  if(!board.move(false, fromX, fromY, toX, toY)) return '?';
  //display info
  cout << "Black Player moved ";
  movedPiece(origin);
  cout << char(fromX+'A'-1) << 8-fromY << " to " <<
  char(toX+'A'-1) << 8-toY << ".\n";
  if(dest != 'X') {
    cout << "White's ";
    takenPiece(dest);
    cout << " was taken.\n/n";
  }
  board.printBoard();
  return dest;
}
