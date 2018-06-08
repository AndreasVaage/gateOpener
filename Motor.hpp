//
//  Motor.hpp
//  portOpener
//
//  Created by Andreas Våge on 20.12.2016.
//  Copyright © 2016 Andreas Våge. All rights reserved.
//

#ifndef Motor_hpp
#define Motor_hpp


class Motor {

public:
	Motor(int speedForward, int speedBackwards,int enable);
	void run(int velocity);
	void stop();
	void accelerateTo(int targetVelocity, int acc);
	void update();
	int getVelocity();
private:
	int _Motor_SpeedForward;
	int _Motor_SpeedBackwards;
	int _Motor_Enabled;
	unsigned long _lastTime;
	int _targetVelocity = 0;
	unsigned long _velocity = 500000;
	int _acceleration = 0;
	bool _accelerating = false;
	bool _acceleratingForward = true;
	bool _doneAccelerateing();
};

#endif /* Motor_hpp */	