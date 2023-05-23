#pragma once

#include <iostream>

namespace ariel
{
    class Point
    {
        double _x_;
        double _y_;

    public:
        Point(double _x_, double _y_);
        //~Point();
        double distance(const Point &point);
        void print();
        static Point moveTowards(Point &src, Point &dst, double dist);
        double getX();
        double getY();
        void setX(double _x_);
        void setY(double _y_);
    };
}