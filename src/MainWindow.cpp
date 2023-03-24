#include "MainWindow.h"
gboolean MainWindow::on_draw(GtkWidget* widget, cairo_t* cr, gpointer data)
    {
         int width, height;
        gtk_widget_get_size_request(widget, &width, &height);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2.0);

        double min_x =0;
        double max_x = 6000;
        double min_y = 0;
        double max_y = 1500;
        double x_scale = width / (max_x - min_x) * 0.9;
        double y_scale = height / (max_x - min_x) * 0.9;

        cairo_move_to(cr, width-70, height-10);
        cairo_show_text(cr, std::to_string(max_x).c_str());
        cairo_move_to(cr, 0, 20);
        cairo_show_text(cr, std::to_string(max_y).c_str());
        // Translate the coordinate system so that (0, height) is at the lower left corner
        cairo_translate(cr, 0.0, height);
        cairo_scale(cr, 1.0, -1.0);

        // Move the coordinate system to the minimum x and y values
        cairo_translate(cr, -min_x * x_scale, -min_y * y_scale);

        for (int c = 0; c < Solver::trajectories.size(); c++)
        {
            cairo_move_to(cr, Solver::trajectories[c].points[0].x * x_scale + 30, Solver::trajectories[c].points[0].y * y_scale + 40);
            for (int i = 0; i < Solver::trajectories[c].points.size(); i++) {
                cairo_line_to(cr, Solver::trajectories[c].points[i].x * x_scale + 30, Solver::trajectories[c].points[i].y * y_scale + 40);
            }
        }
        cairo_stroke(cr);
        return true;
    }
void MainWindow::on_button_clicked(GtkButton* button, gpointer data)
        {

            const gchar* text = gtk_entry_get_text(GTK_ENTRY(MainWindow::entry1));
            double dis = atof(text);
            if (dis != 0)

                Solver::calculateTrajectories(dis);
            g_print("Button clicked\n");
            for (int i = 0; i<Solver::eligible_timeframe.size(); i++)
            {
                    gtk_text_buffer_set_text(MainWindow::buffers[i], std::to_string(Solver::eligible_timeframe[i].arrival_time).c_str(), -1);
                    gtk_text_buffer_set_text(MainWindow::angleTextBuffers[i], std::to_string(Solver::eligible_timeframe[i].angle).c_str(), -1);
                    gtk_text_buffer_set_text(MainWindow::chargeTextBuffers[i], std::to_string(int(Solver::eligible_timeframe[i].charge)).c_str(), -1);
            }
            GtkWidget* drawing_area = GTK_WIDGET(gtk_builder_get_object(MainWindow::builder, "draw"));
            gtk_widget_queue_draw(drawing_area);
        }

void MainWindow::launch(int argc, char* argv[])
        {
            shells[0].charges = {135, 179, 216, 261};
            shells[0].calibre = 0.082;
            shells[0].mass = 3.1;

            shells[1].charges = {191, 221, 247, 272};
            shells[1].calibre = 0.120;
            shells[1].mass = 15.9;
            Solver::shell = shells[0];
            gtk_init(&argc, &argv);

            builder = gtk_builder_new_from_file("bin/ui1.glade");

            window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
            entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "1"));



            massLabel = GTK_LABEL(gtk_builder_get_object(builder, "mass"));
            velocityLabel = GTK_LABEL(gtk_builder_get_object(builder, "velocity"));

            textView = GTK_WIDGET(gtk_builder_get_object(builder, "angleRes"));
            draw_area = GTK_WIDGET(gtk_builder_get_object(builder, "draw"));
            for (int i = 0; i<5; i++)
            {
                timeTextViews[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("t") + std::to_string(i)).c_str()));
                buffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(timeTextViews[i]));

                angleTextViews[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("a") + std::to_string(i)).c_str()));
                angleTextBuffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(angleTextViews[i]));

                chargeTextViews[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("c") + std::to_string(i)).c_str()));
                chargeTextBuffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chargeTextViews[i]));

            }

            g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw), NULL);
            combobox = GTK_WIDGET(gtk_builder_get_object(builder, "combobox"));
            g_signal_connect(combobox, "changed", G_CALLBACK(on_combobox_changed), NULL);
            GtkWidget* button = GTK_WIDGET(gtk_builder_get_object(builder, "calcButton"));
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
            g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

            gtk_widget_show_all(window);
            gtk_main();
        }
