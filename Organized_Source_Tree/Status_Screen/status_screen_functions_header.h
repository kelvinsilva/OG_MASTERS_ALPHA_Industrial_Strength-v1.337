#ifndef STATUS_SCREEN_FUNCTION_H_
#define STATUS_SCREEN_FUNCTION_H_

#include <allegro.h>
#include <string>
#include <deque>
/*Debugging Purposes*/
#include <iostream>

#define WHITE makecol(255,255,255)

using std::string;
using std::deque;

void write_status_screen(string);

void clear_status_screen();

#endif
