 #include "Solver.h"

trajectory Solver::calculate(double angle, double barrel_velocity)
{
    double time = 0;
    physVector velocity(0,0);
    physVector position(0,0);
    velocity.x = barrel_velocity * cos((angle) *(M_PI / 180)); // Разложение начальной скорости на вектора
    velocity.y = barrel_velocity * cos((90 - angle) *(M_PI / 180));
    double g = 9.81;
    double timestep = 0.1;
    trajectory history;
    history.angle = angle;
    history.charge = barrel_velocity;
    history.points.push_back(physVector(0,0));
    double p = 1.1; // Плотность воздуха TODO:Реализовать зависимость плотность воздуха от высоты
    double a;
    bool terminated;
    while (!terminated)
    {
        time +=timestep;
        double V = velocity.mod(); // Модуль скорости
        a = (0.39* pow(shell.calibre, 2)/shell.mass * 1000) * p * ( 0.2002*V - 48.05 + sqrt(pow(0.1648*V-47.95, 2) + 9.6 ) + 0.0442*V*(V-300)/(371+pow(V/200,10))); //Расчет сопротивления воздуха по формуле Сиаччи
       // f = p * pow(velocity.mod(), 2) / 2 * (M_PI * pow(d, 2)/4) * 0.15 / m; // Расчет сопротивления воздуха по базовой формуле

        velocity.x +=- a * cos(velocity.angle()) * timestep; // Разложение ускорения от сопротивления воздуха на компоненты
        velocity.y +=- a * cos(M_PI_4 - velocity.angle()) * timestep;
        velocity.y -= g * timestep; // Гравитация
        position.x = position.x + velocity.x * timestep;
        position.y = position.y + velocity.y * timestep;
        position.t = time;

        if (position.y < 0 || time > 1000)
        {
            terminated = true;
            history.arrival_time = position.t;
        }
        else
            history.points.push_back(position);
    }
    return history;
}
// Брутфорс расчет траекторий
// TODO: Переписать с нуля быстрой сортировкой

void Solver::calculateTrajectories(double dis)
{
    trajectories.clear();
    eligible_timeframe.clear();
    trajectory t;
    double det = 0.01;
    for (int c = 0; c < shell.charges.size(); c++)
    {
        for (double i = 0; i<45; i+= det)
        {
            t = calculate(i, shell.charges[c]);
            if (t.points.back().x > dis)
            {
                trajectories.push_back(t);
                break;
            }
        }
        for (double i = 90; i>45; i-=det)
        {
            t = calculate(i, shell.charges[c]);
            if (t.points.back().x > dis)
            {
                trajectories.push_back(t);
                break;
            }
        }
    }

    std::sort(trajectories.begin(), trajectories.end(), [](const trajectory& t1, const trajectory& t2) -> bool
    { return t1.arrival_time < t2.arrival_time; }); // Сортировка траекторий по времени полета снаряда
    double last_arrival_time = 0;

    // Отбор траекторий с разницей во времени более 5 секунд
    for (int i = 0; i<trajectories.size(); i++)
    {
        if (trajectories[i].arrival_time - last_arrival_time > 5)
        {
            eligible_timeframe.push_back(trajectories[i]);
            last_arrival_time = trajectories[i].arrival_time;
        }
    }
}
