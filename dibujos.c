#include "dibujos.h"
#include "GBT/gbt.h"
#include <stdio.h>
#define FIL 22
#define COL 10
#define PIEZA 4
#define TAM_CELDA 7

void dibujar_cuadrado (int X, int Y, int color, int tam_cel)
{
    for(int dy=1; dy<tam_cel-1; dy++)///Dibuja un cuadrado relleno (sin bordes) de tamaño tam_cel en (X,Y)
    {
        for(int dx=1; dx<tam_cel-1; dx++)
            gbt_dibujar_pixel(X+dx, Y+dy, color);
    }
}

void dibujar_tablero(int cf, int cc,int ini_x, int ini_y,int tam_celda,int color) ///FUNCION ESTETICO DIBUJA FONDO TABLERO
{
    int X,Y;
    for(int i=0; i<cf; i++)
    {
        for(int j=0; j<cc; j++)
        {
            if(i>=2) ///Ignora las primeras 2 filas (zona superior oculta del tablero)
            {
                X=ini_x+j*tam_celda;/// Calcula la posición en píxeles en X
                Y=ini_y+(i-2)*tam_celda;///Calcula la posición en píxeles en Y (ajustada por las 2 filas ocultas)

                dibujar_cuadrado (X,Y,color,tam_celda);
            }
        }
    }
}

void dibujar_matriz(int mat[][COL],int cf, int cc,int ini_x, int ini_y,int tam_celda)
{
    int X,Y;
    for(int i=0; i<cf; i++)
    {
        for(int j=0; j<cc; j++)
        {
            if(mat[i][j]!=0) ///Dibuja solo las celdas ocupadas (valor distinto de 0)
            {
                int color=mat[i][j];///SELECCION DE COLOR (USO TEMPORAL)

                X=ini_x+j*tam_celda;///Calcula la posición en píxeles en X
                Y=ini_y+(i-2)*tam_celda;///Calcula la posición en píxeles en Y (ajustada por las 2 filas ocultas)

                dibujar_cuadrado(X,Y,color,tam_celda);
            }
        }
    }
}


void dibujar_pieza(int pieza[][PIEZA],int ce,int ini_x, int ini_y,int pos_x, int pos_y, int tam_cel)
{
    for(int i=0; i<ce; i++)
    {
        for(int j=0; j<ce; j++)
        {
            int color= pieza[i][j];
            if(pieza[i][j]!=0)
            {
                ///POSICIONA EN LA ESQUINA SUPERIOR IZQUIERDO DE C/BLOQUE DE LA PIEZA
                int X=ini_x+(pos_x+j)*tam_cel;
                int Y=ini_y+(pos_y+i)*tam_cel;

                dibujar_cuadrado (X,Y,color,tam_cel);
            }
        }
    }
}

void dibujar_rectangulo (int ini_x, int ini_y, int ancho_rec, int altura_rec, int color)
{
    for(int i=0; i<ancho_rec; i++) ///Dibuja las líneas horizontal superior e inferior del rectángulo
    {
        gbt_dibujar_pixel(ini_x+i,ini_y,color); //linea superior
        gbt_dibujar_pixel(ini_x+i,ini_y+altura_rec,color);//linea inferior
    }
    for (int j=0; j<altura_rec; j++) /// Dibuja las líneas verticales izquierda y derecha
    {
        gbt_dibujar_pixel(ini_x,ini_y+j,color);//LIENA IZQUIERDA
        gbt_dibujar_pixel(ini_x+ancho_rec,ini_y+j,color);//LINEA DERECHA
    }
}

void dibujar_panel_izquierdo(int inicio_x, int inicio_y,int alto_tab)
{
    int margen=TAM_CELDA*0.5;
    int panel_w= TAM_CELDA*8;

    int panel_x=inicio_x - panel_w - margen;
    int panel_y = inicio_y;

    /// Dibuja el marco del panel izquierdo
    dibujar_rectangulo(panel_x,panel_y,panel_w,alto_tab,15);
}

void dibujar_panel_derecho(int inicio_x, int inicio_y,int ancho_tab,int alto_tab)
{
    int margen=TAM_CELDA*0.5;
    int panel_w= TAM_CELDA*8;

    int panel_x=inicio_x + ancho_tab + margen;
    int panel_y = inicio_y;

    /// Dibuja el marco del panel derecho
    dibujar_rectangulo(panel_x,panel_y,panel_w,alto_tab,15);
}

void moverPieza (int *pos, int limDer, int pieza[PIEZA][PIEZA], int cf)
{
    //falta correjir, hace falta saber cual es la pos mas a la derecha posible y la mas a la izq
    int aux;
    int col=-1; //columna de la pieza mas a la der o izq segun mov
    int i=0, j=0;
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla==GBTK_IZQUIERDA)
    {
        aux=*pos-1;
        //verifica la posicion mas a la izq de la pieza
        while(j<cf && col==-1)
        {
            i=0;
            while(i<cf && col==-1)
            {
                if(pieza[i][j]!=0)
                {
                    col=j;
                }
                i++;

            }
            j++;
        }
        if(aux>=col)
            *pos=aux;
    }

    if(tecla==GBTK_DERECHA)
    {
        aux=*pos+1;
        j=cf-1;
        //verifica la posicion mas a la derecha de la pieza
         while(j>=0 && col==-1)
        {
            i=0;
            while(i<cf && col==-1)
            {
                if(pieza[i][j]!=0)
                {
                    col=j;
                }
                i++;
            }
            j--;
        }
        if(aux<=limDer+col)
            *pos=aux;
    }
}
