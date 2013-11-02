#pragma once
#include "Globals.h"

class Shader
{
public:
	Shader(void);
	~Shader(void);
		
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	int loadShader(char *fileName, unsigned long* len, int kind);
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	int unloadShader(int kind);
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	int compileShader(int kind);
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	int linkShader(int kind);
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	GLchar *getCompilationLog(int kind);
	//kind has to be {VERTEX|GEOMETRY|FRAGMENT} shader
	GLchar *getLinkingLog(int kind);

	int useShader(int kind);

private:
	GLchar *ShaderSource[MAX_SHADERS];
	bool shadersLoaded[MAX_SHADERS];

	GLuint ShaderObject[MAX_SHADERS];
	GLuint ShaderProgram[MAX_SHADERS];
};

