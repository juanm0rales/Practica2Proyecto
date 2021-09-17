 /*          10/08/2021 BOGOT�, D.C. PONTIFICIA UNIVERSIDAD JAVERIANA          *
 *                        PROYECTO EN ELECTR�NICA II                           *
 *                          MAIN CODE, POLLING MODE                            *
 *             AUTORES:JAVIER IB��EZ-JUAN MORALES-ALEJANDRO ARIZA              */

//DEFINICI�N DE LIBRERIAS Y ARCHIVOS .H
#include <xc.h> //LIBRERIA PARA EL COMPILADOR
#include <stdio.h>//LIBRERIA PARA NAVEGACI�N ENTRE ARCHIVOS .H
#define	displayINTERRUPT//NOMBRE DEL ARCHIVO .H

//DECLARACI�N DE LAS FUNCIONES
//SELECCIONA LA FUNCI�N A LLAMAR SEG�N EL NUMERO DEL DIGITO
void selector(int numo);
//FUNCI�N DE DISPLAY PARA IMPRIMIR
void display(int num2, int b);      //num2 ES EL NUMERO A IMPRIMIR Y b ES LA BASE A HABILITAR DE LOS BJTS

//DECLARACION DE LAS VARIABLES
int digt1, digt2, digt3;            //NUMERO DE DIGITOS A IMPRIMIR

//FUNCI�N DE IMPRESI�N DE NUMEROS EN EL DISPLAY 
void display(int num2, int b){
//ALGORTIMO PARA DESCOMPONER LAS CIFRAS DEL NUMERO A IMPRIMIR EN EL DISPLAY
    digt1=num2/100;
    digt2=(num2-digt1*100)/10;
    digt3=(num2-digt1*100-digt2*10);
//MAQUINA DE ESTADOS PARA LA MULTIPLEXACI�N E IMPRESI�N EN EL DISPLAY
    switch (b){
        case 0:    
            RB5=0; 						//VOLTAJE BAJO A LA BASE DEL BJT2 APAGANDO EL DIGITO 2
            RB4=0; 						//VOLTAJE BAJO A LA BASE DEL BJT3 APAGANDO EL DIGITO 3
            RB7=1; 						//VOLTAJE ALTO A LA BASE DEL BJT1 ENCENDIENDO EL DIGITO 1
            selector(digt1); 					//LLAMADO A LA FUNCI�N PARA ENCENDER CADA SEGMENTO SEGUN EL DIGITO
        break;

        case 1:
            RB7=0; 						//VOLTAJE BAJO A LA BASE DEL BJT1 APAGANDO EL DIGITO 1
            RB4=0; 						//VOLTAJE BAJO A LA BASE DEL BJT3 APAGANDO EL DIGITO 3
            RB5=1; 						//VOLTAJE ALTO A LA BASE DEL BJT2 ENCENDIENDO EL DIGITO 2
            selector(digt2); 			//LLAMADO A LA FUNCI�N PARA ENCENDER CADA SEGMENTO SEGUN EL DIGITO
        break;
     
        case 2:
             RB7=0; 					//VOLTAJE BAJO A LA BASE DEL BJT1 APAGANDO EL DIGITO 1
             RB5=0; 					//VOLTAJE BAJO A LA BASE DEL BJT2 APAGANDO EL DIGITO 2
             RB4=1; 					//VOLTAJE ALTO A LA BASE DEL BJT3 ENCENDIENDO EL DIGITO 3
             selector(digt3); 			//LLAMADO A LA FUNCI�N PARA ENCENDER CADA SEGMENTO SEGUN EL DIGITO
        break;
}    
  }

//FUNCI�N PARA INPRIMIR LOS NUMEROS DE CADA DIGITO DEL DISPLAY
void selector(int numo){
//MAQUINA DE 10 ESTADOS DADO EL NUMERO A REPRESENTAR EN CADA UNO, DE 0-9
     switch (numo){ //NUMERO EN DECIMAL DE 0-9, SEG�N EL CASO ENTRA A UN ESTADO
        case 0:
            RA1=1; //A
            RB0=1; //B
            RB6=1; //C
            RA4=1; //D
            RA3=1; //E
            RA7=1; //F
            RA2=0; //G
            RA0=1; //P
        break;

        case 1:
            RA1=0; //A
            RB0=1; //B
            RB6=1; //C
            RA4=0; //D
            RA3=0; //E
            RA7=0; //F
            RA2=0; //G
            RA0=1; //P
        break;
     
        case 2:
            RA1=1; //A
            RB0=1; //B
            RB6=0; //C
            RA4=1; //D
            RA3=1; //E
            RA7=0; //F
            RA2=1; //G
            RA0=1; //P
        break;

        case 3:
            RA1=1; //A
            RB0=1; //B
            RB6=1; //C
            RA4=1; //D
            RA3=0; //E
            RA7=0; //F
            RA2=1; //G
            RA0=1; //P
        break;

        case 4:
            RA1=0; //A
            RB0=1; //B
            RB6=1; //C
            RA4=0; //D
            RA3=0; //E
            RA7=1; //F
            RA2=1; //G
            RA0=1; //P
        break;

        case 5:
            RA1=1; //A
            RB0=0; //B
            RB6=1; //C
            RA4=1; //D
            RA3=0; //E
            RA7=1; //F
            RA2=1; //G
            RA0=1; //P
        break;

        case 6:
            RA1=1; //A
            RB0=0; //B
            RB6=1; //C
            RA4=1; //D
            RA3=1; //E
            RA7=1; //F
            RA2=1; //G
            RA0=1; //P
         break;

        case 7:
            RA1=1; //A
            RB0=1; //B
            RB6=1; //C
            RA4=0; //D
            RA3=0; //E
            RA7=0; //F
            RA2=0; //G
            RA0=1; //P
        break;

        case 8:
            RA1=1; //A
            RB0=1; //B
            RB6=1; //C
            RA4=1; //D
            RA3=1; //E
            RA7=1; //F
            RA2=1; //G
            RA0=1; //P
        break;

       case 9:
            RA1=1; //A
            RB0=1; //B
            RB6=1; //C
            RA4=1; //D
            RA3=0; //E
            RA7=1; //F
            RA2=1; //G
            RA0=1; //P
        break;
}//FIN DE LA FSM
}//FIN DE LA FUNCION VOID