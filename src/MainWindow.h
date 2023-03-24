#include "Header.h"
#include "Solver.h"
class MainWindow
    {
    public:
        static inline shell shells[2];
        static inline GtkWidget* draw_area;
        static inline GtkWidget* window;
        static inline GtkBuilder* builder;
        static inline GtkWidget* entry1;

        static inline GtkWidget* textView;
        static inline GtkWidget* timeTextViews[5];
        static inline GtkTextBuffer *buffers[5];

        static inline GtkWidget* angleTextViews[5];
        static inline GtkTextBuffer *angleTextBuffers[5];

        static inline GtkWidget* chargeTextViews[5];
        static inline GtkTextBuffer *chargeTextBuffers[5];
        static inline GtkWidget *combobox;

        static inline GtkLabel *massLabel;
        static inline GtkLabel *velocityLabel;
        static inline int selected_combobox;
        void static launch(int argc, char* argv[]);

        static void on_button_clicked(GtkButton* button, gpointer data);

        static gboolean on_draw(GtkWidget* widget, cairo_t* cr, gpointer data);
    private:
        static void on_window_destroy(GtkWidget* widget, gpointer data)
        {
            gtk_main_quit();
        }
        static void on_combobox_changed(GtkComboBoxText *combobox, gpointer user_data)
         {
            selected_combobox = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox));
            Solver::shell = shells[selected_combobox];

            std::ostringstream oss, vss;
            oss << std::setprecision(5) << Solver::shell.mass;
            gtk_label_set_text(massLabel, oss.str().c_str());
            vss << std::setprecision(5) << Solver::shell.charges[0];
            gtk_label_set_text(velocityLabel, vss.str().c_str());


        }
    };
