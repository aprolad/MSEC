#ifndef SOLVER
#define SOLVER

#include "Header.h"

struct shell
{
    std::vector<double> charges;
    double calibre;
    double mass;
};

struct physVector
{
    physVector(double x = 0, double y = 0)
    {
        x = x; y = y; t = 0;
    }
    double x, y, t;
    double angle() // Угол от оси x
    {
       return acos(x/this->mod());
    }
    double mod() // Модуль длины вектора
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
    physVector operator = (const physVector& op)
    {
        x = op.x;
        y = op.y;
        return *this;
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
        static void calculateTrajectories(double dis);
    private:
        Solver(){}
        trajectory static calculate(double angle, double bVel);

};

#endif
