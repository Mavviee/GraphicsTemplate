#include "cSkybox.h"
#include "core.h"





//////////////////////////////////////////////////////////////////////////////////////////
// cSkybox() - constructor
//////////////////////////////////////////////////////////////////////////////////////////
cSkybox::cSkybox()
{
	
	m_tex = NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////
// ~cSkybox() - destructor
//////////////////////////////////////////////////////////////////////////////////////////
cSkybox::~cSkybox()
{
	if (m_tex)
	{
		for (int i = 0; i < 6; i++)
		{
			delete[] m_tex[i];
			m_tex[i] = NULL;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
// init() - 
//////////////////////////////////////////////////////////////////////////////////////////
void cSkybox::init()
{
	// load in all textures for this environment map here..
	for(int i = 0; i < 6; i++){
		
		cTex.loadCubeMapTGA(m_tex[i], i);
		//m_tex[i] = loadCubeMapTGA(names[i], i);
	}
	
	
}

void cSkybox::update(cScene* pScene, vec3 PlayerPosition)
{
    cCamera* camera = &pScene->m_Camera[pScene->m_cameraId];
   
    //store cameras position and fov
    vec3 camReset = PlayerPosition + vec3(0.0f, 1.f, 6.0f);

    //camera->m_pos;


    // position camera inside the player object
    camera->m_pos = PlayerPosition ; 
    camera->m_fov = 90.0f;      // change to 90 fov to get a more accurate cube map 
    camera->init();

    // 6 passes ( for loop happens 6 times)
    for (int i = 0; i < 6; i++)
    {
        // make camera at direction e.g left, right, up, down, forward and backwards
        camera->LookAt(direction[i]);

        pScene->backBufferRender(); // render scene 
        // read the back buffer 
        glReadBuffer(GL_BACK);

        // update cube i cube map texture for this iteration. ie left or right 
        glCopyTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 0, 0, 1024.0f, 1024.0f, 0);
        glDrawBuffer(GL_BACK);

        // sets paramaters 
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    }
    // set camera properties back to original 
    camera->m_pos = camReset;

    camera->m_fov = 45;
    camera->init();
    camera->LookAt(direction[4]);
}



