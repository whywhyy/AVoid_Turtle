/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/

#pragma once

#include <glm/glm.hpp>

class GL2_Material
{
public:
	glm::vec4 ambient_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 diffuse_    = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
	glm::vec4 specular_ = glm::vec4(0.2, 0.2, 0.2, 1.0);
	glm::vec4 emission_  = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	float shininess_ = 5.0;

	GL2_Material()
	{
	}

	~GL2_Material()
	{
	}

	void setRed()
	{
		ambient_ = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
		diffuse_ = glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
		specular_ = glm::vec4(0.2, 0.2, 0.2, 1.0);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 5.0;
	}

	void setGold()
	{
		// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
		ambient_ = glm::vec4(0.24725f, 0.2245f, 0.00645f, 1.0f);
		diffuse_ = glm::vec4(0.8f, 0.4f, 0.001f, 1.0f);
		specular_ = glm::vec4(0.797357f, 0.523991f, 0.00208006f, 1.0f);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 83.2;
	}

	void setBlue() {  // blue
		ambient_ = glm::vec4(0.0f, 0.05f, 0.05f, 1.0f);
		diffuse_ = glm::vec4(0.4f, 0.5f, 0.5f, 1.0f);
		specular_ = glm::vec4(0.04f, 0.7f, 0.7f, 1.0f);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 15;
	}
	void setWhite() {  // white
		ambient_ = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
		 diffuse_ = glm::vec4( 0.5f,0.5f,0.5f,1.0f);
		specular_ = glm::vec4( 0.7f,0.7f,0.7f,1.0f);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 10.0f;
	}
	void setPerl() {  // perl
		ambient_ = glm::vec4(0.25f, 0.20725f, 0.20725f, 0.922f );
		diffuse_ = glm::vec4(1.0f, 0.829f, 0.829f, 0.922f );
		specular_ = glm::vec4(0.296648f, 0.296648f, 0.1296648f, 0.922f );
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 11.264f;
	}
	void setBlack() {
		ambient_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f );
		diffuse_ = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f );
		specular_ = glm::vec4(0.50f, 0.50f, 0.50f, 1.0f );
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 32.0f;
	}
	//
	//초록
	void setEmerald() {
		ambient_ = glm::vec4(0.0215f, 0.1745f, 0.0215f, 0.55f );
		diffuse_ = glm::vec4(0.07568f, 0.61424f, 0.07568f, 0.55f );
		specular_ = glm::vec4(0.633f, 0.727811f, 0.633f, 0.55f);
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ = 76.8f;
	}
	//
	//초록2
	void setGreen() {
		//Green rubberfloat[] mat_ambient ={ 0.0f,0.05f,0.0f,1.0f };
		diffuse_ = glm::vec4(0.4f,0.5f,0.4f,1.0f );
		specular_ = glm::vec4(0.04f,0.7f,0.04f,1.0f );
		emission_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		shininess_ =  10.0f;
	}
};
