/*
 * LCD_data_control.h
 *
 * Created: 04.05.2024 
 *  Author: Wiki
 */ 
#include "_include.h"
#ifdef _INC_LCD_DATA_CONTROL
/****************************************************************************************************************
 * Defintions if include required 
*/
#ifndef LCD_DATA_CONTROL_H_
#define LCD_DATA_CONTROL_H_

#include "stdint.h"
#include "Global_macros/bit_mask_macros.h"
//===============================================================================================================

/****************************************************************************************************************
 * Display size parameters
*/
#define DISPLAY_BUFFER_MAX_ROW_AMOUT 16U
#define DISPLAY_BUFFER_MAX_COL_AMOUT 2U

#define DISPLAY_BUFFER_CURRSOR_IDX_START 0U
#define DISPLAY_BUFFER_CURRSOR_IDX_END 15U
#define DISPLAY_BUFFER_LINE_1 0U
#define DISPLAY_BUFFER_LINE_2 1U
//===============================================================================================================

/****************************************************************************************************************
 * Class for menage LCD display 
*/
class LCD_DataControl
{
private:
/*********************************************************************
 * Private variables for class
 */
uint8_t _idx_row, _idx_col;
uint8_t _arrDisplayData[DISPLAY_BUFFER_MAX_COL_AMOUT][DISPLAY_BUFFER_MAX_ROW_AMOUT];
//====================================================================

/**********************************************************************
 * Add and remove data from buffer
*/
uint8_t _PutDataBuffer(uint8_t data);
//====================================================================

public:
    uint8_t curstorPosition;

/*********************************************************************
 * Definitions for public class varibales 
*/
    LCD_DataControl(uint8_t row_n, uint8_t col_n);
    ~LCD_DataControl();

    void ClearData(void);
    void ReturnHome(void);
 
    uint8_t AmountCharsToBegin(void);
    uint8_t AmountCharsToEnd(void);

    // Cursor movement menagment, LCD data displayed momvemt
    bool SetCurrsorToPosition(uint8_t* p_nRow, uint8_t* p_nCol);
    uint8_t SetCurrsorToPosition(uint8_t nRow, uint8_t nCol);
    bool PutOneChar(uint8_t data);

    // Print and delete data from array display. 
    // Both method return amount of characters that have been printed or deleted
    // due to current cursor position
    uint8_t PrintStr(const char pStr[], uint8_t strLen);
    uint8_t PrintStr(char pStr[], uint8_t strLen);

    uint8_t DeletStr(const char pStr[], uint8_t strLen);
    uint8_t DeletStr(char pStr[], uint8_t strLen);
};
//==============================================================================================
#endif // ifndef LCD_DATA_CONTROL_H_
//==============================================================================================
#endif // ifdef _INC_LCD_DATA_CONTROL
//==============================================================================================