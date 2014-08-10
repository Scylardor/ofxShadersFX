ofxShadersFX
============

Shader effects made easy in openFrameworks

ofxShadersFX is an addon for openFrameworks (0.8.0+) to ease the use of common-used shaders in 3D scenes.

Features
--------

- *Lighting*
    - Phong illumination (Vertex and Pixel shader)
    - Blinn-Phong illumination (Vertex and pixel shader)

Coming soon (or later):
- *Lighting*
    - Toon
    - Flat
    - Oren-Nayar
    - Cook-Torrance
    - Ward anisotropic reflection (brushed metal effect)
- *Mapping*
    - Bump mapping
    - Alpha blending
    - Normal mapping
    - Color key mapping


Requirements
------------

- openFrameworks 0.8.3+ (may be compatible with older releases, that's not guaranteed)


Quickstart
----------

Here's how to create a Lighting shader:

- Download or clone the ofxShadersFX git repository in your openFrameworks `addons` folder.
- Create a new openFrameworks project using the project generator, make sure ofxShadersFX is enabled and selected from the list of addons shown.
- Open your project with you IDE of choice.
- Now select your ofApp.h file, and add `#include "ofxShadersFX.h"` under `#include "ofMain.h"`.

Declare in your ofApp a LightingShader attribute:

```cpp
ofxShadersFX::Lighting::LightingShader lshader;
```

```LightingShader``` creates a Blinn-Phong pixel (Phong shading) shader by default. You can modify it both the type (Gouraud/Phong shader) and the lighting method (Phong, Blinn-Phong...) of the shader. E.G. to make it a Gouraud shader, put in your `setup`:

```cpp
lshader.setType(ofxShadersFX::VERTEX_SHADER);
```

Then, to change from Blinn-Phong to Phong, use ```setMethod```:

```cpp
lshader.setMethod(ofxShadersFX::Lighting::PHONG);
```

You now have a Gouraud-shaded Phong lighting shader.

To apply it to your objects, you have to understand that ofxShadersFX shaders don't use their own lights, materials, or camera. They only use those you provide to them. So if you have a point light by which you want a sphere to be Phong illuminated, you have to specify it to the shader.

If you're visualizing 3D, you're probably using some sort of ofCamera (ofEasyCam for example). Providing one to ofxShaderFx shaders is mandatory in OpenGL 3. Let ```my_cam``` be an ```ofCamera```:

```cpp
lshader.useCamera(&my_cam);
```

Now let's tell our shader to use a point light. Let's consider ```plight``` as a simple ```ofLight``` in your app:

```cpp
lshader.useLight(&plight);
```

Finally, to use a material, e.g. ```mat```:

```cpp
lshader.useMaterial(&mat)
```

You're done configuring your Phong shader.

*Note 1*: you only have to do it once (in the ```setup``` function for example), and the shader will remember to use these when it works. If you want to stop using your camera, light, or material, just call ```removeCamera```, ```removeLight``` or ```removeMaterial```. You don't have to pass any parameter to ```removeCamera``` or ```removeMaterial```, since a lighting shader can actually use only one of these, if you tell it to remove them, it will simply discard them.

*Note 2*: all the parameters are pointers, so you have to pass the address (with the ```&```) of objects. If these are dynamically allocated objects (with ```new```), that's your job to ```delete``` them when you want to discard them. However, for *lights*, be sure to do it *after* having removed them from the shader ! Oh, and ```delete``` a pointer you passed to the shader without removing it will probably make your application crash. Be careful !

Finally, to the ```draw``` function. You use an ofxShadersFX shader just like you would use a normal ofShader. So that could be a simple use:

```cpp
my_cam.begin();
lshader.begin();
sphere.draw(); // sphere being an ofSpherePrimitive
lshader.end();
my_cam.end();
```

That's all, your sphere should now be illuminated with Phong's algorithm. Note that enabling / disabling lights used by the shader is useless: it does it automatically for you.
