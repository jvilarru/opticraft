#pragma once
#include "Globals.h"

#define String char*

void printText( int x, int y, char *st, void *font,float r,float g,float b);
void printChar( int x, int y, char c, void *font,float r,float g,float b);

bool folderExists(const char* folderName);

