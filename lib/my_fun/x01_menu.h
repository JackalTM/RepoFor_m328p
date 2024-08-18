/*
 * x01_menu.h
 *
 * Created: 12.06.2024 
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_x01_MENU_H

#include "LCD_application.h"

/********************************************************************************************************************
 * Display value constants
 */
#define MENU_VALUE_ZERO_uint8_t (uint8_t)0U
#define MENU_VALUE_ZERO_uint16_t (uint8_t)0U
//===================================================================================================================

/********************************************************************************************************************
 * Display aplication instructions
 */
#define MENU_x1_APP_ORDER_INIT 0x11U
#define MENU_x1_APP_DISPLAY_UPDATE 0x22U
enum enum_MenuDisplayOrders{
    MENU_DISP_INIT = MENU_x1_APP_ORDER_INIT,
    MENU_DISP_UPDATE = MENU_x1_APP_DISPLAY_UPDATE
    };
//===================================================================================================================

/********************************************************************************************************************
 * @name		MenuApplication: Ref(LCD_application, ConvertTime)
 * @brief		Class that call other class throught reference
 * @note	    Inheritace two children class
 */
class MenuApplication_4x4
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
    volatile bool _display_data_order_active;
    volatile uint8_t _data_from_keypad_IRQ;

    volatile uint8_t _ticketRedNum;
    volatile uint8_t _ticketBluNum;
//==============================================
public:
//===================================================================================================================
// Setup external reference for internal manipulation. Now inside this class access is set to initialized class
    MenuApplication_4x4(LCD_application& Ref_LCD_application,  Keypad4x4& RefKeypad4x4):
        Ref_LCD_application(Ref_LCD_application), RefKeypad4x4(RefKeypad4x4){;}
    ~MenuApplication_4x4(){;}
//==============================================
    void InitializeDisplay_AppTest1(void);
    void Display_App_Test1(void);

    void InitializeDisplay_AppTest2(void);
    void Display_App_Test2(void);
    
    void IRQ_TIM1_Display(void);

    bool KeypadButtonData(uint8_t inData);
    void IRQ_TIM2_Keypad(void);
//==============================================
};
//===================================================================================================================
#endif // _INC_x01_MENU_H
//===================================================================================================================