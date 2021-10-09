# <img src="etc/Logo.png" height="25"/> 3D Renderer

![GitHub release (latest by date)](https://img.shields.io/github/v/release/abansal755/3D-Renderer?label=latest%20release)
![GitHub Release Date](https://img.shields.io/github/release-date/abansal755/3D-Renderer)

## Introduction
This is my first attempt to make a basic 3D Renderer using OpenGL and Qt Framework in C++. As of now, you can add the primitives: plane, cube, cone, cylinder and sphere to the scene. You can modify translate, rotate, scale, color and object specific properties of individual objects. For example, Object specific properties of a cone include its radius and height. In future, I will add the ability to load models from file and serializability of scenes. The scene has only 1 camera through which we can traverse around the scene using WASD keys and mouse. We can change camera settings like FOV, movement speed and turning speed. As of now, there will be only 1 directional light in the scene in the direction of the camera. The light follows the Phong Model of Lighting although only ambient and diffuse components have been coded. We can modify the ambient intensity, diffuse intensity and light color. In future, I will code the specular lighting add the ability to add multiple lights and that too of different types. I have added flat shader and phong shader (being used by sphere).

<img src="etc/Screenshot.png" />

## Contributing
If you would like to contribute, you can contact me through any of the following:
- Email: bansalakshitwork@gmail.com
- LinkedIn: linkedin.com/in/abansal755