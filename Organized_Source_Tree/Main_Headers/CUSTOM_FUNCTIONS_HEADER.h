#ifndef CUSTOM_FUNCTIONS_HEADER_H_
#define CUSTOM_FUNCTIONS_HEADER_H_

#include <allegro.h>
#include <winalleg.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <shlwapi.h>
#include <vector>
#include <fstream>
#include "Game_Levels.hpp"

#define WHITE makecol(255,255,255)

using std::vector;
using std::string;
using std::ifstream;

void drawframe(BITMAP *, BITMAP *, int, int, int, int, int, int, int, int, bool);

int if_neg_ret_zero(int);

string dir_of_game();
vector<std::string> Return_List_OG_LEVELS(bool);
vector<string> parse_out_file_extension(vector<string>);
vector<Game_Level> Load_Level_List(vector<string>); //NOTE: the vector argument must be a path!
vector<string> Ret_Level_List_Name_Game_Info(vector<Game_Level>);

#endif // CUSTOM_FUNCTIONS_HEADER_H_
