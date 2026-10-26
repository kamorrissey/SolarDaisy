/**
 * System Driver Source File
 * 
 * @file system.c
 * 
 * @ingroup systemdriver
 * 
 * @brief This file contains the API implementation for the System driver.
 *
 * @version Driver Version 2.0.3
 *
 * @version Package Version 4.1.4
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../system.h"

/** 
* @ingroup systemdriver
* @brief Initializes the Peripheral Module Disable (PMD) module.
* @param None.
* @return None.
*/
void PMD_Initialize(void);


void SYSTEM_Initialize(void)
{
    CLOCK_Initialize();
    PIN_MANAGER_Initialize();
    ADC_Initialize();
    TMR0_Initialize();
    TMR1_Initialize();
    TMR2_Initialize();
    CMP1_Initialize();
    DAC1_Initialize();
    FVR_Initialize();
    PMD_Initialize();
    PWM1_Initialize();
    INTERRUPT_Initialize();
}

void PMD_Initialize(void)
{
    //IOCMD IOC disabled; NVMMD NVM enabled; SCANMD SCANNER enabled; CRCMD CRC enabled; SYSCMD SYSCLK enabled; TMR0MD TMR0 enabled; 
    PMD0 = (uint8_t)0x20;
    //TMR1MD TMR1 enabled; TMR2MD TMR2 enabled; CCP1MD CCP1 disabled; CCP2MD CCP2 disabled; 
    PMD1 = (uint8_t)0x60;
    //CLC1MD CLC1 disabled; CLC2MD CLC2 disabled; CLC3MD CLC3 disabled; 
    PMD2 = (uint8_t)0xE0;
    //CLC4MD CLC4 disabled; MSSP1MD MSSP1 disabled; FVRMD FVR enabled; CM1MD CM1 enabled; CM2MD CM2 enabled; UART1MD UART1 disabled; 
    PMD3 = (uint8_t)0xB;
    //ADCMD ADC enabled; DAC1MD DAC1 enabled; CLBMD CLB disabled; 
    PMD4 = (uint8_t)0x80;
    //PWM1MD PWM1 enabled; PWM2MD PWM2 disabled; 
    PMD5 = (uint8_t)0x2;
}

