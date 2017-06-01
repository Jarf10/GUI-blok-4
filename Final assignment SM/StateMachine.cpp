#include "MainWindow.h"
#include "StateMachine.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

unsigned int RowsCounted = 0;
char info[20];

void StateMachine::handleEvent(event_SM eventIn) {
   // Handle sequential states.
   while (eventIn != E_NO) {
      eventIn = statemachine(eventIn);
   }
}

event_SM StateMachine::statemachine(event_SM eventIn) {
   NextState = S_NO;
   eventOut = E_NO;
   SM_settings initialise(pDialog);

   switch(currentState)
   {
      case S_START:
         //initialise at the start
         eventOut = E_SM_initialise;
         pHardware->SMinitialise();
         NextState = S_INITIALISED;
         break;
      case S_INITIALISED:

         pDialog->enableButtons(true);
         initialise.print_values();
         NextState = S_WAIT_FOR_INPUT;
         //the start menu will wait for input when it is selected
         pHardware->DSP_ShowInfo("Make a selection:");
         //std::cout << "In wait for input" << std::endl;
         pHardware->StartMenu();
         eventOut = E_NO;
         break;

      case S_WAIT_FOR_INPUT:
      {
         switch(eventIn)
         {
            case E_PRESSED_0:
               pHardware->DSP_ShowInfo("Make a selection:\n");
               pHardware->PreSettingsMenu();
               eventOut = E_NO;
               NextState = S_DETECTED_0;
               break;

            case E_PRESSED_1:
               pHardware->DSP_ShowInfo("Make a selection:\n");
               pHardware->SettingsMenu();
               NextState = S_DETECTED_1;
               break;
               //----------------------Show current settings--------------------------------------------------------
            case E_PRESSED_2:
               initialise.print_values();
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Error in waiting for input state");
               break;
         }
      }
         break;

         //----------------------Below are all states of the keys displayed-----------------------------------
      case S_DETECTED_0:
         switch(eventIn)
         {
            //----------------------presets menu--------------------------------------------------------
            case E_PRESSED_0:
               NextState = S_DETECTED_0_0;
               break;
            case E_PRESSED_1:
               NextState = S_DETECTED_0_1;
               break;
            case E_PRESSED_2:
               NextState = S_DETECTED_0_2;
               break;
            case E_PRESSED_3:
               NextState = S_DETECTED_0_3;
               break;
            case E_PRESSED_4:
               NextState = S_DETECTED_0_4;
               break;
            case E_PRESSED_5:
               NextState = S_DETECTED_0_5;
               break;
            default: pHardware->DSP_ShowDebug("S_WAIT_FOR_INPUT received unknown event");
               NextState = S_WAIT_FOR_INPUT;
               break;
         }
         eventOut = E_SEQ;
         break;

      case S_DETECTED_1:
         switch(eventIn)
         {
            //----------------------manual settings menu--------------------------------------------------------
            case E_PRESSED_0:
               NextState = S_DETECTED_1_0;
               break;
            case E_PRESSED_1:
               NextState = S_DETECTED_1_1;
               break;
            case E_PRESSED_2:
               NextState = S_DETECTED_1_2;
               break;
            case E_PRESSED_3:
               NextState = S_DETECTED_1_3;
               break;
            case E_PRESSED_4:
               NextState = S_DETECTED_1_4;
               break;
            case E_PRESSED_5:
               NextState = S_DETECTED_1_5;
               break;
            default: pHardware->DSP_ShowDebug("S_WAIT_FOR_INPUT received unknown event");
               NextState = S_WAIT_FOR_INPUT;
               break;
         }
         eventOut = E_NO;
         break;

      case S_DETECTED_0_0:
         eventOut = E_SEQ;
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_0_1:
      {
         SM_settings Sundeville(pDialog);
         Sundeville.set_values(10, 20, 6, 2);
         eventOut = pHardware->AreYouSure();
         switch(eventOut)
         {
            case E_PRESSED_0:
               initialise = Sundeville;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_2:
      {
         SM_settings Lantana(pDialog);
         Lantana.set_values(80, 20, 10, 1);
         eventOut = pHardware->AreYouSure();
         switch(eventOut)
         {
            case E_PRESSED_0:
               initialise = Lantana;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_3:
      {
         SM_settings Cyclaam(pDialog);
         Cyclaam.set_values(70, 60, 11, 1);
         eventOut = pHardware->AreYouSure();
         switch(eventOut)
         {
            case E_PRESSED_0:
               initialise = Cyclaam;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_4:
      {
         SM_settings Malva(pDialog);
         Malva.set_values(40, 30, 15, 1);
         eventOut = pHardware->AreYouSure();
         switch(eventOut)
         {
            case E_PRESSED_0:
               initialise = Malva;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_5:
      {
         SM_settings Tibouchina(pDialog);
         Tibouchina.set_values(80, 40, 2, 1);
         eventOut = pHardware->AreYouSure();
         switch(eventOut)
         {
            case E_PRESSED_0:
               initialise = Tibouchina;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_1_0:
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_1_1:
      {
         unsigned int temp_water = initialise.get_w();
         pHardware->Amount_water(&temp_water);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_2:
      {
         unsigned int temp_food = initialise.get_f();
         pHardware->Amount_Plant_Food(&temp_food);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_3:
      {
         unsigned int temp_row = initialise.get_r();
         pHardware->Row(&temp_row);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_4:
      {
         unsigned int temp_speed = initialise.get_s();
         pHardware->Sprinkler_Speed(&temp_speed);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_5:
         initialise.print_values();
         NextState = S_WAIT_FOR_INPUT;
         break;
         //--------------------------From here the running state is described----------------------------------------------------
      case S_RUN_INITIALISE:
         if((initialise.get_w()==0)|(initialise.get_r() == 0))
         {
            //error security check build in here
            pHardware->DSP_ShowDebug("Cannot run with current settings\n");
            NextState = S_WAIT_FOR_INPUT;
         }
         else
         {
            pHardware->DSP_ShowInfo("Running with following settings:\n\n");
            initialise.print_values();
            eventOut = E_MOTOR1_RUN_FORWARDS;
            pHardware->DSP_ShowInfo("Motor 1 is running forwards\n\n");
            eventOut = E_ROW_DETECTED;
            eventOut = E_SEQ;
            NextState = S_RUN;
         }
         break;
      case S_RUN:
         switch(eventOut)
         {
            case E_ROW_DETECTED:
               NextState = S_DETECTED_ROW;
               break;
            case E_MOTOR2_RUN_FORWARDS:
               sprintf(info, "Motor2 running with PWM %d\n", initialise.get_s());
               pHardware->DSP_ShowInfo(info);
               eventOut = E_SPRINKLER_ON;
               sprintf(info, "Watersprinkler is %d%% open\n", initialise.get_w());
               pHardware->DSP_ShowInfo(info);
               sprintf(info, "Foodsprinkler is %d%% open\n\n", initialise.get_f());
               pHardware->DSP_ShowInfo(info);
               eventOut = E_WALL_DETECTED;
               NextState = S_RUN;
               break;
            case E_WALL_DETECTED:
               pHardware->DSP_ShowInfo("Wall detected\n");
               eventOut = E_MOTOR2_STOP;
               pHardware->DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR2_RUN_BACKWARDS;
               pHardware->DSP_ShowInfo("Motor2 going backwards\n");
               eventOut = E_MOTOR2_STOP;
               pHardware->DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR1_RUN_BACKWARDS;
               pHardware->DSP_ShowInfo("Motor1 running backwards\n");
               eventOut = E_MOTOR1_STOP;
               pHardware->DSP_ShowInfo("Motor1 stopped\n\n");
               eventOut = E_SEQ;
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               pHardware->DSP_ShowDebug("Error in S_RUN");
               break;
         }
         break;
      case S_DETECTED_ROW:
         if(RowsCounted < initialise.get_r())
         {
            RowsCounted++;
            if(RowsCounted == initialise.get_r())
            {
               sprintf(info, "Row %d detected\n\n", RowsCounted);
               pHardware->DSP_ShowInfo(info);
            }
            else
            {
               sprintf(info, "Row %d detected\n", RowsCounted);
               pHardware->DSP_ShowInfo(info);
            }
            eventOut = E_SEQ;
            NextState = S_RUN;
         }
         else if(RowsCounted == initialise.get_r())
         {
            eventOut = E_MOTOR1_STOP;
            sprintf(info, "Motor1 stopped\n");
            pHardware->DSP_ShowInfo(info);
            eventOut = E_MOTOR2_RUN_FORWARDS;
            eventOut = E_SEQ;
            NextState = S_RUN;
         }
         else
         {
            pHardware->DSP_ShowDebug("Error in S_DETECTED_ROW");
            eventOut = E_NO;
            NextState = S_WAIT_FOR_INPUT;
         }
         break;
      case S_DETECTED_WALL:
         pHardware->DSP_ShowDebug("Error in S_DETECTED_WALL");
         break;
      default:
         pHardware->DSP_ShowDebug("unknown state you will be redirected to S_WAIT_FOR_INPUT");
         eventOut = E_NO;
         NextState = S_WAIT_FOR_INPUT;
         break;
   }
   currentState = NextState;
   return eventOut;
}
