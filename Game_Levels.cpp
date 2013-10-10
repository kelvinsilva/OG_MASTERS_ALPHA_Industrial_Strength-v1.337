#include "Game_Levels.hpp"

string Game_Level::getFile_Name(){
    return Level_File;
}

string Game_Level::getLevel_Name(){
    return Level_Name;
}

string Game_Level::getGraphic_File_Name(){
    return INTRO_GRAPHIC_NAME;
}

void Game_Level::setLevel_Name(string str){
    Level_Name = str;
}

void Game_Level::setFile_Name(string str){
    Level_File = str;
}

void Game_Level::setGraphic_File_Name(string str){
    INTRO_GRAPHIC_NAME = str;
}

void Game_Level::Load_Intro(){

    INTRO_GRAPHIC = load_bitmap(INTRO_GRAPHIC_NAME.c_str(), NULL);
}

void Game_Level::Display_Intro(BITMAP* draw_surface, int xpos, int ypos){

    draw_sprite(draw_surface, INTRO_GRAPHIC, xpos, ypos);
}

Game_Level::~Game_Level(){

}
