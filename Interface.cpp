#include "Interface.h"

void DoIntroduction(){}

modelMsg GetMessage() {
  modelMsg stcMsg;
  return stcMsg;
}

modelMsg CheckForMessage(std::string sAppPath) {
  modelMsg oMsg;
  oMsg.iMessageCode = NO_MESSAGE;
  return oMsg;
}

void SendMessage(modelMsg msg, bool batch){}

void ExternalErrorHandler(modelErr stcError, int iModelState, bool batch = false){}



