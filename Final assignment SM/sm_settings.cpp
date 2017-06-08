#include "MainWindow.h"
#include "StateMachine.h"
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include <sstream>

SM_settings::SM_settings(MainWindow* pDialog) : choosen_AmountWater(100), choosen_AmountPlantFood(50),
   Selected_Row(1), Speed(2), pDialog(pDialog){}

void SM_settings::set_values(const unsigned int w, const unsigned int f,
                             const unsigned int r, const unsigned int s){
   if((w>=20)&(w<=100)){
      choosen_AmountWater = w;
   }
   else{
   pDialog->setLogger("--ERROR The amount of water must be between 20 and 100%");
   }
   if((f>=0)&(f<=100)){
   choosen_AmountPlantFood = f;
   }
   else{
   pDialog->setLogger("--ERROR The amount of food must be between 0 and 100%");
   }
   if((r>=1)&(r<=40)){
   Selected_Row = r;
   }
   else{
      pDialog->setLogger("--ERROR The amount of rows must be between 1 and 40");
   }
   if((s>=0)&(s<=50)){
    Speed = s;
   }
   else{
      pDialog->setLogger("--ERROR The speed must be between 0 and 50");
   }
}

unsigned int SM_settings::get_w(){
   return choosen_AmountWater;
}

unsigned int SM_settings::get_f(){
   return  choosen_AmountPlantFood;
}

unsigned int SM_settings::get_r(){
   return Selected_Row;
}

unsigned int SM_settings::get_s(){
   return Speed;
}

void SM_settings::print_values(){
   std::stringstream displayBuffer;
   displayBuffer << "\n--Info Amount water: " << choosen_AmountWater
                 << "\n--Info Amount food: " << choosen_AmountPlantFood
                 << "\n--Info Selected row: " << Selected_Row
                 << "\n--Info Selected speed: " << Speed << std::endl;
   pDialog->setLogger(QString(displayBuffer.str().c_str()));
}

