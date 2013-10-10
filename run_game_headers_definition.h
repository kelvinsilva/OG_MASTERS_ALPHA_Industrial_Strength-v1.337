//For the run game prototype, please reference global_variables_function_definition header file.
//This file is for the structs, and other headers needed for the game...
#ifndef RUN_GAME_HEADERS_DEFINITION_H_
#define RUN_GAME_HEADERS_DEFINITION_H_


#include "Global_Variables_Definitions.h"

#include "Actor_Class.h"


#include <allegro.h>

#include <winalleg.h>
#include <mappyal.h>
#include <iostream>
#include <string>
using std::string;

#define WIDTH 1100
#define HEIGHT 480
#define MODE GFX_AUTODETECT_WINDOWED
#define WHITE makecol(255, 255, 255)
//Headers and definitions for collision detection function
struct Colision_Result{

    bool left, right, top, bot;

    RECT rectangle_coords;

    int length_col_rect;
    int width_col_rect;

};


Colision_Result FG_COLISSION(RECT rcte, int xoff, int yoff, float yoffx);

#endif // RUN_GAME_HEADERS_DEFINITION_H_
