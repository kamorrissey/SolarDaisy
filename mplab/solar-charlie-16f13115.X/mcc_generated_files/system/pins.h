/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define LEDCC_TRIS                 TRISAbits.TRISA0
#define LEDCC_LAT                  LATAbits.LATA0
#define LEDCC_PORT                 PORTAbits.RA0
#define LEDCC_WPU                  WPUAbits.WPUA0
#define LEDCC_OD                   ODCONAbits.ODCA0
#define LEDCC_ANS                  ANSELAbits.ANSA0
#define LEDCC_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LEDCC_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LEDCC_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LEDCC_GetValue()           PORTAbits.RA0
#define LEDCC_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LEDCC_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LEDCC_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LEDCC_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LEDCC_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LEDCC_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LEDCC_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LEDCC_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define SOL_TRIS                 TRISAbits.TRISA1
#define SOL_LAT                  LATAbits.LATA1
#define SOL_PORT                 PORTAbits.RA1
#define SOL_WPU                  WPUAbits.WPUA1
#define SOL_OD                   ODCONAbits.ODCA1
#define SOL_ANS                  ANSELAbits.ANSA1
#define SOL_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SOL_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SOL_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SOL_GetValue()           PORTAbits.RA1
#define SOL_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SOL_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SOL_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define SOL_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define SOL_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define SOL_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define SOL_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SOL_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define CP3_TRIS                 TRISAbits.TRISA2
#define CP3_LAT                  LATAbits.LATA2
#define CP3_PORT                 PORTAbits.RA2
#define CP3_WPU                  WPUAbits.WPUA2
#define CP3_OD                   ODCONAbits.ODCA2
#define CP3_ANS                  ANSELAbits.ANSA2
#define CP3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define CP3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define CP3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define CP3_GetValue()           PORTAbits.RA2
#define CP3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define CP3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define CP3_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define CP3_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define CP3_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define CP3_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define CP3_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define CP3_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define CP2_TRIS                 TRISAbits.TRISA4
#define CP2_LAT                  LATAbits.LATA4
#define CP2_PORT                 PORTAbits.RA4
#define CP2_WPU                  WPUAbits.WPUA4
#define CP2_OD                   ODCONAbits.ODCA4
#define CP2_ANS                  ANSELAbits.ANSA4
#define CP2_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define CP2_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define CP2_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define CP2_GetValue()           PORTAbits.RA4
#define CP2_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define CP2_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define CP2_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define CP2_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define CP2_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define CP2_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define CP2_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define CP2_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define CP1_TRIS                 TRISAbits.TRISA5
#define CP1_LAT                  LATAbits.LATA5
#define CP1_PORT                 PORTAbits.RA5
#define CP1_WPU                  WPUAbits.WPUA5
#define CP1_OD                   ODCONAbits.ODCA5
#define CP1_ANS                  ANSELAbits.ANSA5
#define CP1_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define CP1_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define CP1_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define CP1_GetValue()           PORTAbits.RA5
#define CP1_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define CP1_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define CP1_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define CP1_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define CP1_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define CP1_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define CP1_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define CP1_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/