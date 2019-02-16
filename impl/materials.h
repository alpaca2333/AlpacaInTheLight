/*
 * @brief   basic material implementations.
 * @author  qwertysun
 * @date    12/27/2018
 */
#pragma once

#include "stdafx.h"
#include "core/engine.h"

class Lambertian : public Material
{
public:
    Lambertian(const Vector3& attenuation) : attenuation(attenuation) { }
    bool Scatter(
            const Ray& r, HitRecord& hr) const override;

protected:
    Vector3 attenuation;
};

class Metal : public Material
{
public:
    Metal(const Vector3& attenuation) : attenuation(attenuation) { }
    bool Scatter(
            const Ray& r, HitRecord& hr) const override;
protected:
    Vector3 attenuation;
};

class Glass : public Material
{
public:
    Glass(double r) : r(r) { }
    bool Scatter(
            const Ray& r, HitRecord& hr) const override;
protected:
    double r; // relative refractive index
};