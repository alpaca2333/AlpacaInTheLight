/*
 * @brief   Interfaces to generate graphs.
 * @author  qwertysun
 * @date    12/26/2018
 */


#pragma once
#include "common.h"
#include "stdafx.h"
#include "math.h"
#include "engine.h"

/**
 * Output an image in ppm format
 */
int WriteRGBImg(const char* path, int nx, int ny, Color *pix);

// PPM writer
class PPM
{
public:
    PPM(int nx, int ny, const char* filePath);

    // Could change the value of color if rgb values exceed 255
    void Write(Color &c);

    ~PPM() { delete fout; }
protected:
    const char* filePath;
    std::ofstream *fout;
};

/*
 * All Write operations are done in memory first.
 * Call WriteToFile() to save changes to file.
 * Being add to support multi-thread rendering.
 */
class CachedPPM
{
public:
    CachedPPM(int nx, int ny, const char* filePath);

    void WriteToFile();

    void Write(int x, int y, const Color &c);

    inline double Progress() { return sum / ((double) nx * ny); }

    inline void ClearProgress() { sum = 0; }

    ~CachedPPM() { delete colorCache; }
private:
    int nx, ny;
    const char* filePath;
    Color* colorCache;
    int sum;
};
