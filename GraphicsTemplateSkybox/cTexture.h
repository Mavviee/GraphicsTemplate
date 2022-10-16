#pragma once
#include "core.h"

class cTexture
{
public:
	cTexture() {}
	~cTexture() {}

	int loadTGA(char* TexName, GLuint TexHandle, GLuint textureID);
	int loadCubeMapTGA(char* TexName, int face);
};

extern cTexture cTex;
