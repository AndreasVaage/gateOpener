
#if 0
#include "UserInput.h"
#include <ClickEncoder.h>
#include <TimerOne.h>


ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
  encoder->service();
}

void UserInput_Setup() {
  encoder = new ClickEncoder(A1, A0, A2);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  
  last = -1;
}

Button_e UserInput_GetButtonStatus() {  
  ClickEncoder::Button button = encoder->getButton();
  if (button != ClickEncoder::Open) 
  {
    switch (button) 
    {
      case ClickEncoder::Pressed:
      	return ButtonPressed;
      	break;
      case ClickEncoder::Held:
    	return ButtonHeld;
      	break;
      case ClickEncoder::Released:
      	return ButtonRealesed;
      	break;
      case ClickEncoder::Clicked:
      	return ButtonClicked;
      	break;
      case ClickEncoder::DoubleClicked:
      	return ButtonDubbleClicked;
        break;
      case default:
      	return ButtonNothing;
    }
  }
}
bool UserInput_CheckForEncoderChange()
{
	value += encoder->getValue();
  
 	if (value != last) 
  	{
    	last = value;
    	return true;
  	}
  	return false;
}
int16_t UserInput_ReadEncoder()
{
  	return value;
}

int16_t UserInput_ResetEncoder()
{
	value = 0;
}
#endif
