# simple openGL implementation

This framework is for the developer who wants to simply and efficiently draw images on the screen using modern openGL features such as instancing without having to deal with or even see raw openGL code.

## dependencies: ##
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h "stb_image")
* [glm](https://github.com/g-truc/glm "glm")
#### you will need also these or substitudes for these: ####
* [GLFW](https://www.glfw.org "GLFW")
* [GLEW](http://glew.sourceforge.net "GLEW")

## instructions to get something drawn: ##

* create a shader object, giving paths of vertex and fragment shaders as parameters respectively (you can use the ones included for basic uses)
```c++
shader yourshader("basic_fs.shader", "basic_vs.shader");
```
* bind the shader
```c++
yourshader.bind();
```
* create a texture object
```c++
texture yourcooltexture(const char* filepath);
```
* create a thing object
```c++
thing yourthing(float width, float height);
```
if you are to draw a high number of your things at a time, call _instance()_ specifying count and array of position vectors of all of your object instances to enable rendering with instancing
```c++
yourthing.instance(unsigned int count, glm::vec2 positions[]);
```
* to display:
  * create a model matrix with your position data
  * pass the matrix to the shader width the name "mvp" multiplying by your projection matrix
  * bind your texture
  * call your thing's display method
```c++
glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));
basic.setUmat4f("mvp", proj * model);
yourcooltexture.bind();
yourthing.display();
```
you do not need to use a model matrix if you enabled instancing for your thing

## ##
feel free to let me know about any thought
