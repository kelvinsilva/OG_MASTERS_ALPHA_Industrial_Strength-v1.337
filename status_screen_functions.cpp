#include "status_screen_functions_header.h"


deque<string>messages;

const int max_messages_on_screen = 6;
const int message_pixel_offset = 10;
int messages_written = 0;

void clear_status_screen(){
    rectfill(screen, 0, 483, 1100, 550, 0);
}

void write_status_screen(string str){

    if (messages_written >= max_messages_on_screen){

        clear_status_screen();

        messages.pop_front();
        messages_written--;

    }
    messages.push_back(str);
    messages_written++;

    int height_text = 485;
    for(int messageswritten = 0; messageswritten < messages_written; messageswritten++){

        textprintf_ex(screen, font,0, height_text, WHITE, 0, messages[messageswritten].c_str());
        height_text+=message_pixel_offset;

        //*Debugging Purposes*//
        std::cout <<"\n" <<messages[messageswritten].c_str();

    }


}

