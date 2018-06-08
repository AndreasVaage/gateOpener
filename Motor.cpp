//
// Motor.cpp
// C++ code
// Project 		portOpener
//
// Created by 	Andreas Våge, 20.12.2016 17.17
#include "Arduino.h"
#include "Motor.hpp"


Motor::Motor(int speedForward, int speedBackwards, int enable) {
    
    _Motor_SpeedForward = speedForward;
    _Motor_SpeedBackwards = speedBackwards;
    _Motor_Enabled = enable;

   pinMode(_Motor_SpeedForward, OUTPUT);
   pinMode(_Motor_SpeedBackwards, OUTPUT);
   pinMode(_Motor_Enabled, OUTPUT);

   digitalWrite(_Motor_Enabled,LOW);
}

void Motor::run(int velocity){
	velocity = constrain(velocity, -255,255);
	_velocity = map(velocity,-255,255,0,1000000);
	if (velocity < 0){
		digitalWrite(_Motor_Enabled,HIGH);
		digitalWrite(_Motor_SpeedForward,LOW);
    	analogWrite(_Motor_SpeedBackwards,-velocity);
	}else if (velocity >= 0){
		digitalWrite(_Motor_Enabled,HIGH);
		digitalWrite(_Motor_SpeedBackwards,LOW);
        analogWrite(_Motor_SpeedForward,velocity);
    }
}

void Motor::stop(){
	_velocity = 500000;
	digitalWrite(_Motor_SpeedForward,LOW);
	digitalWrite(_Motor_SpeedBackwards,LOW);
	digitalWrite(_Motor_Enabled,LOW);
}

void Motor::accelerateTo(int targetVelocity, int acc){
	_acceleration = acc;
	_targetVelocity = targetVelocity;
	_acceleratingForward = _targetVelocity > map(_velocity,0,1000000,-255,255);
	_accelerating = true;
	_lastTime = millis();
}

int Motor::getVelocity(){
	return map(_velocity,0,1000000,-255,255);
}

bool Motor::_doneAccelerateing(){
	int velocity = map(_velocity,-255,255,0,1000000);
	if (_targetVelocity == velocity){
		return true;
	}else if (_targetVelocity < velocity && _acceleratingForward){
		return true;
	}else if(_targetVelocity > velocity && !_acceleratingForward){
		return true;
	}else{
		return false;
	}
}

void Motor::update(){
	if (!_accelerating )
	{
		return;
	}

	int diff = millis() - _lastTime;

	if (diff < 1) {
		return;
	}

	if (_doneAccelerateing()){
		_accelerating = false;
		_velocity = map(_targetVelocity,-255,255,0,1000000);
		
	}else{
		if (_acceleratingForward){
			_velocity += diff*_acceleration;
		}else{
			_velocity -= diff*_acceleration;
		}

	}
	run(map(_velocity,0,1000000,-255,255));
	_lastTime = millis();
	
}

