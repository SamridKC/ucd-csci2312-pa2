//
// Created by Samrid on 2/20/2016.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bits/algorithmfwd.h>

#include "Cluster.h"
#include "Point.h"

// iostream
using std::cout;
using std::endl;

// fstream
using std::ifstream;

// sstream
using std::stringstream;
using std::string;

using Clustering::Point;

namespace Clustering {

    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n) { };

    void Cluster::__del() {
        if (__points != nullptr) {
            LNodePtr delPtr = __points;
            __points = __points->next;
            delete delPtr;
            __size--;
        }
    }

    Cluster::Cluster() : __size(0), __points(nullptr) { };

    Cluster::Cluster(const Cluster &rtSide) : __size(0), __points(nullptr) {
        for (int i = 0; i < rtSide.__size; ++i) {
            add(rtSide[i]);
        }
    }

    Cluster &Cluster::operator=(const Cluster &rtSide) {
        if (this == &rtSide) {
            return *this;
        }

        __del();

        LNodePtr current = rtSide.__points;
        while (current != nullptr) {
            for (int i = 0; i < rtSide.__size; ++i) {
                add(rtSide[i]);
            }
            current = current->next;
            return *this;
        }
    }

    Cluster::~Cluster() {
        __del();
    }

    int Cluster::getSize() const {
        return __size;
    }

    void Cluster::add(const Point &point) {
        LNodePtr a = new LNode(point, nullptr);
        if (__points == nullptr) {
            __points = a;
        }
        else if (__points->point > point) {
            a->next = __points;
            __points = a;
        }
        else {
            LNodePtr c = __points, n = __points->next;
            while (true) {
                if (n == nullptr || n->point > point) {
                    c->next = a;
                    a->next = n;
                    break;
                }
                else {
                    c = n;
                    n = n->next;
                }
            }
        }
        __size++;
    }

    const Point &Cluster::remove(const Point &point) {
        LNodePtr c = nullptr;
        LNodePtr n = nullptr;

        if (!__points) {
            return point;
        }
        if (__points->point == point) {
            __points = __points->next;
            delete c;
            __size--;
        }
        else {
            c = __points;
            while (c != nullptr && c->point != point) {
                n = c;
                c = c->next;
            }
            if (c != nullptr) {
                n->next = c->next;
                delete c;
            }
        }
        return point;
    }

    bool Cluster::contains(const Point &point) {
        LNodePtr targetNode = __points;

        while (targetNode != nullptr) {
            if (targetNode->point == point) {
                return true;
            }
            targetNode = targetNode->next;
        }
        return false;
    }

    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr temp = __points;

        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return (temp->point);
    }

    Cluster &Cluster::operator+=(const Point &point) {
        add(point);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &point) {
        remove(point);
        return *this;
    }

    Cluster &Cluster::operator+=(const Cluster &cluster) {
        LNodePtr current;
        current = cluster.__points;

        while (current) {
            add(current->point);
            current = current->next;
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &cluster) {
        LNodePtr current;
        current = cluster.__points;

        while (current) {
            remove(current->point);
            current = current->next;
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
        LNodePtr current;
        current = cluster.__points;

        while (current) {
            os << current->point << endl;
            current = current->next;
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Cluster &cluster) {
//        std::string line;
//        while (getline(is,line)) {
//            int d = (int) std::count(line.begin(),
//                                     line.end(),
//                                     ',');
//            Point ptr(d + 1);
//            std::stringstream lineStream(line);
//            lineStream >> ptr;
//           cluster.add(ptr);
//        }
//        return is;
    }

    bool operator==(const Cluster &ltSide, const Cluster &rtSide) {
        LNodePtr lt;
        LNodePtr rt;

        if (ltSide.__size != rtSide.__size) {
            return false;
        }
        else {
            lt = ltSide.__points;
            rt = rtSide.__points;

            while (lt && rt) {
                if (lt->point == rt->point) {
                    lt = lt->next;
                    rt = rt->next;
                }
                else {
                    return false;
                }
            }
            return true;
        }
    }

    bool operator!=(const Cluster &ltSide, const Cluster &rtSide) {
        return !(ltSide == rtSide);
    }

    const Cluster operator+(const Cluster &cluster, const Point &point) {
        Cluster c(cluster);
        c += point;
        return c;
    }

    const Cluster operator-(const Cluster &cluster, const Point &point) {
        Cluster c(cluster);
        c -= point;
        return c;
    }

    const Cluster operator+(const Cluster &ltCluster, const Cluster &rtCluster) {
        Cluster c(ltCluster);
        c += rtCluster;
        return c;
    }

    const Cluster operator-(const Cluster &ltCluster, const Cluster &rtCluster) {
        Cluster c(ltCluster);
        c -= rtCluster;
        return c;
    }
}