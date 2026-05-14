#ifndef DIBUJOS_H_INCLUDED
#define DIBUJOS_H_INCLUDED
#include "GBT/gbt.h"

void dibujar_cuadrado (int X, int Y, int color, int tam_cel);
void dibujar_tablero(int cf, int cc,int ini_x, int ini_y,int tam_celda,int color);
void dibujar_matriz(int mat[][10],int cf, int cc,int ini_x, int ini_y,int tam_celda);
void dibujar_pieza(int pieza[][4],int ce,int ini_x, int ini_y,int pos_x, int pos_y, int tam_cel);
void dibujar_rectangulo (int ini_x, int ini_y, int ancho_rec, int altura_rec, int color);
void dibujar_panel_izquierdo(int inicio_x, int inicio_y,int alto_tab);
void dibujar_panel_derecho(int inicio_x, int inicio_y,int ancho_tab,int alto_tab);

void fijar(int mat[][10], int FIL, int COL, int pieza[][4], int pos_y, int pos_x);
void caidaFicha (tGBT_Temporizador *temporizador, int *pos_y, int lim_inferiorY);
void moverPieza (int *pos_x, int limDer, int pieza [4][4], int PIEZA);
int colision (int mat [][10], int cf, int cc, int pieza [][4], int pos_y, int pos_x);

#endif // DIBUJOS_H_INCLUDED
