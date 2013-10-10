#ifndef BOX_LIST_CLASS_HPP_
#define BOX_LIST_CLASS_HPP_

//Kelvin Silva
//For use with allegro version < 5
//Makes a box with a list and a rectangle to select
//Current bugs: if you declare a box with length higher than size of display vector
//The box will scroll infinitely.
//Make sure the length of box is equal to or less than the amount of display contents on the vector

//Usage:
/*NOTE: I haven't implemented the way that this is going to be used with
dynamic memory (eg. new), so for the moment, only use this class on stack*/

/*
0. Declare box object and call constructor.

Constructor is as follows:
template<class Type1, class Type2>
BOX_LIST<Type1, Type2>::BOX_LIST(int x, int y, int l, int w, int thick, int col, BITMAP* bitmp, FONT *fon, int fonsz)
NOTE: Length semantically is used here as the downward size.
Width is the size going left and right.

Type 1 is the vector type that you want to display as a list
Type 2 is the vector that matches the display but contains an actual value
Think of it as an improvised std::map;

x, and y :: are the starting position (top left corner) of box
l and w :: are the width of box, this determines overall size.
thick :: is how thick the outisde of the box will be.
col :: is color of box using allegro's makecol() function.
bitmp ::  is where the box will be drawn to. Note this class uses vector graphics function
fon :: is the font used to make the box. The height of each letter on the font is fonsz.
It is very important that fonsz be an accurate number or else display() wont work correctly.

*/

/*
1. call load_display_array. It can be any array that matches the type used in constructor.
2. call load_value_array. ->self explanatory.
3. call display(). It draws the box onto bitmap.
4. Handle select_down and select_up functions.
*/

#include <allegro.h>
#include <winalleg.h>
#include <vector>
#include <string>
#include "CUSTOM_FUNCTIONS_HEADER.h"

using std::string;
using std::vector;

template<class Type1, class Type2>
class BOX_LIST{

private:

    int xpos, ypos; //Note that this deontes top right corner.... //Starting position of the box
    int sizex2, sizey2; //This is the second corner of the triangle required by the rect() function. Calculate by length and width
    int thickness_box;  //Thickness means how thick the outline of the box is. Each unit of thicknes is equivalen to 1 pixel thickness.
    //This is left alone. Its calculated by the constructor of the function
    int length, width;



    int shift_start; //When you scroll down think of a window on an array.
                     //You can only see certain items at a time.
                     //When you move the shift, you scroll through the array.

    int cursorposct; //Cursor position count
                     //Tells us which item index of vector we are

    int items_per_box; //How many items per box are displayed.

    //These four integers indicate the size of selection rectangle
    int cursorx1, cursory1, cursorx2, cursory2;



    BITMAP *draw_surface; //Which bitmap to draw to.
    FONT *font_box; //Font of each letter used

    int font_sz; //Font size
    int color; //Color of box and font

    vector<Type1> box_contents_display;
    vector<Type2> box_contents_value;

    //These private functions manipulate the shift based on select_down or up
    void scroll_up();
    void scroll_down();

    //This function is used by display().
    //Just made sense to split it up and makes easier to read.
    void display_cursor();


public:

           //sizex1, sizey1, sizex2, sizey2, thickness, itemsperbox, contents of box.
    BOX_LIST(int, int, int, int, int, int, BITMAP*, FONT*, int);
    ~BOX_LIST();

    //This function returns 0 if a number is negative.
    //Absolute value didnt really work for my uses
    friend int if_neg_ret_zero(int);

    void select_up(); //Moves the selection cursor up
    void select_down(); //Down
    void display(); //Draws to bitmp

    void load_display_array(vector<Type1>);
    void load_value_array(vector<Type2>);


    int return_index_content(); //Returns index
    //These values are determined upon the index_content return value.
    //I.e what is selected = is the index content
    Type1 return_display_content(); //Returns display content
    Type2 return_value_content(); //Returns value array content


};

template<class Type1, class Type2>
BOX_LIST<Type1, Type2>::BOX_LIST(int x, int y, int l, int w, int thick, int col, BITMAP* bitmp, FONT *fon, int fonsz){

        xpos = x;
        ypos = y;

        length = l;
        width = w;

        sizex2 = (x+width);
        sizey2 = (y+length);

        thickness_box = thick;


        color = col;

        draw_surface = bitmp;
        font_box = fon;
        font_sz = fonsz;

        items_per_box = (length/font_sz);

        cursorx1 = xpos+2;
        cursory1 = 0; //NOTE: ***!!!!*** Since x position on cursor always stays the same, it is safe to assign on constructor
                      //Since the y position is constantly changing, that is why we assign it to zero on constructor
                      //But we manipulate Y values of cursor in the display_cursor_function.
        cursorx2 = sizex2-2;
        cursory2 = 0;

        shift_start = 0;
        cursorposct = 0;

}

template<class Type1, class Type2>
BOX_LIST<Type1, Type2>::~BOX_LIST(){



}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::display(){


    for(int i = 0; i < thickness_box; i++){
        rect(draw_surface, xpos+i, ypos+i, sizex2+i, sizey2+i, color);
    }

    int x = 0;
    for(int i = shift_start; i < box_contents_display.size() && i < items_per_box+shift_start; i++, x++){

       textprintf_ex(draw_surface, font_box, xpos+thickness_box+5, ypos+thickness_box+(x*font_sz) , color, -1, box_contents_display[i].c_str());

    }

    display_cursor();

}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::display_cursor(){

    cursory1 = if_neg_ret_zero((ypos+(cursorposct*font_sz)));
    cursory2 = if_neg_ret_zero((ypos+2+font_sz+(cursorposct*font_sz)));

    rect(draw_surface, cursorx1+thickness_box+2, cursory1,  cursorx2-2, cursory2, color);
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::scroll_up(){

    shift_start--;
    shift_start = if_neg_ret_zero(shift_start);
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::scroll_down(){

    shift_start++;
    if(shift_start >= box_contents_display.size() - items_per_box){
        shift_start = box_contents_display.size() - items_per_box;
    }
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::select_up(){


    cursorposct--;
    if(cursorposct < 0){
        cursorposct = 0;
        scroll_up();
    }
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::select_down(){

    cursorposct++;
    if(cursorposct >= items_per_box){
        cursorposct = items_per_box-1;
        scroll_down();
    }
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::load_display_array(vector<Type1> disp){
    box_contents_display = disp;
}

template<class Type1, class Type2>
void BOX_LIST<Type1, Type2>::load_value_array(vector<Type2> val){
    box_contents_value = val;
}

template<class Type1, class Type2>
int BOX_LIST<Type1, Type2>::return_index_content(){
    return cursorposct+shift_start;
}

template<class Type1, class Type2>
Type1 BOX_LIST<Type1, Type2>::return_display_content(){
    return box_contents_display[return_index_content()];
}

template<class Type1, class Type2>
Type2 BOX_LIST<Type1, Type2>::return_value_content(){
    return box_contents_value[return_index_content()];
}
#endif // BOX_LIST_CLASS_HPP_
