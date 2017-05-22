#include "MainWindow.h"
#include "StateMachine.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

void StateMachine::handleEvent(event_SM eventIn) {
   // Handle sequential states.
   while (eventIn != E_NO) {
      eventIn = statemachine(eventIn);
   }
}

event_SM StateMachine::statemachine(event_SM eventIn) {
   state_SM NextState = S_NO;
   event_SM eventOut = E_NO;

   switch(currentState)
   {
      case S_START:
         //initialise at the start
         event_SM Event = E_SM_initialise;
         SMinitialise();
         NextState = S_INITIALISED;
         break;

      case S_INITIALISED:
         SM_settings initialise;
         initialise.print_values();
         Event = E_READY;
         NextState = S_WAIT_FOR_INPUT;
         break;

      case S_WAIT_FOR_INPUT:
         //the start menu will wait for input when it is selected
         DSP_ShowInfo("Make a selection:\n");
         Event = StartMenu();
         switch(Event)
         {
            case E_PRESSED_0:
               DSP_ShowInfo("Make a selection:\n");
               Event = PreSettingsMenu();
               switch(Event)
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
                  default: DSP_ShowDebug("S_WAIT_FOR_INPUT received unknown event");
                     NextState = S_WAIT_FOR_INPUT;
                     break;
               }
               break;
            case E_PRESSED_1:
               DSP_ShowInfo("Make a selection:\n");
               Event = SettingsMenu();
               switch(Event)
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
                  default: DSP_ShowDebug("S_WAIT_FOR_INPUT received unknown event");
                     NextState = S_WAIT_FOR_INPUT;
                     break;
               }
               break;
               //----------------------Show current settings--------------------------------------------------------
            case E_PRESSED_2:
               initialise.print_values();
               NextState = S_WAIT_FOR_INPUT;
               break;
         }
         break;
         //----------------------Below are all states of the keys displayed-----------------------------------
      case S_DETECTED_0_0:
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_0_1:
         SM_settings Sundeville;
         Sundeville.set_values(10, 20, 6, 2);
         Event = AreYouSure();
         switch(Event)
         {
            case E_PRESSED_0:
               initialise = Sundeville;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      case S_DETECTED_0_2:         
         SM_settings Lantana;
         Lantana.set_values(80, 20, 10, 1);
         Event = AreYouSure();
         switch(Event)
         {
            case E_PRESSED_0:
               initialise = Lantana;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      case S_DETECTED_0_3:
         SM_settings Cyclaam;
         Cyclaam.set_values(70, 60, 11, 1);
         Event = AreYouSure();
         switch(Event)
         {
            case E_PRESSED_0:
               initialise = Cyclaam;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      case S_DETECTED_0_4:
         SM_settings Malva;
         Malva.set_values(40, 30, 15, 1);
         Event = AreYouSure();
         switch(Event)
         {
            case E_PRESSED_0:
               initialise = Malva;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      case S_DETECTED_0_5:
         SM_settings Tibouchina;
         Tibouchina.set_values(80, 40, 2, 1);
         Event = AreYouSure();
         switch(Event)
         {
            case E_PRESSED_0:
               initialise = Tibouchina;

               NextState = S_RUN_INITIALISE;
               break;
            case E_PRESSED_1:
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      case S_DETECTED_1_0:
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_1_1:
         Amount_water(initialise.get_w());
         NextState = S_WAIT_FOR_INPUT;
         break;
      case S_DETECTED_1_2:
         Amount_Plant_Food(&initialise.choosen_AmountPlantFood);
         NextState = S_WAIT_FOR_INPUT;
         break;
      case S_DETECTED_1_3:
         Row(&initialise.Selected_Row);
         NextState = S_WAIT_FOR_INPUT;
         break;
      case S_DETECTED_1_4:
         Sprinkler_Speed(&initialise.Speed);
         NextState = S_WAIT_FOR_INPUT;
         break;
      case S_DETECTED_1_5:
         DSP_ShowSettings(&initialise);
         NextState = S_WAIT_FOR_INPUT;
         break;
         //--------------------------From here the running state is described----------------------------------------------------
      case S_RUN_INITIALISE:
         if((initialise.choosen_AmountWater==0)|(initialise.Selected_Row == 0))
         {
            //error security check build in here
            DSP_ShowDebug("Cannot run with current settings\n");
            NextState = S_WAIT_FOR_INPUT;
         }
         else
         {
            DSP_ShowInfo("Running with following settings:\n\n");
            DSP_ShowSettings(&initialise);
            Event = E_MOTOR1_RUN_FORWARDS;
            DSP_ShowInfo("Motor 1 is running forwards\n\n");
            Event = E_ROW_DETECTED;
            NextState = S_RUN;
         }
         break;
      case S_RUN:
         switch(Event)
         {
            case E_ROW_DETECTED:
               NextState = S_DETECTED_ROW;
               break;
            case E_MOTOR2_RUN_FORWARDS:
               sprintf(info, "Motor2 running with PWM %d\n", initialise.Speed);
               DSP_ShowInfo(info);
               Event = E_SPRINKLER_ON;
               sprintf(info, "Watersprinkler is %d%% open\n", initialise.choosen_AmountWater);
               DSP_ShowInfo(info);
               sprintf(info, "Foodsprinkler is %d%% open\n\n", initialise.choosen_AmountPlantFood);
               DSP_ShowInfo(info);
               Event = E_WALL_DETECTED;
               NextState = S_RUN;
               break;
            case E_WALL_DETECTED:
               DSP_ShowInfo("Wall detected\n");
               Event = E_MOTOR2_STOP;
               DSP_ShowInfo("Motor2 stopped\n");
               Event = E_MOTOR2_RUN_BACKWARDS;
               DSP_ShowInfo("Motor2 going backwards\n");
               Event = E_MOTOR2_STOP;
               DSP_ShowInfo("Motor2 stopped\n");
               Event = E_MOTOR1_RUN_BACKWARDS;
               DSP_ShowInfo("Motor1 running backwards\n");
               Event = E_MOTOR1_STOP;
               DSP_ShowInfo("Motor1 stopped\n\n");
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Error in S_RUN");
               break;
         }
         break;
      case S_DETECTED_ROW:
         if(RowsCounted < initialise.Selected_Row)
         {
            RowsCounted++;
            if(RowsCounted == initialise.Selected_Row)
            {
               sprintf(info, "Row %d detected\n\n", RowsCounted);
               DSP_ShowInfo(info);
            }
            else
            {
               sprintf(info, "Row %d detected\n", RowsCounted);
               DSP_ShowInfo(info);
            }unsigned
                  NextState = S_RUN;
         }
         else if(RowsCounted == initialise.Selected_Row)
         {
            Event = E_MOTOR1_STOP;
            sprintf(info, "Motor1 stopped\n");
            DSP_ShowInfo(info);
            Event = E_MOTOR2_RUN_FORWARDS;
            NextState = S_RUN;
         }
         else
         {
            DSP_ShowDebug("Error in S_DETECTED_ROW");
            NextState = S_WAIT_FOR_INPUT;
         }
         break;
      case S_DETECTED_WALL:
         DSP_ShowDebug("Error in S_DETECTED_WALL");
         break;
      default:
         DSP_ShowDebug("unknown state you will be redirected to S_WAIT_FOR_INPUT");
         NextState = S_WAIT_FOR_INPUT;
         break;
   }
   currentState = NextState;
   return eventOut;
}
