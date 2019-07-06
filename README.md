# simple opengl implementation

This framework is for the developer who wants to simply and efficiently draw images on the screen using modern openGL features such as instancing.

## dependencies: ##
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h "stb_image")
* [glm](https://github.com/g-truc/glm "glm")
#### you will need also these or substitudes for these: ####
* [GLFW](https://www.glfw.org "GLFW")
* [GLEW](http://glew.sourceforge.net "GLEW")

## instructions to get something drawn: ##
* create a texture object
```c++
texture yourcooltexture(const char* filepath);
```
* create a thing object
```c++
thing yourthing(float width, float height);
```
call _instance()_ specifying count and array of position vectors to enable rendering with instancing. you do not need to do this if you are goint to draw your things one at a time
```c++
yourthing.instance(unsigned int count, glm::vec2 positions[]);
```
* to display:
  * create a model matrix with your position data
  * pass the matrix to the shader multiplying by projection, scale and view matrices
  * bind your texture
  * call your thing's display method
```c++
glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));
basic.setUmat4f("mvp", proj * view * model * scale);
yourcooltexture.bind();
yourthing.display();
```
