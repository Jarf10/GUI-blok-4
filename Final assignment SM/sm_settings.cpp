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
 choosen_AmountWater = w;
 choosen_AmountPlantFood = f;
 Selected_Row = r;
 Speed = s;
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
   displayBuffer << "Amount water: " << choosen_AmountWater
                 << "\nAmount food: " << choosen_AmountPlantFood
                 << "\nSelected row: " << Selected_Row
                 << "\nSelected speed: " << Speed;
   pDialog->setLogger(QString(displayBuffer.str().c_str()));
}

