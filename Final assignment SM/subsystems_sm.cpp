#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "StateMachine.h"
#include "MainWindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

//Each hardware accessable fuction is described below

void Hardware::SMinitialise()
{
    //Display initialised
    DSP_Initialise();
    //Pressure Detector initialised
    PDT_Initialise();
    FOOD_Initialise();
    RCNT_Initialise();
    MOTOR1_Initialise();
    MOTOR2_Initialise();
    DSP_ShowDebug("Subsystems initialised:\n"
                  "\tDisplay initialised\n"
                  "\tPressure detector initialised\n"
                  "\tFood detected\n"
                  "\tRow counter initialised\n"
                  "\tMotor1 initialised\n"
                  "\tMotor2 initialised\n\n");

}

void Hardware::DSP_Initialise()
{
    DSP_ShowDebug("Display: initialised");
}

void Hardware::PDT_Initialise()
{
    DSP_ShowDebug("Pressure detector: initialised");
}

void Hardware::FOOD_Initialise()
{
    DSP_ShowDebug("Food: detected");
}

void Hardware::MOTOR1_Initialise()
{
    DSP_ShowDebug("Motor1: initialised");
}

void Hardware::MOTOR2_Initialise()
{
    DSP_ShowDebug("Motor2: initialised\n\n");
}

void Hardware::RCNT_Initialise()
{
    DSP_ShowDebug("Row counter: initialised");
}

void Hardware::DSP_ShowSettings(SM_settings *currentsettings)
{
    char info[50];
    sprintf(info, "Current settings:\n");
    DSP_ShowInfo(info);
    sprintf(info, "Amount of water = %d%%\n", currentsettings->get_w());
    DSP_ShowInfo(info);
    sprintf(info, "Amount of plant food = %d%%\n", currentsettings->get_f());
    DSP_ShowInfo(info);
    sprintf(info, "Selected row = %d\n", currentsettings->get_r());
    DSP_ShowInfo(info);
    sprintf(info, "Speed = %d\n\n", currentsettings->get_s());
    DSP_ShowInfo(info);
}

void Hardware::DSP_ShowInfo(char *text)
{
   std::stringstream displayBuffer;
   displayBuffer << "--Info " << text << std::endl;
   pDialog->setLogger(QString(displayBuffer.str().c_str()));

   //printf("--Info %s\n", text);
}

void Hardware::DSP_ShowDebug(char *text)
{
   std::stringstream displayBuffer;
   displayBuffer << "--DEBUG " << text << std::endl;
   pDialog->setLogger(QString(displayBuffer.str().c_str()));
   //printf("--DEBUG %s\n", text);

    time_t rawtime;
      struct tm * timeinfo;

      time ( &rawtime );
      timeinfo = localtime ( &rawtime );

    FILE *debuglog = fopen("Debuglog.txt", "a");
    if (debuglog == NULL)
    {
        DSP_ShowInfo("Error opening file!\n");
        exit(1);
    }

    /* print some text */
    fprintf(debuglog, "\nTime: %s -- %s",asctime (timeinfo), text);

    fclose(debuglog);
}

event_SM Hardware::StartMenu(void)
{
    DSP_ShowInfo("<0> Preset settings <1> Settings <2> Show settings\n");
    /*int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');

    switch(selection)
    {
    case 0:
        return E_PRESSED_0;
        break;
    case 1:
        return E_PRESSED_1;
        break;
    case 2:
        return E_PRESSED_2;
        break;
    default:
        DSP_ShowDebug("An error occurred in StartMenu\n\tDid you press a number between the 0 and 2?");
        break;
    }*/
}

void Hardware::PreSettingsMenu(void)
{
    DSP_ShowInfo("<0> Run <1> Sundeville <2> Lantana <3> Cyclaam <4> Malva <5> Tibouchina\n");
    /*
    switch(selection)
    {
    case 0:
        return E_PRESSED_0;
        break;
    case 1:
        return E_PRESSED_1;
        break;
    case 2:
        return E_PRESSED_2;
        break;
    case 3:
        return E_PRESSED_3;
        break;
    case 4:
        return E_PRESSED_4;
        break;
    case 5:
        return E_PRESSED_5;
        break;
    default:
        DSP_ShowDebug("Unknown command");
        break;
    }*/
}

event_SM Hardware::AreYouSure(void)
{
    DSP_ShowInfo("Do you want to run with these settings?\n\n");
    DSP_ShowInfo("<0> Yes <1> No\n");
    int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');

    switch(selection)
    {
    case 0:
        return E_PRESSED_0;
        break;
    case 1:
        return E_PRESSED_1;
        break;
    default:
        DSP_ShowDebug("Unknown command");
        break;
    }

}

event_SM Hardware::SettingsMenu(void)
{
    DSP_ShowInfo("<0> Run <1> Water <2> Food <3> Row <4> Speed <5> Show selection\n");
    int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');

    switch(selection)
    {
    case 0:
        return E_PRESSED_0;
        break;
    case 1:
        return E_PRESSED_1;
        break;
    case 2:
        return E_PRESSED_2;
        break;
    case 3:
        return E_PRESSED_3;
        break;
    case 4:
        return E_PRESSED_4;
        break;
    case 5:
        return E_PRESSED_5;
        break;
    default:
        DSP_ShowDebug("Unknown command");
        break;
    }
}

void Hardware::Amount_water(unsigned int *choosen_AmountWater)
{
    DSP_ShowInfo("How much water do you like to sprinkle?\n");
    unsigned int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');
    if((selection>=20)&(selection<=100))
    {
        *choosen_AmountWater = selection;
    }
    else{
        DSP_ShowDebug("Invalid value!\n");
    }
}
void Hardware::Amount_Plant_Food(unsigned int *choosen_AmountPlantFood)
{
    DSP_ShowInfo("How much food do you like to mix?\n");
    int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');
    if((selection>=0)&(selection<=100))
    {
        *choosen_AmountPlantFood = selection;
    }
    else{
        DSP_ShowDebug("Invalid value!\n");
    }
}
void Hardware::Row(unsigned int *Selected_Row)
{
    DSP_ShowInfo("What/Which row(s) do you like to sprinkle?\n");
    int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');
    if((selection>=1)&(selection<=40))
    {
        *Selected_Row = selection;
    }
    else{
        DSP_ShowDebug("Invalid value!\n");
    }
}
void Hardware::Sprinkler_Speed(unsigned int *Speed)
{
    DSP_ShowInfo("How fast do you want to sprinkle?\n");
    int selection;
    scanf("%d", &selection);
    // Empty input buffer
    while ((getchar()) != '\n');
    if((selection>=0)&(selection<=50))
    {
        *Speed = selection;
    }
    else{
        DSP_ShowDebug("Invalid value!\n");
    }
}
