A C++ graphics library inspired by [Processing](https://processing.org). In development. 

## features - development status
- [x] orthographic and perspective projection
- [x] window handling
- [x] complete matrix handling
- [x] 2D textures
- [x] instancing
- [ ] text rendering
- [ ] light
- [ ] face culling

## usage

**creating a window:**
```c++
fly::createWindow(std::string windowTitle, int width, int height);
```
**creating a fullscreen window:**
```c++
fly::createWindow(std::string windowTitle);
```
**initialization**
```c++
fly::initialize(fly::projectionMethod::ORTHO);
```
or
```c++
fly::initialize(fly::projectionMethod::PERSPECTIVE);
```
Check [examples](https://github.com/flightcoded/fly-graphics/tree/master/examples) also.

## dependencies
* [GLAD](https://glad.dav1d.de) (configured for OpenGL 3.3 Core)
* [GLFW](https://www.glfw.org)
* [GLM](https://github.com/g-truc/glm)
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

There is a complete Visual Studio project with all dependencies linked and included under [releases](https://github.com/flightcoded/fly-graphics/releases).
