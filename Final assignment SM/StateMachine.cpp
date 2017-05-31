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
      std::cout << "State" << std::endl;
      eventIn = statemachine(eventIn);
   }
}

event_SM StateMachine::statemachine(event_SM eventIn) {
   NextState = S_NO;
   eventOut = E_NO;
   SM_settings initialise;

   switch(currentState)
   {
      case S_START:
         //initialise at the start
         eventOut = E_SM_initialise;
         SMinitialise();
         pDialog->enableCentButtons(true);
         pDialog->setLogger("test");
         NextState = S_INITIALISED;
         break;
      case S_INITIALISED:
      {
         std::cout << "state initialise before printing values" << std::endl;
         initialise.print_values();
         eventOut = E_READY;
         NextState = S_WAIT_FOR_INPUT;
         std::cout << "state initialise after printing values" << std::endl;
         break;
      }
      case S_WAIT_FOR_INPUT:
      {
         //the start menu will wait for input when it is selected
         DSP_ShowInfo("Make a selection:\n");
         std::cout << "In wait for input" << std::endl;
         StartMenu();
         switch(eventIn)
         {
            case E_PRESSED_0:
               DSP_ShowInfo("Make a selection:\n");               
               eventOut = PreSettingsMenu();
               std::cout << "In wait for input pressed 0" << std::endl;
               switch(eventOut)
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
               eventOut = SettingsMenu();
               switch(eventOut)
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
      }
         //----------------------Below are all states of the keys displayed-----------------------------------
      case S_DETECTED_0_0:
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_0_1:
      {
         SM_settings Sundeville;
         Sundeville.set_values(10, 20, 6, 2);
         eventOut = AreYouSure();
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
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_2:
      {
         SM_settings Lantana;
         Lantana.set_values(80, 20, 10, 1);
         eventOut = AreYouSure();
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
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_3:
      {
         SM_settings Cyclaam;
         Cyclaam.set_values(70, 60, 11, 1);
         eventOut = AreYouSure();
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
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_4:
      {
         SM_settings Malva;
         Malva.set_values(40, 30, 15, 1);
         eventOut = AreYouSure();
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
               DSP_ShowDebug("Invalid choice");
               break;
         }
         break;
      }
      case S_DETECTED_0_5:
      {
         SM_settings Tibouchina;
         Tibouchina.set_values(80, 40, 2, 1);
         eventOut = AreYouSure();
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
               DSP_ShowDebug("Invalid choice");
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
         Amount_water(&temp_water);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_2:
      {
         unsigned int temp_food = initialise.get_f();
         Amount_Plant_Food(&temp_food);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_3:
      {
         unsigned int temp_row = initialise.get_r();
         Row(&temp_row);
         NextState = S_WAIT_FOR_INPUT;
         break;
      }
      case S_DETECTED_1_4:
      {
         unsigned int temp_speed = initialise.get_s();
         Sprinkler_Speed(&temp_speed);
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
            DSP_ShowDebug("Cannot run with current settings\n");
            NextState = S_WAIT_FOR_INPUT;
         }
         else
         {
            DSP_ShowInfo("Running with following settings:\n\n");
            initialise.print_values();
            eventOut = E_MOTOR1_RUN_FORWARDS;
            DSP_ShowInfo("Motor 1 is running forwards\n\n");
            eventOut = E_ROW_DETECTED;
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
               DSP_ShowInfo(info);
               eventOut = E_SPRINKLER_ON;
               sprintf(info, "Watersprinkler is %d%% open\n", initialise.get_w());
               DSP_ShowInfo(info);
               sprintf(info, "Foodsprinkler is %d%% open\n\n", initialise.get_f());
               DSP_ShowInfo(info);
               eventOut = E_WALL_DETECTED;
               NextState = S_RUN;
               break;
            case E_WALL_DETECTED:
               DSP_ShowInfo("Wall detected\n");
               eventOut = E_MOTOR2_STOP;
               DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR2_RUN_BACKWARDS;
               DSP_ShowInfo("Motor2 going backwards\n");
               eventOut = E_MOTOR2_STOP;
               DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR1_RUN_BACKWARDS;
               DSP_ShowInfo("Motor1 running backwards\n");
               eventOut = E_MOTOR1_STOP;
               DSP_ShowInfo("Motor1 stopped\n\n");
               NextState = S_WAIT_FOR_INPUT;
               break;
            default:
               DSP_ShowDebug("Error in S_RUN");
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
               DSP_ShowInfo(info);
            }
            else
            {
               sprintf(info, "Row %d detected\n", RowsCounted);
               DSP_ShowInfo(info);
            }
            NextState = S_RUN;
         }
         else if(RowsCounted == initialise.get_r())
         {
            eventOut = E_MOTOR1_STOP;
            sprintf(info, "Motor1 stopped\n");
            DSP_ShowInfo(info);
            eventOut = E_MOTOR2_RUN_FORWARDS;
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
