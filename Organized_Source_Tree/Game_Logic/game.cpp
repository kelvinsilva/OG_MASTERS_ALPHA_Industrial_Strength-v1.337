#include "run_game_headers_definition.h"
#include "First_Level_Game_Functions.h"
#include "status_screen_functions_header.h"

//In header: Colision_Result FG_COLISSION(RECT rcte, int xoff, int yoff, float yoffx);



void game(){

    int blood_crip_popo = 0; //blood crip police
    string mappy_file_path = "";

    int ret = game_play_menu(blood_crip_popo, mappy_file_path); ///Ask the user which character they want to play, and locate the map file they want...
    //The below is the game loop acting on the two above parameters.

    //If ret is zero, then we want to terminate the game loop.
    if (ret == 0){
        return;
    }

      //NOTE, index 0 is blood, 1 for crip, 2 popo
    //Kelvin Silva --> Sept 3 2013


    //int jump = 0;
    int xoff = 0;
    int yoff = 0;
    int game_tick = 0;

        BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
        BITMAP *guy = load_bitmap("BITMAPS\\guy.bmp", NULL);


        //__________________________________________________________________
        //----->>>>Actor Class Constructor Description<<<<-----------------|
        //1. Draw Destination  | 2. Start X Position                       |
        //3. Start Y Position  | 4. Frame is flipped (facing)              |
        //5. Ptr to bitmap art | 6. Width of each frame on sprite sheet    |
        //7. H of frame sprite | 8. Total number of frames on sprite sheet |
        //------------------------------------------------------------------
        //           1.      2.  3.  4.  5.  6. 7.  8.
        //           |       |   |   |   |   |  |   |
        //           V       V   V   V   V   V  V   V
        Actor thing(buffer, 50, 50, 0, guy, 50, 64, 8);

        thing.set_col_rect(60, 59, 80, 110);
        char direc[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, direc);
        string directory_map; directory_map.append(direc); directory_map.append(mappy_file_path);

        write_status_screen("Loading map: ");
        write_status_screen(directory_map);

        rest(150);

        if (MapLoad((char *)directory_map.c_str()) != 0){
            write_status_screen("MAP LOAD FAILED\nCheck Map Level Text files");
            allegro_message("MAP LOAD FAILED. ABORTING\nCheck Map Level Text files");
            return;
        }

        write_status_screen("Map Loaded Successfully. Leading into game routine.");

        rest(150);

        int framect = 0;

        RECT rectangle;
        float dx = 0 , dy = 0;
        int x = 50, y = 50; //Starting position of character

        bool jumpstate = false;
        int gravity = 3;
        int x_acceleration = 1;


        while(!key[KEY_ESC]){ //Quit if KEY_ESC == true


    //The first step is to retrieve input from the user
            if(key[KEY_SPACE] && !jumpstate){
                dy = -35;  //If space is pressed, destination is to -35 pixels
                jumpstate = true;
            }
            if(key[KEY_LEFT] && game_tick % 4 == 0){
                dx -= x_acceleration;
                framect++; //As the user is pressing left or right keys we update the framecount for walking animation
            }
            if(key[KEY_RIGHT] && game_tick % 4 == 0){
                dx += x_acceleration;
                framect--;
            }

    //Then we apply the input from user into the actor or thing we want to move
        dy*=.9; //As we multiply by .9 the number gets smaller and smaller hence simulating friction or gravity
        dx*=.9;
        x += dx; //Apply destination
        y += dy;

        //Insert data into the object
        thing.update_position(x, y);


        //Retrieve our collision rectangle
        rectangle = thing.getrect();
        //Obtain results
        //If the input from the user will be checked for collisions.

        Colision_Result results = FG_COLISSION(rectangle, xoff, yoff, 0);

        //If the input from the user trips any of the flags then we must readjust
         // the dx, dy, x, and y variables to satisfy game restrictions
        if(results.left){
            x += x_acceleration+1; //Add 1 so we actually dont permanently stick to the wall
        //cout << "\nresults: " << dx;
            dx = 0;
        }

        if(results.right){
            x -= x_acceleration;  //Add 1 so we actually dont permanently stick to the wall
            dx = 0;
        }

        if(results.top){

            dy = 0;
        }

        if(results.bot){ //If bottom collision happens

            if(!jumpstate){ //stop acceleration if you are not jumping
                y -= dy; //If you find that the collision rectangle goes inside map tile, uncomment this line.
                dy = 0;
            }else{
                y-= dy;
                dy = 0;
            }
            jumpstate = false;

        }else{          //Apply gravity
            dy+=gravity;
            dy*= .9;
        }

        //Once the game restrictions have been applied to user input, readjust the position of game actor.
        thing.update_position(x, y);
        rectangle = thing.getrect();

        //If the framecount counter exceeds or deceeds number of frames(going negative), keep it within bounds
        //Use for walking animations, etc....
            if (framect > 8)
                framect = 0;
            if (framect < 0)
                framect = 8;


        //clear(screen);

    //help here....
        xoff = (thing.getxpos() );
        xoff +=  thing.getxpos()*(mapwidth*mapblockwidth / WIDTH);
        yoff = thing.getypos() ;

        //The map scrolls as the character moves around.

        //If the scrolling variable is bigger than the actual
        //width of the map in pixels minus width of the screen, then we keep it within bounds.

        if(xoff >= (mapwidth*mapblockwidth-WIDTH)){
            xoff =  (mapwidth*mapblockwidth-WIDTH);
        }
        if(xoff < 0){
            xoff = 0;
        }

        if(yoff >= (mapheight*mapblockheight-HEIGHT)){
            yoff = mapheight*mapblockheight-HEIGHT;
        }
        if(yoff < 0){
            yoff = 0;
        }

               //Draw BG background and FG foreground
                MapDrawBG(buffer, xoff, yoff, 0, 0, WIDTH-1, HEIGHT-1);
                MapDrawFG(buffer, xoff, yoff, 0, 0, WIDTH-1, HEIGHT-1, 0);

                //Draw object and collision rectangle
                thing.display(framect);
                rect(buffer, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, WHITE);
                textprintf_ex(buffer, font, 0, 460, WHITE, 0, "Frames Drawn: %i", frames_drawn);
                textprintf_ex(buffer, font, 0, 470, WHITE, 0, "OG_MASTERS ALPHA v1.337 -INDUSTRIAL STRENGTH-");

                //Copy buffer to screen
                blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
                game_tick++;
                frames_drawn++;
                rest(8);
                //The rest was personal preference. I wanted to limit the framerate below my Monitor's refresh rate.
            vsync();
        }

        //Garbage Collection:
          //  BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
           // BITMAP *guy = load_bitmap("guy.bmp", NULL);


        destroy_bitmap(buffer);
        destroy_bitmap(guy);
        MapFreeMem();

        rest(200);



}
