#include "Header.h"
#include "Solver.h"
class MainWindow
{
    public:

        // Блок обьявления указателей на виджеты(хэндлы для управления объектами интерфейса)
        static inline GtkWidget* draw_area;
        static inline GtkWidget* window;
        static inline GtkBuilder* builder;
        static inline GtkWidget* distance_entry;
        static inline GtkWidget* textView;
        static inline GtkWidget* timeTextViews[5];
        static inline GtkTextBuffer *buffers[5];
        static inline GtkWidget* angleTextViews[5];
        static inline GtkTextBuffer *angleTextBuffers[5];
        static inline GtkWidget* chargeTextViews[5];
        static inline GtkTextBuffer *chargeTextBuffers[5];
        static inline GtkWidget *combobox;
        static inline GtkWidget* button;
        static inline GtkLabel *massLabel;
        static inline GtkLabel *velocityLabel;

        static inline int selected_combobox;
        static inline shell shells[2];

        void static launch(int argc, char* argv[]);

    private:

        static void gtk_binding(); // Получение хэндлов из glade

        static void gtk_signal_connect(); //Назначение callback

        static void on_window_destroy(GtkWidget* widget, gpointer data);

        static void on_combobox_changed(GtkComboBoxText *combobox, gpointer user_data); // Обработчик выпадающего списка

        static void on_button_clicked(GtkButton* button, gpointer data); // Обработчик кнопки расчета

        static gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer data); // Рисование
};
