#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "main.h"

int ShowError();
void ShowEmptyBoard();
void ShowInitialNumbersOnBoard();
void ShowOneSymbol(int i, int j, int color, int sym, cairo_t *cr);
void MouseClick(gdouble x, gdouble y);
void ButtonClick(int num);
void ShowAllBoard();
void FaceShow(int x, int y);
int ShowWin();
void FaceClick();
void ShowStars(int n);
int ShowNoHelp();
void setColor(int sym, int type, cairo_t *cr);

#endif // VIEW_H_INCLUDED
