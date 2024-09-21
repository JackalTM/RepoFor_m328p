/*
 * LCD_application.h
 *
 * Created: 17.05.2024 
 *  Author: Wiki
 */
#include "_include.h"
#ifdef _INC_CONVERSION_METHODS

#include "stdint.h"
#include "Global_macros/bit_mask_macros.h"

#define CONVERSION_TYPE_DEC_uint8_t 4U
#define CONVERSION_TYPE_DEC_uint16_t 6U
#define CONVERSION_TYPE_DEC_uint32_t 10U

#define CONVERSION_TYPE_DEC_int8_t 5U
#define CONVERSION_TYPE_DEC_int16_t 7U
#define CONVERSION_TYPE_DEC_int32_t 11U

#define CONVERSION_TYPE_ASCI_HEX_BASE ('A' - 0xA)

enum DecimalNumberStringSize
{
    TYPE_DEC_uin8_t = 4U, TYPE_DEC_int8_t = 5U, 
    TYPE_DEC_uint16_t = 6U, TYPE_DEC_int16_t = 7U,
    TYPE_DEC_uint32_t = 10U, TYPE_DEC_int32_t = 11U,
};
enum HexadeciNumberStringSize
{
    TYPE_HEX_uin8_t = 3U, TYPE_HEX_int8_t = 3U, 
    TYPE_HEX_uint16_t = 5U, TYPE_HEX_int16_t = 5U,
    TYPE_HEX_uint32_t = 8U, TYPE_HEX_int32_t = 8U
};

struct NumberStrSize_t
{
    enum enum_DecimalNumberStringSize
    {
        TYPE_DEC_uin8_t = 4U, TYPE_DEC_int8_t = 5U, 
        TYPE_DEC_uint16_t = 6U, TYPE_DEC_int16_t = 7U,
        TYPE_DEC_uint32_t = 10U, TYPE_DEC_int32_t = 11U,
    };
}; // https://en.cppreference.com/w/cpp/language/enum

/*****************************************************************************************************
 * @name		NumbersConversion
 * @brief		Clas to convert nmbers system
 */
class NumbersConversion
{
private:
    uint8_t _StrMax, _Str_n;

    char* itoa_simple_helper(char *dest, int i);
    char* itoa_simple(char *dest, int i);

public:
    NumbersConversion(void) {;}
    ~NumbersConversion() {;}

    void SetMaxStringLenght(DecimalNumberStringSize strSize)     { _StrMax = strSize; _Str_n = 0; }
    void SetMaxStringLenght(HexadeciNumberStringSize strSize)    { _StrMax = strSize; _Str_n = 0; }
    
    char* Uint_to_str_dec(char *pStr, uint8_t uint);
    char* Uint_to_str_hex(char *pStr, uint8_t uint);
};
//====================================================================================================

/*****************************************************************************************************
 * @brief   Definitions for time conversion
 */
#define TIME_CONVERSION_STR_LEN 0x08U

#define TIME_CONVERSION_HOURS_MAX 24U
#define TIME_CONVERSION_MINUTES_MAX 60U
#define TIME_CONVERSION_SOCUNDS_MAX 60U
//====================================================================================================

/*****************************************************************************************************
 * @brief   Definitions for time conversion
 */
#define TIME_CONVERSION_STR_LEN 0x08U

#define TIME_CONVERSION_HOURS_MAX 24U
#define TIME_CONVERSION_MINUTES_MAX 60U
#define TIME_CONVERSION_SOCUNDS_MAX 60U

#define CONVERSION_BASE_NUM_DIGIT_MIN (char)'0'
#define CONVERSION_BASE_NUM_DIGIT_MAX (char)'9'

#define CONVERSION_BASE_NUM_LETER_MIN (char)'A'
#define CONVERSION_BASE_NUM_LETER_MAX (char)'Z'

#define TIME_CONVERSION_NUMBER_BASEBNUM 0x40
//====================================================================================================

/*****************************************************************************************************
 * @name		ConvertTime
 * @brief		Clas to convert nmbers system
 */
class FormatConvert: private NumbersConversion
{
private:
    void _SetCharArray(char arrChar[], uint8_t strLen, char inChar);

public:
    FormatConvert(void);
    ~FormatConvert();

    // Conversion methods 
    void NumToString(uint8_t number, char arrChar[], DecimalNumberStringSize strSize);
    void NumToString(uint8_t number, char arrChar[], HexadeciNumberStringSize strSize);

    // String custom formating 
    void ToStrFormatDec(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST);
    void ToStrFormatHex(char arrSRC[], uint8_t lenSRC, char arrDST[], uint8_t lenDST);
};
//====================================================================================================
#endif // _INC_CONVERSION_METHODS
//====================================================================================================