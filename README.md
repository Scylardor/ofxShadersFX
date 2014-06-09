ofxShadersFX
============

Shader effects made easy in openFrameworks

ofxShadersFX is an addon for openFrameworks (0.8.0+) to ease the use of common-used shaders in 3D scenes.

Its goal is to provide a simple, unified interface for a wide variety of shaders that work with both the old renderer using OpenGL fixed-pipeline functionality and the new OpenGL Core programmable pipeline.

Also, as frequently as possible, two versions of each shader are available: a vertex shader one and a pixel shader one (especially with *Lighting* shaders). This also makes ofxShadersFX a great tool for study purposes, to analyze the differences and advantages between two ways of doing the same thing.

*Note*: ofxShadersFX does *not* pretend to use the most performant or the most customisable shaders in the world ! It is just an interface to make the use and study of shaders easier.

The ofxShadersFX namespace is divided in smaller, thematic namespaces, called *modules*. For now, the only module available is *Lighting*, which groups all the lighting-related shaders used by ofxShadersFX.

In order to function, it relies on a collection of GLSL shaders that you must import in your openFrameworks project's `data/` directory. You can then use ofxShadersFX shader classes to make use of the shaders provided by the addon, seamlessly.


Features
--------

So far, the following effects are available with ofxShadersFX:
- *Lighting*
    - Phong illumination (Vertex and Pixel shader)
    - Blinn-Phong illumination (Vertex and pixel shader)

The following effects are planned:
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

- openFrameworks 0.8.0+


Getting Started
---------------

Let's go through a quick tutorial on how to start using ofxShadersFX. First:

- Download or clone the ofxShadersFX git repository in your openFrameworks `addons` folder.
- Create a new openFrameworks project using the project generator, make sure ofxShadersFX is enabled and selected from the list of addons shown.
- Be sure to copy the contents of the addon's ```data/``` folder to your own project's ```data/``` folder.
- Open your project with you IDE of choice.
- Now select your ofApp.h file, and add `#include "ofxShadersFX.h"` under `#include "ofMain.h"`.

Now, in this tutorial, we're taking the example of a Phong lighting vertex shader.

Declare in your ofApp a LightingShader attribute:

```cpp
ofxShadersFX::Lighting::LightingShader phong;
```

By default, ```LightingShader``` creates a Blinn-Phong pixel shader. Not quite what we want here. To modify it, in your ```setup``` function, first change the shader type to vertex shader :

```cpp
phong.setType(ofxShadersFX::VERTEX_SHADER);
```

(To write less, you can of course place ```using namespace ofxShadersFX``` in your source file)

Then, to change the method of lighting used by the lighting shader, use ```setMethod```:

```cpp
phong.setMethod(ofxShadersFX::Lighting::PHONG);
```

That's it ! Now let's say you want to use this shader with an ofSpherePrimitive of yours; let's call it ```sphere```.

An important thing to understand with ofxShadersFX shaders is that they don't use their own lights, materials, or camera, but only uses those you provide to them. So, for example if you have, say, a point light by which you want your sphere to be Phong illuminated, you have to specify it to the shader.

But you should first of all add a camera to the shader. That's mandatory only if you're using the new OpenGL programmable renderer (if you don't know whether you're using it or not, you're probably not), but you're better doing it anyway. Let ```my_cam``` be an ```ofCamera```:

```cpp
phong.useCamera(&my_cam);
```

Now let's tell our shader to use our point light. Let's consider ```plight``` as a simple ```ofLight``` in your app :

```cpp
phong.useLight(&plight);
```

Finally, to use a material on this sphere, say ```mat``` :

```cpp
phong.useMaterial(&mat)
```

And then you're done with it.

*Note 1*: you only have to do all this once (in the ```setup``` function for example), and the shader will remember to use these when it works. If you want to stop using your camera, light, or material, just call ```removeCamera```, ```removeLight``` or ```removeMaterial```. You don't have to pass any parameter to ```removeCamera``` or ```removeMaterial```, since a lighting shader can actually use only one of these, if you tell it to remove them, it will simply discard them.

*Note 2*: all the parameters are pointers, so you have to pass the address (with the ```&```) of objects. If these are dynamically allocated objects (with ```new```), that's your job to ```delete``` them when you want to discard them. However, for *lights*, be sure to do it *after* having removed them from the shader ! Oh, and ```delete``` a pointer you passed to the shader without removing it will probably make your application crash. Be careful !

Finally, to the ```draw``` function. You use an ofxShadersFX shader just like you would use a normal ofShader. So that could be a simple use:

```cpp
my_cam.begin();
phong.begin();
sphere.draw();
phong.end();
my_cam.end();
```

That's all, your sphere should now be illuminated in a Phong fashion ! Note that you absolutely don't have to enable / disable the lights used by the shader (if you're using the old renderer): it does it automatically for you.

Have fun !
