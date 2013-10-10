#include "run_game_headers_definition.h"


Colision_Result FG_COLISSION(RECT rcte, int xoff, int yoff, float yoffx){

/*This Function is to be used with the Collision_Results structure*/
/*Use this function only to check collision with mappy foreground tiles*/
/*A different function will be used for actual game environment object collision detection*/
/*Note that this only works for blocks of 24x24 pixels*/
/*Change '24' to the desired setting*/

/*NOTE! If you wish to use a big rectangle, implement a for loop to check a
collision rectangle that has bigger width or height than the height or width of each map tile

**** test_top = WIDTH_OR_HEIGH_OF_TILE / WIDTH_OR_HEIGHT_OF_COLLISION_RECTANGLE
Implement for loop yet to be added
*/

    RECT rct;

    BLKSTR *blockdata;  //Instantiate a mappy blkstructure pointer
    Colision_Result results{false, false, false, false, rct,0, 0};   //Set the collision results structure as if nothing has collided

/* *******************************************
Assign rectangle values + the offset of the map.
This is so we can get the real position of the
rectangle on the map instead of it merely on the viewing screen
*****************************************************/
    rct.top = rcte.top + yoff;
    rct.bottom = rcte.bottom + yoff;
    rct.left = rcte.left + xoff;
    rct.right = rcte.right + xoff;


    int width = rcte.right-rcte.left;
    int length = rcte.bottom - rcte.top;
    results.length_col_rect = length;
    results.width_col_rect = width;

/*The work flows as follows:
1. Obtain a certain tile from the map at X,Y coordinates
2. If a certain flag is checked along the X,Y coordinates of the rect structure passed, then we have a collision
3. Set the corresponding colision_results flags to true
*/

        //As the block approaches the top left from left side
        blockdata = MapGetBlockInPixels((int)rct.left+5, (int)rct.top);

        if(blockdata->bl || blockdata->br){
            results.top = true;
        }

        //As block approaches the top right from right side
        blockdata = MapGetBlockInPixels(rct.right-5, (int)rct.top);
        if(blockdata->bl || blockdata->br){
            results.top = true;

        }

        //As tile approaches bottom from left side going left
        blockdata = MapGetBlockInPixels((int)rct.right-5 , (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //As tile approache bottom from right going right
        blockdata = MapGetBlockInPixels((int)rct.left+5, (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //check bottom middle
        blockdata = MapGetBlockInPixels((int)rct.left+(width/2) , (int)rct.bottom) ;
        if(blockdata->tl || blockdata->tr){
                results.bot = true;
        }

        //As tile approaches left side going down
        blockdata = MapGetBlockInPixels((int)rct.left, (int)rct.top+10);
        if(blockdata->tl || blockdata->bl){
            results.left = true;
        }
        //As tile approaches left side going up
        blockdata = MapGetBlockInPixels((int)rct.left, rct.bottom-10) ;
        if(blockdata->tl || blockdata->bl){
                results.left = true;
        }
        //As tile approaches right side going up
        blockdata = MapGetBlockInPixels((int)rct.right, (int)rct.bottom-10) ;
        if(blockdata->tr || blockdata->br){
                results.right = true;
        }

        blockdata = MapGetBlockInPixels(rct.right, (int)rct.top+10);
        if(blockdata->tr || blockdata->br){
            results.right = true;
        }

    return results;
}
