/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18426
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#define MAX_CHARACTERS 10
/*
                         Main application
 */

//!----------------NUEVOS TIPOS DE DATOS---------------------!
enum status {CAL = 0, WORK = 1};
typedef unsigned char BYTE;
typedef struct FIFO_t{
    BYTE buffer[MAX_CHARACTERS];
    BYTE* writeBuffer;
    BYTE* readBuffer;
    bool newData;
    bool statusFIFO; // 0 it's full and 1 is empty
} FIFO;
bool timerINT = 0;


//!---------------------PROTOTIPOS---------------------!
BYTE popData(FIFO *targetFIFO);
void pushInteger(FIFO *targetFIFO, uint16_t value);
void pushString(FIFO *targetFIFO, char* newString);
void checkBoundaries(FIFO *targetFIFO, BYTE** bufferPointer);
bool statusFIFO(FIFO *targetFIFO);
void InitializeFIFO(FIFO *targetFIFO);

FIFO struct_eusart1;
FIFO* eusart1 = &struct_eusart1;

//!------------------PROGRAMA PRINCIPAL---------------------!

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    InitializeFIFO(eusart1);
    
    //INTERRUPTOR PARA EL ESTADO
    enum status statusSystem = CAL;
    //VARIABLES PARA LA LECTURA DEL ADC
    uint16_t mul_sin, mul_cos, gan_sin, gan_cos = 0;
    //CICLO UTIL DE LOS PWMs UTILIZADOS PARA CALIBRAR
    uint16_t dutyCycle_sin, dutyCycle_cos = 200;
    
    while (1)
    {
        //REVISAMOS EL MODO DEL SISTEMA
        statusSystem = SWITCH_GetValue();
        //SI HAY NUEVA INFORMACION POR ENVIAR Y LA EUSART ESTA DISPONIBLE, SE ENVIA
        if((PIR3bits.TX1IF) && statusFIFO(eusart1)){
            EUSART1_Write(popData(eusart1));
        }
        //SI HAY UNA NUEVA INTERRUPCION DEL TIMER MAESTRO
        if(timerINT){
            TEST_SetHigh();
            //NUEVAS MUESTRAS
            gan_sin = (uint16_t)(ADCC_GetSingleConversion(0x2));
            gan_cos = (uint16_t)(ADCC_GetSingleConversion(0x10));
            mul_sin = (uint16_t)(ADCC_GetSingleConversion(0x11));
            mul_cos = (uint16_t)(ADCC_GetSingleConversion(0x12));
            //SE LLENA LA FIFO CON NUEVAS MUESTRAS
            pushInteger(eusart1, mul_sin);
            pushString(eusart1, ",");
            pushInteger(eusart1, mul_cos);
            pushString(eusart1, "\n");
            //VERIFICAMOS MODO ACTUAL
            if(statusSystem == CAL){
                //SI ESTA EN MODO DE CALIBRACION
                //CALIBRAMOS LA SENAL DEL SENO
                dutyCycle_sin = (uint16_t) (gan_sin/10.2);
                PWM6_LoadDutyValue(dutyCycle_sin);
                //CALIBRAMOS LA SENAL DEL COSENO
                dutyCycle_cos = (uint16_t) (gan_cos/10.2);
                PWM7_LoadDutyValue(dutyCycle_cos);
            }
            //SE BAJA LA BANDERA DE INTERRUPCION
            timerINT = 0;
            TEST_SetLow();
        }
    }
}

void pushString(FIFO *targetFIFO, char* newString){
    BYTE letterCounter = 0;
    
    int size = sizeof(newString);
    
    while(((((targetFIFO->writeBuffer) != (targetFIFO->readBuffer))||(targetFIFO->statusFIFO))&&(newString[letterCounter] != '\0'))){
        size = sizeof(newString);
        *(targetFIFO->writeBuffer) = newString[letterCounter];
        letterCounter += 1;
        checkBoundaries(targetFIFO, &(targetFIFO->writeBuffer));
        (targetFIFO->newData) = 1;
    }
    
    if((targetFIFO->writeBuffer) == (targetFIFO->readBuffer)){
        if(targetFIFO->statusFIFO == 1)
            targetFIFO->statusFIFO = 0;        
    }
}
void pushInteger(FIFO *targetFIFO, uint16_t value){
    register uint16_t digit, reconstructedNum;
    reconstructedNum = value;
    //char* array;
    register BYTE array[5]={};
    BYTE pos = 0;
    
    for(BYTE i = 0; reconstructedNum != 0; i++){
        digit   = reconstructedNum % 10;
        reconstructedNum /= 10;
        array[pos] = (BYTE)('0'+digit);
        pos++;
    }
    while((((targetFIFO->writeBuffer)!= (targetFIFO->readBuffer))||(targetFIFO->statusFIFO))&&(pos != 0)){
        *(targetFIFO->writeBuffer) = array[pos-1];
        checkBoundaries(targetFIFO, &targetFIFO->writeBuffer);
        if((targetFIFO->writeBuffer) == (targetFIFO->readBuffer)){
            targetFIFO->statusFIFO = 0; 
        }
        else{
            pos--;
        }
    }
}
BYTE popData(FIFO *targetFIFO){
    BYTE currentChar = ' ';
    if((targetFIFO->writeBuffer) != (targetFIFO->readBuffer)||(!(targetFIFO->statusFIFO))){
        currentChar = *(targetFIFO->readBuffer);
        checkBoundaries(targetFIFO, &(targetFIFO->readBuffer));
    }
    else{
        (targetFIFO->newData) = 0;
    }
    if((targetFIFO->writeBuffer) == (targetFIFO->readBuffer)){
        if(targetFIFO->statusFIFO == 0)
            targetFIFO->statusFIFO = 1;        
    }
    return currentChar;
}
void checkBoundaries(FIFO *targetFIFO, BYTE** bufferPointer){
    if(*bufferPointer == &(targetFIFO->buffer[MAX_CHARACTERS-1])){
        *bufferPointer = &(targetFIFO->buffer[0]);
    }
    else{
        *bufferPointer += 1;
    }
}
bool statusFIFO(FIFO *targetFIFO){
    return (targetFIFO->newData);
}
void InitializeFIFO(FIFO *targetFIFO){
    targetFIFO->writeBuffer = &((targetFIFO->buffer[0]));
    targetFIFO->readBuffer = &((targetFIFO->buffer[0]));
    targetFIFO->newData = 0;
    targetFIFO->statusFIFO = 1;
}
/**
 End of File
*/