
#include "mbed.h"
#include <iostream>

using namespace std;


// Blinking rate in milliseconds
#define BLINKING_RATE     100ms
UnbufferedSerial serial(USBTX, USBRX, 9600);

int hexToDecimal(string hexNumber) {
    int decimalNumber = 0;
    int base = 16; // Base hexadecimal

    // Recorrer el número hexadecimal de derecha a izquierda
    for (int i = hexNumber.size() - 1, exp = 0; i >= 0; i--, exp++) {
        char digit = hexNumber[i];

        if (isdigit(digit)) {
            decimalNumber += (digit - '0') * pow(base, exp);
        } else if (isalpha(digit)) {
            // Convertir letras a números equivalentes (A=10, B=11, ..., F=15)
            decimalNumber += (toupper(digit) - 'A' + 10) * pow(base, exp);
        } else {
            // Carácter no válido en el número hexadecimal
            cout << "Caracter no valido en el numero hexadecimal: " << digit << endl;
            return -1; // Valor de error
        }
    }

    return decimalNumber;
}

int main()
{
    // Initialise the digital pin LED1 as an output
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    float pwmR = 0.0;
    float pwmG = 0.0;
    float pwmB = 0.0;
   


    while (true) {
        /*cout << "Ingresa la intensidad del led rojo: ";
        cin >> pwmR;

        cout << "Ingresa la intensidad del led verde: ";
        cin >> pwmG;

        cout << "Ingresa la intensidad del led azul: ";
        cin >> pwmB;*/
        string hex  = "";
        string hexR  = "";
        string hexG  = "";
        string hexB  = "";

        cout << "Ingrese el código hexadecimal: ";
        cin >> hex;

        for(int i = 0; i < hex.length(); i++){
            if(i == 0 || i == 1){
                hexR += hex[i]; 
            }else if(i == 2 || i == 3){
                hexG += hex[i];  
            }else{
                hexB += hex[i]; 
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