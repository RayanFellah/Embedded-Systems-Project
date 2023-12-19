#pragma once
#include "Led.h"
#include "PhotoResistance.h"
#include "Motors.h"
#include "Uart.h"
#include "Buttons.h"
#include "DistanceCaptor.h"
#include "Memory.h"

enum State {
   INIT,  
   START_PARKOUR,
   AWAIT,
   FOLLOW_LIGHT,
   WRITE_MEMORY,
   REDO_PARKOUR,
   FINISHED
};

static volatile State gCurrentState = State::INIT;

class Robot {
public:
   Robot();
   
   bool verifyLight();
   void followLight();
   bool detectWall();
   bool findNewWall();
   void followWall();
   void performUTurn();

   void writeMemory(uint8_t velocityLeft, uint8_t velocityRight);
   void readMemory();

   void testButton();
   void testMotors();
   void testPhotoResistance();
   void testDistanceCaptor();

   void executeParkour();


private:
   Led led_;
   PhotoResistance photoResistance_;
   Motors motors_;
   Buttons buttons_;
   Uart uart_;
   DistanceCaptor distanceCaptor_;
   Memory memory_;
};
