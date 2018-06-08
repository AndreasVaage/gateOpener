//
//  GateDriver.hpp
//  portOpener
//
//  Created by Andreas Våge on 20.12.2016.
//  Copyright © 2016 Andreas Våge. All rights reserved.
//

#ifndef GateDriver_hpp
#define GateDriver_hpp

#include <stdio.h>
#include "RBD_Motor.h" // https://github.com/alextaujenis/RBD_Motor
#include "RBD_Button.h"

class GateDriver {
public:
	GateDriver(int speedLeftPin, int speedRigthPin, int enableMotorPin, 
	int closeButton, int openButton);
	void openGate();
	void closeGate();
	void stopGate();
	void update();
	int getSpeed();

	bool isOpenEndButtonPressed();
	bool isCloseEndButtonPressed();
private:
	RBD::Button openEndButton;
	RBD::Button closeEndButton;
	RBD::Motor motor;
	int motorVelosity = 160;
	unsigned long openingTime = 3000;
unsigned long closingTime = 5000;
	unsigned long stopTime = 1000;

};

#endif /* GateDriver_hpp */
