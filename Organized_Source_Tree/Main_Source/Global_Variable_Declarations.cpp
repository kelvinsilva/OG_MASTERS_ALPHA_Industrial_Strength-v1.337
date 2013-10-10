#include "Global_Variables_Definitions.h"

int volume = 100;
int volume_background = 14;
int pan = 128;
int pitch = 1000;


int frames_drawn = 0;

/*

Thanks for Downloading OG Masters Alpha -->Industrial Strength<--
--Kelvin Silva

Things that are still missing.

1. An actual playable game

Things that are going to be implemented in the upcoming beta

1. Enemies and enemy spawn, and AI
2. Shooting of weapons and picking up items
3. Better collision detection
4. Redesigned artwork
5. Integration of music

So why even have such a shitty alpha?
I wanted to make a skeleton as for how the game would work. Design comes first, then small implementations.

What you see here is the mere skeleton. Most graphics you see are placeholder
graphics for the actual game (the actual game wont have good graphics either, since I dont have any friends willing to give free artwork to me).

Thanks for your time. If you have any questions please email me at kelvinsilva747@gmail.com

****Developer Stuff****
Source code can be found at:
https://bitbucket.org/kelvinsilva/og_masters_alpha_industrial_strength-v1.337

3rd Party libraries used:

#include <allegro.h> //Version 4.4
#include <winalleg.h> //Instead of including windows.h, we use winalleg.h since allegro.h and windows.h conflict
#include <iostream> //Used for debugging and tinkering but will not be part of actual game.
#include <stdlib.h>
#include <SFML/audio.hpp>
#include <vector>
#include <allegro.h>
#include <string>
#include <shlwapi.h>
#include <fstream>

Self made classes and functions

status_screen_functions.cpp
status_screen_functions_header.h

Game_Levels.hpp
Box_LIST_CLASS.hpp
Actor_Class.h
Actor_Class.cpp
Collision_Detection.cpp

Code Statistics:
Number of Files: 18
51% Code Only
4% Code + Comment
15% Comments
30% Empty
Code only: 904
Empty Lines: 543
Comment Lines: 270
Code and Comments: 73
Total Lines: 1790

These stats shall improve!!

*/
