/*
 * File:   timer01oscilator.c
 * Author: roner
 *
 * Created on 24 de Abril de 2017, 21:48
 */

#define _XTAL_FREQ 4000000;
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer01.h"



/****variable***************/
unsigned int auxCounter = 0x00;
unsigned int auxCounterTwo = 0x00;

/*********map hardware*/
void main() {

    CMCON = 0x07; //disable internal comparator
    T1CON = 0x31; // enable timer 01 and pre escale to 1: 8 and internal clock

    // calc para 30 ms in high and 70 ms in low  with period of 100 ms   let make 10 ms okay
    // overflow= prescale* 2^16 * machinecycle 
    // 10ms  = 8 * TMR1L:TMR1H * [1/(4E6 / 4)]      machinecycle = 1us ;
    // TMR1L:TMR1H = [ 10ms /(8 * 1E-6]
    //TMR1L:TMR1H = 1250    in (1250 - 2^16)= 64286    the counter start in 64286 and finishe in 65536;
    // 64286 in decimal in equal  FB1E   in hex
    TMR1L = 0x1e; // value   to make  10ms  
    TMR1H = 0xfb; //

    INTCONbits.GIE = 0x01; //Global interrupt enable
    INTCONbits.PEIE = 0x01; //peripherial interrupt enable
    PIE1bits.TMR1IE = 0x01; // ENABLE TIMER1
    PIR1bits.TMR1IF = 0x00; //start flag clear


    TRISBbits.TRISB7 = 0x00; // RB7 as output 

    PORTBbits.RB7 = 0x00; // RB7 start in 0 volt 



    while (1) {




    }


}

void interrupt rontineInterrupt() {




    if (PIR1bits.TMR1IF == 0x01) {

        PIR1bits.TMR1IF = 0x00; //clear flag


        //  PORTBbits.RB7 = ~PORTBbits.RB7; 


        auxCounter++; //make just 70ms
        PORTBbits.RB7 = 0x00;

        if (auxCounter == 0x07) {



            PORTBbits.RB7 = 0x01; // make 30 ms  
            auxCounter = 0x00;

            //            auxCounterTwo++;
            //            
            //
            //
            //            if (auxCounterTwo == 0x03) {
            //
            //                auxCounter = 0x00; //clear  variable auxiliares 
            //
            //                auxCounterTwo = 0x00;
            //
            //
            //            }





        }




    }




}