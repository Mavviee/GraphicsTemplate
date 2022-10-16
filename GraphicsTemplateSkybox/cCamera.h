#pragma once
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class cCamera
{
public:
	cCamera();
	~cCamera();

	void init();
	void update();
	void LookAt(vec3 point)
	{
		vec3 up = vec3(0.0f, 1.0f, 0.0f);
		if ((point.y == 1.0f) || (point.y == -1.0f))
		{
			up = vec3(0.0f, 0.0f, point.y);
		}

		viewMatrix = glm::lookAtLH(m_pos, vec3(m_pos + point), up);
	}

	glm::mat4 projectionMatrix;		// projection matrix
	glm::mat4 viewMatrix;			// view matrix

	glm::vec3 m_pos;
	glm::vec3 m_rot;

	float m_fov;
	float m_near;
	float m_far;
};

