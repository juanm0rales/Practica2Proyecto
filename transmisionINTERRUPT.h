 /*          10/08/2021 BOGOT�, D.C. PONTIFICIA UNIVERSIDAD JAVERIANA          *
 *                        PROYECTO EN ELECTR�NICA II                           *
 *                          MAIN CODE, POLLING MODE                            *
 *             AUTORES:JAVIER IB��EZ-JUAN MORALES-ALEJANDRO ARIZA              */

//DEFINICI�N DE LIBRERIAS Y ARCHIVOS .H
#include <xc.h>                      //LIBRERIA PARA EL COMPILADOR
#include <stdio.h>                   //LIBRERIA PARA NAVEGACI�N ENTRE ARCHIVOS .H
#define	transmisionINTERRUPT         //NOMBRE DEL ARCHIVO .H

//DECLARACION DE LAS VARIABLES
int sw_digt_tx=0;                   //VARIABLE AUXILIAR PARA SELECCIONAR EL CARACTER A TRANSMITIR
int digt1tx, digt2tx, digt3tx;      //TRES DIGITOS A TRANSMITIR EN FORMATO HEXADECIMAL

//DECLARACI�N DE NUMEROS IMPORTANTES
#define Puntohx 0x2E                        //REPRESENTACI�N DE UN PUNTO EN HEXADECIMAL
#define Conversionhx 0x30                   //PARA CONVERTIR DE DECIMAL A HEXADECIMAL
#define Espacio 0x20                        //REPRESENTACI�N DE UN ESPACIO EN HEXADECIMAL

//FUNCI�N DE TRANSMISI�N POR EUSART  
void transmision(int N){
 //ALGORTIMO PARA DESCOMPONER LAS CIFRAS DEL NUMERO A IMPRIMIR EN EL DISPLAY Y SE CONVIERTE A HEXA PARA TRANSMITIR POR EL SERIAL
    digt1tx=N/100;
    digt2tx=(N-digt1tx*100)/10;
    digt3tx=(N-digt1tx*100-digt2tx*10);
//PARA CONVERTIR UN NUMERO DECIMAL A HEXA SE SUMA POR 30
    digt1tx +=Conversionhx;
    digt2tx +=Conversionhx;
    digt3tx +=Conversionhx;
//MAQUINA DE ESTADOS PARA LA TRANSMISI�N DE LOS 5 CARACTERES 
    switch(sw_digt_tx){
        case 0:
            TXREG=digt1tx;          //TRANSMISI�N DEL PRIMER DIGITO
            sw_digt_tx=1;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;
        
        case 1:
            TXREG=Puntohx;             //TRANSMISI�N DEL PUNTO
            sw_digt_tx=2;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;
        
        case 2:
            TXREG=digt2tx;          //TRANSMISI�N DEL SEGUNDO DIGITO
            sw_digt_tx=3;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;

        case 3:
            TXREG=digt3tx;          //TRANSMISI�N DEL TERCER DIGITO
            sw_digt_tx=4;           //SALTO A TRANSMITIR EL SIGUIENTE CARACTER
            break;

        case 4:
            TXREG=0x20;             //TRANSMISI�N DEL ESPACIO
            sw_digt_tx=0;           //REINICIO DE LA MAQUINA
            break;     
    }//FINALIZA EL SWITCH
}//FINALIZA EL VOID