# Jade Engine
## 1. Project Overview

### 1.1 Purpose
The main reason for building this engine is to create a reusable tool for making 2D/3D single and multiplayer games.

### 1.2 Target Users:
The main users of this engine will be small game studios that want to make games on a low budget but want a good performing product.

## 2. Target Platforms
Initial target platforms: Windows
Future target platforms: Xbox, PlayStation, Nintendo Switch, iOS, Android

## 3. Game Type & Features

### 3.1 Game Genres Supported:
It will support a wide range of genres, from a simple 2D platformer to a 3D MMORPG.

### 3.2 Core Features
* 2D/3D Rendering
* 2D/3D Physics
* Audio
* Input
* Networking

### 3.3 Optional Features
* Scripting

### 3.4 Future Features
* AR/VR support

## 4. Technical Requirements

### 4.1 Rendering
The engine will use Vulkan as the main rendering API. In the future the engine may support DirectX, Metal and the PS4/PS5 rendering api’s.

### 4.2 Physics
The physics system will be capable of doing collision detection, raycasting, soft-body physics, rigid-body physics, cloth-physics, spring-physics and fluid simulations.

### 4.3 Audio
The audio system will be able to output stereo, spacial audio, music and audio effects.

### 4.4 Input
The initial plans for the input system are made to only support keyboard and mouse. This may also change in the future as we move on to other platforms.

### 4.5 Scripting
Scripting will be done in C#. More languages may be added later.

### 4.6 Networking
The networking layer will be able to support single player games as well as multiplayer or even MMO games.