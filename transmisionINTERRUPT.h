 /*          10/08/2021 BOGOTÁ, D.C. PONTIFICIA UNIVERSIDAD JAVERIANA          *
 *                        PROYECTO EN ELECTRÓNICA II                           *
 *                          MAIN CODE, POLLING MODE                            *
 *             AUTORES:JAVIER IBÁÑEZ-JUAN MORALES-ALEJANDRO ARIZA              */

//DEFINICIÓN DE LIBRERIAS Y ARCHIVOS .H
#include <xc.h>                      //LIBRERIA PARA EL COMPILADOR
#include <stdio.h>                   //LIBRERIA PARA NAVEGACIÓN ENTRE ARCHIVOS .H
#define	transmisionINTERRUPT         //NOMBRE DEL ARCHIVO .H

//DECLARACION DE LAS VARIABLES
int sw_digt_tx=0;                   //VARIABLE AUXILIAR PARA SELECCIONAR EL CARACTER A TRANSMITIR
int digt1tx, digt2tx, digt3tx;      //TRES DIGITOS A TRANSMITIR EN FORMATO HEXADECIMAL

//DECLARACIÓN DE NUMEROS IMPORTANTES
#define Puntohx 0x2E                        //REPRESENTACIÓN DE UN PUNTO EN HEXADECIMAL
#define Conversionhx 0x30                   //PARA CONVERTIR DE DECIMAL A HEXADECIMAL
#define Espacio 0x20                        //REPRESENTACIÓN DE UN ESPACIO EN HEXADECIMAL

//FUNCIÓN DE TRANSMISIÓN POR EUSART  
void transmision(int N){
 //ALGORTIMO PARA DESCOMPONER LAS CIFRAS DEL NUMERO A IMPRIMIR EN EL DISPLAY Y SE CONVIERTE A HEXA PARA TRANSMITIR POR EL SERIAL
    digt1tx=N/100;
    digt2tx=(N-digt1tx*100)/10;
    digt3tx=(N-digt1tx*100-digt2tx*10);
//PARA CONVERTIR UN NUMERO DECIMAL A HEXA SE SUMA POR 30
    digt1tx +=Conversionhx;
    digt2tx +=Conversionhx;
    digt3tx +=Conversionhx;
//MAQUINA DE ESTADOS PARA LA TRANSMISIÓN DE LOS 5 CARACTERES 
    switch(sw_digt_tx){
        case 0:
            TXREG=digt1tx;          //TRANSMISIÓN DEL PRIMER DIGITO
            sw_digt_tx=1;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;
        
        case 1:
            TXREG=Puntohx;             //TRANSMISIÓN DEL PUNTO
            sw_digt_tx=2;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;
        
        case 2:
            TXREG=digt2tx;          //TRANSMISIÓN DEL SEGUNDO DIGITO
            sw_digt_tx=3;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;

        case 3:
            TXREG=digt3tx;          //TRANSMISIÓN DEL TERCER DIGITO
            sw_digt_tx=4;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;

        case 4:
            TXREG=0x20;             //TRANSMISIÓN DEL ESPACIO
            sw_digt_tx=0;           //REINICIO DE LA MAQUINA
            break;     
    }//FINALIZA EL SWITCH
}//FINALIZA EL VOID