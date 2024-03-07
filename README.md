# About project
This is my attempt to create a simple 2D game engine and game built upon it (Battle City 1985 mini clone)
Right now it provides enough(or almost enough :) ) functionality to make simple 2D games with fixed camera view



_____
# Engine

This is kinda core of whole game. This part use a lot from TheCherno OpenGL/GameEngine series https://www.youtube.com/c/TheChernoProject.
Basic setup for platform, graphic api, window creation, window events, input events, logging, abstract engine layers, entry point



_____
# Framework2D

This module include most engine functionality for game creation.


## Render
Texture, Shader, Renderer, ResourceLoader abstartions are here. They provides as basic functionality to simple 2D-quad entity creation.

BaseEntity, SolidEntity, SpriteEntity, SpriteSequence, SpriteFlipFlop are basic 2d graphic objects. They should be adde to Group abstraction
Layer2D includes group with entities. Layer2D inherited from engine Layer. so it's updated every frame. This is where render logic called.


## Global functionality
**SystemInput** simple way to pass input from engine to actual game module

It has **SystemTimer** that acts similar to UE4 TimerManager.

**SystemCollision** handles collision for entity with enabled collision.
It use abstraction like CollisionFilter (Block, Overlap), CollisionType (Static, Dynamic, Projectile)
Collision checked every frame, all dynamic against all static + dynamic against dynamic
Projectile type allow as properly check collision for very fast entities (like with pos delta 1000px per frame)


## Gameplay framework

This part was inspired by Unreal Engine gameplay framework. 

Gameplay framework represented by next abstartions:

- Actor component (with few components already created like  HealthComp, EntityComp)
- Actor (main game entity, it has components they adds functionality like visual representation, logic for interaction)
- Level (where actors placed)

- AIController (many to one)
- PlayerController (one to one)

- HUD
- HUDCanvas, HUDElement, HUDIcon, HUDItem
Provide as base functionality to create simple ui hud with icon frame-per-frame drawing

- GameMode 
This one owns level, hud, controllers

Well it's do around the same stuff as similiar named classes in UE4 but in very, very basic level :).


_____
# Game

It's just works.

Well there we make derrived classes from thoose which in Framework2D/Gameplay

Game -> initializing game, contain global consts, res pathes

TankiGameMode -> gameplay win/loose logic, handle restart, start, end
TankiHUD -> can draw win/loose plate, visualize playerRespawnNum, icons with enemies to kill
TankiAIController -> dumb af ai logic
TankiPlayerConroller -> move/fire player tank
TankiLevel_0 -> prebuilded game level: static actors, enemy spawner that kind of stuff.

Actors:
	Boosters, Pickups, Blocks, Spawner, Tank, Bullet, Base, BoomFX. Game specific entities in general.


_____
# Visual studio solution structure

- This engine-game project only work on win x64 with OpenGL ver 4.3
- Availiable Release-x64-win and Debug-x64-win modes.

####  Solution includes 6 projects:
GLEW, GLFW, GLM, Engine, Framework2D, Game.

GLEW - static lib linked to Engine.dll
GLFW - static lib linked to Engine.dll
GLM - static lib linked to Engine.dll

Engine - dynamic lib linked to Framework2D.dll and Game.exe

Framework2D - dynamic lib linked to Game.exe

Game - main exe file

#### Third parties source libs list:

GLEW, GLFW, GLM, spdlog, stbimage(import png textures)

_____
# How to run
1. Clone git repo
2. Compile entire solution (Release or Debug does not matter, i mean release much faster of course :) )
* When compiling first time, please compile it two times, some post builds events need to happen)))

_____
# ToDo

- Need optimize render to use texture atlases to make less draw calls
- We can pass z value to verticies to store sprites hierarchy directly on render side and minimize overhead on cpu side

- We can use more sophisticated and age proof collision check logic

- It's safer to implement some smart memory management system

- It will be cool too implement some multithreaded functionality. For example we can implement some audio module and make it operate in separate thread

- Implement camera and world tiling in this project will be amazing too!

_____
# Video

https://www.youtube.com/watch?v=WZQA-QomFUE
