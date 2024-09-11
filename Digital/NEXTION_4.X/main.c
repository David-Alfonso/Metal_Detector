/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
        Device            :  PIC18F46K42
        Driver Version    :  2.00
*/

#include "mcc_generated_files/mcc.h"
#include <xc.h>


#define size_num_FIR 16
#define size_num_sim_FIR 8
#define MAX_CHARACTERS 200

typedef enum {PAR,IMPAR} FLAG_T;


FLAG_T flag_sim = size_num_FIR % 2;

int16_t FIR_num[size_num_FIR] = {
    0,     12,   -108,   -708,   -924,   2588,  11568,  20336,  20336,
    11568,   2588,   -924,   -708,   -108,     12,      0
};
int16_t FIR_num_sim[size_num_sim_FIR] = {
    0,     12,   -108,   -708,   -924,   2588,  11568,  20336
};

void reorder_array_pt(int16_t *arr, int array_size);
int16_t FIR_pointer_sim(int16_t *in, int16_t *num, int size_in, int size_num, FLAG_T flag);
void separate_digits(int16_t num, char digits[]);
char categorize_number(uint8_t num, char sec);
void send_uart(char str[], int size);
void send_6F();
uint16_t abs_16(int16_t num);
void send_number(uint8_t num);
void get_page();
void get_gain();
void send_final_0();

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

// Result Variables
int16_t final_result_0 = 0;     // Final Result raw
int16_t final_result_1 = 0;     // Final Result raw
int16_t final_result_send_0 = 0;     // Final Result raw
int16_t final_result_send_1 = 0;     // Final Result raw
int16_t ref_0 = 0;
int16_t ref_1 = 0;
char send_result[3] = {};
char send_Fs[] = {0xFF,0xFF,0xFF,'\0'};
char sent_fifo[4] = {};
uint8_t gain = 0x00;

uint16_t adc_0 = 0;
uint16_t adc_1 = 0;
int32_t adc_0_acc = 0;
int32_t adc_1_acc = 0;
int16_t avg_adc_0 = 0;
int16_t avg_adc_1 = 0;
int flag_meas_acc = 0;

int ask_page = 0;
int ask_gain = 0;
int send_gain = 0;
int send_fifo = 0;
int num_page[4] = {};
int pos_num_page = 0;
int num_gain[4] = {};
int state_get_page = 0;
int state_get_gain = 0;
int state_send_final_0 = 0;


/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // array that saves the digits of the final result
    char digitos[4] = {};
    
    // Enable global interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    InitializeFIFO(eusart1);
    
    SPI1_Open(SPI1_DEFAULT);
    PGA_CS_SetHigh();
    
    
    PGA_CS_SetLow();
    // Instruction Byte
    // 0b01000000
    SPI1_ExchangeByte(0x40);
    
    // Gain Byte (5)
    // 0b00000011
    SPI1_ExchangeByte(gain);
    
    PGA_CS_SetHigh();
    
    // Arrays for saving the in values for each FIR filter
    int16_t in_values_0[size_num_FIR] = {};
    int16_t in_values_1[size_num_FIR] = {};
    
    // Pointers to arrays for saving the in values for each FIR filter
    int16_t *pt_in_values_0 = in_values_0;
    int16_t *pt_in_values_1 = in_values_1;

    // Pointers to the arrays that save the numerators of the FIR fs/10 filter
    // The arrays for the implementation with and without simmetry
    int16_t *pt_FIR_num = FIR_num;
    int16_t *pt_FIR_num_sim = FIR_num_sim;
    
    uint8_t num = 0;
    uint16_t num16_0 = 25923;
    uint16_t num16_1 = 0;
    
    send_uart("print dp",8);
    send_6F();
    send_uart("print dp",8);
    send_6F();
    send_uart("print dp",8);
    send_6F();
    send_uart("print dp",8);
    send_6F();
    
    while (1)
    {
        if(flag_meas_acc == 1)
        {
            flag_meas_acc = 0;
            avg_adc_0 = (int16_t)(adc_0_acc >> 6);
            avg_adc_1 = (int16_t)(adc_1_acc >> 6);
            adc_0_acc = 0;
            adc_1_acc = 0;
            
            // FIR filter with pointer and simmetry implementation and cut-off frequency of fs/10
            in_values_0[0] = (int16_t)(avg_adc_0);// saves last read of the adc in the in values array
            // calculates the result of the filter with the function 
            final_result_0 = FIR_pointer_sim(pt_in_values_0,pt_FIR_num_sim,size_num_FIR,size_num_sim_FIR,flag_sim);
            // reorder the in values array for the next sample
            reorder_array_pt(pt_in_values_0,size_num_FIR);
            
            // FIR filter with pointer and simmetry implementation and cut-off frequency of fs/10
            in_values_1[0] = (int16_t)(avg_adc_1);// saves last read of the adc in the in values array
            // calculates the result of the filter with the function 
            final_result_1 = FIR_pointer_sim(pt_in_values_1,pt_FIR_num_sim,size_num_FIR,size_num_sim_FIR,flag_sim);
            // reorder the in values array for the next sample
            reorder_array_pt(pt_in_values_1,size_num_FIR);
            
            if(ask_page == 1)
            {
                get_page();
            }
            else if(ask_gain == 1)
            {
                get_gain();
            }
            else if(send_gain == 1)
            {
                if((num_page[0] == 5) || (num_page[1] == 5) || (num_page[2] == 5) || (num_page[3] == 5))// || (num_gain[0] == 5) || (num_gain[1] == 5) || (num_gain[2] == 5) || (num_gain[3] == 5))
                {
                    gain = 0x00;
                }
                else if((num_page[0] == 6) || (num_page[1] == 6) || (num_page[2] == 6) || (num_page[3] == 6))// || (num_gain[0] == 6) || (num_gain[1] == 6) || (num_gain[2] == 6) || (num_gain[3] == 6))
                {
                    gain = 0x01;
                }
                else if((num_page[0] == 7) || (num_page[1] == 7) || (num_page[2] == 7) || (num_page[3] == 7))// || (num_gain[0] == 7) || (num_gain[1] == 7) || (num_gain[2] == 7) || (num_gain[3] == 7))
                {
                    gain = 0x02;
                }
                else if((num_page[0] == 8) || (num_page[1] == 8) || (num_page[2] == 8) || (num_page[3] == 8))// || (num_gain[0] == 8) || (num_gain[1] == 8) || (num_gain[2] == 8) || (num_gain[3] == 8))
                {
                    gain = 0x03;
                }
                else if((num_page[0] == 9) || (num_page[1] == 9) || (num_page[2] == 9) || (num_page[3] == 9))// || (num_gain[0] == 9) || (num_gain[1] == 9) || (num_gain[2] == 9) || (num_gain[3] == 9))
                {
                    gain = 0x04;
                }
                else if((num_page[0] == 10) || (num_page[1] == 10) || (num_page[2] == 10) || (num_page[3] == 10))// || (num_gain[0] == 10) || (num_gain[1] == 10) || (num_gain[2] == 10) || (num_gain[3] == 10))
                {
                    gain = 0x05;
                }
                else if((num_page[0] == 11) || (num_page[1] == 11) || (num_page[2] == 11) || (num_page[3] == 11))// || (num_gain[0] == 11) || (num_gain[1] == 11) || (num_gain[2] == 11) || (num_gain[3] == 11))
                {
                    gain = 0x06;
                }
                else if((num_page[0] == 12) || (num_page[1] == 12) || (num_page[2] == 12) || (num_page[3] == 12))// || (num_gain[0] == 12) || (num_gain[1] == 12) || (num_gain[2] == 12) || (num_gain[3] == 12))
                {
                    gain = 0x07;
                }
                PGA_CS_SetLow();
                // Instruction Byte
                // 0b01000000
                SPI1_ExchangeByte(0x40);
                // Gain Byte (5)
                // 0b00000011
                SPI1_ExchangeByte(gain);
                

                PGA_CS_SetHigh();
                
                send_gain = 0;
            }
            else if(send_fifo == 1)
            {
                if((num_page[0] == 1) || (num_page[1] == 1) || (num_page[2] == 1) || (num_page[3] == 1))
                {
                    ref_0 = final_result_0;
                    ref_1 = final_result_1;
                }
                else if((num_page[0] == 2) || (num_page[1] == 2) || (num_page[2] == 2) || (num_page[3] == 2))
                {
                    num16_0 = abs_16(final_result_0-ref_0);
                    num16_1 = abs_16(final_result_1-ref_1);
                    //pushString(eusart1,"a.val=0x");
                    pushString(eusart1,"add 1,0,0x");
                    send_result[0] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 1);
                    send_result[1] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 0);
                    send_result[2] = '\0';
                    pushString(eusart1,send_result);
                    pushString(eusart1,send_Fs);
                    //pushString(eusart1,"b.val=0x");
                    pushString(eusart1,"add 1,1,0x");
                    send_result[0] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 1);
                    send_result[1] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 0);
                    send_result[2] = '\0';
                    pushString(eusart1,send_result);
                    pushString(eusart1,send_Fs);
                }
                else if((num_page[0] == 3) || (num_page[1] == 3) || (num_page[2] == 3) || (num_page[3] == 3))
                {
                    num16_0 = abs_16(final_result_0-ref_0);
                    num16_1 = abs_16(final_result_1-ref_1);
                    
                    /* Send Sine */
                    pushString(eusart1,"sin.val=0x");
                    send_result[0] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 1);
                    send_result[1] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 0);
                    send_result[2] = '\0';
                    pushString(eusart1,send_result);
                    pushString(eusart1,send_Fs);
                    
                    /* Send Cosine */
                    pushString(eusart1,"cos.val=0x");
                    send_result[0] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 1);
                    send_result[1] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 0);
                    send_result[2] = '\0';
                    pushString(eusart1,send_result);
                    pushString(eusart1,send_Fs);
                    
//                    /* Send Sine Reference */
//                    pushString(eusart1,"refsin.val=0x");
//                    send_result[0] = categorize_number(0, 1);
//                    send_result[1] = categorize_number(0, 0);
//                    send_result[2] = '\0';
//                    pushString(eusart1,send_result);
//                    pushString(eusart1,send_Fs);
//                    
//                    /* Send Cosine Reference */
//                    pushString(eusart1,"refcos.val=0x");
//                    send_result[0] = categorize_number(0, 1);
//                    send_result[1] = categorize_number(0, 0);
//                    send_result[2] = '\0';
//                    pushString(eusart1,send_result);
//                    pushString(eusart1,send_Fs);
                    
                    /* Refresh */
                    pushString(eusart1,"ref page3");
                    pushString(eusart1,send_Fs);
                    pushString(eusart1,"refresh.en=1");
                    pushString(eusart1,send_Fs);
                }
                else if((num_page[0] == 4) || (num_page[1] == 4) || (num_page[2] == 4) || (num_page[3] == 4))
                {
                    num16_0 = abs_16(final_result_0-ref_0);
                    num16_1 = abs_16(final_result_1-ref_1);
                    if(num16_1 > num16_0)
                    {
                        pushString(eusart1,"readVal.val=0x");
                        send_result[0] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 1);
                        send_result[1] = categorize_number((uint8_t)((num16_1&0x07FF)>>3), 0);
                        send_result[2] = '\0';
                        pushString(eusart1,send_result);
                        pushString(eusart1,send_Fs);
                    }
                    else
                    {
                        
                        pushString(eusart1,"readVal.val=0x");
                        send_result[0] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 1);
                        send_result[1] = categorize_number((uint8_t)((num16_0&0x07FF)>>3), 0);
                        send_result[2] = '\0';
                        pushString(eusart1,send_result);
                        pushString(eusart1,send_Fs);
                    }
                }
            }
            
        }
        if(uart1RxCount > 0)
        {
            num_page[pos_num_page] = UART1_Read();
            pos_num_page++;
            if(pos_num_page >= 4)
            {
                pos_num_page = 0;
            }
        }
        if(!(PIE3bits.U1TXIE) && statusFIFO(eusart1) && (send_fifo == 1)){
            sent_fifo[3] = sent_fifo[2];
            sent_fifo[2] = sent_fifo[1];
            sent_fifo[1] = sent_fifo[0];
            sent_fifo[0] = popData(eusart1);
            if(!((sent_fifo[3] == 0xFF) && (sent_fifo[2] == 0xFF) && (sent_fifo[1] == 0xFF) && (sent_fifo[0] == ' ')))
            {
                UART1_Write(sent_fifo[0]);
            }
        }
    }
}

void reorder_array_pt(int16_t *arr, int array_size)
{
    int16_t *ptr = arr + array_size - 2; // Pointer to the second to last value
    for (int i = array_size - 2; i >= 0; i--)
    {
        *(ptr + 1) = *ptr; // Move value to the right
        ptr--; // Move pointer to the left
    }
}

int16_t FIR_pointer_sim(int16_t *in, int16_t *num, int size_in, int size_num, FLAG_T flag)
{
    int32_t resp = 0;
    
    for(int i = 0; i < size_num; i++)
    {
        // Add to the answer the multiplications of the pointed values
        resp += (((int32_t)(*(in+i)))+((int32_t)(*(in+size_in-i-1))))*((int32_t)(*(num+i)));
    }
    
    if(flag == IMPAR)
    {
        // If the coeficients are uneven, the last multiplication is double
        // It is needed to substract the last value
        resp -= ((int32_t)(*(in+size_num-1)))*((int32_t)(*(num+size_num-1)));
    }
    
    return ((int16_t)(resp>>16));
}

void separate_digits(int16_t num, char digits[])
{
    if(num < 0)
    {
        num = -num;
        //UART1_Write('-');
    }
    digits[0] = (num/1000) + '0';
    digits[1] = ((num%1000)/100) + '0';
    digits[2] = ((num%100)/10) + '0';
    digits[3] = (num%10) + '0';
}

char categorize_number(uint8_t num, char sec)
{
    char asciiValues[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    char mask = (sec == 0) ? 0x0f : 0xf0;
    char ascii;
    char real_val = (sec == 0) ? num & mask : (num & mask)>>4;
    /*
    if(real_val < 10){
        ascii = '0' + real_val;
    }
    else if(real_val == 10){
        ascii = 'A';
    }
    else if(real_val == 11){
        ascii = 'B';
    }
    else if(real_val == 12){
        ascii = 'C';
    }
    else if(real_val == 13){
        ascii = 'D';
    }
    else if(real_val == 14){
        ascii = 'E';
    }
    else{
        ascii = 'F';
    }
     * */
    ascii = asciiValues[real_val];
    return ascii;
}

void send_uart(char str[], int size)
{
    
//    UART1_Write(52);
    for(int i = 0; i < size; i++)
    {
        UART1_Write(str[i]);
    }
            
        //UART1_Write('\n');
    
}

void send_6F()
{
    UART1_Write(0xFF);
    UART1_Write(0xFF);
    UART1_Write(0xFF);
}

uint16_t abs_16(int16_t num)
{
    uint16_t resp = 0;
    if(num > 0)
    {
        resp = (uint16_t)(num);
    }
    else
    {
        resp = (uint16_t)(-num);
    }
    return resp;
}

void send_number(uint8_t num)
{
    UART1_Write(categorize_number(num, 1));
    UART1_Write(categorize_number(num, 0));
}

void send_final_0()
{/*
    switch( state_send_final_0 )
    {
        case 0:
            UART1_Write('a');
            state_send_final_0++;
            break;
        case 1:
            UART1_Write('.');
            state_send_final_0++;
            break;
        case 2:
            UART1_Write('v');
            state_send_final_0++;
            break;
        case 3:
            UART1_Write('a');
            state_send_final_0++;
            break;
        case 4:
            UART1_Write('l');
            state_send_final_0++;
            break;
        case 5:
            UART1_Write('=');
            state_send_final_0++;
            break;
        case 6:
            UART1_Write('0');
            state_send_final_0++;
            break;
        case 7:
            UART1_Write('x');
            state_send_final_0++;
            break;
        case 8:
            UART1_Write(categorize_number(((final_result_0&0xFF00)>>8), 1));
            state_send_final_0++;
            break;
        case 9:
            UART1_Write(categorize_number(((final_result_0&0xFF00)>>8), 0));
            state_send_final_0++;
            break;
        case 10:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
        case 11:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
        case 12:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
        case 13:
            UART1_Write('a');
            state_send_final_0++;
            break;
        case 14:
            UART1_Write('.');
            state_send_final_0++;
            break;
        case 2:
            UART1_Write('v');
            state_send_final_0++;
            break;
        case 3:
            UART1_Write('a');
            state_send_final_0++;
            break;
        case 4:
            UART1_Write('l');
            state_send_final_0++;
            break;
        case 5:
            UART1_Write('=');
            state_send_final_0++;
            break;
        case 6:
            UART1_Write('0');
            state_send_final_0++;
            break;
        case 7:
            UART1_Write('x');
            state_send_final_0++;
            break;
        case 8:
            UART1_Write(categorize_number(((final_result_0&0xFF00)>>8), 1));
            state_send_final_0++;
            break;
        case 9:
            UART1_Write(categorize_number(((final_result_0&0xFF00)>>8), 0));
            state_send_final_0++;
            break;
        case 10:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
        case 11:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
        case 12:
            UART1_Write(0xFF);
            state_send_final_0++;
            break;
            
            
            
            
            
            
        case 10:
            UART1_Write(categorize_number((final_result_0&0x00FF), 1));
            state_send_final_0++;
            break;
        case 11:
            UART1_Write(categorize_number((final_result_0&0x00FF), 0));
            state_send_final_0++;
            break;
    }
                send_uart("va0.val=0x",10);
    state_send_final_0 = 0;
    final_result_send_0 = final_result_0;/**/
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

void get_page()
{
    switch( state_get_page )
    {
        case 0:
            send_fifo = 0;
            UART1_Write('p');
            state_get_page++;
            break;
        case 1:
            UART1_Write('r');
            state_get_page++;
            break;
        case 2:
            UART1_Write('i');
            state_get_page++;
            break;
        case 3:
            UART1_Write('n');
            state_get_page++;
            break;
        case 4:
            UART1_Write('t');
            state_get_page++;
            break;
        case 5:
            UART1_Write(' ');
            state_get_page++;
            break;
        case 6:
            UART1_Write('d');
            state_get_page++;
            break;
        case 7:
            UART1_Write('p');
            state_get_page++;
            break;
        case 8:
            UART1_Write(0xFF);
            state_get_page++;
            break;
        case 9:
            UART1_Write(0xFF);
            state_get_page++;
            break;
        case 10:
            UART1_Write(0xFF);
//            num_page[0] = UART1_Read();
//            num_page[1] = UART1_Read();
//            num_page[2] = UART1_Read();
//            num_page[3] = UART1_Read();
            ask_page = 0;
            if((num_page[0] == 1) || (num_page[1] == 1) || (num_page[2] == 1) || (num_page[3] == 1))
            {
                ask_gain = 1;
            }
            else
            {
                send_fifo = 1;
            }
            
            state_get_page = 0;
            break;
    }
}

void get_gain()
{
    switch( state_get_gain )
    {
        case 0:
            PROOF_SetHigh();
            send_fifo = 0;
            UART1_Write('p');
            state_get_gain++;
            break;
        case 1:
            UART1_Write('r');
            state_get_gain++;
            break;
        case 2:
            UART1_Write('i');
            state_get_gain++;
            break;
        case 3:
            UART1_Write('n');
            state_get_gain++;
            break;
        case 4:
            UART1_Write('t');
            state_get_gain++;
            break;
        case 5:
            UART1_Write(' ');
            state_get_gain++;
            break;
        case 6:
            UART1_Write('g');
            state_get_gain++;
            break;
        case 7:
            UART1_Write('a');
            state_get_gain++;
            break;
        case 8:
            UART1_Write('.');
            state_get_gain++;
            break;
        case 9:
            UART1_Write('v');
            state_get_gain++;
            break;
        case 10:
            UART1_Write('a');
            state_get_gain++;
            break;
        case 11:
            UART1_Write('l');
            state_get_gain++;
            break;
        case 12:
            UART1_Write(0xFF);
            state_get_gain++;
            break;
        case 13:
            UART1_Write(0xFF);
            state_get_gain++;
            break;
        case 14:
            UART1_Write(0xFF);
//            num_gain[0] = UART1_Read();
//            num_gain[1] = UART1_Read();
//            num_gain[2] = UART1_Read();
//            num_gain[3] = UART1_Read();
            ask_gain = 0;
            send_fifo = 1;
            send_gain = 1;
            state_get_gain = 0;
            PROOF_SetLow();
            break;
    }
}

/**
 End of File
*/