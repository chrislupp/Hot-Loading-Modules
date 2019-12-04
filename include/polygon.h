/*
    Hot Loading Modules Tutorial

    This source file was adapted from:

    https://github.com/knusbaum/CPP-Dynamic-Class-Loading
*/
#pragma once



/*!
    \brief Polygon class
*/
template<typename Type>
class Polygon
{
protected:
    //! \brief side length
    Type side_length_;

public:
    //! \brief Constructor
    Polygon() {};

    //! \brief Destructor
    virtual ~Polygon() {};

    //! \brief Sets the side length of the polygon
    void SetSideLength(Type side_length)
    {
        side_length_ = side_length;
    };

    //! \brief Calculates and returns the area of the polygon
    virtual double Area() const = 0;

    typedef Polygon* Create();
    typedef void Destroy(Polygon<Type>*);
};