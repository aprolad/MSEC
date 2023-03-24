#ifndef SOLVER
#define SOLVER

#include "Header.h"
struct shell
{
    double barrel_velocity;
    std::vector<double> charges;
    double calibre;
    double mass;
};

struct physVector
{
    physVector(double x = 0, double y = 0)
    {
        x = 0; y = 0; t = 0; mv = 0;
    }
    double x, y, t, mv;
    double angle()
    {
       return acos(x/this->mod());
    }
    double mod()
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
     physVector operator + (const physVector& op) const
    {
        return physVector{x + op.x, y + op.y};
    }
     physVector operator * (const double op) const
    {
        return physVector{x * op, y * op};
    }
};

struct trajectory
{
    std::vector<physVector> points;
    double arrival_time;
    double angle;
    double charge;
};
class Solver
{
    public:
        static inline std::vector<trajectory> trajectories;
        static inline std::vector<trajectory> eligible_timeframe;
        static inline shell shell;
        static void calculateTrajectories(double dis)
        {
            trajectories.clear();
            eligible_timeframe.clear();
            trajectory t;
            double det = 0.01;
            for (int c = 0; c<4; c++)
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
         //  sort(arrivalTimes.begin(), arrivalTimes.end());
           std::sort(trajectories.begin(), trajectories.end(), [](const trajectory& t1, const trajectory& t2) -> bool
    { return t1.arrival_time < t2.arrival_time; });
    double last_arrival_time = 0;
    for (int i = 0; i<trajectories.size(); i++)
    {
        if (trajectories[i].arrival_time - last_arrival_time > 5)
        {
            eligible_timeframe.push_back(trajectories[i]);
            last_arrival_time = trajectories[i].arrival_time;
        }
    }

        }
    private:
        Solver(){}
        trajectory static calculate(double angle, double bVel);

};

#endif
