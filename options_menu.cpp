#include "Global_Variables_Definitions.h"
#include "CUSTOM_FUNCTIONS_HEADER.h"
#include <cmath>

void options_menu(){

    BITMAP *buffer_options  = create_bitmap(1100, 480);
    BITMAP *OPTIONS_BACKGROUND = load_bitmap("BITMAPS\\OPTIONS_MENU_BACKGROUND.bmp", NULL);
    BITMAP *measure_cartridge[2];
    measure_cartridge[0] = load_bitmap("BITMAPS\\OPTIONS_MENU_MEASURE.bmp", NULL);
    measure_cartridge[1] = load_bitmap("BITMAPS\\OPTIONS_MENU_MEASURE.bmp", NULL);

    BITMAP *vol_options = load_bitmap("BITMAPS\\VOL_OPTIONS.bmp", NULL);


    int menct = 0;
    int setting_measure[2] = {0, 0};
    bool stay_in_options = true;

    SAMPLE *menu_guntrigger = load_sample("OG_MUSIC\\gun_menu_choose.wav");

    while(stay_in_options){

        if(key[KEY_ESC]){
            stay_in_options = false;
        }
        if(key[KEY_UP] && frames_drawn % 2 == 0){
            play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
            menct--;
        } else if (key[KEY_DOWN] && frames_drawn % 2 == 0){
            play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
            menct++;
        }
        if (menct > 1){
            play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
            menct = 0;
        }else if (menct < 0){
            play_sample(menu_guntrigger, volume, pan, pitch, FALSE);
            menct = 1;
        }

        if(key[KEY_LEFT]){

            if(menct == 0){
                volume_background += volume_background < 0 ? 0 : -28;

            }else if(menct == 1) {
                volume += (volume < 0) ? 0 : -14;
            }

        }else if(key[KEY_RIGHT] ){

            if(menct == 0){

                volume_background += (volume_background > 100) ? 0 : 14;


            }else if(menct == 1) { //If menct == 1, the frame will be that of sound FX and modify the sound FX bullet magazine
                volume += (volume > 200) ? 0 : 28;
            }

        }


        blit(OPTIONS_BACKGROUND, buffer_options, 0, 0, 0, 0, 1100, 480);
        //blit(measure_cartridge, buffer_options, 0, 0, 0, 0, 237, 563);
        //draw_sprite(buffer_options, measure_cartridge, 0, 0);

        drawframe(buffer_options, vol_options, 20, 50, 636, 140, 0, 0, 2, menct, true);

        //Determine Which Frame to draw based on settings
        //Calculation :  setting/default = x frame drawn/(max frames allowed-1)

        setting_measure[0] = ceil((volume_background * 6)/100);
        setting_measure[1] = ceil((volume * 6)/200);

        //Make sure that negatives are zeroed values

        setting_measure[0] = if_neg_ret_zero(setting_measure[0]);
        setting_measure[1] = if_neg_ret_zero(setting_measure[1]);
        volume_background = if_neg_ret_zero(volume_background);
        volume = if_neg_ret_zero(volume);

        drawframe(buffer_options, measure_cartridge[0], 660, 50, 226, 78, 0, 0, 7, setting_measure[0], true);
        drawframe(buffer_options, measure_cartridge[1], 660, 130, 226, 78, 0, 0, 7, setting_measure[1], true);

        textprintf_ex(buffer_options, font, 900, 470, WHITE, 0, "Written By: Kelvin Silva");
        //textprintf_ex(buffer_options, font, 0, 470, WHITE, 0, "Volumebackground: %i", volume_background);
        textprintf_ex(buffer_options, font, 0, 470, WHITE, 0, "Frames Drawn: %i", frames_drawn);



        blit(buffer_options, screen, 0, 0, 0, 0, 1100, 480);

        vsync();
        rest(50);
        frames_drawn++;
    }


    destroy_bitmap(OPTIONS_BACKGROUND);
    destroy_bitmap(buffer_options);
    destroy_bitmap(measure_cartridge[0]);
    destroy_bitmap(measure_cartridge[1]);
    destroy_sample(menu_guntrigger);

}
