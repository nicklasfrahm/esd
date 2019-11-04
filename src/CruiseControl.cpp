#include "CruiseControl.hpp"

CruiseControl::CruiseControl(void) {
  statePointer = CruiseControlOff::getInstance();
}
void CruiseControl::enable(void) { this->statePointer->enable(this); }
void CruiseControl::disable(void) { this->statePointer->disable(this); }
void CruiseControl::activate(void) { this->statePointer->activate(this); }
void CruiseControl::suspend(void) { this->statePointer->suspend(this); }
void CruiseControl::resume(void) { this->statePointer->resume(this); }
void CruiseControl::limit(void) { this->statePointer->limit(this); }
void CruiseControl::clutchPressed(void) {
  this->statePointer->clutchPressed(this);
}
void CruiseControl::brakePressed(void) {
  this->statePointer->brakePressed(this);
}
void CruiseControl::speederPressed(void) {
  this->statePointer->speederPressed(this);
}
void CruiseControl::speederReleased(void) {
  this->statePointer->speederReleased(this);
}
void CruiseControl::setState(CruiseControlState *statePointer) {
  this->statePointer = statePointer;
}

CruiseControlState::CruiseControlState(void) {}
void CruiseControlState::enable(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::disable(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::clutchPressed(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::brakePressed(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::speederPressed(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::speederReleased(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::activate(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::suspend(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::resume(CruiseControl *cruiseControlPointer) {}
void CruiseControlState::limit(CruiseControl *cruiseControlPointer) {}

CruiseControlOff *CruiseControlOff::instancePointer = 0;
CruiseControlOff *CruiseControlOff::getInstance(void) {
  if (CruiseControlOff::instancePointer == 0) {
    CruiseControlOff::instancePointer = new CruiseControlOff();
  }
  return CruiseControlOff::instancePointer;
}
void CruiseControlOff::enable(CruiseControl *cruiseControlPointer) {
  cruiseControlPointer->setState(CruiseControlIdle::getInstance());
}

Opened *Opened::instancePTR = 0;
Opened *Opened::getInstance() {
  if (instancePTR == 0) {
    instancePTR = new Opened();
  }
  return instancePTR;
}
Opened::Opened(void) {}
void Opened::close(House *hPTR) {
  hPTR->setState(Closed::getInstance());
  printf(" state is closed %d keys left \n", keys);
}

Closed *Closed::instancePTR = 0;
Closed *Closed::getInstance() {
  if (instancePTR == 0) {
    instancePTR = new Closed();
  }
  return instancePTR;
}
Closed::Closed(void) {}
void Closed::open(House *hPTR) {
  hPTR->setState(Opened::getInstance());
  printf(" state is opened %d keys left \n", keys);
}
void Closed::lock(House *hPTR) {
  if (keys > 0) {
    keys--;
    hPTR->setState(Locked::getInstance());
    printf(" state is locked %d keys left \n", keys);
  } else {
    printf(" state is closed %d keys left \n", keys);
  }
}

Locked *Locked::instancePTR = 0;
Locked *Locked::getInstance() {
  if (instancePTR == 0) {
    instancePTR = new Locked();
  }
  return instancePTR;
}
Locked::Locked(void) {}
void Locked::unlock(House *hPTR) {
  hPTR->setState(Closed::getInstance());
  printf(" state is closed %d keys left \n", keys);
}