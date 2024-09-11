/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18426
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set GAN_SIN aliases
#define GAN_SIN_TRIS                 TRISAbits.TRISA2
#define GAN_SIN_LAT                  LATAbits.LATA2
#define GAN_SIN_PORT                 PORTAbits.RA2
#define GAN_SIN_WPU                  WPUAbits.WPUA2
#define GAN_SIN_OD                   ODCONAbits.ODCA2
#define GAN_SIN_ANS                  ANSELAbits.ANSA2
#define GAN_SIN_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define GAN_SIN_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define GAN_SIN_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define GAN_SIN_GetValue()           PORTAbits.RA2
#define GAN_SIN_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define GAN_SIN_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define GAN_SIN_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define GAN_SIN_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define GAN_SIN_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define GAN_SIN_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define GAN_SIN_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define GAN_SIN_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()              PORTAbits.RA5
#define RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()             do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()           do { WPUAbits.WPUA5 = 0; } while(0)
#define RA5_SetAnalogMode()         do { ANSELAbits.ANSA5 = 1; } while(0)
#define RA5_SetDigitalMode()        do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set GAN_COS aliases
#define GAN_COS_TRIS                 TRISCbits.TRISC0
#define GAN_COS_LAT                  LATCbits.LATC0
#define GAN_COS_PORT                 PORTCbits.RC0
#define GAN_COS_WPU                  WPUCbits.WPUC0
#define GAN_COS_OD                   ODCONCbits.ODCC0
#define GAN_COS_ANS                  ANSELCbits.ANSC0
#define GAN_COS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define GAN_COS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define GAN_COS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define GAN_COS_GetValue()           PORTCbits.RC0
#define GAN_COS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define GAN_COS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define GAN_COS_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define GAN_COS_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define GAN_COS_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define GAN_COS_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define GAN_COS_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define GAN_COS_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set MUL_SIN aliases
#define MUL_SIN_TRIS                 TRISCbits.TRISC1
#define MUL_SIN_LAT                  LATCbits.LATC1
#define MUL_SIN_PORT                 PORTCbits.RC1
#define MUL_SIN_WPU                  WPUCbits.WPUC1
#define MUL_SIN_OD                   ODCONCbits.ODCC1
#define MUL_SIN_ANS                  ANSELCbits.ANSC1
#define MUL_SIN_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define MUL_SIN_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define MUL_SIN_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define MUL_SIN_GetValue()           PORTCbits.RC1
#define MUL_SIN_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define MUL_SIN_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define MUL_SIN_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define MUL_SIN_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define MUL_SIN_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define MUL_SIN_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define MUL_SIN_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define MUL_SIN_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set MUL_COS aliases
#define MUL_COS_TRIS                 TRISCbits.TRISC2
#define MUL_COS_LAT                  LATCbits.LATC2
#define MUL_COS_PORT                 PORTCbits.RC2
#define MUL_COS_WPU                  WPUCbits.WPUC2
#define MUL_COS_OD                   ODCONCbits.ODCC2
#define MUL_COS_ANS                  ANSELCbits.ANSC2
#define MUL_COS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define MUL_COS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define MUL_COS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define MUL_COS_GetValue()           PORTCbits.RC2
#define MUL_COS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define MUL_COS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define MUL_COS_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define MUL_COS_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define MUL_COS_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define MUL_COS_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define MUL_COS_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define MUL_COS_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set SWITCH aliases
#define SWITCH_TRIS                 TRISCbits.TRISC3
#define SWITCH_LAT                  LATCbits.LATC3
#define SWITCH_PORT                 PORTCbits.RC3
#define SWITCH_WPU                  WPUCbits.WPUC3
#define SWITCH_OD                   ODCONCbits.ODCC3
#define SWITCH_ANS                  ANSELCbits.ANSC3
#define SWITCH_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SWITCH_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SWITCH_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SWITCH_GetValue()           PORTCbits.RC3
#define SWITCH_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SWITCH_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define SWITCH_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define SWITCH_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set TEST aliases
#define TEST_TRIS                 TRISCbits.TRISC5
#define TEST_LAT                  LATCbits.LATC5
#define TEST_PORT                 PORTCbits.RC5
#define TEST_WPU                  WPUCbits.WPUC5
#define TEST_OD                   ODCONCbits.ODCC5
#define TEST_ANS                  ANSELCbits.ANSC5
#define TEST_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define TEST_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define TEST_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define TEST_GetValue()           PORTCbits.RC5
#define TEST_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define TEST_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define TEST_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define TEST_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define TEST_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define TEST_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define TEST_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define TEST_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/