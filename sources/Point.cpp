#include <math.h>
#include "Point.hpp"

namespace ariel
{
    Point::Point(double _x_, double _y_) : _x_(_x_), _y_(_y_)
    {
    }

    double Point::distance(const Point &point)
    {
        return sqrt(pow(this->_x_ - point._x_, 2) + pow(this->_y_ - point._y_, 2));
    }

    void Point::print()
    {
        std::cout << "(" << this->_x_ << ", " << this->_y_ << ")" << std::endl;
    }

    Point Point::moveTowards(Point &src, Point &dest, double dist)
    {
        if(dist<0)
            throw std::invalid_argument("negative distance");
        double src_to_dest = src.distance(dest);
        if (dist >= src_to_dest)
            return dest;
        double ratio = dist / src_to_dest;
        return Point(src._x_ + ratio * (dest._x_ -src._x_), src._y_ + ratio * (dest._y_ -src._y_));
    }

    double Point::getX()
    {
        return _x_;
    }

    double Point::getY()
    {
        return _y_;
    }

    void Point::setX(double _x_)
    {
        this->_x_ = _x_;
    }

    void Point::setY(double _y_)
    {
        this->_y_ = _y_;
    }
}