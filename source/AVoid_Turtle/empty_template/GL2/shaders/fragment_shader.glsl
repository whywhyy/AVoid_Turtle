/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/

#version 330

uniform vec4 light_position;
uniform vec4 light_product_ambient;
uniform vec4 light_product_diffuse;
uniform vec4 light_product_specular;
uniform float mat_shininess;

in vec4 v;
in vec4 N;

out vec4 frag_color;

// https://www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.1.50.pdf
void main()
{
	vec3 L = (normalize(light_position.xyz - v.xyz)).xyz;
	vec3 E = (normalize(-v.xyz)).xyz;	// we are in Eye Coordinates, so EyePos is (0,0,0)  
	vec3 R = (normalize(-reflect(L.xyz, N.xyz))).xyz;

	//calculate Ambient Term:  
	vec4 Iamb = light_product_ambient;

	//calculate Diffuse Term:  
	vec4 Idiff = light_product_diffuse * max(dot(N.xyz, L.xyz), 0.0);

	// calculate Specular Term:
	vec4 Ispec = light_product_specular	* pow(max(dot(R, E), 0.0), 0.3*mat_shininess);

	// write Total Color:  
	frag_color = Iamb + Idiff + Ispec;
};