#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef int error_t;

typedef enum {NOERR} error_e;

typedef enum {S_NO,
              S_START,
              S_INITIALISED,
              S_WAIT_FOR_INPUT,
              S_RUN_INITIALISE, S_RUN,
              S_DETECTED_0_0, S_DETECTED_0_1, S_DETECTED_0_2, S_DETECTED_0_3, S_DETECTED_0_4, S_DETECTED_0_5,
              S_DETECTED_1_0, S_DETECTED_1_1, S_DETECTED_1_2, S_DETECTED_1_3, S_DETECTED_1_4, S_DETECTED_1_5,
              S_DETECTED_ROW, S_DETECTED_WALL
             } state_SM;

typedef enum {E_NO,
              E_READY,
              E_SM_initialise,
              E_PRESSED_0, E_PRESSED_1, E_PRESSED_2, E_PRESSED_3,E_PRESSED_4, E_PRESSED_5, E_return,
              E_ROW_DETECTED, E_WALL_DETECTED,
              E_MOTOR1_RUN_FORWARDS, E_MOTOR1_RUN_BACKWARDS, E_MOTOR1_STOP, E_MOTOR2_RUN_FORWARDS, E_MOTOR2_RUN_BACKWARDS, E_MOTOR2_STOP,
              E_SPRINKLER_ON, E_SPRINKLER_OFF
             } event_SM;

class MainWindow;

class SM_settings {
public:
   SM_settings();
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

class StateMachine {
public:
   StateMachine(MainWindow* pDialog):
      pDialog(pDialog),
      currentState(S_START), money(0.0), priceCoke(125) {}
   ~StateMachine() {}

   void handleEvent(event_SM eventIn);
   state_SM getCurrentState() const { return currentState; }

private:
   MainWindow *pDialog;
   state_SM currentState;
   int money;
   int stock;
   const int priceCoke;
   event_SM statemachine(event_SM eventIn);
   event_SM checkCents(const int cents);
};

void SMinitialise(void);
void DSP_Initialise(void);
void PDT_Initialise(void);
void FOOD_Initialise(void);
void MOTOR1_Initialise(void);
void MOTOR2_Initialise(void);
void RCNT_Initialise(void);
void DSP_ShowSettings(void);
void DSP_ShowInfo(char *text);
void DSP_ShowDebug(char *text);
event_SM StartMenu(void);
event_SM PreSettingsMenu(void);
event_SM AreYouSure(void);
event_SM SettingsMenu(void);
void Amount_water(unsigned int *choosen_AmountWater);
void Amount_Plant_Food(unsigned int *choosen_AmountPlantFood);
void Row(unsigned int *Selected_Row);
void Sprinkler_Speed(unsigned int *Speed);
#endif
