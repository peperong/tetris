#include "tetromino.h"
#include <string>
#include "console/console.h"
Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");


Tetromino::Tetromino(std::string name, int size, std::string shape) {
    this->name_ = name;
    size_ = size;
    original_ = this;

    for(int i = 0; i < size_; i++) {
        for(int j = 0; j < size_; j++) {
            shape_[j][i] = shape[i*size_+j] == 'O' ? true : false;
        }
    if (name == "I") {
      original_ = &I;
    }
    else if (name == "O") {
      original_ = &O;
    }
    else if (name == "T") {
      original_ = &T;
    }
    else if (name == "S") {
      original_ = &S;
    }
    else if (name == "Z") {
      original_ = &Z;
    }
    else if (name == "J") {
      original_ = &J;
    }
    else if (name == "L") {
      original_ = &L;
    }
    }
}
Tetromino Tetromino::rotatedCW() {
  std::string newShape(size_ * size_, 'X'); 
  
  for(int i = 0; i < size_; i++) {
    for(int j = 0; j < size_; j++) {
      newShape[size_ * (size_ - j - 1) + i] = 
        shape_[i][j] ? 'O' : 'X';
    }
  }
  
  for(int i = 0; i < size_; i++) {
    for(int j = 0; j < size_; j++) {
      shape_[i][j] = newShape[i * size_ + j] == 'O';
    }
  }
}
Tetromino Tetromino::rotatedCCW() {
  std::string newShape(size_ * size_, 'X');
  
  for(int i = 0; i < size_; i++) {
    for(int j = 0; j < size_; j++) {
      newShape[size_ * j + (size_ - i - 1)] = 
        shape_[i][j] ? 'O' : 'X';
    }
  }

  for(int i = 0; i < size_; i++) {
    for(int j = 0; j < size_; j++) {
      shape_[i][j] = newShape[i * size_ + j] == 'O';
    }
  }
}
void Tetromino::drawAt(std::string s, int x, int y) {

  for(int i = 0; i < size_; i++) {
    for(int j = 0; j < size_; j++) {
      
      if(shape_[j][i] == true) {
        console::draw(x + i, y + j, s);  
      }
    }
  }
}
