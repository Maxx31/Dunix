# Dunix
Dunix Engine 

Dunix is a lightweight C++ game engine. The engine is designed to separate the core engine systems from the tools used to build and run games.

Project Structure

Dunix – the core engine that contains the rendering system, utilities, and engine framework.

DunixEditor – the editor application used to create, manage, and run projects inside the engine. It provides tools for working with scenes, assets, and debugging.

Game – a separate project where the actual game code lives. New games are intended to be created as their own projects using the Dunix engine.


Third-Party Libraries:

The engine uses several external libraries located in the vendor directory:

Glad – OpenGL function loader used to access modern OpenGL APIs.

GLFW – window creation, input handling, and context management.

GLM – mathematics library for vectors, matrices, and transformations.

ImGui – immediate mode GUI used to build the DunixEditor interface.

spdlog – fast logging library used for engine and debugging logs.

stb_image – image loading library used for textures and asset importing.

<img width="1273" height="942" alt="image" src="https://github.com/user-attachments/assets/fbaf8836-8a73-432a-b72c-fda54ac0f550" />

<img width="1278" height="948" alt="image" src="https://github.com/user-attachments/assets/987b5de3-de84-4d50-801c-6e486e8ac004" />

