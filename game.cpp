#include <string>
#include "game.h"
#include "console/console.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "tetromino.h"
Tetromino I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino O("0", 2, "OOOO");
Tetromino T("T", 3, "XOXOOOXXX");
Tetromino S("S", 3, "XOOOOXXXX");
Tetromino Z("Z", 3, "OOXXOOXXX");
Tetromino J("J", 3, "OXXOOOXXX");
Tetromino L("L", 3, "XXOOOOXXX");
Tetromino tetro = I;
Tetromino next = I;
Tetromino hold = I;
Game::Game() {
  maketetro(1);
  //initial();
  line=LINES;

  srand((unsigned int)time(NULL));
  times=DROP_DELAY;
}
void Game::createBoard() {
    console::drawBox(0, 0, BOARD_WIDTH + 1, BOARD_HEIGHT + 1);
}
void Game::createNextBox() {
    console::drawBox(BOARD_WIDTH+3, 0, BOARD_WIDTH+8, 5);
    console::draw(BOARD_WIDTH+4, 0, "Next");
}
void Game::createHoldBox() {
    console::drawBox(BOARD_WIDTH+9, 0, BOARD_WIDTH+14, 5);
    console::draw(BOARD_WIDTH+10, 0, "Hold");
}

void Game::draw() {
    createBoard();
    createNextBox();
    createHoldBox();
    printline();
    tetro.drawAt("■",x_, y_);
}
void Game::update() {
    times++;
    timer = clock();
    m=timer/60000;
    s=timer/1000;
    ms=timer%100;
    times--;
    if(times == 0){
        times = DROP_DELAY;
        y_++;
    }
    maketetro(1);
    tetro.drawAt(SHADOW_STRING, x_, y_);
    tetro.drawAt(BLOCK_STRING, x_, y_);
    next.drawAt(BLOCK_STRING, BOARD_WIDTH+4, 1);
    hold.drawAt(BLOCK_STRING, BOARD_WIDTH+10, 1);
}

bool Game::shouldExit() {
    if(console::key(console::K_ESC)){
        console::draw(2, BOARD_WIDTH/2, "You lost");
        return true;
    }
    else if (line == 0) {
        console::draw(2, BOARD_WIDTH/2, "You win");
        return true;
    };
    return false;
}

void Game::printline() {
    line = LINES;
    for(int y = BOARD_HEIGHT, linecnt = 0; y >= 2; y--) {
        linecnt = 0;
        for(int x = 1; x <= BOARD_WIDTH; x++) {
            if(board_[x][y])
                linecnt++;
        }
        if(linecnt == BOARD_WIDTH) {
            for(int i = y; i >= 2; i--) {
                for(int x = 1; x <= BOARD_WIDTH; x++) {
                    board_[x][i] = board_[x][i - 1];
                }
            }
            for(int x = 1; x <= BOARD_WIDTH; x++)
                board_[x][1] = false;
            line--;
        }
    }
    console::draw(0, 22, std::to_string(line) + " lines left");
}

void Game::maketetro(int num) {
     int shape = rand()%7;
        switch (shape)
        {
        case 0:
            if (num == 0)
                tetro = I;
            else
                next = I;
            break;
        case 1:
            if (num == 0)
                tetro = O;
            else
                next = O;
            break;
        case 2:
            if (num == 0)
                tetro = T;
            else
                next = T;
            break;
        case 3:
            if (num == 0)
                tetro = S;
            else
                next = S;
            break;
        case 4:
            if (num == 0)
                tetro = Z;
            else
                next = Z;
            break;
        case 5:
            if (num == 0)
                tetro = J;
            else
                next = J;
        case 6:
            if (num == 0)
                tetro = L;
            else
                next = L;
            break;
        default:
            break;
        }
}
void Game::handleinput() {
    if(console::key(console::K_LEFT)){
      if(x_>1){
        x_--;
        //shad_x--;
        //shadow();
      }
    }
    if(console::key(console::K_RIGHT)){
      if(x_+tetro.size()-1<BOARD_WIDTH){
        x_++;
        //shad_x++;
        //shadow();
      }
    }
    if(console::key(console::K_UP))
      y_=BOARD_HEIGHT+1-tetro.size();
    if(console::key(console::K_DOWN))
      y_++;
    if(console::key(console::K_SPACE)){
      if(hold.size()==0){
        hold=*tetro.original();
        maketetro(1);
        //shadow();
        //shad_t=t;
      }
      else{
        Tetromino tmp=tetro;
        tetro=hold;
        hold=tmp;
      }
    }
    if(console::key(console::K_X))
      tetro.rotatedCW();
    if(console::key(console::K_Z))
      tetro.rotatedCCW();
    if(console::key(console::K_NONE))
      times=DROP_DELAY;

    if(y_+tetro.size()==BOARD_HEIGHT){//끝에 도착
      for(int y=y_; y<y_+tetro.size(); y++){
        for(int x=x_; x<x_+tetro.size(); x++){
          if(tetro.check(x,y))
            board_[x][y]=true;
        }
      }
      tetro=next;
     // initial();
    }
}
std::string Game::stringTime(clock_t start) {
        int m, s, ss;
        ss = times % 100;
        times /= 100;
        s = times % 60;
        times /= 60;
        m = times;

        std::string str_m = std::to_string(m);
        std::string str_s = std::to_string(s);
        std::string str_ss = std::to_string(ss);

        if (m < 10) {
            str_m.insert(0, "0");
        }
        if (s < 10) {
            str_s.insert(0, "0");
        }
        if (ss < 10) {
            str_ss.insert(0, "0");
        }

        std::string stringtimes = str_m + ":" + str_s + "." + str_ss; 
        return stringtimes;
    }