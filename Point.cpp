#include "Point.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <assert.h>

using namespace std;
using namespace Clustering;

namespace Clustering
{

    unsigned int Point::__idGen = 0;

    Clustering::Point::Point(int i)
    {
        __dim = i;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = 0.0;
        __id = __idGen++;
    }

    Point::Point(int i, double *pDouble)
    {
        __dim = i;
        __values = pDouble;
        __id = __idGen++;
    }

    Point::Point(const Point &point)
    {
        __dim = point.__dim;
        __values = new double[__dim];
        for (int count = 0; count < __dim; ++count)
            __values[count] = point.__values[count];
        __id = point.__id;
    }

    Point &Point::operator=(const Point &point)
    {
        if (this == &point)
            return *this;
        else {
            __dim = point.__dim;
            for (int count = 0; count < __dim; ++count)
                __values[count] = point.__values[count];
            __id = point.__id;
        }
        return *this;
    }

    Point::~Point()
    {
        std::cout << "This is the value " << &__values << std::endl;
        delete[] __values;
    }

    // Accessors & mutators
    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const
    {
        return __dim;
    }

    void Point::setValue(int dim, double val)
    {
        if (dim >= 0 && dim < __dim) {
            __values[dim] = val;
        }
    }

    double Point::getValue(int dim) const
    {
        if (dim >= 0 && dim < __dim)
            return __values[dim];
        else
            return 0;
    }

    double Point::distanceTo(const Point &compPoint) const
    {
        if (__dim != compPoint.__dim)
            return false; // dimenstions aren't the same, don't calculate.

        double TotalProduct = 0;
        for (int i = 0; i < __dim; ++i)
        {
            TotalProduct += pow(compPoint.getValue(i) - getValue(i), 2);
        }
        return sqrt(TotalProduct);
    }

    Point &Point::operator*=(double val)
    {
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] *= val;
        }

        return *this;
    }


    Point &Point::operator/=(double val)
    {
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] /= val;
        }

        return *this;
    }

    const Point Point::operator*(double val) const
    {
        Point p(*this);

        p *= val;

        return p;
    }


    const Point Point::operator/(double val) const
    {
        Point p(*this);

        p /= val;

        return p;
    }


    // Read and write index
    double &Point::operator[](int index) {
        if (index < 0 || index >= __dim)
            index = 0;

        return __values[index];
    }


    // Friends
    Point &operator+=(Point &lhs, const Point &rhs)
    {
        int usedDims = max(lhs.getDims(), rhs.getDims());

        // Resize left array if right is larger
        if (lhs.__dim < usedDims)
        {
            delete[] lhs.__values;


            lhs.__values = new double[usedDims];
        }


        // Add values of right to values of left
        for (int i = 0; i < usedDims; ++i)
        {
            lhs[i] += rhs.getValue(i);      // getValue returns 0 if out of bounds
        }


        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs)
    {
        int usedDims = max(lhs.getDims(), rhs.getDims());


        if (lhs.__dim < usedDims)
        {
            delete[] lhs.__values;

            lhs.__values = new double[usedDims];
        }


        for (int i = 0; i < usedDims; ++i)
        {
            lhs[i] -= rhs.getValue(i);
        }


        return lhs;
    }


    const Point operator+(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);

        p += rhs;

        return p;
    }


    const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);

        p -= rhs;

        return p;
    }


    bool operator==(const Point &lhs, const Point &rhs)
    {
        if (lhs.__id != rhs.__id)
            return false;   // ID's don't match, not the same


        for (int i = 0; i < std::max(lhs.__dim, rhs.__dim); ++i)
        {
            if (lhs.getValue(i) != rhs.getValue(i))
                return false; // Any dimensional value doesn't match
        }


        // ID's are the same, values are the same
        return true;
    }


    bool operator!=(const Point &lhs, const Point &rhs)
    {
        return !(lhs == rhs);
    }


    bool operator<(const Point &lhs, const Point &rhs)
    {
        int usedDims = max(lhs.__dim, rhs.__dim);


        for (int i = 0; i < usedDims; ++i)
        {
            if (lhs.getValue(i) != rhs.getValue(i))
            {
                return (lhs.getValue(i) < rhs.getValue(i));
            }
        }


        // if all values equal, return false
        return false;
    }


    bool operator>(const Point &lhs, const Point &rhs)
    {
        return (rhs < lhs);
    }


    bool operator<=(const Point &lhs, const Point &rhs)
    {
        return !(lhs > rhs);
    }


    bool operator>=(const Point &lhs, const Point &rhs)
    {
        return !(lhs < rhs);
    }


    ostream &operator<<(ostream &out, const Point &p)
    {
        int i = 0;
        for (; i < p.__dim - 1; ++i)
            out << p.__values[i] << ", ";


        out << p.__values[i];


    }


    istream &operator>>(istream &in, Point &p)
    {
        //std::stringstream ss;
        string str;


        getline(in, str);
        int size = count(str.begin(), str.end(), ',') + 1;


        stringstream ss(str);


        if (p.getDims() != size)
        {
            delete[] p.__values;


            p.__dim = size;
            p.__values = new double[p.__dim];
        }


        int index = 0;  // current dimension index of point



        while (!ss.eof())
        {

            string svalue;

            getline(ss, svalue, ',');



            stringstream streamvalue(svalue);



            streamvalue >> p.__values[index];



            ++index;

        }



        return in;

    }


}
