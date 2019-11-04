#include <stdio.h>

enum event_t {
  ENABLE,
  DISABLE,
  CLUTCH_PRESSED,
  BRAKE_PRESSED,
  SPEEDER_PRESSED,
  SPEEDER_RELEASED,
  ACTIVATE,
  SUSPEND,
  RESUME,
  LIMIT
};
enum event_t event;

class CruiseControlState;

class CruiseControl {
 public:
  CruiseControl(void);
  void enable(void);
  void disable(void);
  void activate(void);
  void suspend(void);
  void resume(void);
  void limit(void);
  void clutchPressed(void);
  void brakePressed(void);
  void speederPressed(void);
  void speederReleased(void);
  void setState(CruiseControlState *statePointer);

 private:
  CruiseControlState *statePointer;
};

class CruiseControlState {
 public:
  CruiseControlState(void);
  virtual void enable(CruiseControl *cruiseControlPointer);
  virtual void disable(CruiseControl *cruiseControlPointer);
  virtual void clutchPressed(CruiseControl *cruiseControlPointer);
  virtual void brakePressed(CruiseControl *cruiseControlPointer);
  virtual void speederPressed(CruiseControl *cruiseControlPointer);
  virtual void speederReleased(CruiseControl *cruiseControlPointer);
  virtual void activate(CruiseControl *cruiseControlPointer);
  virtual void suspend(CruiseControl *cruiseControlPointer);
  virtual void resume(CruiseControl *cruiseControlPointer);
  virtual void limit(CruiseControl *cruiseControlPointer);
};

class CruiseControlOff : public CruiseControlState {
 public:
  void enable(CruiseControl *cruiseControlPointer);
  static CruiseControlOff *getInstance();

 private:
  CruiseControlOff(void);
  static CruiseControlOff *instancePointer;
};

class CruiseControlOn : public CruiseControlState {
 public:
  void deactivate(CruiseControl *cruiseControlPointer);
  void brakePressed(CruiseControl *cruiseControlPointer);
  void clutchPressed(CruiseControl *cruiseControlPointer);
  void limit(CruiseControl *cruiseControlPointer);
  static CruiseControlOn *getInstance();

 private:
  CruiseControlOn(void);
  static CruiseControlOn *instancePointer;
};

class CruiseControlIdle : public CruiseControlState {
 public:
  void activate(CruiseControl *cruiseControlPointer);
  static CruiseControlIdle *getInstance();

 private:
  CruiseControlIdle(void);
  static CruiseControlIdle *instancePointer;
};

class CruiseControlSuspended : public CruiseControlState {
 public:
  void resume(CruiseControl *cruiseControlPointer);
  static CruiseControlSuspended *getInstance();

 private:
  CruiseControlSuspended(void);
  static CruiseControlSuspended *instancePointer;
};

class CruiseControlOvertaking : public CruiseControlState {
 public:
  void resume(CruiseControl *cruiseControlPointer);
  static CruiseControlOvertaking *getInstance();

 private:
  CruiseControlOvertaking(void);
  static CruiseControlOvertaking *instancePointer;
};

class CruiseControlCruising : public CruiseControlState {
 public:
  void resume(CruiseControl *cruiseControlPointer);
  static CruiseControlCruising *getInstance();

 private:
  CruiseControlCruising(void);
  static CruiseControlCruising *instancePointer;
};

// int main(void) {
//   int s;
//   House house;
//   keys = 3;
//   for (EVER) {
//     printf(" open:   0 \n");
//     printf(" close:  1 \n");
//     printf(" lock:   2 \n");
//     printf(" unlock: 3 \n");
//     printf(" enter number \n");

//     scanf_s("%d", &s);
//     event = (Event)s;

//     switch (event) {
//       case ENABLE:;
//       case DISABLE:;
//       case CLUTCH_PRESSED:;
//       case BRAKE_PRESSED case SPEEDER_PRESSED case SPEEDER_RELEASED case
//       ACTIVATE case SUSPEND case RESUME case LIMIT case OPEN:
//         house.open();
//         break;
//       case CLOSE:
//         house.close();
//         break;
//       case LOCK:
//         house.lock();
//         break;
//       case UNLOCK:
//         house.unlock();
//         break;
//     }  // end case event

//   }  // end forever
//   return 0;
// }
