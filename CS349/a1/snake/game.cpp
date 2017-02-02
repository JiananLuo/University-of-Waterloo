/*
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake->cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/

#include <iostream>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <cmath>

#include "game.h"
#include "displayable.h"

using namespace std;

//display globals
int BLOCK_SIZE = 10, WIDTH_BOUND, HEIGHT_BOUND;
int FRAME_RATE = 60, ONE_SECOND = 1000000;
float FRAME_COUNTER = 0, MOVE_BASE_COUNTER;
useconds_t waitTime;
float SPEED_BUFFER = 2.5;

//game globals
const int GAME_STATUS_RUN = 0, GAME_STATUS_PAUSE = 1, GAME_STATUS_DEAD = 2, GAME_STATUS_SPLASH_SCREEN = 3;
int GAME_STATUS, GAME_SPEED = 5, GAME_LEVEL = 0;
bool NO_BOUNDARY_MODE = false;
int FLASH_COUNTER = 0;
bool FLASH_ON = false;

//objects globals
list<Displayable *> dList;
Text *MSG_NAME, *MSG_STUDENT_NUMBER, *MSG_DESCRIPTION, *MSG_BEGIN;
Snake *SNAKE;
Fruit *FRUIT;
Obstacles *OBSTACLES;
Text *MSG_SCORE, *MSG_FPS, *MSG_SPEED, *MSG_DEAD, *MSG_PAUSE;

//testing globals
unsigned long timePassed;

void gameInit(int argc, char *argv[], XInfo &xInfo)
{
  //read command arguments
  if(argc > 1)
  {
    FRAME_RATE = atoi(argv[1]);
    if(argc > 2)
    {
      GAME_SPEED = atoi(argv[2]);
      if(argc > 3)
      {
        GAME_LEVEL = atoi(argv[3]);
        if(argc > 4)
        {
          string mode = argv[4];
          if(mode == "true")
          {
            NO_BOUNDARY_MODE = true;
          }
        }
      }
    }
  }

  //init display
  WIDTH_BOUND = WIDTH - BLOCK_SIZE;
  HEIGHT_BOUND = HEIGHT - BLOCK_SIZE;
  waitTime = ONE_SECOND/FRAME_RATE;
  MOVE_BASE_COUNTER = (float)FRAME_RATE / GAME_SPEED / SPEED_BUFFER;

  //init game info
  GAME_STATUS = GAME_STATUS_SPLASH_SCREEN;

  //init objects
  MSG_NAME = new Text(320, 240, "Name: Jianan Luo (j43luo)");
  MSG_STUDENT_NUMBER = new Text(320, 260, "Student Number: 20523403");
  MSG_DESCRIPTION = new Text(165, 280, "Direction: 'W', 'A', 'S', 'D'  Pause/Resume: 'SPACE'  Restart: 'R'  Quit: 'Q'");
  MSG_BEGIN = new Text(305, 300, "Press 'ENTER' to start the game");
  string FPS_STR = argv[1];
  string STR_FPS = "FPS: " + FPS_STR;
  string SPEED_STR = argv[2];
  string STR_SPEED = "SPEED: " + SPEED_STR;
  MSG_SCORE = new Text(20, 580, "Score: 0");
  MSG_FPS = new Text(730, 550, STR_FPS);
  MSG_SPEED = new Text(730, 580, STR_SPEED);
  MSG_DEAD = new Text(210, 290, "You are dead! Press 'r' to restart. Press 'q' to quit the game.");
  MSG_PAUSE = new Text(380, 290, "PAUSE");

  //init color
  initX(argc, argv, xInfo);
  initColor(xInfo);
}

void gameDisplay()
{
  dList.clear();
  dList.push_back(MSG_NAME);
  dList.push_back(MSG_STUDENT_NUMBER);
  dList.push_back(MSG_DESCRIPTION);
  dList.push_back(MSG_BEGIN);
}

void gameStart()
{
  GAME_STATUS = GAME_STATUS_RUN;
  delete SNAKE;
  delete FRUIT;
  delete OBSTACLES;
  SNAKE = new Snake(100, 400);
  FRUIT = new Fruit(300, 400);
  OBSTACLES = new Obstacles();
  dList.clear();
  dList.push_back(SNAKE);
  dList.push_back(FRUIT);
  dList.push_back(OBSTACLES);
  dList.push_back(MSG_SCORE);
  dList.push_back(MSG_FPS);
  dList.push_back(MSG_SPEED);
}

void gameEnd(XInfo &xInfo, string reasonMsg)
{
  cout << "Game End. " << reasonMsg << endl;
  GAME_STATUS = GAME_STATUS_DEAD;
  dList.push_back(MSG_DEAD);
  FLASH_ON = true;
  repaint(xInfo);
}

void gameQuit()
{
  cout << "Game Quit Normally." << endl;
  delete MSG_NAME;
  delete MSG_STUDENT_NUMBER;
  delete MSG_DESCRIPTION;
  delete MSG_BEGIN;
  delete SNAKE;
  delete FRUIT;
  delete OBSTACLES;
  delete MSG_SCORE;
  delete MSG_FPS;
  delete MSG_SPEED;
  delete MSG_DEAD;
  delete MSG_PAUSE;
  dList.clear();
  exit(0);
}

void handleKeyPress(XInfo &xInfo, XEvent &event)
{
	KeySym key;
	char text[BufferSize];

	int i = XLookupString((XKeyEvent *)&event, text, BufferSize, &key, NULL);
	if (i == 1)
  {
		cout << "Got key press -- " << text[0] << endl;

		if (text[0] == 'q')
    {
			gameQuit();
		}
    else if(GAME_STATUS == GAME_STATUS_SPLASH_SCREEN)
    {
      if(text[0] == '\r')
      {
        timePassed = now();
        gameStart();
      }
    }
    else
    {
      if (text[0] == 'r')
      {
  			gameStart();
  		}
  		else if (text[0] == ' ')
      {
        if(GAME_STATUS == GAME_STATUS_RUN)
        {
          GAME_STATUS = GAME_STATUS_PAUSE;
          dList.push_back(MSG_PAUSE);
          FLASH_ON = true;
        }
        else if(GAME_STATUS == GAME_STATUS_PAUSE)
        {
          GAME_STATUS = GAME_STATUS_RUN;
          if(FLASH_ON)
          {
            dList.pop_back();
            FLASH_ON = false;
          }
        }
  		}
      else if (text[0] == '+')
      {
        SNAKE->grow();
      }
      else if (GAME_STATUS == GAME_STATUS_RUN && SNAKE->movedFlag)
      {
        if (text[0] == W)
        {
          SNAKE->goW();
    		}
    		else if (text[0] == A)
        {
          SNAKE->goA();
    		}
    		else if (text[0] == S)
        {
          SNAKE->goS();
    		}
    		else if (text[0] == D)
        {
          SNAKE->goD();
    		}
        SNAKE->movedFlag = false;
      }
    }
	}
}

void handleAnimation(XInfo &xInfo, int inside)
{
  if(GAME_STATUS == GAME_STATUS_RUN)
  {
    while(FRAME_COUNTER >= MOVE_BASE_COUNTER)
    {
      if(GAME_STATUS == GAME_STATUS_RUN)
      {
    	  SNAKE->move(xInfo, *FRUIT);
      }
      FRAME_COUNTER -= MOVE_BASE_COUNTER;
    }
    FRAME_COUNTER++;
  }
  else if(GAME_STATUS == GAME_STATUS_PAUSE || GAME_STATUS == GAME_STATUS_DEAD)
  {
    if((FLASH_COUNTER == FRAME_RATE || FLASH_COUNTER == FRAME_RATE/2))
    {
      if(FLASH_ON)
      {
        dList.pop_back();
      }
      else
      {
        if(GAME_STATUS == GAME_STATUS_PAUSE)
        {
          dList.push_back(MSG_PAUSE);
        }
        else if(GAME_STATUS == GAME_STATUS_DEAD)
        {
          dList.push_back(MSG_DEAD);
        }
      }
      FLASH_ON = !FLASH_ON;
    }
    FLASH_COUNTER++;
    if(FLASH_COUNTER > FRAME_RATE)
    {
      FLASH_COUNTER = 0;
    }
  }
}

unsigned long now()
{
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void eventLoop(XInfo &xInfo)
{
	XEvent event;
	unsigned long lastRepaint = 0;
	int inside = 0;

	while(true)
  {
		if (XPending(xInfo.display) > 0)
    {
			XNextEvent(xInfo.display, &event);
      if(event.type != 2)
      {
        continue;
      }
			switch(event.type)
      {
				case KeyPress:
					handleKeyPress(xInfo, event);
					break;
				case EnterNotify:
					inside = 1;
					break;
				case LeaveNotify:
					inside = 0;
					break;
			}
		}

		usleep(waitTime);
    handleAnimation(xInfo, inside);
		repaint(xInfo);
  }
}

int main (int argc, char *argv[])
{
	XInfo xInfo;
  gameInit(argc, argv, xInfo);
  gameDisplay();
	eventLoop(xInfo);
	XCloseDisplay(xInfo.display);
}
