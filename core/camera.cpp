//
// Created by qwertysun on 18-12-26.
//

#include "camera.h"

using namespace std;

Camera::Camera(const Vector3& lookFrom, const Vector3& lookAt,
               const Vector3& vup, float vfov, float aperture, float focusDist,
               int nx, int ny) : nx(nx), ny(ny)
{
    lensRadius = aperture / 2;
    double theta = vfov * M_PI / 180;
    double halfHeight = tan(theta / 2);
    double aspect = (double) nx / ny;
    double halfWidth = aspect * halfHeight;
    origin = lookFrom;
    w = (lookFrom - lookAt).UnitVector();
    u = vup.Cross(w).UnitVector();
    v = w.Cross(u);
    downLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
    hv = 2 * halfWidth * focusDist * u;
    vv = 2 * halfHeight * focusDist * v;
    // default color generator
    getColor = [](const Ray& r, Objects& os, int depth)
    {
        return Color(0, 0, 0);
    };
}

// rand ray of the pixel
Ray Camera::GetRay(double u, double v)
{
    Vector3 rd = lensRadius * RandomUnitVector();
    Vector3 offset = this->u * rd.e[0] + this->v * rd.e[1];
    Ray result{origin + offset, downLeftCorner + u * hv + v * vv - origin - offset};
    return result;
}

void Camera::Render(CachedPPM& ppm, Objects& objects)
{
    int samples = antiAliasing ? this->aaSamples : 1;
    int pi = 0;

#pragma omp parallel for schedule(dynamic)
    for (int j = ny - 1; j >= 0; --j)
    {
        for (int i = 0; i < nx; ++i)
        {
            Color tmp{0, 0, 0};
            // anti-aliasing
            for (int k = 0; k < samples; ++k)
            {
                double u = (double) i / nx;
                double v = (double) j / ny;
                double a = (2 * 3.1415926535 * (k + drand48()) / samples);
                u += (drand48() * cos(a)) / nx;
                v += (drand48() * sin(a)) / ny;
                Ray r = GetRay(u, v);
                tmp += vsqrt(getColor(r, objects, 0)) * 255.99;
            }
            tmp /= samples;
            ppm.Write(i, ny - 1 - j, tmp);
            pi++;
            LogProgress(ppm.Progress());
        }
    }

    // render finished
    ppm.WriteToFile();
}

void Camera::LogProgress(double percent)
{
    std::cout << "\33[2K\r";
    printf("%.2f%%", percent * 100);
}

