#include "Shader.h"


Shader::Shader(void)
{
	shadersLoaded[VERTEX_SHADER] = false;
	shadersLoaded[GEOMETRY_SHADER] = false;
	shadersLoaded[FRAGMENT_SHADER] = false;
}


Shader::~Shader(void)
{
}

unsigned long getFileLength(FILE *file) {
	fseek(file, 0, SEEK_END);
	unsigned long offset = ftell(file);
	fseek(file, 0, SEEK_SET);
	return offset;
}

int Shader::loadShader(char *fileName, unsigned long* len, int kind) {
	FILE *fd;
	fd = fopen(fileName, "r");
	if(fd != NULL) {
		if(kind < 0 || kind > 2) return ERR_NONEXISTENT_KIND_SHADER;

		int pos = kind;

		unsigned long len = getFileLength(fd);
		if(len==0) return ERR_EMPTY;

		ShaderSource[pos] = (GLchar*) new char[len+1];
		if (ShaderSource[pos] == 0) return ERR_OUT_MEM;   // can't reserve memory
   
		unsigned int i=0;
		int c;
		c = getc(fd);
		while (c != EOF) {
			ShaderSource[pos][i] = c;      // get character from file.
			c = getc(fd);
			i++;
		}
		ShaderSource[pos][i] = 0;  // 0-terminate it at the correct position
		fclose(fd);
		shadersLoaded[pos] = true;
		return OK;
	}
	return ERR_FD_NULL;
}

int Shader::unloadShader(int kind) {
	for(int i = 0; i<MAX_SHADERS; ++i) {
		delete[] ShaderSource[i];
		ShaderSource[i] = NULL;
	}
	return OK;
}

int Shader::compileShader(int kind) {
	if(kind < 0 || kind > 2) return ERR_NONEXISTENT_KIND_SHADER;
	
	GLint len;
	if(kind == VERTEX_SHADER) {
		ShaderObject[kind] = glCreateShader(GL_VERTEX_SHADER);
		len = strlen(ShaderSource[VERTEX_SHADER]);
		glShaderSource(ShaderObject[kind], 1, (const GLchar**)&ShaderSource[VERTEX_SHADER], &len);
	} else if(kind == GEOMETRY_SHADER) {
		ShaderObject[kind] = glCreateShader(GL_GEOMETRY_SHADER);
		len = strlen(ShaderSource[GEOMETRY_SHADER]);
		glShaderSource(ShaderObject[kind], 1, (const GLchar**)&ShaderSource[GEOMETRY_SHADER], &len);
	} else if(kind == FRAGMENT_SHADER) {
		ShaderObject[kind] = glCreateShader(GL_FRAGMENT_SHADER);
		len = strlen(ShaderSource[FRAGMENT_SHADER]);
		glShaderSource(ShaderObject[kind], 1, (const GLchar**)&ShaderSource[FRAGMENT_SHADER], &len);
	}
	glCompileShader(ShaderObject[kind]);

	GLint compiled;
	glGetObjectParameterivARB(ShaderObject[kind], GL_COMPILE_STATUS, &compiled);
	if(compiled) {
		return OK;
	}
	
	return ERR_COMPILE;
}

int Shader::linkShader(int kind) {
	if(kind < 0 || kind > 2) return ERR_NONEXISTENT_KIND_SHADER;

	ShaderProgram[kind] = glCreateProgram();
	glAttachShader(ShaderProgram[kind], ShaderObject[kind]);

	glLinkProgram(ShaderProgram[kind]);

	GLint linked;
	glGetProgramiv(ShaderProgram[kind], GL_LINK_STATUS, &linked);
	if(linked) {
		return OK;
	}

	return ERR_LINK;
}

GLchar* Shader::getCompilationLog(int kind) {
	if(kind < 0 || kind > 2) return NULL;

	GLint blen = 0;	
	GLsizei slen = 0;
	GLchar *compiler_log;
	glGetShaderiv(ShaderObject[kind], GL_INFO_LOG_LENGTH , &blen);       
	if (blen > 1) {
		compiler_log = (GLchar*)malloc(blen);
		glGetInfoLogARB(ShaderObject[kind], blen, &slen, compiler_log);
	}

	return compiler_log;
}

GLchar* Shader::getLinkingLog(int kind) {
	if(kind < 0 || kind > 2) return NULL;

	GLint blen = 0;	
	GLsizei slen = 0;
	GLchar *linker_log;
	glGetShaderiv(ShaderProgram[kind], GL_INFO_LOG_LENGTH , &blen);       
	if (blen > 1) {
		linker_log = (GLchar*)malloc(blen);
		glGetInfoLogARB(ShaderProgram[kind], blen, &slen, linker_log);
	}

	return linker_log;
}

int Shader::useShader(int kind) {
	if(kind < 0 || kind > 2) return ERR_NONEXISTENT_KIND_SHADER;
	glUseProgram(ShaderProgram[kind]);
	return OK;
}
