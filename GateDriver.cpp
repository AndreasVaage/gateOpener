//
//  GateDriver.cpp
//  portOpener
//
//  Created by Andreas Våge on 20.12.2016.
//  Copyright © 2016 Andreas Våge. All rights reserved.
//

#include "GateDriver.hpp"
#include "RBD_Timer.h" // https://github.com/alextaujenis/RBD_Timer



GateDriver::GateDriver(int speedLeftPin, int speedRigthPin, int enableMotorPin, 
	int closeButton, int openButton): 
	motor(enableMotorPin,speedRigthPin,speedLeftPin,true), 
	openEndButton(openButton),closeEndButton(closeButton){
}

void GateDriver::openGate(){
	motor.ramp(motorVelosity, openingTime);
}
void GateDriver::closeGate(){
	motor.ramp(-motorVelosity,closingTime);
}
void GateDriver::stopGate(){
	motor.ramp(0,stopTime);
}

int GateDriver::getSpeed(){
	return motor.getSpeed();
}
void GateDriver::update(){
	motor.update();
}


  bool GateDriver::isOpenEndButtonPressed(){
    //Serial.println(openEndButton.isReleased());
    return openEndButton.isReleased();
  }
  bool GateDriver::isCloseEndButtonPressed(){
    //Serial.println(closeEndButton.isReleased());
    return closeEndButton.isReleased();
  }

