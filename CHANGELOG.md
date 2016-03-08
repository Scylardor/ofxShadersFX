3.0.1
=====
	General
	-------

	- Fix a bug in Lighting shaders that broke Lighting in OpenGL2. Only spotlights seemed to work.
	It seems it was a problem in the system of light IDs we were using to determine if a light was on or not.
	OpenGL3 versions were unaffected.
	- The shader sources in "readable" format are now part of the repo. They're very useful e.g. to reason about the
	logic of the shader code, compared to the minified versions embedded in ofxShadersFX source code.
	- Made some misc changes in the example projects to match current openFrameworks standards. This mainly includes
	replacing deprecated functions and renaming.
	- The whole project goes MIT license. You can do whatever you want with it as long as you mention the original authors.
	- Added QBS project files so we can start and work with the example projects in Qt Creator IDE.

3.0
===

General
-------

- External and internal changes of the API to provide a better naming convention
- Main new feature of this major version, the new shader namespace: Mapping
- Three types of Mapping shaders added: Displacement, Alpha Blending and Color Key
- Stop reloading a shader upon each modification, the shader is now reloaded once before use if necessary
  (implements a "dirtiness" system to reload if modified)

Lighting
--------

The bases of the Lighting shader never have been so clean, as I purged a lot of dead and/or dumb code that wasn't used anymore.
A lot of terminology has also changed to be more generic, so that will probably ease the creation of other shaders in the future.

I'm also happy to fix really dumb limitations, like the need to disable ARB texturing in GLSL 1.2. I just didn't know all I needed
to do was to enable the ARB texture extension in the shaders.

- Fixed ARB texturing broken in GL 1.2 (enabled the extension)
- Remove old unused code and adapt the class to new API
- Generally cleaner code

Mapping
-------

As these shaders can come in various ways and sizes about how they work with the mapping data we give to them,
I chose to design the ofxShadersFX::Mapping namespace differently than the Lighting one.

Instead of having one base class able to practically do anything by changing mere parameters, I found it to be more
appropriate to create a base MappingShader class, handling all the image storage process, and to derive it
to several smaller ones, representing the possible mapping shaders. This way provides great parameter safety, preventing
users to add more maps to a given shader than needed, but also simplicity in management of shader-specific parameters
(e.g.: the height of a displacement shader), and easier understanding of how to use the shaders: having one class
per shader allows less generic method and parameters names.

I hope this new approach won't be too confusing, since the Lighting namespace works quite differently.

- first version of Displacement, Alpha Blending and Color Key
- added example_Mapping
