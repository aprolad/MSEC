#include "MainWindow.h"

void MainWindow::on_combobox_changed(GtkComboBoxText *combobox, gpointer user_data)
{
    selected_combobox = gtk_combo_box_get_active(GTK_COMBO_BOX(combobox)); // Получение id текущего выбранного элемента списка
    Solver::shell = shells[selected_combobox];

    std::ostringstream oss, vss; // TODO: Написать обертку для stringstream
    oss << std::setprecision(5) << Solver::shell.mass;
    gtk_label_set_text(mass_label, oss.str().c_str());
    vss <<std::setprecision(5) << Solver::shell.charges[0]<<" ~ "<< Solver::shell.charges.back();
    gtk_label_set_text(velocity_label, vss.str().c_str());
}

gboolean MainWindow::on_draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    int width, height;
    gtk_widget_get_size_request(widget, &width, &height);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2.0);

    // Нахождение масштаба графика
    double min_x =0;
    double max_x = 6000;
    double min_y = 0;
    double max_y = 1500;
    double x_scale = width / (max_x - min_x) * 0.9;
    double y_scale = height / (max_x - min_x) * 0.9;

    // Подписи максимальных значений у осей
    cairo_move_to(cr, width-70, height-10);
    cairo_show_text(cr, std::to_string(max_x).c_str());
    cairo_move_to(cr, 0, 20);
    cairo_show_text(cr, std::to_string(max_y).c_str());
    cairo_translate(cr, 0.0, height);

    cairo_scale(cr, 1.0, -1.0);
    cairo_translate(cr, -min_x * x_scale, -min_y * y_scale);

    // Отрисовка графика полета
    for (int c = 0; c < Solver::trajectories.size(); c++)
    {
        cairo_move_to(cr, Solver::trajectories[c].points[0].x * x_scale + 30, Solver::trajectories[c].points[0].y * y_scale + 40);
        for (int i = 0; i < Solver::trajectories[c].points.size(); i++)
        {
            cairo_line_to(cr, Solver::trajectories[c].points[i].x * x_scale + 30, Solver::trajectories[c].points[i].y * y_scale + 40);
        }
    }
    cairo_stroke(cr);
    return true;
}

void MainWindow::on_button_clicked(GtkButton* button, gpointer data)
{
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(distance_entry)); // Получение дистанции из поля ввода
    double dis = atof(text);
    if (dis != 0)
        Solver::calculateTrajectories(dis);

    // Вывод характеристик траекторий в правую таблицу
    for (int i = 0; i<Solver::eligible_timeframe.size(); i++)
    {
        gtk_text_buffer_set_text(MainWindow::time_text_buffers[i], std::to_string(Solver::eligible_timeframe[i].arrival_time).c_str(), -1);
        gtk_text_buffer_set_text(MainWindow::angle_text_buffers[i], std::to_string(Solver::eligible_timeframe[i].angle).c_str(), -1);
        gtk_text_buffer_set_text(MainWindow::charge_text_buffers[i], std::to_string(int(Solver::eligible_timeframe[i].charge)).c_str(), -1);
    }
    GtkWidget* drawing_area = GTK_WIDGET(gtk_builder_get_object(MainWindow::builder, "draw"));
    gtk_widget_queue_draw(drawing_area);
}

void MainWindow::gtk_binding()
{
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    distance_entry = GTK_WIDGET(gtk_builder_get_object(builder, "1"));
    mass_label = GTK_LABEL(gtk_builder_get_object(builder, "mass"));
    velocity_label = GTK_LABEL(gtk_builder_get_object(builder, "velocity"));
    text_view = GTK_WIDGET(gtk_builder_get_object(builder, "angleRes"));
    draw_area = GTK_WIDGET(gtk_builder_get_object(builder, "draw"));
    combobox = GTK_WIDGET(gtk_builder_get_object(builder, "combobox"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "calcButton"));
    // Получение хэндлов из glade с названиями по типу t0, t1..,t4
    for (int i = 0; i<5; i++)
    {
        time_text_views[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("t") + std::to_string(i)).c_str()));
        time_text_buffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(time_text_views[i]));
        angle_text_views[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("a") + std::to_string(i)).c_str()));
        angle_text_buffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(angle_text_views[i]));
        charge_text_views[i] = GTK_WIDGET(gtk_builder_get_object(builder, std::string(std::string("c") + std::to_string(i)).c_str()));
        charge_text_buffers[i] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(charge_text_views[i]));
    }
}

void MainWindow::gtk_signal_connect()
{
    g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(combobox, "changed", G_CALLBACK(on_combobox_changed), NULL);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
}

void MainWindow::on_window_destroy(GtkWidget* widget, gpointer data)
    {
        gtk_main_quit();
    }

void MainWindow::launch(int argc, char* argv[])
    {

        // Вшитые значения для двух видов орудий
        // TODO: Загрузчик и парсер из текстового файла
        shells[0].charges = {135, 179, 216, 261};
        shells[0].calibre = 0.082;
        shells[0].mass = 3.1;
        shells[1].charges = {191, 221, 247, 272};
        shells[1].calibre = 0.120;
        shells[1].mass = 15.9;
        Solver::shell = shells[0]; // Орудие по умолчанию до выбора из списка


        gtk_init(&argc, &argv);
        builder = gtk_builder_new_from_file("ui1.glade");

        gtk_binding();

        gtk_signal_connect();

        gtk_widget_show_all(window);
        gtk_main();
    }
