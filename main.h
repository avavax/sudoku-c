#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "view.h"
#include "model.h"

#define _LOCALE_TO_UTF8(str) g_locale_to_utf8((const char *)(str), -1, NULL, NULL, NULL)
#define _UTF8_TO_LOCALE(str) g_locale_from_utf8((const char *)(str), -1, NULL, NULL, NULL)
#define _UTF8(str) _LOCALE_TO_UTF8((str))
#define _LOCALE(str) _UTF8_TO_LOCALE((str))
#define _U(str) _UTF8((str))
#define _L(str) _LOCALE((str)) )

#define ROWS        9   //количество р€дов
#define SYM_SIZE    40    //размер цифры
#define CELL_SIZE   50    //размер €чейки
#define FACE_H      145    //высота картинки
#define FACE_W      115    //высота картинки

int Board[ROWS][ROWS]; //массив, c игровым полем
int Request[ROWS][ROWS]; //массив с решением
int Status[ROWS][ROWS]; //массив со статусом €чеек
int helpItem; // подсказки
int diffLevel; // уровень сложности
int pointerX; // указатель на выбранную €чейку
int pointerY; // указатель на выбранную €чейку
int isRequest; // есть ли запрос
int moveCounter; // счетчик ходов
int gameStatus; // 0 - игры нет 1 - игра идЄт
int colorProfile; // 0 - чб 1 - цветна€

struct
{
    cairo_surface_t *image;
    gint img_width;
    gint img_height;
} board, stars, face;

GtkWidget   *window1, *aboutdialog, *vbox1, *vbox2, *hbox1;
GtkWidget   *area1, *area2, *area3, *button1;

#endif // MAIN_H_INCLUDED
