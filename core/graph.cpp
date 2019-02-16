//
// Created by qwertysun on 18-12-26.
//

#include "graph.h"


using namespace std;

int WriteRGBImg(const char* path, int nx, int ny, Color *pix)
{
    std::ofstream fout(path);
    fout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int i = 0; i < nx * ny; ++i)
    {
        fout << (int) pix[i][0] << "\t" << (int) pix[i][1] << "\t" << (int) pix[i][2] << "\n";
    }
    fout.flush();
    return 0;
}


PPM::PPM(int nx, int ny, const char *filePath) : filePath(filePath)
{
    fout = new ofstream(filePath);
    *fout << "P3\n" << nx << " " << ny << "\n255\n";
}

void PPM::Write(Color &pix)
{

    double max = pix.e[0];
    max = max < pix.e[1] ? pix.e[1] : max;
    max = max < pix.e[2] ? pix.e[2] : max;
    if (max > 255.99)
    {
        pix.e[0] /= max / 255.99;
        pix.e[1] /= max / 255.99;
        pix.e[2] /= max / 255.99;
    }
    *fout << (int) pix.e[0] << "\t" << (int) pix.e[1] << "\t" << (int) pix.e[2] << "\n";
}

CachedPPM::CachedPPM(int nx, int ny, const char *filePath)
{
    this->nx = nx;
    this->ny = ny;
    this->filePath = filePath;
    colorCache = new Color[nx * ny];
    sum = 0;
}

#define max(a, b) (a > b ? a : b)
void CachedPPM::Write(int x, int y, const Color &c)
{
    int offset = y * nx + x;
    colorCache[offset] = c;
    double max = max(c.e[0], c.e[1]);
    max = max(max, c.e[2]);
    if (max > 255.99)
    {
        colorCache[offset] /= max / 255.99;
    }
    synchronized {
            ++this->sum;
    }
}

void CachedPPM::WriteToFile()
{
    ofstream fout(filePath);
    fout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            int offset = j * nx + i;
            fout << (int) colorCache[offset].e[0] << "\t"
                 << (int) colorCache[offset].e[1] << "\t"
                 << (int) colorCache[offset].e[2] << "\n";
        }
    }
}