#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <string>

typedef int error_t;

typedef enum {NOERR} error_e;

typedef enum {S_NO,
              S_START,
              S_SHOWMENU,
              S_WAIT_FOR_INPUT,
              S_RUN_INITIALISE, S_RUN,
              S_DETECTED_0, S_DETECTED_1,
              S_DETECTED_0_0, S_DETECTED_0_1, S_DETECTED_0_2, S_DETECTED_0_3,
              S_DETECTED_0_4, S_DETECTED_0_5, S_DETECTED_1_0, S_DETECTED_1_1,
              S_DETECTED_1_2, S_DETECTED_1_3, S_DETECTED_1_4, S_DETECTED_1_5,
              S_DETECTED_ROW, S_DETECTED_WALL, S_SURE, S_INSERT_NUMBERS
             } state_SM;

typedef enum {E_NO, E_SEQ,
              E_READY,
              E_SM_initialise,
              E_PRESSED_0, E_PRESSED_1, E_PRESSED_2, E_PRESSED_3,E_PRESSED_4,
              E_PRESSED_5, E_PRESSED_6, E_PRESSED_7, E_PRESSED_8, E_PRESSED_9,
              E_return, E_PRESSED_OKAY, E_PRESSED_BACK, E_ROW_DETECTED, E_BACKWALL_DETECTED,
              E_WALL_DETECTED, E_MOTOR1_RUN_FORWARDS, E_MOTOR1_RUN_BACKWARDS,
              E_MOTOR1_STOP, E_MOTOR2_RUN_FORWARDS, E_MOTOR2_RUN_BACKWARDS,
              E_MOTOR2_STOP, E_SPRINKLER_ON, E_SPRINKLER_OFF
             } event_SM;

class MainWindow;

class SM_settings {
public:
   SM_settings(MainWindow* pDialog);
   void set_values(const unsigned int w, const unsigned int f,
                   const unsigned int r, const unsigned int s);
   unsigned int get_w();
   unsigned int get_f();
   unsigned int get_r();
   unsigned int get_s();
   void print_values();

private:
   unsigned int choosen_AmountWater;
   unsigned int choosen_AmountPlantFood;
   unsigned int Selected_Row;
   unsigned int Speed;
   MainWindow *pDialog;
};

class Hardware{
public:
   Hardware(MainWindow* pDialog): pDialog(pDialog){}
   void SMinitialise();
   void DSP_Initialise();
   void PDT_Initialise();
   void FOOD_Initialise();
   void MOTOR1_Initialise();
   void MOTOR2_Initialise();
   void RCNT_Initialise();
   void DSP_ShowSettings(SM_settings *currentsettings);
   void DSP_ShowInfo(const std::string& text);
   void DSP_ShowDebug(const std::string& text);
   event_SM StartMenu();
   void PreSettingsMenu();
   void AreYouSure();
   void SettingsMenu();
   void Amount_water();
   void Amount_Plant_Food();
   void Row();
   void Sprinkler_Speed();
private:
   MainWindow *pDialog;
};

class StateMachine {
public:
   StateMachine(MainWindow* pDialog):
      pDialog(pDialog), pHardware(new Hardware(pDialog)),
      currentState(S_START), initialise(pDialog), newinitialise(pDialog),
      firsttime(true), RowsCounted(0), insertednumbers(0), numberinserted(false){}
   ~StateMachine() {}

   void handleEvent(event_SM eventIn);
   state_SM getCurrentState() const { return currentState; }

private:
   MainWindow *pDialog;
   Hardware* pHardware;
   state_SM LastState;
   state_SM currentState;
   state_SM NextState;
   event_SM eventOut;
   event_SM lasteventOut;
   event_SM statemachine(event_SM eventIn);
   SM_settings initialise;
   SM_settings newinitialise;
   unsigned int insertednumbers;
   bool numberinserted;
   bool firsttime;
   unsigned int RowsCounted;
   char info[20];
};

#endif
