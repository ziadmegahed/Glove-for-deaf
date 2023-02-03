#define F_CPU 16000000
#include <util/delay.h>
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HLCD_interface.h"
#include "MADC_interface.h"


u16_t Little_Finger; //(00001)
u16_t Ring_Finger;   //(00010)
u16_t Middle_Finger; //(00100)
u16_t Index_Finger;  //(01000)
u16_t Thumb_Finger;  //(10000)


#define A0 Little_Finger<511
#define A1 Little_Finger>511
#define B0 Ring_Finger<511
#define B1 Ring_Finger>511
#define C0 Middle_Finger<511
#define C1 Middle_Finger>511
#define D0 Index_Finger<511
#define D1 Index_Finger>511
#define E0 Thumb_Finger<511
#define E1 Thumb_Finger>511






int main(void)
{

	

	madc_init(AREF_MODE,ADC_10_BITS,ADC_PRESCALER_128);
	
	hlcd_init();
	
	
	
	hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
	hlcd_displayString((u8_t*)"welcome");	
	_delay_ms(1000);

	hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
	hlcd_displayString((u8_t*)"for deaf people");	
	_delay_ms(1000);
	
	
	while (1)
	{
		hlcd_Clear();
		_delay_ms(1000);
		madc_singleConversion(ADC_CHANNEL_0,&Little_Finger);
		madc_singleConversion(ADC_CHANNEL_1,&Ring_Finger);
		madc_singleConversion(ADC_CHANNEL_2,&Middle_Finger);
		madc_singleConversion(ADC_CHANNEL_3,&Index_Finger);
		madc_singleConversion(ADC_CHANNEL_4,&Thumb_Finger);
       

		if   (A1 && B1 && C1 && D1 && E1)
		{
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_7);
			hlcd_displayString((u8_t*)"nothing");
			_delay_ms(1000);
		}
		
		else if  (A0 && B1 && C1 && D0 && E1)
		{
			//hlcd_Clear();

			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"That's terrible");
			
			
			_delay_ms(1000);
			
		}
		
		else if  (A0 && B1 && C1 && D0 && E0)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"I love you");
			
			
			_delay_ms(1000);
			
		}
		
		else if  (A0 && B1 && C0 && D0 && E0)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"I realy love ");
			hlcd_displayPosition(LCD_ROW_1,LCD_COL_1);
			hlcd_displayString((u8_t*)"you");
			
			_delay_ms(1000);
			
		}
		
		else if  (A1 && B1 && C0 && D0 && E1)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"I watch you");
			
			_delay_ms(1000);
			
		}
		
		else if  (A1 && B1 && C1 && D0 && E1)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"You");
			
		
			_delay_ms(1000);
			
		}
		
		else if  (A1 && B1 && C1 && D1 && E0)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"Good work");
			
			
			_delay_ms(1000);
		
		}
		
		else if  (A0 && B0 && C0 && D0 && E0)
		{
			//hlcd_Clear();
			
			hlcd_displayPosition(LCD_ROW_0,LCD_COL_1);
			hlcd_displayString((u8_t*)"I wish you a ");
			hlcd_displayPosition(LCD_ROW_1,LCD_COL_1);
			hlcd_displayString((u8_t*)"happy life");
		
			_delay_ms(1000);
			
		}
		
	}
	
}
