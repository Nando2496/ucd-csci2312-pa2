
#include <cassert>
#include <iomanip>
#include <sstream>
#include "Cluster.h"

namespace Clustering
{

    LNode::LNode(const Point &p, LNodePtr n = nullptr) : point(0)
    {
        point = p;
        next = n;
    }

    Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;
    }

    Cluster::Cluster(const Cluster &cluster)
    {
        __size = cluster.__size;
        if (__size == 0)
            __points = nullptr;
        else {
            for (int count = 0; count < cluster.__size; ++count) {
                add(cluster[count]);

            }
        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster)
    {
        if (this == &cluster)
            return *this;
        else {
            for (int count = 0; count < cluster.__size; ++count)
            {
                add(cluster[count]);
            }
        }
        return *this;
    }

    int Cluster::getSize() const
    {
        return __size;
    }
    Cluster::~Cluster() {
        if (__points != nullptr) {
            LNodePtr currPtr = __points;
            LNodePtr nextPtr = nullptr;
            while (currPtr != nullptr) {
                nextPtr = currPtr->next;
                delete currPtr;
                currPtr = nextPtr;
            }
        }
        else
            assert(__size == 0);
    }
        Cluster &Cluster::operator+=(const Point& point)
        {
            add(point);
            return *this;
        }
    Cluster &Cluster::operator-=(const Point& point)
    {
        remove(point);
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster& c)
    {
        for( int i =0; i < c.getSize(); ++i)
            add(c[i]);
               return *this;
    }

    Cluster &Cluster::operator-=(const Cluster& c)
    {
        for( int i =0; i < c.getSize(); ++i)
            remove(c[i]);
        return *this;
    }

    void Cluster::add(const Point &point)
        {
        Point p(point);
        LNodePtr insertPtr = new LNode(p, nullptr);
        LNodePtr prev = __points;
        LNodePtr next = __points;
        if (__points == nullptr)
        {
            __points = insertPtr;
            __size++;
        }
        else if (__points->next == nullptr)
        {
            if (point < __points->point)
            {
                __points = insertPtr;
                __size++;
            }
            else
                __points->next = insertPtr;
        }
        else {
            while (next != nullptr && (prev->point < point && point >= next->point))
            {
                prev = next;
                next = next->next;
            }
            prev->next = insertPtr;
        }
    }

    const Point &Cluster::operator[](unsigned int index) const
    {
        assert(__points != nullptr && index < __size);
        LNodePtr cursor = __points;
        for (int count = 0; count < index; ++count)
            cursor = cursor->next;
        return cursor->point;
    }

    void Cluster:: __del()
    {
        //stub
    }
    void Cluster:: __cpy(LNodePtr pts)
    {
        // stub
    }
    bool Cluster:: __in(const Point &p) const
    {
        // stub
    }
    std::ostream &operator<<(std::ostream &out, const Cluster &cluster)
    {
        out << std::setprecision(20);
            for (int i = 0; i < cluster.getSize(); ++i)
            {
                out << cluster[i] << std::endl;

            }
                return out;
             }
    std::istream &operator>>(std::istream &in, Cluster &cluster)
    {
        while (!in.eof()) {
            Point p(1);

            std::string str1;
            std:: getline(in, str1);
            if (str1.length() > 0){
                std::stringstream stream1(str1);
                stream1 >> p;

                cluster.add(p);
            }
            return in;
        }


    }


         // Friends: Comparison
    bool operator==(const Cluster &lhs, const Cluster &rhs)
         {
                 if (lhs.getSize() != rhs.getSize())
                         return false;


                 for (int i = 0; i < lhs.getSize(); ++i)
                 {
                         if (lhs[i] != rhs[i])
                                 return false;
                 }


                 return true;
             }
    bool operator!=(const Cluster &lhs, const Cluster &rhs)
    {
        return !(lhs == rhs);
    }


         // Friends: Arithmetic (Cluster and Point)
         const Cluster operator+(const Cluster &lhs, const Point &rhs) {
                 Cluster sum(lhs);
                 sum += rhs;
                 return sum;
             }
         const Cluster operator-(const Cluster &lhs, const Point &rhs) {
                 Cluster sub(lhs);
                 sub -= rhs;
                 return sub;
             }


    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    { // union
        Cluster sum(lhs);
        sum += rhs;
        return sum;
    }
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
       { // (asymmetric) difference
                 Cluster sub(lhs);
                 sub -= rhs;
                 return sub;
       }

    const Point &Cluster::remove(const Point & refPoint)
    {
        if (contains(refPoint)) {
            LNodePtr next;
            LNodePtr prev = nullptr;

            next = __points;

            while (next != nullptr) {
                if (next->point == refPoint) {
                    if (prev == nullptr) {
                        __points = next->next;

                        delete next;

                        --__size;
                        break;
                    }
                    else {
                        prev->next = next->next;
                        delete next;

                        --__size;
                        break;


                    }
                }
                prev = next;
                next = next -> next;
            }


        }
        return refPoint;
    }
    bool Cluster::contains(const Point &refPoint)
    {
        LNodePtr next = __points;

        while (next != nullptr)
        {
            if (next->point.getId() == refPoint.getId())
                return true;
            else
                next = next->next;
        }
        return false;
    }


}

