#include "main.h"

void LoadPics()
{
    board.image = cairo_image_surface_create_from_png("field.png");
    board.img_width = cairo_image_surface_get_width(board.image);
    board.img_height = cairo_image_surface_get_height(board.image);

    face.image = cairo_image_surface_create_from_png("face_fill.png");
    face.img_width = cairo_image_surface_get_width(face.image);
    face.img_height = cairo_image_surface_get_height(face.image);

    stars.image = cairo_image_surface_create_from_png("stars.png");
    stars.img_width = cairo_image_surface_get_width(stars.image);
    stars.img_height = cairo_image_surface_get_height(stars.image);
}

G_MODULE_EXPORT void on_drawingarea1_expose_event(GtkWidget* widget, GdkEventExpose* event, gpointer data)
{
    //ShowEmptyBoard();
    ShowAllBoard();
}

G_MODULE_EXPORT void on_drawingarea2_expose_event(GtkWidget* widget, GdkEventExpose* event, gpointer data)
{
    FaceShow(1, diffLevel == 0 ? 1 : diffLevel);
}

G_MODULE_EXPORT void on_drawingarea3_expose_event(GtkWidget* widget, GdkEventExpose* event, gpointer data)
{
    ShowStars(helpItem);
}

void NewGame()
{
    srand(time(0)); //Инициализируем датчик случайных чисел
    pointerX = -1;
    pointerY = -1;
    moveCounter = 0;
    ShowEmptyBoard();
    FieldInit();
    ShowInitialNumbersOnBoard();
    FaceShow(1, diffLevel);
    helpItem = 5;
    ShowStars(helpItem);
    gameStatus = 1;
}

G_MODULE_EXPORT void on_menuitem2_activate (GtkObject *object, gpointer user_data)
{
    useHelp();
}

G_MODULE_EXPORT void on_newlevel1_activate (GtkObject *object, gpointer user_data)
{
    diffLevel = 1;
    NewGame();
}

G_MODULE_EXPORT void on_newlevel2_activate (GtkObject *object, gpointer user_data)
{
    diffLevel = 2;
    NewGame();
}

G_MODULE_EXPORT void on_newlevel3_activate (GtkObject *object, gpointer user_data)
{
    diffLevel = 3;
    NewGame();
}

G_MODULE_EXPORT void on_newlevel4_activate (GtkObject *object, gpointer user_data)
{
    diffLevel = 4;
    NewGame();
}

G_MODULE_EXPORT void on_newlevel5_activate (GtkObject *object, gpointer user_data)
{
    diffLevel = 5;
    NewGame();
}

G_MODULE_EXPORT void on_imagemenuitem5_activate (GtkObject *object, gpointer user_data)
{
    gtk_main_quit();
}

G_MODULE_EXPORT void on_imagemenuitem10_activate (GtkObject *object, gpointer user_data)
{
    gtk_window_set_position(GTK_WINDOW(aboutdialog), GTK_WIN_POS_CENTER);
    gtk_widget_show (aboutdialog);
    g_signal_connect_swapped (aboutdialog,"response", G_CALLBACK (gtk_widget_destroy),aboutdialog);
}

G_MODULE_EXPORT void on_menuitem5_activate (GtkObject *object, gpointer user_data)
{
    colorProfile = 0;
    ShowAllBoard();
}

G_MODULE_EXPORT void on_menuitem6_activate (GtkObject *object, gpointer user_data)
{
    colorProfile = 1;
    ShowAllBoard();
}

G_MODULE_EXPORT void on_button1_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(1);
}

G_MODULE_EXPORT void on_button2_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(2);
}

G_MODULE_EXPORT void on_button3_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(3);
}

G_MODULE_EXPORT void on_button4_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(4);
}

G_MODULE_EXPORT void on_button5_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(5);
}

G_MODULE_EXPORT void on_button6_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(6);
}

G_MODULE_EXPORT void on_button7_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(7);
}

G_MODULE_EXPORT void on_button8_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(8);
}

G_MODULE_EXPORT void on_button9_clicked (GtkButton *button, gpointer label)
{
    ButtonClick(9);
}

gboolean mouse_button_press_event (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (event->button == 1 && gameStatus == 1)
    {
        MouseClick(event->x, event->y);
    }
    return TRUE;
}

gboolean mouse_button_press_event_face (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (event->button == 1)
    {
       FaceClick();
    }
    return TRUE;
}

int ShowMainWindow()
{
    GtkBuilder  *builder;
    GdkPixbuf *icon;

	builder = gtk_builder_new ();
	if (gtk_builder_add_from_file (builder, "main.glade", NULL))
	{
        builder = gtk_builder_new ();

        gtk_builder_add_from_file(builder, "main.glade", NULL);
        window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
        aboutdialog = GTK_WIDGET(gtk_builder_get_object(builder, "aboutdialog1"));
        area1 = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea1"));
        area2 = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea2"));
        area3 = GTK_WIDGET(gtk_builder_get_object(builder, "drawingarea3"));
        vbox1 = GTK_WIDGET(gtk_builder_get_object(builder, "vbox1"));
        vbox2 = GTK_WIDGET(gtk_builder_get_object(builder, "vbox2"));
        hbox1 = GTK_WIDGET(gtk_builder_get_object(builder, "hbox2"));
        //button1 =  GTK_WIDGET(gtk_builder_get_object(builder, "button1"));

        gtk_window_set_title(GTK_WINDOW(window1), "Sudoku");
        gtk_window_set_icon_from_file(GTK_WINDOW(window1), "icon.png", NULL);

        LoadPics();
        gtk_window_set_default_size (GTK_WINDOW (window1), board.img_width + 200, board.img_height + 40);
        gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);

        gtk_builder_connect_signals (builder, NULL);
        g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect (area1, "button-press-event", G_CALLBACK (mouse_button_press_event), NULL);
        g_signal_connect (area2, "button-press-event", G_CALLBACK (mouse_button_press_event_face), NULL);

        gtk_widget_set_events (area1, gtk_widget_get_events (area1)
                             | GDK_LEAVE_NOTIFY_MASK
                             | GDK_BUTTON_PRESS_MASK
                             | GDK_POINTER_MOTION_MASK
                             | GDK_POINTER_MOTION_HINT_MASK);

        gtk_widget_set_events (area2, gtk_widget_get_events (area2)
                             | GDK_LEAVE_NOTIFY_MASK
                             | GDK_BUTTON_PRESS_MASK
                             | GDK_POINTER_MOTION_MASK
                             | GDK_POINTER_MOTION_HINT_MASK);

        gtk_widget_set_events (area3, gtk_widget_get_events (area3)
                             | GDK_LEAVE_NOTIFY_MASK
                             | GDK_BUTTON_PRESS_MASK
                             | GDK_POINTER_MOTION_MASK
                             | GDK_POINTER_MOTION_HINT_MASK);


        gtk_widget_show (window1);

        return 1;
	}
    else
	{
	    return 0;
	}
}

int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    if (ShowMainWindow ())
    {
       gtk_main ();
       return 0;
    }
    else
    {
       ShowError();
       return 1;
    }
}
