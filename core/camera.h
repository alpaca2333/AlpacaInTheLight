/*
 * @brief   Camera definition and implementation.
 * @author  qwertysun
 * @date    12/26/2018
 */

#pragma once

#include "stdafx.h"
#include "math.h"
#include "engine.h"
#include "graph.h"

class Camera
{
public:
    Camera(const Vector3& lookFrom, const Vector3& lookAt,
           const Vector3& vup, float vfov, float aperture, float focusDist,
           int nx, int ny);
    Ray GetRay(double u, double v);
    void SetAntiAliasing(bool aa) { antiAliasing = aa; }

    /* Set number of samples for each pixel the camera would take when rendering */
    void SetAaSamples(int samples) { aaSamples = samples; }
    void SetColorHandler(const ColorHandler& handler) { getColor = handler; }
    void Render(CachedPPM& ppm, Objects& objects);
    void LogProgress(double percent);
protected:
    bool antiAliasing = true;
    int aaSamples = 100;    // amount of sample token for each pixel
    Vector3 origin;
    Vector3 downLeftCorner;
    Vector3 u, v, w;
    Vector3 hv, vv;
    int nx, ny;
    // the color handler will decide each pixel's color
    // it is the most important method
    ColorHandler getColor;
    float lensRadius;
};

