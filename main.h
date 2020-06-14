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

#define ROWS        9   //���������� �����
#define SYM_SIZE    40    //������ �����
#define CELL_SIZE   50    //������ ������
#define FACE_H      145    //������ ��������
#define FACE_W      115    //������ ��������

int Board[ROWS][ROWS]; //������, c ������� �����
int Request[ROWS][ROWS]; //������ � ��������
int Status[ROWS][ROWS]; //������ �� �������� �����
int helpItem; // ���������
int diffLevel; // ������� ���������
int pointerX; // ��������� �� ��������� ������
int pointerY; // ��������� �� ��������� ������
int isRequest; // ���� �� ������
int moveCounter; // ������� �����
int gameStatus; // 0 - ���� ��� 1 - ���� ���
int colorProfile; // 0 - �� 1 - �������

struct
{
    cairo_surface_t *image;
    gint img_width;
    gint img_height;
} board, stars, face;

GtkWidget   *window1, *aboutdialog, *vbox1, *vbox2, *hbox1;
GtkWidget   *area1, *area2, *area3, *button1;

#endif // MAIN_H_INCLUDED
