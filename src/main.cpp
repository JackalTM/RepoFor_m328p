#include <Init.h>
//#include "converion_methods.h"
//#include "LCD_application.h"
#include <KeyPad.h>
#include "x01_menu.h"

/**************************************************************************
 * Initialization of a class objects
*/
InitPeryferia_m328p 	myInitialization_uC;
LCD_application 		myLCD_app(16,2);
//ConvertTime				myTime;
Keypad4x4 				instKeyPad(0x07);

MenuApplication			myMenuApplication(myLCD_app, instKeyPad);
//=========================================================================

/**************************************************************************
 * Initialization of a global variables
*/
//volatile uint8_t globalKeypadState;
//=========================================================================

int main(void)
{
	myInitialization_uC.DataDirectionsResistrsInit();	// Inicializacja Port�w
	myInitialization_uC.Timer1Init();	// Inicializacja TIMER2
	myInitialization_uC.Timer2Init();	// Inicializacja TIMER2

// Inicializacja wyswetlacza LCD, zajmje przynajmniej 40ms
myLCD_app.InitializeDevice();
//============================================================================

// Miejsce na inicializacje danych pod wstępnej inicializacji 
	myLCD_app.PrintStr("RED:", 3, 0,0);
	myLCD_app.PrintStr("BLU:", 3, 0,1);
while(1)
{
	//myLCD_app.MenuTwoTeamsIncrease();
	;
}
return 0;
}
//=============================================================================

/******************************************************************************
 * Przerwanie dla Timer1 z powodu przepełnienia
*/
ISR(TIMER1_OVF_vect)
{
	myMenuApplication.IRQ_TIM1_Display();
}
//=============================================================================

/******************************************************************************
 * Interrupt call for Timer 2
*/
ISR(TIMER2_OVF_vect)
{ 
/*
	globalKeypadState = instKeyPad.KeypadStateEvaluation();
	if(globalKeypadState != KEYCODE_NOPRESS)
	{
		if(globalKeypadState == KEYPAD_KEYPAD_STATE_PULS)
		{	myLCD_app.OrderDisplay_IRQ(instKeyPad.GetKeyCode()); }
		else{;}
	}
	else{;}
*/
	myMenuApplication.IRQ_TIM2_Keypad();
}
//=============================================================================