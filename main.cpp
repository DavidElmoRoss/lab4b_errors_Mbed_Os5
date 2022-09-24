    /*
    Title:  Program to display temperature on PC Screen from Grove Temp Sensor
    Author: David Ross
    Date:   July 13, 2017
    Description:    This program assumes that the Grove Temperature Module 
                    has been connected to Connector A0 of the Grove Shield V2.
                    It will constantly update the Temperature on the PC screen
                    in both Celsius and Fahrenheit, as well as show the Resistance.
*/
//Function Prototypes
void clear(void);                   // clears the PC screen
void position(int x, int y);        // positions screen cursor at (x,y)

#include "mbed.h"                   // include the mbed.h library
AnalogIn input1(A2);                // set Analog input1 to A0 
                                    // (A1 is not connected)
// Global Variables and Constants
const int B=4250;                   // B constant for Thermistor
                                    // in Temp Sensor V1.2
volatile double temperature;                 // output temperature
volatile unsigned short voltage;               // voltage  from Grove Temperature Sensor


int main(void)
{
    volatile double R;                       // variable used to compute temperature
    clear();                        // clear the screen
    position(11,36);                // positions curson at (11,36)
    printf("Temperature");          // print title Temperature
    fflush(stdout);                 // flush output buffer to screen
 
    while(1)                        // loop forever
    {
        
      // wait_ms(500);                // wait 0.5 seconds 
        ThisThread::sleep_for(500);  
       voltage=input1.read();       //  gets 16-bit raw A/D value 
                                    //voltage=32768 will give 25deg and 100.0Kohms
 
       R=65536.0/((double)voltage)-1.0; 
                                    // temperature conv based on data sheet
       temperature=1.0/(log(R)/B+1/298.15)-273.15; 

       position(12,30);    
       printf("%6.1f",temperature); // output temperature value on screen
       putchar(0xf8);               // change Putty Translation to CP437 
                                    // output Celsius and Fahrenheit temps 
       printf("C   %9.1f",((9.0/5.0)*temperature+32));
       putchar(0xf8);               // change Putty Translation to CP437  
       printf("F");
       position(14,35);             // set cursor 2 lines down
       printf("R= %6.2f Kohms",R*100);
       fflush(stdout);
    }
}
void clear(void)
{
    printf("\e[2J");
    fflush(stdout);   
}
void position(int x, int y)
{
    printf("\e[%d;%dH",x,y);
    fflush(stdout);
}