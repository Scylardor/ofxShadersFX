Contributing
============

Like any open source project, contributors, including the main ones, may not always be as available as they'd want to, and the project may sometimes slow down a bit.

But like most open source projects, you can freely contribute to it if you think there's a *must-have* feature missing or if things go too slow for you !

Here are some various guidelines to help you do so:

What you can do
---------------

There are some boring things that nobody likes to do, but that still need to be done almost at any time:

- try the addon on the most platforms you can (especially ones it hasn't been tested on before), and report any incompatibilities
- adapt the examples for various IDEs (I, for instance, haven't any Mac, so I can't provide XCode project files)
- try to make the addon crash by any means and report bugs !
- analyze the shaders provided by the addon, and propose corrections or more performant implementations if you see a flaw
- propose (and / or develop ! :) ) new shaders, or new shader modules, for the addon


Before everything else
----------------------

- If you have an idea of improvement, be sure to:
- check the current tip of the develop branch to see what has been worked on recently
- open an issue about your idea so it can be filed as a feature request (or an explicit notice you're going to work on it).

Style guidelines
----------------

> "Code is read much more often than it is written."
> Guido Van Rossum

So you decided to contribute to the project. Here's some style guidelines I'd like to follow, in order to keep maximum clarity and consistency in the repository source code :

- Class attributes / parameters : as much as possible, the class attributes names are prefixed by "m_" and implementations parameters names are prefixed with "p_".

- Any class declaration should declare the "public" section before any other ("private", "protected"...). C++ declares everything private by default, but everyone's not aware of that

- For multi-word names, use camelCase, with the first letter of the first word not capitalized. underscore_names are tolerated

- Shaders: Uniforms first, then varying/in/out, then globals, then code. One blank line between each and two blank lines between globals and code

- Usually, two blank lines between each function implementation.

```cpp
// good
void theLife() {

}


void ofBrian() {

}
```

- In functions, declare variables as close as possible to where you actually use them. If you're only using a variable in a for loop, declare it in the loop scope (the brackets).
  As much as possible, make variables declarations blocks, let one blank line, and then start instructions.

```cpp
// good
int i, j;
string blah;

i = 42;
cout << i << endl;
for (j = 0;;) {
    int k;

    cout << k << endl;    
}
```

```cpp
// Not good
int i;
i = 42;
cout << i << endl;
string blah;
int j = i;
int k;
for (j = 0;;) {
    cout << k << endl;    
}
```

- No if or for without brackets, even when it spans on one line only. You can put the first bracket on the same line:

```cpp
if (answer == 42) {
   ...
}
```

Contributors
============

Here are some credits about people who helped the project in any way.

- Thanks to Ludovic Migneault, Mathieu Hébert-Vallières and Sidki Bouslama (Université Laval, Québec) for being indirectly at the source of the project and helped me with shaders fundamentals.