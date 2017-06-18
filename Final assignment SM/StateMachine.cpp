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

      if(eventIn == E_PRESSED_BACK){
         if(LastState==S_WAIT_FOR_INPUT){
            eventOut = E_SEQ;
            currentState = S_SHOWMENU;
         }
         else{
            eventIn = lasteventOut;
            currentState = LastState;
         }
      }
   }
}

event_SM StateMachine::statemachine(event_SM eventIn) {
   NextState = S_NO;
   eventOut = E_NO;

   switch(currentState)
   {
      case S_START:
         //initialise at the start
         eventOut = E_SM_initialise;
         pHardware->SMinitialise();
         pDialog->enableButtons(true);
         initialise.print_values();
         NextState = S_SHOWMENU;
         break;
      case S_SHOWMENU:
         //the start menu will wait for input when it is selected
         pHardware->DSP_ShowInfo("Make a selection:");
         pHardware->StartMenu();
         eventOut = E_NO;
         NextState = S_WAIT_FOR_INPUT;
         break;

      case S_WAIT_FOR_INPUT:
      {
         switch(eventIn)
         {
            case E_PRESSED_0:
               pHardware->DSP_ShowInfo("Make a selection:");
               pHardware->PreSettingsMenu();
               eventOut = E_NO;
               NextState = S_DETECTED_0;
               break;

            case E_PRESSED_1:
               pHardware->DSP_ShowInfo("Make a selection:");
               pHardware->SettingsMenu();
               eventOut = E_NO;
               NextState = S_DETECTED_1;
               break;
               //----------------------Show current settings--------------------------------------------------------
            case E_PRESSED_2:
               initialise.print_values();
               eventOut = E_SEQ;
               NextState = S_SHOWMENU;
               break;
            default:
               pHardware->DSP_ShowDebug("Error in waiting for input state");
               eventOut = E_SEQ;
               NextState = S_SHOWMENU;
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
         eventOut = E_SEQ;
         break;

      case S_DETECTED_0_0:
         eventOut = E_SEQ;
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_0_1:
      {
         SM_settings Sundeville(pDialog);
         Sundeville.set_values(60, 20, 6, 2);
         newinitialise = Sundeville;
         eventOut = E_SEQ;
         NextState = S_SURE;
         break;
      }
      case S_DETECTED_0_2:
      {
         SM_settings Lantana(pDialog);
         Lantana.set_values(80, 20, 10, 1);
         newinitialise = Lantana;
         eventOut = E_SEQ;
         NextState = S_SURE;
         break;
      }
      case S_DETECTED_0_3:
      {
         SM_settings Cyclaam(pDialog);
         Cyclaam.set_values(70, 60, 11, 1);
         newinitialise = Cyclaam;
         eventOut = E_SEQ;
         NextState = S_SURE;
         break;
      }
      case S_DETECTED_0_4:
      {
         SM_settings Malva(pDialog);
         Malva.set_values(40, 30, 15, 1);
         newinitialise = Malva;
         eventOut = E_SEQ;
         NextState = S_SURE;
         break;
      }
      case S_DETECTED_0_5:
      {
         SM_settings Tibouchina(pDialog);
         Tibouchina.set_values(80, 40, 2, 1);
         newinitialise = Tibouchina;
         eventOut = E_SEQ;
         NextState = S_SURE;
         break;
      }
      case S_DETECTED_1_0:
         eventOut = E_SEQ;
         NextState = S_RUN_INITIALISE;
         break;
      case S_DETECTED_1_1:
      {
         if(!numberinserted){
            pHardware->Amount_water();
            eventOut = E_NO;
            NextState = S_INSERT_NUMBERS;
         }
         else{
            initialise.set_values(insertednumbers, initialise.get_f(), initialise.get_r(),
                                  initialise.get_s());
            numberinserted = false;
            insertednumbers = 0;
            eventOut = E_SEQ;
            NextState = S_SHOWMENU;
         }
         break;
      }
      case S_DETECTED_1_2:
      {
         if(!numberinserted){
            pHardware->Amount_Plant_Food();
            eventOut = E_NO;
            NextState = S_INSERT_NUMBERS;
         }
         else{
            initialise.set_values(initialise.get_w(), insertednumbers, initialise.get_r(),
                                  initialise.get_s());
            numberinserted = false;
            insertednumbers = 0;
            eventOut = E_SEQ;
            NextState = S_SHOWMENU;
         }
         break;
      }
      case S_DETECTED_1_3:
      {
         if(!numberinserted){
            pHardware->Row();
            eventOut = E_NO;
            NextState = S_INSERT_NUMBERS;
         }
         else{
            initialise.set_values(initialise.get_w(), initialise.get_f(), insertednumbers,
                                  initialise.get_s());
            numberinserted = false;
            insertednumbers = 0;
            eventOut = E_SEQ;
            NextState = S_SHOWMENU;
         }
         break;
      }
      case S_DETECTED_1_4:
      {
         if(!numberinserted){
            pHardware->Sprinkler_Speed();
            eventOut = E_NO;
            NextState = S_INSERT_NUMBERS;
         }
         else{
            initialise.set_values(initialise.get_w(), initialise.get_f(), initialise.get_r(),
                                  insertednumbers);
            numberinserted = false;
            insertednumbers = 0;
            eventOut = E_SEQ;
            NextState = S_SHOWMENU;
         }
         break;
      }
      case S_DETECTED_1_5:
         initialise.print_values();
         eventOut = E_SEQ;
         NextState = S_SHOWMENU;
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
            pHardware->DSP_ShowInfo("Running with following settings:");
            initialise.print_values();
            eventOut = E_MOTOR1_RUN_FORWARDS;
            pDialog->toggleLed(pDialog->led1);
            pHardware->DSP_ShowInfo("Motor 1 is running forwards");
            eventOut = E_NO;
            NextState = S_RUN;
         }
         break;
      case S_RUN:
         switch(eventIn)
         {
            case E_ROW_DETECTED:
               eventOut = E_SEQ;
               NextState = S_DETECTED_ROW;
               break;
            case E_MOTOR2_RUN_FORWARDS:
               pDialog->toggleLed(pDialog->led2);
               sprintf(info, "Motor2 running with PWM %d\n", initialise.get_s());
               pHardware->DSP_ShowInfo(info);
               eventOut = E_SPRINKLER_ON;
               pDialog->setmanometer(pDialog->manw, initialise.get_w());
               sprintf(info, "Watersprinkler is %d%% open\n", initialise.get_w());
               pHardware->DSP_ShowInfo(info);
               pDialog->setmanometer(pDialog->manf, initialise.get_f());
               sprintf(info, "Foodsprinkler is %d%% open\n\n", initialise.get_f());
               pHardware->DSP_ShowInfo(info);
               eventOut = E_NO;
               NextState = S_RUN;
               break;
            case E_WALL_DETECTED:
               pHardware->DSP_ShowInfo("Wall detected\n");
               eventOut = E_MOTOR2_STOP;
               pDialog->toggleLed(pDialog->led2);
               pHardware->DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR2_RUN_BACKWARDS;
               pDialog->toggleLedback(pDialog->led2);
               pHardware->DSP_ShowInfo("Motor2 going backwards\n");
               eventOut = E_NO;
               NextState = S_RUN;
               break;
            case E_BACKWALL_DETECTED:
               pDialog->setmanometer(pDialog->manw, 0);
               pDialog->setmanometer(pDialog->manf, 0);
               eventOut = E_MOTOR2_STOP;
               pDialog->toggleLedback(pDialog->led2);
               pHardware->DSP_ShowInfo("Motor2 stopped\n");
               eventOut = E_MOTOR1_RUN_BACKWARDS;
               pDialog->toggleLedback(pDialog->led1);
               pHardware->DSP_ShowInfo("Motor1 running backwards\n");
               eventOut = E_NO;
               NextState = S_DETECTED_ROW;
               break;
            default:
               pHardware->DSP_ShowDebug("Error in S_RUN");
               break;
         }
         break;
      case S_DETECTED_ROW:
         if((RowsCounted < initialise.get_r())&&(pDialog->led1->color() == (QColor(0, 200, 0))))
         {
            RowsCounted++;
            if(RowsCounted == initialise.get_r())
            {
               sprintf(info, "Row %d detected\n", RowsCounted);
               pHardware->DSP_ShowInfo(info);

               eventOut = E_MOTOR1_STOP;
               sprintf(info, "Motor1 stopped\n");
               pDialog->toggleLed(pDialog->led1);
               pHardware->DSP_ShowInfo(info);
               //RowsCounted = 0;
               eventOut = E_MOTOR2_RUN_FORWARDS;
            }
            else
            {
               sprintf(info, "Row %d detected", RowsCounted);
               pHardware->DSP_ShowInfo(info);
               eventOut = E_NO;
            }

            NextState = S_RUN;
         }
         else if(RowsCounted > 0)
         {
            RowsCounted--;
            if(RowsCounted == 0)
            {
               sprintf(info, "Row %d detected\n", RowsCounted);
               pHardware->DSP_ShowInfo(info);
               eventOut = E_MOTOR1_STOP;
               pDialog->toggleLedback(pDialog->led1);
               pHardware->DSP_ShowInfo("Motor1 stopped\n\n");
               eventOut = E_SEQ;
               NextState = S_SHOWMENU;
            }
            else
            {
               sprintf(info, "Row %d detected", RowsCounted);
               pHardware->DSP_ShowInfo(info);
               eventOut = E_NO;
               NextState = S_RUN;
            }
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
      case S_SURE:
         if(firsttime){
            pHardware->AreYouSure();
            eventOut = E_NO;
            NextState = S_SURE;
            firsttime = false;
         }
         else{
            switch(eventIn)
            {
               case E_PRESSED_0:
                  initialise = newinitialise;
                  eventOut = E_SEQ;
                  NextState = S_RUN_INITIALISE;
                  break;
               case E_PRESSED_1:
                  eventOut = E_SEQ;
                  NextState = S_SHOWMENU;
                  break;
               default:
                  pHardware->DSP_ShowDebug("Invalid choice");
                  eventOut = E_NO;
                  NextState = S_DETECTED_1;
                  break;
            }
            firsttime = true;
         }
         break;
      case S_INSERT_NUMBERS:
         switch (eventIn) {
            case E_PRESSED_0:
               insertednumbers = insertednumbers*10;
               break;
            case E_PRESSED_1:
               insertednumbers = insertednumbers*10+1;
               break;
            case E_PRESSED_2:
               insertednumbers = insertednumbers*10+2;
               break;
            case E_PRESSED_3:
               insertednumbers = insertednumbers*10+3;
               break;
            case E_PRESSED_4:
               insertednumbers = insertednumbers*10+4;
               break;
            case E_PRESSED_5:
               insertednumbers = insertednumbers*10+5;
               break;
            case E_PRESSED_6:
               insertednumbers = insertednumbers*10+6;
               break;
            case E_PRESSED_7:
               insertednumbers = insertednumbers*10+7;
               break;
            case E_PRESSED_8:
               insertednumbers = insertednumbers*10+8;
               break;
            case E_PRESSED_9:
               insertednumbers = insertednumbers*10+9;
               break;
            case E_PRESSED_OKAY:
               pDialog->setLogger("\n");
               numberinserted = true;
               NextState = LastState;
               break;
         }
         eventOut = E_SEQ;
         if(NextState != LastState){
            std::stringstream buffer;
            buffer << "--info current number: " << insertednumbers ;
            pDialog->setLogger(QString(buffer.str().c_str()));
            pDialog->setLogger("When you are statisfied press OKAY");
            eventOut = E_NO;
            NextState = S_INSERT_NUMBERS;
         }
         break;
      default:
         pHardware->DSP_ShowDebug("unknown state you will be redirected to S_SHOWMENU");
         eventOut = E_SEQ;
         NextState = S_SHOWMENU;
         break;
   }
   if (currentState != S_INSERT_NUMBERS){
      LastState = currentState;
   }
   currentState = NextState;
   lasteventOut = eventOut;
   return eventOut;
}
