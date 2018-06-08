
#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <RCSwitch.h>

enum Message {openGate = 11, closeGate = 12, none = 13, openOrClose = 14};

class Communication {
  public:
    Communication(int interupt);
    Message checkForReciver(); 
  private:
    RCSwitch mySwitch = RCSwitch();
    static const int openCodesCount = 2;
    static const int closeCodesCount = 2;
    static const int oneButtonCodesCount = 3;
    unsigned long openCodes[openCodesCount] = {5592332,9883716};
    unsigned long closeCodes[closeCodesCount] = {5592368,9883720};
    unsigned long oneButtonCodes[oneButtonCodesCount] = {16078079,348671,16078847};
};
#endif
