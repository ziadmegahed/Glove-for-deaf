/**
 * @file    MDIO_program.c
 * @author  ziad megahed (ziadmegahed074@gmail.com)
 * @brief   This file contains logical implementation related to DIO module
 * @version 1.0
 * @date    2022-09-10
 * 
 * 
 */

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"


#define DDRA    *(volatile u8_t*)0x3A
#define DDRB    *(volatile u8_t*)0x37
#define DDRC    *(volatile u8_t*)0x34
#define DDRD    *(volatile u8_t*)0x31



#define PINA    *(volatile u8_t*)0x39
#define PINB    *(volatile u8_t*)0x36
#define PINC    *(volatile u8_t*)0x33
#define PIND    *(volatile u8_t*)0x30

#define NULL    0
/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

#define NUMBER_OF_PORTS    (4)

/***************************************************************************************************/
/*                                        Important variables                                      */
/***************************************************************************************************/

/*DDRx array*/
static volatile u8_t* garr_ddrArray[NUMBER_OF_PORTS] = {MDIO_DDRA_ADDRESS, MDIO_DDRB_ADDRESS, MDIO_DDRC_ADDRESS, MDIO_DDRD_ADDRESS};

/*PORTx array*/
static volatile u8_t* garr_portArray[NUMBER_OF_PORTS] = {MDIO_PORTA_ADDRESS, MDIO_PORTB_ADDRESS, MDIO_PORTC_ADDRESS, MDIO_PORTD_ADDRESS};

/*PINx array*/
static volatile u8_t* garr_pinArray[NUMBER_OF_PORTS] = {MDIO_PINA_ADDRESS, MDIO_PINB_ADDRESS, MDIO_PINC_ADDRESS, MDIO_PIND_ADDRESS};

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void mdio_setPinDirection (u8_t au8_port ,u8_t au8_pin ,u8_t PinDirection)
{
 if ((au8_port<=3)&&(au8_pin<=7)&&((output==PinDirection)||(input==PinDirection)))
 {
  switch(au8_port)
  {
	  case PORTA:   //2         //mmkn switch gowa switch bas 3shan mantla8batsh
	     if (output==PinDirection)
		 {
			 SET_BIT(DDRA,au8_pin);
		 }
		 else  
		 {
			CLEAR_BIT(DDRA,au8_pin) ;
		 }
	  break;
	  
	  case PORTB://2
	   if (output==PinDirection)
	   {
		   SET_BIT(DDRB,au8_pin);
	   }
	   else
	   {
		   CLEAR_BIT(DDRB,au8_pin) ;
	   }
	  break;
	  
	  case PORTC:
	   if (output==PinDirection)
	   {
		   SET_BIT(DDRC,au8_pin);
	   }
	   else
	   {
		   CLEAR_BIT(DDRC,au8_pin) ;
	   }
	  break;
	  
	  case PORTD:
	   if (output==PinDirection)
	   {
		   SET_BIT(DDRD,au8_pin);
	   }
	   else
	   {
		   CLEAR_BIT(DDRD,au8_pin) ;
	   }
	  break;
	  
  }
 }
}

void mdio_setPinStatus(u8_t au8_port, u8_t au8_pin, u8_t au8_status)
{
    /*Switching over pin status*/
    switch(au8_status)
    {
        /*In case of input float*/
        case INPUT_FLOAT:

            /*Clearing the specified pins in DDRx register*/
            *garr_ddrArray[au8_port] &= ~(au8_pin);

            /*Breaking from this case*/
            break;

        /*In case of input pull up*/
        case INPUT_PULLUP:

            /*Clearing the specified pins in DDRx register*/
            *garr_ddrArray[au8_port] &= ~(au8_pin);

            /*Setting the specified pins in PORTx register*/
            *garr_portArray[au8_port] |= (au8_pin);

            /*Break from this case*/
            break;

        /*In case of output*/
        case OUTPUT:

            /*Setting the specified pins in DDRx register*/
            *garr_ddrArray[au8_port] |= (au8_pin);

            /*Break from this case*/
            break;

        /*In case of default*/
        default:

            /*Break from this case*/
            break;
    }    

    /*Return from this function*/
    return;
}

void mdio_setPinValue(u8_t au8_port, u8_t au8_pin, u8_t au8_value)
{
    /*Switching over pin value*/
    switch(au8_value)
    {
        /*In case of LOW*/
        case LOW:

            /*Clearing the specified pins in PORTx register*/
            *garr_portArray[au8_port] &= ~(au8_pin);

            /*Breaking from this case*/
            break;

        /*In case of input HIGH*/
        case HIGH:

            /*Setting the specified pins in PORTx register*/
            *garr_portArray[au8_port] |= (au8_pin);

            /*Break from this case*/
            break;

        /*In case of default*/
        default:

            /*Break from this case*/
            break;
    }    

    /*Return from this function*/
    return;
}

void mdio_togglePinValue(u8_t au8_port, u8_t au8_pin)
{
    /*Toggling the specified pins in PORTx register*/
    *garr_portArray[au8_port] ^= (au8_pin);

    /*Return from this function*/
    return;
}

void mdio_getPinValue(u8_t au8_port, u8_t au8_pin, u8_t* pu8_pinValue)
{
    /*Checking the PINx value for a specified port pin if it's LOW or not*/
    if( (*garr_pinArray[au8_port] & au8_pin) == LOW )
    {
        /*Setting the pin value as LOW*/
        *pu8_pinValue = LOW;
    }
    else
    {
        /*Satting the pin value as HIGH*/
        *pu8_pinValue = HIGH;
    }

    /*Return from this function*/
    return;
}
void DIO_getPinValue (u8_t au8_port ,u8_t au8_pin ,u8_t* PinValue ) //mmkn return u8 bas void a7san
{
	if ((au8_port<=3)&&(au8_pin<=7)&&(PinValue!=NULL))
	{
		switch (au8_port)
		{
			case PORTA:
			
			*PinValue =GET_BIT(PINA,au8_pin);
			
			break;
			
			
			
			case PORTB:
			
			*PinValue =GET_BIT(PINB,au8_pin);
			
			break;
			
			case PORTC:
			
			*PinValue =GET_BIT(PINC,au8_pin);
			
			break;
			
			
			case PORTD:
			
			*PinValue =GET_BIT(PIND,au8_pin);
			
			break;
		}
	}
}