//
//  chess.h
//  chess.cpp
//
//  Created by Sara Pisanelli on 4/21/18.
//  Copyright © 2018 Sara Pisanelli. All rights reserved.
//

#ifndef chess_h
#define chess_h

class Piece {
protected:
  bool taken = false;
  bool color = false;
  char symbol = 'X';
  
public:
  Piece() {}
  
  Piece(bool team, char sym)
  : color(team), symbol(sym) {}
  
  void operator=(Piece other) {
    color = other.color;
    symbol = other.symbol;
  }

  char getSymbol() {return symbol;}
  bool getTaken() {return taken;}
  bool getColor() {return color;}
};

class Label : public Piece {
public:
  Label(char sym) : Piece(false, sym) {}
};

class Pawn : public Piece {
public:
  Pawn(bool team, char sym) : Piece(team, sym) {}

};


class Rook : public Piece {
public:
  Rook(bool team, char sym) : Piece(team, sym) {}
  
};


class Horse : public Piece {
public:
  Horse(bool team, char sym) : Piece(team, sym) {}
  
};


class Bishop : public Piece {
public:
  Bishop(bool team, char sym) : Piece(team, sym) {}
  
};


class Queen : public Piece {
public:
  Queen(bool team, char sym) : Piece(team, sym) {}
  
};


class King : public Piece {
public:
  King(bool team, char sym) : Piece(team, sym) {}
  
};


#endif /* chess_h */
