/*
 * @brief   Physical model. Basic definitions of
 *          Ray, Color, Material, etc.
 * @author  qwertysun
 * @date    12/26/2018
 */

#pragma once

#include "stdafx.h"
#include "math.h"

#define SURFACE_THICKNESS 0.0000001

class Color;
class Vector3;
class Material;
class HitRecord;

Vector3 RandomUnitVector();

/*
 * described by P = A + k·B
 * P is any point on the ray.
 * A is the origin point. B is the direction.
 */
class Ray
{
public:
    Ray() = default;
    Ray(const Vector3& A, const Vector3& B) : A(A), B(B) { }
    Ray(const Vector3& A, const Vector3& B, const Ray& previous): Ray(A, B)
    {
        refracted = previous.refracted;
    }
    Vector3 Origin() const { return A; }
    Vector3 Direction() const { return B; }
    Vector3 P(double k) const { return A + B * k; }
    Vector3 operator[](double k) const { return P(k); }
    bool refracted = false;
protected:
    Vector3 A, B;
};


class Color : public Vector3
{
public:
    Color() = default;
    Color(const Vector3& vec) : Vector3(vec) { }
    Color(double a, double b, double c) : Vector3(a, b, c) { }
    friend std::ostream& operator<<(std::ostream& os, const Color& c);
};
// material definition
struct ScatterInfo
{
    Vector3 attenuation;
    Ray outRay;
};


/**
 * Stores information about at which point a ray hits
 * an object and what the t-param is in the ray.
 */
struct HitRecord
{
    HitRecord() = default;
    HitRecord(
            double t, const Vector3& p, const Vector3 normal, const Material& m
    ) : t(t), p(p), normal(normal), scatterInfos(scatterInfos) { }
    double t;
    Vector3 p, normal;
    std::vector<ScatterInfo> scatterInfos;
};

/*
 * Base definition of material.
 * Concrete definitions of materials should be put in 'material.h'
 */
class Material
{
public:
    virtual bool Scatter(
            const Ray &r, HitRecord &hr) const { hr.scatterInfos = {}; return true; };
};

/**
 * common object definition.
 */
class Object
{
public:
    Object(const Material& m): material(m) {   }
    // decide whether the ray r hits this object.
    virtual bool IsHit(const Ray& r, double minT, double maxT, HitRecord& hitRec) = 0;
    const Material& material;
};

class Objects
{
public:
    virtual bool IsHit(const Ray& r, double minT, double maxT, HitRecord& hitRec);
    void Add(Object* hittable) { objects.push_back(hittable); }
    void Release() { for (auto* p: objects) delete p; }
    ~Objects() { Release(); }
protected:
    std::vector<Object*> objects;
};

/*
 * A color handler is directly called by camera's render function.
 * It decides the color of each tracing ray.
 */
typedef std::function<Color(const Ray&, Objects&, int)> ColorHandler;