/*
    Hot Loading Modules Tutorial

    This source file was adapted from:

    https://github.com/knusbaum/CPP-Dynamic-Class-Loading
*/

#include <cmath>

#include "polygon.h"


/*!
    \brief Square class
*/
template <typename Type>
class Square : public Polygon<Type>
{
public:
    Square() {};

    virtual Type Area() const
    {
        return side_length_ * side_length_;
    }

private:
    using Polygon<Type>::side_length_;
};


// class factories
//----------------
extern "C" Polygon<double>* Create()
{
    return new Square<double>();
}

extern "C" void Destroy(Polygon<double>* p)
{
    delete p;
}