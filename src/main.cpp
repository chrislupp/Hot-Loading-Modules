/*
    Hot Loading Modules Tutorial
*/

#include <iostream>
#include <memory>
#include <cmath>

#include "module.h"
#include "polygon.h"

using std::shared_ptr;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::sqrt;


int main(int argc, char **argv)
{
    // module names
    string triangle_name, square_name;

    // read module names from the command line options or use defaults
    if (argc == 3)
    {
        triangle_name = string(argv[1]);
        square_name = string(argv[2]);

        cout << "Using the following module libraries: " << endl;
        cout << triangle_name << " and " << square_name << endl << endl;
    }
    else
    {
        triangle_name = "./triangle.so";
        square_name = "./square.so";
    }


    // create the module loaders
    auto triangle_loader = new Module<Polygon<double>>();
    triangle_loader->SetModuleName(triangle_name);

    auto square_loader = new Module<Polygon<double>>();
    square_loader->SetModuleName(square_name);

    // create the triangle and square objects
    shared_ptr<Polygon<double>> triangle = triangle_loader->CreateObject();
    shared_ptr<Polygon<double>> square = square_loader->CreateObject();

    // delete the module loaders
    delete triangle_loader;
    delete square_loader;
    

    // triangle
    //---------
    double triangle_area = 0.0;

    if(!triangle)
        cerr << "Triangle was not instantiated." << endl;
    else
    {
        // call area function
        triangle->SetSideLength(3.0);
        triangle_area = triangle->Area();

        cout << "Triangle area: " << triangle->Area() << endl;
    }

    // set pointer to NULL
    triangle = shared_ptr<Polygon<double>>(NULL);
    

    // square
    //-------
    double square_area = 0.0;

    if(!square)
        cerr << "Square was not instantiated." << endl;
    else
    {
        // call area function
        square->SetSideLength(5.0);
        square_area = square->Area();

        cout << "Square area: " << square_area << endl;
    }

    // set pointer to NULL
    square = shared_ptr<Polygon<double>>(NULL);


    // test if the triangle and square areas are correct
    if (triangle_area != (9.0 * sqrt(3.0) / 2.0) or (square_area != 25.0))
    {
        cerr << "Wrong area value. Expected values are 7.79423 and 25.0"
            << endl;
            
        return -1;
    }


    return 0;
}