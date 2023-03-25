#ifndef MAINWINDOW
#define MAINWINDOW

#include "Header.h"
#include "Solver.h"
class MainWindow
{
    public:

        // ���� ���������� ���������� �� �������(������ ��� ���������� ��������� ����������)
        static inline GtkWidget* draw_area;
        static inline GtkWidget* window;
        static inline GtkBuilder* builder;
        static inline GtkWidget* distance_entry;
        static inline GtkWidget* text_view;
        static inline GtkWidget* time_text_views[5];
        static inline GtkTextBuffer* time_text_buffers[5];
        static inline GtkWidget* angle_text_views[5];
        static inline GtkTextBuffer *angle_text_buffers[5];
        static inline GtkWidget* charge_text_views[5];
        static inline GtkTextBuffer *charge_text_buffers[5];
        static inline GtkWidget *combobox;
        static inline GtkWidget* button;
        static inline GtkLabel *mass_label;
        static inline GtkLabel *velocity_label;

        static inline int selected_combobox;
        static inline shell shells[2];

        void static launch(int argc, char* argv[]);

    private:

        static void gtk_binding(); // ��������� ������� �� glade

        static void gtk_signal_connect(); //���������� callback

        static void on_window_destroy(GtkWidget* widget, gpointer data);

        static void on_combobox_changed(GtkComboBoxText *combobox, gpointer user_data); // ���������� ����������� ������

        static void on_button_clicked(GtkButton* button, gpointer data); // ���������� ������ �������

        static gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer data); // ���������
};

#endif
