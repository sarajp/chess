//
//  board.h
//  chess.cpp
//
//  Created by Sara Pisanelli on 4/21/18.
//  Copyright © 2018 Sara Pisanelli. All rights reserved.
//

#ifndef board_h
#define board_h
#include "pieces.h"
#include <iostream>
#include <cstring>
#include <vector>

class Board {
  Piece board[9][9] = {{Piece()}};

public:
  Board() {
    //label edges
    for(int i = 0; i < 8; ++i) board[i][0] = Label('8' - char(i));
    for(int i = 0; i < 8; ++i) board[8][i+1] = Label('A' + char(i));
  
    //create pawns
    for(int i = 0; i < 8; ++i) board[1][i+1] = Pawn(false, 'p');
    for(int i = 0; i < 8; ++i) board[6][i+1] = Pawn(true, 'P');
    
    //create rooks
    board[0][1] = Rook(false, 'r');
    board[0][8] = Rook(false, 'r');
    board[7][1] = Rook(true, 'R');
    board[7][8] = Rook(true, 'R');
    
    //create horses
    board[0][2] = Horse(false, 'h');
    board[0][7] = Horse(false, 'h');
    board[7][2] = Horse(true, 'H');
    board[7][7] = Horse(true, 'H');
    
    //create bishops
    board[0][3] = Bishop(false, 'b');
    board[0][6] = Bishop(false, 'b');
    board[7][3] = Bishop(true, 'B');
    board[7][6] = Bishop(true, 'B');
    
    //create queens
    board[0][4] = Queen(false, 'q');
    board[7][4] = Queen(true, 'Q');
    
    //create kings
    board[0][5] = King(false, 'k');
    board[7][5] = King(true, 'K');
    
    printBoard();
  }
  
  //special case for pawns
  void promote(int x, int y) {
    Piece promoted = board[8][0];
    char request = 'X';
    std::cout << "Select a piece to promote your pawn to.\n";
    while(promoted.getSymbol() != 'X') {
      std::cin >> request;
      switch(request) {
        case 'p':
          promoted = Pawn(false, 'p');
          break;
        case 'P':
          promoted = Pawn(true, 'p');
          break;
        case 'r':
          promoted = Rook(false, 'r');
          break;
        case 'R':
          promoted = Rook(true, 'R');
          break;
        case 'h':
          promoted = Horse(false, 'h');
          break;
        case 'H':
          promoted = Horse(true, 'H');
          break;
        case 'b':
          promoted = Bishop(false, 'b');
          break;
        case 'B':
          promoted = Bishop(true, 'B');
          break;
        case 'q':
          promoted = Queen(false, 'q');
          break;
        case 'Q':
          promoted = Queen(true, 'Q');
          break;
        case 'k':
        case 'K':
          std::cout << "Nice try.\n";
          break;
        default:
          std::cout << "You must select an eligible piece\n";
          break;
      }
    }
    overwrite(x, y, promoted);
  }
  
  //returns Piece at given board space
  Piece checkSpace(int x, int y) {return board[y][x];}
  
  //changes a board space
  void overwrite(int x, int y, Piece &incoming) {
    board[y][x] = incoming;
  }
  
  //checks for valid input
  bool onBoard(int x, int y) {
    if((x < 1) || (x > 8) || (y < 0) || (y > 7)) return false;
    return true;
  }
  
  //checks if given player and piece match
  bool myPiece(int x, int y, bool player) {
    if(player && (checkSpace(x, y).getSymbol() <= 'Z') &&
       (checkSpace(x, y).getSymbol() != 'X')) return true;
    if(!player && checkSpace(x, y).getSymbol() >= 'a') return true;
    return false;
  }
  
  //checks that the end position is blank or an enemy
  bool validTarget(int x, int y, bool player) {
    if(checkSpace(x, y).getSymbol() == 'X') return true;
    if(!player && (checkSpace(x, y).getSymbol() <= 'Z')) return true;
    if(player && checkSpace(x, y).getSymbol() >= 'a') return true;
    return false;
  }
  
  //prints the board
  void printBoard() {
    for(int i = 0; i < 9; ++i) {
      for(int j = 0; j < 9; ++j) {
        if(j == 1) std::cout << "| ";
        std::cout << board[i][j].getSymbol() << "  ";
      }
      std::cout << "\n\n";
      if(i == 7) std::cout << "---------------------------\n\n";
    }
  }
  
  //checks if move is valid, calls overwrite
  bool move(bool team, int startX, int startY, int endX, int endY) {
    //check start and end pieces and positions
    if(myPiece(startX, startY, team) && validTarget(endX, endY, team) &&
       onBoard(startX, startY) && onBoard(endX, endY)) {
      Piece currentPiece = board[startY][startX];
      //white's turn
      if(team) {
        if(validWhiteMove(currentPiece.getSymbol(), startX, startY, endX, endY)) {
          overwrite(endX, endY, currentPiece);
          overwrite(startX, startY, board[8][0]);
          if((currentPiece.getSymbol() == 'P') && (endY == 0)) promote(endX, endY);
        } else {
          std::cout << "Invalid move.\n";
          return false;
        }
      //black's turn
      } else {
        if(validBlackMove(currentPiece.getSymbol(), startX, startY, endX, endY)) {
          overwrite(endX, endY, currentPiece);
          overwrite(startX, startY, board[8][0]);
          if((currentPiece.getSymbol() == 'p') && (endY == 7)) promote(endX, endY);
        } else {
          std::cout << "Invalid move.\n";
          return false;
        }
      }
    } else {
      std::cout << "Invalid move.\n";
      return false;
    }
    return true;
  }
  
  bool rookMove(int startX, int startY, int endX, int endY) {
    //vertical movement
    if(startX == endX) {
      int i = startY;
      //up
      if(startY < endY) {
        while(startY < endY) {
          if(board[startX][i].getSymbol() != 'X') return false;
          ++i;
        }
      //down
      } else if(startY > endY) {
        while(startY > endY) {
          if(board[startX][i].getSymbol() != 'X') return false;
          --i;
        }
      }
      return true;
    //horizontal movement
    } else if(startY == endY) {
      int i = startX;
      //right
      if(startX < endX) {
        while(i < endX) {
          if(board[i][startY].getSymbol() != 'X') return false;
          ++i;
        }
      //left
      } else if(startX > endX) {
        while(i > endX) {
          if(board[i][startY].getSymbol() != 'X') return false;
          --i;
        }
      }
      return true;
    }
    return false;
  }
  
  bool bishopMove(int startX, int startY, int endX, int endY) {
    int i = startX;
    int j = startY;
    if(startX > endX) {
      //check left
      if(startY > endY) {
        //top left
        while((i > endX) && (j > endY)) {
          if(board[i][j].getSymbol() != 'X') return false;
          --i;
          --j;
        }
        return true;
      } else {
        //bottom left
        while((i > endX) && (j < endY)) {
          if(board[i][j].getSymbol() != 'X') return false;
          --i;
          ++j;
        }
        return true;
      }
    } else {
      //check right
      if(startY > endY) {
        //top right
        while((i < endX) && (j > endY)) {
          if(board[i][j].getSymbol() != 'X') return false;
          ++i;
          --j;
        }
        return true;
      } else {
        //bottom right
        while((i < endX) && (j < endY)) {
          if(board[i][j].getSymbol() != 'X') return false;
          ++i;
          ++j;
        }
        return true;
      }
    }
    return false;
  }
  
  bool horseMove(int startX, int startY, int endX, int endY) {
    //move up
    if((startY + 2 == endY) && (startX + 1 == endX)) return true;
    if((startY + 2 == endY) && (startX - 1 == endX)) return true;
    //move down
    if((startY - 2 == endY) && (startX + 1 == endX)) return true;
    if((startY - 2 == endY) && (startX - 1 == endX)) return true;
    //move right
    if((startY + 1 == endY) && (startX + 2 == endX)) return true;
    if((startY - 1 == endY) && (startX + 2 == endX)) return true;
    //move left
    if((startY + 1 == endY) && (startX + 2 == endX)) return true;
    if((startY - 1 == endY) && (startX + 2 == endX)) return true;
    
    return false;
  }
  
  bool validWhiteMove(char sym, int startX, int startY, int endX, int endY) {
    switch(sym) {
      case 'P':
        //basic pawn move
        if((startX == endX) && (startY-1 == endY)) return true;
        //left/right capture
        if((startY+1 == endY) && (startX-1 == endX)) return true;
        if((startY-1 == endY) && (startX-1 == endX)) return true;
        //first double move
        if((startY == 6) && (startX == endX) && (startY-2 == endY)) return true;
        
        return false;
      case 'R':
        return rookMove(startX, startY, endX, endY);
      case 'H':
        return horseMove(startX, startY, endX, endY);
      case 'B':
        return bishopMove(startX, startY, endX, endY);
      case 'Q':
        return (rookMove(startX, startY, endX, endY) ||
                bishopMove(startX, startY, endX, endY));
      case 'K':
        if((abs(startX - endX) < 2) && (abs(startY - endY) < 2)) return true;
        return false;
      default:
        std::cout << "Error: Not a valid piece.\n";
        return false;
        break;
    }
  }
  
  bool validBlackMove(char sym, int startX, int startY, int endX, int endY) {
    switch(sym) {
      case 'p':
        //basic pawn move
        if((startX == endX) && (startY+1 == endY)) return true;
        //left/right capture
        if((startY+1 == endY) && (startX+1 == endX)) return true;
        if((startY-1 == endY) && (startX+1 == endX)) return true;
        //first double move
        if((startY == 1) && (startX == endX) && (startY+2 == endY)) return true;
        return false;
      case 'r':
        return rookMove(startX, startY, endX, endY);
      case 'h':
        return horseMove(startX, startY, endX, endY);
      case 'b':
        return bishopMove(startX, startY, endX, endY);
      case 'q':
        return (rookMove(startX, startY, endX, endY) ||
                bishopMove(startX, startY, endX, endY));
      case 'k':
        if((abs(startX - endX) < 2) && (abs(startY - endY) < 2)) return true;
        return false;
      default:
        std::cout << "Error: Not a valid piece.\n";
        return false;
        break;
    }
  }
  
  
  //TODO
    //edge cases: castling
  
};

#endif /* board_h */
