/*
    Hot Loading Modules Tutorial

    This source file was adapted from:

    https://github.com/knusbaum/CPP-Dynamic-Class-Loading
*/

#include <cmath>

#include "polygon.h"


/*!
    \brief Triangle class
*/
template <typename Type>
class Triangle : public Polygon<Type>
{
public:
    Triangle() {};

    virtual Type Area() const
    {
        return side_length_ * side_length_ * sqrt(3.0) / 2.0;
    }

private:
    using Polygon<Type>::side_length_;
};


// class factories
//----------------
extern "C" Polygon<double>* Create()
{
    return new Triangle<double>();
}

extern "C" void Destroy(Polygon<double>* p)
{
    delete p;
}