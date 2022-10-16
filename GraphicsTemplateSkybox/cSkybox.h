#pragma once
#include "core.h"
#include "cTexture.h"

class cSkybox
{
public:
	cSkybox();
	~cSkybox();
	void init();
	void update(class cScene* pScene, vec3 PlayerPosition);


		vec3 direction[6] = { vec3(1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0),
							  vec3(0.0, 1.0, 0.0), vec3(0.0, -1.0, 0.0),
							  vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, -1.0) };

		char** m_tex;

	//cTexture cTex;
	
private:

};