 #include "Solver.h"

trajectory Solver::calculate(double angle, double bVel)
        {
            double time = 0;
            physVector velocity(0,0);
            physVector position(0,0);
            velocity.x = bVel * cos((angle) *(M_PI / 180));
            velocity.y = bVel * cos((90 - angle) *(M_PI / 180));
            double g = 9.81;
            double timestep = 0.1;
            trajectory history;
            history.angle = angle;
            history.charge = bVel;
            history.points.push_back(physVector(0,0));
            double p = 1.1;
            double f;
            double mvel = velocity.x;
            bool terminated;
            while (!terminated)
            {
                time +=timestep;
                double V = velocity.mod();
                f = (0.39* pow(shell.calibre, 2)/shell.mass * 1000) * p * ( 0.2002*V - 48.05 + sqrt(pow(0.1648*V-47.95, 2) + 9.6 ) + 0.0442*V*(V-300)/(371+pow(V/200,10))); //Расчет сопротивления воздуха по формуле Сиаччи
               // f = p * pow(velocity.mod(), 2) / 2 * (M_PI * pow(d, 2)/4) * 0.15 / m; // Расчет сопротивления воздуха по базовой формуле

                velocity.x +=- f * cos(velocity.angle()) * timestep;
                velocity.y +=- f * cos(M_PI_4 - velocity.angle()) * timestep;
                velocity.y -= g * timestep;
                position.x = position.x + velocity.x * timestep;
                position.y = position.y + velocity.y * timestep;

                position.t = time;
                position.mv = mvel;
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
