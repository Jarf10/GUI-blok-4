//----------SprinklerSoftware-----------------------
#include <stdio.h>
#include <ctype.h>
#include "SM.h"

//----------Global variables-------------------
state_SM CurrentState = S_START;
event_SM Event = E_NO;
int choosen_AmountWater = 0;
int choosen_AmountPlantFood = 0;
int Selected_Row = 0;
int Speed = 0;
//---------SM---------------------------------------

int main(void)
{
    DSP_ShowMenu(&choosen_AmountWater, &choosen_AmountPlantFood, &Selected_Row, &Speed);
    while(1)
    {
        Sprinkler_machine();
    }
    return 0;
}

//--------Implementation SM--------------------------

void Sprinkler_machine(void)
{
    state_SM NextState = S_NO;
    switch(CurrentState)
    {
    case S_START:
        Event = SMinitialise();
        nextState = S_INITIALISED;
        break;
    case S_INITIALISED:
        break;
    case S_WAIT_FOR_INPUT:
        break;
    case S_DETECTED_0:
    break;
    case S_DETECTED_1:
    break;
    case S_DETECTED_2:
    break;
    case S_DETECTED_3:
    break;
    case S_DETECTED_4:
    break;
    case S_DETECTED_5:
    break;
    default: printf("error");
        break;
    }
}

ffverzinnen(){
    switch(DSP_SelectionMenu())
    {
    case 0: SM_Run();
        break;
    case 1: Amount_water(&choosen_AmountWater);
        break;
    case 2: Amount_Plant_Food(&choosen_AmountPlantFood);
        break;
    case 3: Row(&Selected_Row);
        break;
    case 4: Sprinkler_Speed(&Speed);
        break;
    case 5: DSP_ShowMenu(&choosen_AmountWater, &choosen_AmountPlantFood, &Selected_Row, &Speed);
        break;
    default: DSP_ShowDebug("Invalid choice");
        break;
    }
}
SMinitialise()
{
    DSP_Initialise();

}
