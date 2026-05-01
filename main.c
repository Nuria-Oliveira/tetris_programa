/*
Apellido: Lopez Nina, Aylin Yussel
DNI: 94593626
Usuario: AylinLopez05
Entrega: Sí

Apellido: Magnone, Mauro Marcelo
DNI: 42565840
Usuario: Mauro-Mag
Entrega: Sí

Apellido: Oliveira, Nuria Elisa
DNI: 31652404
Usuario: Nuria-Oliveira
Entrega: Sí
*/


#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "dibujos.h"
#define ANCHO_VENTANA 200
#define ALTO_VENTANA 180
#define ESCALA_VENTANA 4
#define TAM_CELDA 7
#define FIL 22
#define COL 10
#define COLOR 15
#define PIEZA 4
#include "GBT/gbt.h" ///BIBLIOTECA GBT

int main()
{
    char nombreVentana[160];
    int matriz[22][10]= {{0}};
    ///PRUEBAS QUE DIBUJA LOS TETRAMINOS SEGUN SU POSICION EN LA MATRIZ (TESTEO)
    //matriz[21][4]= 1;
    //matriz[21][5]= 1;
    //matriz[20][5]= 1;
    ///pureba de posicion de la pieza (PARA TESTEO )
    int pieza[4][4]=
    {
        {0,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    int pos_x=3; //COLUMNA EN EL TABLERO
    int pos_y=0;//FILA EN EL TABLERO

    printf("Hello world!\n");
///CREACION DE LA VENTANA
    sprintf(nombreVentana, "Ventana %dx%d", ANCHO_VENTANA,ALTO_VENTANA);

    if (gbt_iniciar()!=0)
    {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
    }

    gbt_crear_ventana(nombreVentana,ANCHO_VENTANA,ALTO_VENTANA,ESCALA_VENTANA);

///INICIA TEMPORIZADOR SERA USADO MAS ADELANTE
    tGBT_Temporizador *temporizador = gbt_temporizador_crear(1.0);
    if (!temporizador)
    {
        fprintf(stderr, "Error al crear el temporizador: %s\n", gbt_obtener_log());
        return -1;
    }

    int corriendo=1;
    int jugando=0;


    while(corriendo) ///LOOP PRINCIPAL
    {
        int pausado=0;
        gbt_borrar_backbuffer(0);///COLOCAR UNA COLOR A TODA LA VENTANA
        gbt_volcar_backbuffer();
        gbt_procesar_entrada();///INICIA EL PROCESADOR DE ENTRAS DE TECLADO
        eGBT_Tecla tecla=gbt_obtener_tecla_presionada();///GUARDA ULTIMA TECLA PRESIONADA EN tecla
        ///CALCULO PIXELES VENTANA DE JUEGO
        int ancho_tab=COL*TAM_CELDA;
        int alto_tab=(FIL-2)*TAM_CELDA;

        int inicio_x= (ANCHO_VENTANA-ancho_tab)/2;
        int inicio_y= (ALTO_VENTANA-alto_tab)/2;


        if(tecla == GBTK_ENTER)
            jugando=1;
        if(tecla == GBTK_ESCAPE)///CERRAR VENTANA CON ESC
            corriendo=0;
        while(jugando)  ///PRESIONAR ENTER PARA JUGAR
        {
            gbt_procesar_entrada();
            tecla=gbt_obtener_tecla_presionada();
            if(tecla == GBTK_p) ///P PARA SALIR DE PAUSA
            {
                pausado=0;
            }
            if(tecla == GBTK_ESCAPE) ///SALIR DEL JUEGO CON ESCAPE (SOLO SI ESTA PAUSADO)
            {
                jugando=0;
            }
            while(!pausado)
            {

                gbt_procesar_entrada();
                tecla=gbt_obtener_tecla_presionada();

                if(tecla == GBTK_p) ///P PARA PAUSAR JUEGO
                {
                    pausado=1;
                }

                ///FUNCIO DIBUJA EL FONDO DEL TETRIZ
                dibujar_tablero(FIL,COL,inicio_x,inicio_y,TAM_CELDA,COLOR);

                ///FUNCION QUE DIBUJA LAS PIEZAS EN SU POSICION FINAL
                dibujar_matriz(matriz,FIL,COL,inicio_x,inicio_y,TAM_CELDA);

                ///FUNCION QUE MUESTA EN EL JUEGO EL MOVIMIENTO DEL TETRAMINO (A MEJORAR)
                dibujar_pieza(pieza,PIEZA,inicio_x, inicio_y,pos_x,pos_y, TAM_CELDA);

                ///PANEL IZQUIERDO
                dibujar_panel_izquierdo(inicio_x,inicio_y,alto_tab);

                ///PANEL DERECHO
                dibujar_panel_derecho(inicio_x,inicio_y,ancho_tab,alto_tab);

                ///TEMPORIZADOR QUE RENTELIZA EL MOVIMIENTO DE LA PIEZA (TESTEO)
                if(gbt_temporizador_consumir(temporizador))
                {
                    pos_y++;
                }
                ///FUNCION QUE SUBE/DIBUJA TODO EN EL TETRIZ
                gbt_volcar_backbuffer();

                gbt_esperar(20);

            }


        }
    }

    gbt_temporizador_destruir(temporizador);
    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;

}

///DONDE DE DICE TESTEO SE BORRA
