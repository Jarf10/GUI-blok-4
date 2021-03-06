#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "StateMachine.h"
#include "MainWindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>

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
                 "\tMotor2 initialised");

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
   DSP_ShowInfo("Current settings:");
   sprintf(info, "Amount of water = %d%%", currentsettings->get_w());
   DSP_ShowInfo(info);
   sprintf(info, "Amount of plant food = %d%%", currentsettings->get_f());
   DSP_ShowInfo(info);
   sprintf(info, "Selected row = %d", currentsettings->get_r());
   DSP_ShowInfo(info);
   sprintf(info, "Speed = %d\n", currentsettings->get_s());
   DSP_ShowInfo(info);
}

void Hardware::DSP_ShowInfo(const std::string& text)
{
   std::stringstream displayBuffer;
   displayBuffer << "--Info " << text;// << std::endl;
   pDialog->setLogger(QString(displayBuffer.str().c_str()));
}

void Hardware::DSP_ShowDebug(const std::string& text)
{
   std::stringstream displayBuffer;
   displayBuffer << "--DEBUG " << text;// << std::endl;
   pDialog->setDebugLogger(QString(displayBuffer.str().c_str()));

   std::time_t timeinfo = std::time(nullptr);

   std::ofstream debuglog;
   debuglog.open ("Debuglogcpp.txt", std::fstream::app);
   debuglog << "Time: " << std::asctime(std::localtime(&timeinfo)) << " -- "
            << text << std::endl;
   debuglog.close();

   /*time_t rawtime;
   struct tm * timeinfo;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );

   FILE *debuglog = fopen("Debuglogc.txt", "a");
   if (debuglog == NULL)
   {
      DSP_ShowInfo("Error opening file!\n");
      exit(1);
   }

   fprintf(debuglog, "\nTime: %s -- %s", asctime(timeinfo), text);

   fclose(debuglog);*/
}

event_SM Hardware::StartMenu()
{
   DSP_ShowInfo("<0> Preset settings");
   DSP_ShowInfo("<1> Settings");
   DSP_ShowInfo("<2> Show settings\n");
}

void Hardware::PreSettingsMenu()
{
   DSP_ShowInfo("<0> Run");
   DSP_ShowInfo("<1> Sundeville");
   DSP_ShowInfo("<2> Lantana");
   DSP_ShowInfo("<3> Cyclaam");
   DSP_ShowInfo("<4> Malva");
   DSP_ShowInfo("<5> Tibouchina\n");
}

void Hardware::AreYouSure()
{
   DSP_ShowInfo("Do you want to run with these settings?\n");
   DSP_ShowInfo("<0> Yes <1> No\n");
}

void Hardware::SettingsMenu()
{
   DSP_ShowInfo("<0> Run <1> Water <2> Food <3> Row <4> Speed <5> Show selection\n");
}

void Hardware::Amount_water()
{
   DSP_ShowInfo("How much water do you like to sprinkle?\n");
}
void Hardware::Amount_Plant_Food()
{
   DSP_ShowInfo("How much food do you like to mix?\n");
}
void Hardware::Row()
{
   DSP_ShowInfo("What/Which row(s) do you like to sprinkle?\n");
}
void Hardware::Sprinkler_Speed()
{
   DSP_ShowInfo("How fast do you want to sprinkle?\n");
}
