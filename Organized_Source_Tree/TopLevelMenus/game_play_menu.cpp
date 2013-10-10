/*Called from game.cpp!!!!*/

#include "Global_Variables_Definitions.h"
#include "CUSTOM_FUNCTIONS_HEADER.h"
#include "BOX_LIST_CLASS.hpp"
#include "First_Level_Game_Functions.h"

int game_play_menu(int &blood_crip_popo, string &path_to_FMP){

    BITMAP *buffer_play_menu  = create_bitmap(1100, 480);
    BITMAP *PLAY_BACKGROUND_CHOICE = load_bitmap("BITMAPS\\PLAY_BACKGROUND_CHOICE.bmp", NULL);
    BITMAP *player_actor[3];
    BITMAP *CRIP_BLOOD_POPO = load_bitmap("BITMAPS\\CRIP_BLOOD_POPO.bmp", NULL);

    FONT *PLAY_LEVEL_FONT = load_font("BITMAPS\\PLAY_LEVEL_FONT.pcx", NULL, NULL);
    FONT *BOX_FONT = load_font("BITMAPS\\BOX_FONT.pcx", NULL, NULL);

    BOX_LIST<string, Game_Level> box(22, 300, 150, 250, 5, 0, buffer_play_menu, BOX_FONT, 40);


    vector<string> OG_DIRECTORIES = Return_List_OG_LEVELS(true); //With relative paths, scan for text files..
    OG_DIRECTORIES.erase(OG_DIRECTORIES.begin()); //Delete first element for relative .. directory

    vector<Game_Level> Level_Info = Load_Level_List(OG_DIRECTORIES); //Then take those paths and scan each file name file to retrieve information into game_level...
    std::cout << Level_Info[0].getFile_Name();

    for(int i = 0; i  < Level_Info.size(); i++){    //Load the bitmaps into memory refer to game_levels.cpp
        Level_Info[i].Load_Intro();
    }

    vector<string> OG_LEVELS_DISPLAY = Ret_Level_List_Name_Game_Info(Level_Info); //Scan each Game_List object for its level name.

    //OG_LEVEL_TXT.erase(OG_LEVEL_TXT.begin());
    //OG_LEVELS_DISPLAY.erase(OG_LEVELS_DISPLAY.begin());


    //Remove first element since its a directory reference: ..

    player_actor[0] = load_bitmap("BITMAPS\\BLACK_PERSON_BLOOD.bmp", NULL);
    player_actor[1] = load_bitmap("BITMAPS\\BLACK_PERSON_CRIPS.bmp", NULL);
    player_actor[2] = load_bitmap("BITMAPS\\POLICE_PIG.bmp", NULL);

    box.load_display_array(OG_LEVELS_DISPLAY);
    box.load_value_array(Level_Info);

    BITMAP *bitmptro = load_bitmap(Level_Info[0].getGraphic_File_Name().c_str(), NULL);



     //Create first frame of police officer, crip and blood
     //NOTE BCP = blood_crip_police
     //NOTE, index 0 is blood, 1 for crip, 2 popo


    bool stay_menu = true;
    bool exit_game = false;
    int choiceframe = 0;
    while(stay_menu){

        if(key[KEY_ESC]){
            stay_menu = false; //We want to end the loop and exit this menu
            exit_game = true;
        }
        if(key[KEY_ENTER]){
            stay_menu = false;  //We want to end the loop and execute the game logic entry point
            exit_game = false;

        }

        if(key[KEY_LEFT] && frames_drawn % 2 == 0){
            choiceframe--;
        }else if(key[KEY_RIGHT] && frames_drawn % 2 == 0){
            choiceframe++;
        }
        if(choiceframe > 2){
            choiceframe = 0;
        }else if(choiceframe < 0){
            choiceframe = 2;
        }

        if(key[KEY_DOWN] && frames_drawn % 2 == 0){
             box.select_down();
        }else if(key[KEY_UP] && frames_drawn % 2 == 0){
             box.select_up();
        }




        blit(PLAY_BACKGROUND_CHOICE, buffer_play_menu, 0, 0, 0, 0, 1100, 480);
        box.display();

        drawframe(buffer_play_menu, CRIP_BLOOD_POPO, 20, 50, 905, 220, 0, 0, 3, choiceframe, true);
        Level_Info[box.return_index_content()].Display_Intro(buffer_play_menu, 400, 300);


        // draw_sprite(buffer, main_menu_background, 0, 0);
        //Everything else below this line, goes on top of background in buffer
        //draw_sprite(buffer_play_menu, bitmptro, 0, 0);
       //drawframe(buffer_play_menu, player_actor[2], test2, 0, 213, 220, 0, 0, 3, (test%3), true);

        textprintf_ex(buffer_play_menu, PLAY_LEVEL_FONT, 10, 10, makecol(213, 121, 211), -1, "Use left/right and up/down arrows");

        textprintf_ex(buffer_play_menu, font, 900, 470, WHITE, 0, "Written By: Kelvin Silva");
        //textprintf_ex(buffer_options, font, 0, 470, WHITE, 0, "Volumebackground: %i", volume_background);
        textprintf_ex(buffer_play_menu, font, 0, 470, WHITE, 0, "Frames Drawn: %i", frames_drawn);

        blit(buffer_play_menu, screen, 0, 0, 0, 0, 1100, 480);

        frames_drawn++;
        vsync();
        rest(75);

    }

/*Garbage Collection:

    BITMAP *buffer_play_menu
    BITMAP *PLAY_BACKGROUND_CHOICE
    BITMAP *player_actor[3]
    BITMAP *CRIP_BLOOD_POPO

    */
    destroy_bitmap(buffer_play_menu);
    destroy_bitmap(PLAY_BACKGROUND_CHOICE);
    for (int i = 0; i < 3; i++){
        destroy_bitmap(player_actor[i]);
    }
    destroy_bitmap(CRIP_BLOOD_POPO);

    //Set the parameters given....
        int i = 0;
        if (!exit_game){
            blood_crip_popo = choiceframe;
            path_to_FMP =  Level_Info[box.return_index_content()].getFile_Name();
            i = 1;
        }

    return i;
}
