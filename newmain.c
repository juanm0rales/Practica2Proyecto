 /*          10/08/2021 BOGOTÁ, D.C. PONTIFICIA UNIVERSIDAD JAVERIANA          *
 *                        PROYECTO EN ELECTRÓNICA II                           *
 *                          MAIN CODE, INTERRUPT MODE                          *
 *             AUTORES:JAVIER IBÁÑEZ-JUAN MORALES-ALEJANDRO ARIZA              */

//DEFINICIÓN DE LIBRERIAS Y ARCHIVOS .H
#include <xc.h>                       //LIBRERIA PARA EL COMPILADOR
#include <stdio.h>                    //LIBRERIA PARA NAVEGACIÓN ENTRE ARCHIVOS .H
#include "configINTERRUPT.h"          //DEFINICIÓN DE ARCHIVO .H ADJUNTO
#include "transmisionINTERRUPT.h"     //DEFINICIÓN DE ARCHIVO .H ADJUNTO
#include "displayINTERRUPT.h"         //DEFINICIÓN DE ARCHIVO .H ADJUNTO

//DECLARACIÓN DE VARIABLES
int counterADC=0;                     //CONTADOR PARA CONTROLAR EL TIEMPO DE OPERACIÓN DEL ADC
int counterTrans=0;                   //CONTADOR PARA CONTROLAR EL TIEMPO DE OPERACIÓN DEL ADC
int counterLEDs=0;                    //CONTADOR PARA CONTROLAR LA FRECUENCIA DE MULTIPLEXACIÓN DEL DISPLAY
int resultADC;                        //RESULTADO DE LA CONVERSIÓN DE ADC DE 0-1023
float resultfloat;                    //OPERACION DE AJUSTE PARA EL DISPLAY resultfloat=resultADC*999/1023
int result;                           //CASTING PARA CONVERTIR resultfloat EN ENTERO
volatile char flag_timer = 0;         //BANDERA HABILITADA POR LA ISR SEGUN TMR1IF
volatile char flag_adc = 0;           //BANDERA HABILITADA POR LA ISR SEGUN ADIF

// DECLARACIÓN DE FUNCIONES
void configuration();                 //FUNCION DE CONFIGURACION DEL DISPOSITIVO Y REGISTROS
void display(int num2, int b);        //FUNCION DE TRANSMISION POR LA UART
void transmision(int num);            //FUNCION DE TRANSMISION POR LA UART
void __interrupt() timer1_isr (void); //RTUINA DE SERVICIO DE INTERRUPCION ISR PARA EL COMPILADOR 

//DECLARACIÓN DE NUMEROS IMPORTANTES
#define BJTS 2                        //NUMERO HASTA DONDE SE CUENTA PARA LA MULTIPLEXACIÓN DE LAS BASES DE LOS BJTS Y POR TANTO DEL DISPLAY
#define onesec 167                    //NUMERO DE VECES QUE CUENTA counterADC PARA LLEGAR A 1s Y AJUSTANDO SEGUN EL TIEMPO DE COMPILACIÓN
#define timerinit 63535               //VALOR DE INICIO DEL CONTADOR DE TIMER 1
#define timetrans 30                  // NUMERO DE VECES QUE CUENTA counterTrans PARA TRANSMITIR CADA CARACTER
#define ecuacion 0.9765395894         // RESULTADO DE LA ADECUACIÓN DE 999/1023

//FUNCION PRINCIPAL
void main(){
    configutation();		 			//LLAMADO A CONFIGURACIÓN DEL DISPOSITIVO
    while(1){
        RA6=0;                          //PIN DISPONIBLE PARA MEDIR EL TIEMPO DE CONVERSIÓN
        if (flag_timer==1){
            counterADC++; 				//CONTADOR DEL ADC PARA CONTAR 1 SEGUNDO
            counterLEDs++; 				//CONTADOR PARA MULTIPLEXAR EL DISPLAY
            counterTrans++; 		    //CONTADOR PARA REALIZAR LA TRANSMISIÓN DE CADA CARACTER EN 0.2s
            INTCONbits.GIE  = 1; 		//INTERRUPCIONES GLOBALES HABILITADAS
            PIE1bits.TMR1IE = 1;        //INTERRUPCIONES DEL TIMER1 HABILITADAS
            INTCONbits.PEIE = 1;        //INTERRUPCIONES DE PERIFERICOS HABILITADAS
            flag_timer=0;				//APAGA LA BANDERA GENERADA POR ISR EN EL FLAG DE TMR1IF DEL TIMER 1
        }
        if (flag_adc==1){
            RA6=1;                                  //PIN DISPONIBLE PARA MEDIR EL TIEMPO DE CONVERSIÓN
            resultADC = ADRESL | (ADRESH << 8); 	//RESULTADO DEL ADC GUARDADO A DERECHA
            resultfloat = resultADC*ecuacion; 		//ADECUACIÓN DEL RESULTADO PARA EL RANGO EN LOS DISPLAY
            result = resultfloat;                   //CASTING PARA CONVERTIR LA ADECUACIÓN A ENTERO
            INTCONbits.GIE  = 1;                    //INTERRUPCIONES GLOBALES HABILITADAS
            PIE1bits.ADIE = 1;                      //INTERRUPCIONES DEL ADC HABILITADAS
            INTCONbits.PEIE = 1;                	//INTERRUPCIONES DE PERIFERICOS HABILITADAS
            flag_adc=0;                             //APAGA LA BANDERA GENERADA POR ISR EN EL FLAG ADIF DEL ADC
        }
//CUANDO counterADC LLEGA A 500 SE HA COMPLETADO 1 SEGUNDO PARA EMPEZAR A CONVERTIR EN EL ADC 
        if(counterADC==onesec){
            ADCON0bits.GO_nDONE = 1;                //INICIA LA CONVERSIÓN DEL ADC        
            counterADC=0;                           //SE REINICIA EL CONTADOR        
        }
//CUANDO counterTrans LLEGA A 100 SE HA COMPLETADO 0.2 SEGUNDO Y SE EMPIEZA A TRANSMITIR
        if(counterTrans==timetrans){
            transmision(result);                    //SE TRANSMITE EL RESULTADO DEL ADC YA ADECUADO
            counterTrans=0;                         //SE REINICIA EL CONTADOR
        }
//counterLEDs SE INCREMENTA CADA 2ms HASTA LLEGAR A DOS Y ASI MULTIPLEXAR CADA BASE DE LOS BJTS
        if(counterLEDs>BJTS){        
            counterLEDs=0;                          //SE REINICIA EL CONTADOR
        }  
//LLAMADO A LA FUNCION DE DISPLAY
        display(result,counterLEDs);            //SE ENVIA AL DISPLAY EL RESULTADO A IMPRIMIR Y CUAL BASE ENCENDER DE LOS BJTS
    }//FINALIZA WHILE(1)
}//FINALIZA VOID MAIN

//RUTINA DE INTERRUPCIÓN ISR
void __interrupt(high_priority) timer1_isr (void){
    if(TMR1IF && TMR1IE){                           //EVALUA LA BANDERA QUE GENERA LA INTERRUPCIÓN TENIENDO PRIORIDAD TIMER 1
        flag_timer=1;                               //BANDERA DE HABILITACIÓN PARA INCREMENTAR LOS CONTADORES 
        TMR1 = timerinit;                           //REINICIA EL VALOR DEL CONTADOR
        PIR1bits.TMR1IF = 0;                        //BAJA LA BANDERA DE INTERRUPCIÓN DE TIMER 1
    }
    if(ADIF && ADIE){                               //EVALUA LA BANDERA QUE GENERA LA INTERRUPCIÓN TENIENDO SEGUNDA PRIORIDAD EL ADC      
        flag_adc=1;                                 //BANDERA DE HABILITACIÓN PARA EL ADC
        PIR1bits.ADIF = 0;                          //BAJA LA BANDERA DE INTERRUPCIÓN DE ADC
    }
}//FINALIZA VOID ISR 