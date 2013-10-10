#include "Global_Variables_Definitions.h"
#include "First_Level_Game_Functions.h"

#include <allegro.h>
#include <winalleg.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/audio.hpp>
#include <vector>

#include "BOX_LIST_H.h"
#include "CUSTOM_FUNCTIONS_HEADER.h"
#include "status_screen_functions_header.h"

using std::vector;

//General Game Settings



int main(){



    allegro_init();
    install_keyboard();
    if(install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0){

        allegro_message("error initializing the sound system");

    }


    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1100, 550, 0, 0);

    write_status_screen("Status$>_Allegro Engine Initialization Successfull");
//******************************************************************************//
//*****************************************************************************//
//Write code below this line since allegro has been initialized//

    BITMAP *main_menu_background;
    BITMAP *main_title, *main_menu;
    BITMAP *buffer;

    /*Menu music*/
   // load_sample("OG_MUSIC\\straight_outta_compton_menu.ogg");

    //Setup Audiostream for Main Menu Music//

    write_status_screen("Status$> Loading OGG Music Stream: \"Straight Outta Compton.OGG\"");

    sf::Music main_menu_track;
    main_menu_track.openFromFile("OG_MUSIC\\straight_outta_compton_menu.ogg");
    main_menu_track.play();



//logg_get_stream("straight_outta_compton_menu.ogg", volume, pan, true);



    SAMPLE *menu_guntrigger = load_sample("OG_MUSIC\\gun_menu_choose.wav");


    /*Menu count*/
    int menct = 0;

    buffer = create_bitmap(1100, 480);
    textprintf_ex(screen, font, 0, 0, WHITE, 0, "Resolution = %ix%i ", SCREEN_W, SCREEN_H);

    main_menu_background = load_bitmap("BITMAPS\\COMPTON_START_MENU_FADED_TWO.bmp", NULL);
    main_title = load_bitmap("BITMAPS\\OGM_TITLE.bmp", NULL);
    main_menu = load_bitmap("BITMAPS\\MAIN_MENU.bmp", NULL);


    write_status_screen("Status$>_Bitmaps loaded into memory!");
    write_status_screen("Status$> Loading OG Sound Effects......:");
    write_status_screen("Status$> ********Press Esc to Quit!*********");




    bool stay_in_menu_loop = true;
    bool menu_controls = true;
    while(stay_in_menu_loop){

        if(key[KEY_ESC]){
            stay_in_menu_loop = false;
        }


    /*Handle Controls First modulus 2 to make selection easier, every second frame, keypress is captured. DO NOT DO (modulus 2 thing) THIS FOR ACTUAL GAMEPLAY*/

        if (menu_controls){
            if(key[KEY_UP] && frames_drawn % 2 == 0){
                play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
                menct--;
            } else if (key[KEY_DOWN] && frames_drawn % 2 == 0){
                play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
                menct++;
            }
            if (menct > 3){
                play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
                menct = 0;
            }else if (menct <0){
                play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
                menct = 3;
            }
        }

        if(key[KEY_ENTER]){

            switch(menct){

                case 0:{
                    game(); //Refer to game.cpp under game Logic.
                }  //Play
                break;

                case 1:{

                    stay_in_menu_loop = false;
                } //Load Save
                break;

                case 2:{
                    options_menu(); //Refer to top level menu functions virtual folder

                }  // Options
                break;

                case 3:{

                    allegro_message("OGM Credits -->Industrial Strength<--\n\nCreated by Kelvin Silva, a shitty programmer.\nUsing:\nSFML Library\nAllegro Library\nMappyAL Library\nWin32 Api");
                    write_status_screen("***********************************************************************");
                    write_status_screen("*                   -->Industrial Strength<--                         *");
                    write_status_screen("*Created by Kelvin Silva, a shitty programmer.                        *");
                    write_status_screen("*Using: SFML Library, Allegro Library, MappyAL Library, Win32 Api     *");
                    write_status_screen("*Thank you for wasting your time on this game                         *");
                    write_status_screen("***********************************************************************");
                    //stay_in_menu_loop = false;  //Credits
                }
                break;


            }

        }
        rest(10);


        //Erase everything
        clear(buffer);

        //status box
        rectfill(screen, 0, 480, 1100, 483, WHITE);

        /*Draw the frame based on user input*/
        draw_sprite(buffer, main_menu_background, 0, 0);
        draw_sprite(buffer, main_title, 315, 10);
        drawframe(buffer, main_menu, 485, 145, 332, 305, 0, 0, 4, menct, true);
        //blit(main_title, screen, 0, 0, 50, 50, 540, 96);
        //masked_blit(main_title, screen, 0, 0, 50, 50, 540, 96);

        //masked_blit(source, dest, framex, framey, x, y, width, height);

        //Blit credits and buffer to screen
        textprintf_ex(buffer, font, 900, 470, WHITE, 0, "Written By: Kelvin Silva");

        textprintf_ex(buffer, font, 0, 470, WHITE, 0, "Frames Drawn: %i", frames_drawn);

        blit(buffer, screen, 0, 0, 0, 0, 1100, 480);

        //Adjust settings here
        main_menu_track.setVolume(volume_background);


        /*Wait for vsync, rest a little, update framecount and prompt for more input*/
        vsync();
        frames_drawn++;
        rest(50);
    }

    //Clean up main menu stuff..
    write_status_screen("Status$>_Cleaning up main menu");



    destroy_bitmap(main_menu_background);
    destroy_bitmap(main_title);
    destroy_bitmap(buffer);
    destroy_bitmap(main_menu);
    destroy_sample(menu_guntrigger);

    destroy_sample(menu_guntrigger);

    clear_status_screen();
    //NOTE NEED TO SETUP MEMORY DESTRUCTION

    allegro_exit();

    return 0;
}
END_OF_MAIN()

