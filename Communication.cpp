
#include "Communication.h"
#include "Arduino.h"
/*
  Example for receiving

  https://github.com/sui77/rc-switch/

  If you want to visualize a telegram copy the raw data and
  paste it into http://test.sui.li/oszi/
*/
bool contains(unsigned long x, unsigned long list[], int nrOfCodes);

Communication::Communication(int interupt) {
  mySwitch.enableReceive(interupt);  // Receiver on interrupt 0 => that is pin #2
}

Message Communication::checkForReciver() {
  if (mySwitch.available()) {
    unsigned long recivedValue = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    if (contains(recivedValue, openCodes, openCodesCount)) {
      return openGate;
    } else if (contains(recivedValue, closeCodes, closeCodesCount)) {
      return closeGate;
    } else if (contains(recivedValue, oneButtonCodes, oneButtonCodesCount)) {
      return openOrClose;
    } else {
      return none;
    }
  }
}

bool contains (unsigned long x, unsigned long list[], int nrOfCodes) {
  for (int i = 0; i < nrOfCodes; i++) {
    if (list[i] == x) {
      return true;
    }
  }
  return false;
}


