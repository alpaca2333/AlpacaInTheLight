# AlpacaInTheLight
Serious ray tracing renderer.

I would like to render an alpaca for myself. So i decide to compose a ray tracing renderer to do this. 

## Features
[√] Basic shapes <br/>
[√] Anti-aliasing <br/>
[√] Diffuse reflection material <br/>
[√] Mirrors <br/>
[ ] motion blur <br/>
[√] Glass <br/>
[√] DOF(Depth of fields) <br/>
[√] focus <br/>
[ ] Custom texture <br/>
[ ] Custom Shape from universal 3d model files support (e.g. *.obj *.fbx) <br/>
[ ] Path tracing <br/>

Still working on it!!

## Build and Test
Change dir to the root directory. 

requires gcc 4.8.5 + and cmake 3.2+.

``` bash
mkdir build && cd build
cmake ..
make -j12
./alpaca
```