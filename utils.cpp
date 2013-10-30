#include "utils.h"

void printText( int x, int y, char *st, void *font,float r,float g,float b){
	int i,len;
	len = strlen(st);
	glColor3f(r,g,b);
	glRasterPos2i( x, y);
	for( i=0; i < len; i++){
		glutBitmapCharacter(font, st[i]); // Print a character on the screen
	}
	glColor3f(1.0, 1.0, 1.0);
}


void printChar (int x, int y, char c, void *font, float r, float g,  float b) {
	glColor3f(r,g,b);
	glRasterPos2i( x, y);
	glutBitmapCharacter(font, c); // Print a character on the screen
	glColor3f(1.0, 1.0, 1.0);
}


bool folderExists(const char* folderName) {
	DWORD attribs = ::GetFileAttributes(folderName);
	if(attribs == INVALID_FILE_ATTRIBUTES) return false;
	return (attribs & FILE_ATTRIBUTE_DIRECTORY)!= 0;
}