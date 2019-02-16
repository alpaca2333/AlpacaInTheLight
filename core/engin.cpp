//
// Created by qwertysun on 18-12-26.
//
#include "engine.h"

using namespace std;

Vector3 RandomUnitVector()
{
    Vector3 p;
    do
    {
        p = 2.f * Vector3((double) drand48(), (double) drand48(), (double) drand48()) - Vector3(1, 1, 1);
    } while (p.Length() >= 1);
    return p;
}


bool Objects::IsHit(const Ray &r, double minT, double maxT, HitRecord &hitRec)
{
    bool hit = false;
    double tempt = maxT;
    int lastI = -1 ;
    for (int i = 0; i < objects.size(); ++i)
    {
        if (objects[i]->IsHit(r, minT, tempt, hitRec))
        {
            hit = true;
            tempt = hitRec.t;
            lastI = i;
        }
    }
    if (lastI > -1)
    {
        objects[lastI]->material.Scatter(r, hitRec);
    }
    return hit;
}

std::ostream &operator<<(std::ostream &os, const Color &c)
{
    os << "Color {" << c.e[0] << " ," << c.e[1] << " ," << c.e[2] << "}";
    return os;
}
