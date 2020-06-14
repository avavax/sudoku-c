#include "view.h"

int ShowError()
{
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
                                 GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                 _U(" Ошибка программы :( \n Обратитесь к разработчику!"));

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return 0;
}

int ShowWin()
{
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
                                 GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 _U(" Поздравляю! \n Заслуженная победа!"));

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return 0;
}

int ShowNoHelp()
{
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
                                 GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                 _U(" Подсказки кончились! \n Дальше думай сам"));

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return 0;
}

void ShowEmptyBoard()
{
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area1));
    // Вывод игрового поля
    cairo_set_source_surface(cr, board.image, 0, 0);
    cairo_paint(cr);

    cairo_destroy (cr);
}

void ShowAllBoard()
{
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area1));
    cairo_set_source_surface(cr, board.image, 0, 0);
    cairo_paint(cr);
    cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 40.0);

    char buf[10];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if(Request[i][j] == 0) continue;
            cairo_move_to(cr, 15 + CELL_SIZE * j , 43 + CELL_SIZE * i);

            setColor(Request[i][j], 1 - Status[i][j], cr);

            /*if(Status[i][j] == 1) {
                cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
            } else {
                cairo_set_source_rgb(cr, 0, 0, 0);
            }*/

            if(pointerX == i && pointerY == j) {
                sprintf(buf, "%c", '?');
            } else {
                sprintf(buf, "%d", Request[i][j]);
            }
            cairo_show_text(cr, buf);
            cairo_stroke(cr);
        }
    }

    if (pointerX != -1 && gameStatus != 0) {
        cairo_move_to(cr, 15 + CELL_SIZE * pointerY , 43 + CELL_SIZE * pointerX);
        setColor(-1, 1, cr);
        ShowOneSymbol(pointerX, pointerY, 1, -1, cr);
    }

    cairo_destroy (cr);
}

void ShowInitialNumbersOnBoard()
{
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area1));

    cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 40.0);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            ShowOneSymbol(i, j, 0, Request[i][j], cr);
        }
    }
    cairo_destroy (cr);
}

void ShowOneSymbol(int i, int j, int color, int sym, cairo_t *cr)
{
    if(sym == 0) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_rectangle(cr, 5 + CELL_SIZE * j, 5 + CELL_SIZE * i, 45, 45 );
        cairo_fill(cr);
        return;
    }

    char buf[10];

    setColor(sym, color, cr);

    if(sym == -1) {
        sprintf(buf, "%c", '?');
    } else {
        sprintf(buf, "%d", sym);
    }

    cairo_move_to(cr, 15 + CELL_SIZE * j , 43 + CELL_SIZE * i);
    cairo_show_text(cr, buf);
    cairo_stroke(cr);
}

void MouseClick(gdouble x, gdouble y)
{
    if(Board[0][0] == 0) {
        return;
    }

    int x0, y0;

    x0 = y / CELL_SIZE;
    y0 = x / CELL_SIZE;

    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area1));
    cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 40.0);

    if(Status[x0][y0] == 1) {
        cairo_destroy (cr);
        return;
    }

    if(Status[x0][y0] == 2) {
        ShowOneSymbol(x0, y0, 1, 0, cr);
        Status[x0][y0] = 0;
        pointerX = -1;
        pointerY = -1;
       cairo_destroy (cr);
       return;
    }

    if(pointerX == x0 && pointerY ==y0) {
       ShowOneSymbol(pointerX, pointerY, 1, 0, cr);
       pointerX = -1;
       pointerY = -1;
       cairo_destroy (cr);
       return;
    }
    if (pointerX != -1) {
        ShowOneSymbol(pointerX, pointerY, 1, 0, cr);
    }

    pointerX = x0;
    pointerY = y0;
    ShowOneSymbol(pointerX, pointerY, 1, -1, cr);
    cairo_destroy (cr);

}

void ButtonClick(int num)
{
    if (pointerX == -1) {
        return;
    }

    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area1));
    cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 40.0);

    Status[pointerX][pointerY] = 2;
    Request[pointerX][pointerY] = num;
    ShowOneSymbol(pointerX, pointerY, 0, 0, cr);
    ShowOneSymbol(pointerX, pointerY, 1, num, cr);

    pointerX = -1;
    pointerY = -1;


    if (isWinner()) {
       ShowWin();
       FaceShow(7, diffLevel);
       gameStatus = 0;
    } else {
        int fasePosition = rand() % 3 + 1;
        FaceShow(fasePosition, diffLevel);
    }
}

void FaceShow(int x, int y)
{
    int height, width, dx, dy;
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area2));
    height = FACE_H;
    dy = 25 - (y - 1) * FACE_H;

    switch (x) {
        case 1:
        case 2:
        case 3:
            width = FACE_W;
            dx = 45 - (x - 1) * FACE_W;
            break;
        case 4:
        case 5:
            width = 125;
            dx = 45 - 345 - (x - 4) * width;
            break;
        case 6:
        case 7:
            width = FACE_W;
            //height = 160;
            dx = 45 - 590 - (x - 6) * width;
            break;
        case 8:
        case 9:
            width = FACE_W;
            dx = 45 - 820 - (x - 8) * width;
            break;
        default:
            width = FACE_W;
            dx = 45 - (x - 1) * FACE_W;
            break;
     }

    cairo_set_source_surface(cr, face.image, dx, dy);
    cairo_rectangle (cr, 45, 25, width, height);

    cairo_fill(cr);
    cairo_destroy (cr);
}

void FaceClick() {
    FaceShow(4, diffLevel);
    usleep(500000);
    FaceShow(5, diffLevel);
    usleep(500000);
    FaceShow(8, diffLevel);
}

void ShowStars(int n)
{
    cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(area3));

    cairo_set_source_surface(cr, stars.image, 30, -29 * n);
    cairo_rectangle (cr, 30, 0, 140, 29);

    cairo_fill(cr);
    cairo_destroy (cr);
}

void setColor(int sym, int type, cairo_t *cr)
{
    if(colorProfile == 1) {
        // если цветная схема. начало
        if(type) {
            cairo_set_source_rgb(cr, 1, 0, 0);
        } else {
            cairo_set_source_rgba(cr, 0, 0, 1, 0.6);
        }
        if(sym == -1) {
            cairo_set_source_rgb(cr, 0, 0.5, 0.5);
        }
        // если цветная схема. конец
    } else {
        if(type) {
            cairo_set_source_rgb(cr, 0, 0, 0);
        } else {
            //cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
            cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
        }
    }

}




