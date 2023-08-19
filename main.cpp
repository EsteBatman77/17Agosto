
#include "mbed.h"
#include <iostream>

using namespace std;


// Blinking rate in milliseconds
#define BLINKING_RATE     100ms
UnbufferedSerial serial(USBTX, USBRX, 9600);

int hexaDeci(string nHex) {
    int nDeci = 0;
    int base = 16;
    
    for (int i = nHex.size() - 1, exp = 0; i >= 0; i--, exp++) {
        char digit = nHex[i];

        if (isdigit(digit)) {
            nDeci += (digit - '0') * pow(base, exp);
        } else if (isalpha(digit)) {
            // (A=10, B=11, ..., F=15)
            nDeci += (toupper(digit) - 'A' + 10) * pow(base, exp);
        } else {
            // Error 
            cout << "Caracter no valido en el numero hexadecimal: " << digit << endl;
            return -1;
        }
    }

    return nDeci;
}

int main()
{
    // Initialise the digital pin LED1 as an output
    PwmOut red(LED1);
    PwmOut green(LED2);
    PwmOut blue(LED3);
    
    int hexV;
    float pwmR = 0.0;
    float pwmG = 0.0;
    float pwmB = 0.0;
   
    while (true) {

        cout << "Ingrese el código hexadecimal: ";
        cin >> hexV;

        for(int i = 0; i < hex.length(); i += 2){
            if(i == 0 ){
                if(hex[i] < 10){
                    hexR = (hex[i] * 10 + hex[i+1]) / 10;
                }else{
                    hexR = (hex[i] + hex[i+1]) / 10;
                }
            }else if(i == 2){
                 if(hex[i] < 10){
                    hexG = (hex[i] * 10 + hex[i+1]) / 10;
                }else{
                    hexG = (hex[i] + hex[i+1]) / 10;
                }  
            }else{
                 if(hex[i] < 10){
                    hexB = (hex[i] * 10 + hex[i+1]) / 10;
                }else{
                    hexB = (hex[i] + hex[i+1]) / 10;
                }
            }
        }
        
        pwmR = hexToDecimal(hexR);
        pwmG = hexToDecimal(hexG);
        pwmB = hexToDecimal(hexB);

        pwmR /= 255;
        pwmG /= 255;
        pwmB /= 255;

        ledR.write(1.0 - pwmR);
        ledG.write(1.0 - pwmG);
        ledB.write(1.0 - pwmB);
    }
}
