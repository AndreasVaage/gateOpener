
//Encoder: https://github.com/0xPIT/encoder
//Rf Receiver:  ZABR1-1 433MHz receiver
//     Code: https://github.com/sui77/rc-switch/blob/master/examples/ReceiveDemo_Advanced/output.ino
//     Hardware: https://dzrmo.wordpress.com/2012/07/08/remote-control-pt2272-for-android/
//Rf Sender: PT2264


#include "FiniteStateMachine.h"
#include "GateDriver.hpp"
#include "Communication.h"
#include "RBD_Timer.h"
//#include "LowPower.h"
#include <avr/sleep.h>

void openButtonPressed();
void closeButtonPressed();
void checkForCommunication();
void stopTheGate();
void openTheGate();
void closeTheGate();
void enterStoppedState();
void exitStoppedState();
void update();

GateDriver gateDriver(5, 6, 7, 8, 9);
Communication communication(0);

State Opening(openTheGate, update, stopTheGate);
State Closing(closeTheGate, update, stopTheGate);
State Stopped(enterStoppedState, update, exitStoppedState);
FiniteStateMachine gateFSM(Stopped);
bool lastDirectionWasOpening = false;
RBD::Timer startDelay(2000);
RBD::Timer oneButtonStopDelay(2000);
RBD::Timer motorOnTime(15000);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
}

void loop() {
  gateFSM.update();
  delay(100);
}

void enterStoppedState() {}

void exitStoppedState() {
  motorOnTime.restart();
}

void checkForCommunication() {
  switch (communication.checkForReciver()) {
    case openGate: openButtonPressed(); break;
    case closeGate: closeButtonPressed(); break;
    case openOrClose:
      if (gateFSM.isInState(Stopped)) {
        (lastDirectionWasOpening) ? closeButtonPressed() : openButtonPressed();
        oneButtonStopDelay.restart();
      }
      else if (oneButtonStopDelay.isExpired()) {
        (gateFSM.isInState(Opening)) ? closeButtonPressed() : openButtonPressed();
      }
      break;
    case none: break;
  }
}

void openButtonPressed() {
  if (gateDriver.isOpenEndButtonPressed()) {
    return;
  }
  if (gateFSM.isInState(Stopped) && startDelay.isExpired()) {
    gateFSM.transitionTo(Opening);
  }
  else if (gateFSM.isInState(Closing)) {
    gateFSM.transitionTo(Stopped);
    startDelay.restart();
  }
}

void closeButtonPressed() {
  if (gateDriver.isCloseEndButtonPressed()) {
    return;
  }
  if (gateFSM.isInState(Stopped) && startDelay.isExpired()) {
    gateFSM.transitionTo(Closing);
  }
  else if (gateFSM.isInState(Opening)) {
    gateFSM.transitionTo(Stopped);
    startDelay.restart();
  }
}

void stopTheGate() {
  //Serial.println("Stopping gate");
  gateDriver.stopGate();
}
void openTheGate() {
  //Serial.println("Opening gate");
  gateDriver.openGate();
  lastDirectionWasOpening = true;
}
void closeTheGate() {
  //Serial.println("Closing gate");
  gateDriver.closeGate();
  lastDirectionWasOpening = false;
}

void update() {
  checkForCommunication();
  gateDriver.update();

  if (gateDriver.isOpenEndButtonPressed() && gateFSM.isInState(Opening)) {
    lastDirectionWasOpening = true;
    gateFSM.transitionTo(Stopped);
  } else if (gateDriver.isCloseEndButtonPressed() && gateFSM.isInState(Closing)) {
    lastDirectionWasOpening = false;
    gateFSM.transitionTo(Stopped);
  }
  if (!gateFSM.isInState(Stopped) && motorOnTime.isExpired()) {
    gateFSM.transitionTo(Stopped);
  }
}
