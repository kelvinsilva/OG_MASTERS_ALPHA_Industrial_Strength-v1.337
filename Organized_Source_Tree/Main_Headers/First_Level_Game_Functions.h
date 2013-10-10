#ifndef FIRST_LEVEL_GAME_FUNCTIONS_H_
#define FIRST_LEVEL_GAME_FUNCTIONS_H_

#define WHITE makecol(255,255,255)

#include <string>

void options_menu();
int game_play_menu(int &blood_crip_popo, std::string &path_to_FMP); //Menu to choose map and blood crip or police, the return value is to signal if user exited the menu...
void game(); //mappy file path: Level_Info[box.return_index_content()].getFile_Name();

#endif // FIRST_LEVEL_GAME_FUNCTIONS_H_
