/*
 * x01_menu.h
 *
 * Created: 12.06.2024 
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_x01_MENU_H

#include "LCD_application.h"
///#include "converion_methods.h"

/********************************************************************************************************************
 * @name		MenuApplication: Ref(LCD_application, ConvertTime)
 * @brief		Class that call other class throught reference
 * @note	    Inheritace two children class
 */
class MenuApplication
{
private:
//**********************************************
// Reference variables to external class objects
    LCD_application&    Ref_LCD_application;
    //ConvertTime&        RefConvertTime;
    Keypad4x4&          RefKeypad4x4;
//==============================================
    char arrChars1[4];
    char arrChars2[4];
    volatile uint8_t _keypad_state;
//==============================================
public:
//==============================================================================================================
    MenuApplication(LCD_application& Ref_LCD_application,  Keypad4x4& RefKeypad4x4):
        Ref_LCD_application(Ref_LCD_application), RefKeypad4x4(RefKeypad4x4){;}
    ~MenuApplication(){;}
//==============================================================================================================
    void Main_Display(void);
    void IRQ_TIM1_Display(void);
    void IRQ_TIM2_Keypad(void);
//==============================================
};
//===================================================================================================================
#endif // _INC_x01_MENU_H
//===================================================================================================================