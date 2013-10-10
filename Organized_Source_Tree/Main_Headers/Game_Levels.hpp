#ifndef GAME_LEVELS_HPP_
#define GAME_LEVELS_HPP_

#include <string>
#include <allegro.h>

using std::string;

class Game_Level{

private:
    string Level_File;  //mappy file....
    string Level_Name;
    string INTRO_GRAPHIC_NAME;
    BITMAP* INTRO_GRAPHIC;
public:

    string getLevel_Name();
    string getFile_Name();
    string getGraphic_File_Name();

    ~Game_Level();

    void setLevel_Name(string);
    void setFile_Name(string);
    void setGraphic_File_Name(string);
    void Load_Intro();
    void Display_Intro(BITMAP*, int, int);

};

#endif // GAME_LEVEL_HPP_
