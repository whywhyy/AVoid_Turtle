/*
Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
for Introduction to Computer Graphics, 2017 Spring
*/
#include <utility> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <GL/freeglut.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include "Geometry/TriangularSurface/StaticTriangularSurface.h"
#include "GL2/GL2_Object.h"
#include "GL2/GL2_World.h"
#include "GL2/GL2_Light.h"
#include "GL2/GL2_Material.h"
#include "ParticleSystem.h"
#include <time.h>
#include "BMPImage.h"
#include <queue>


int which_move = 0;

std::queue< std::pair<int, int> > detection;//save turtle x,z//

int width_window = 640;
int height_window = 480;
/////////////////////////////////////////
float step[5] = { 0, 0, 0, 0, 0 };
///////////////////////////////////////////w
GL2_World gl_world;
bool pressW = false;
bool pressA = false;
bool pressD = false;
StaticTriangularSurface surface1;
StaticTriangularSurface mario_stand_surface;
StaticTriangularSurface mario_move_surface;

StaticTriangularSurface turtle_1_surface;
StaticTriangularSurface turtle_2_surface;
StaticTriangularSurface turtle_3_surface;
StaticTriangularSurface turtle_4_surface;
StaticTriangularSurface turtle_5_surface;
StaticTriangularSurface turtle_6_surface;
StaticTriangularSurface turtle_7_surface;
StaticTriangularSurface turtle_8_surface;
StaticTriangularSurface turtle_9_surface;
StaticTriangularSurface turtle_10_surface;
StaticTriangularSurface turtle_11_surface;
StaticTriangularSurface turtle_12_surface;


GL2_Object gl_obj1;
GL2_Object gl_obj_mario_stand;
GL2_Object gl_obj_mario_move;


GL2_Object gl_obj_turtle_1;
GL2_Object gl_obj_turtle_2;
GL2_Object gl_obj_turtle_3;
GL2_Object gl_obj_turtle_4;
GL2_Object gl_obj_turtle_5;
GL2_Object gl_obj_turtle_6;
GL2_Object gl_obj_turtle_7;
GL2_Object gl_obj_turtle_8;
GL2_Object gl_obj_turtle_9;
GL2_Object gl_obj_turtle_10;
GL2_Object gl_obj_turtle_11;
GL2_Object gl_obj_turtle_12;


ParticleSystem ps(0,0.85,0);
ParticleSystem ps_1(-0.7,-0.52,0);
ParticleSystem ps_2(+0.7, -0.52, 0);

clock_t begin, end;
clock_t mario_move_time;

TV mario_s_loc;
TV mario_m_loc;


int move_count = 3;
int finish_count = 150;///////////끝나는 push갯수
bool ground_move_W = false;

float draw_ground_centor_x = -2;
float draw_ground_centor_z = 0;

//////////////////////////////////////
StaticTriangularSurface surface_box;
GL2_Object gl_box;
void generateBOX() {
	gl_box.initPhongSurface(surface_box);
	gl_box.mat_.setRed();
}
void MoveBox() {
	if ( 1 < move_count && move_count <= 3) {
		surface_box.translate(TV(+1, 0, 0));
		gl_box.updatePhongSurface(surface_box);
	}
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	gl_world.camera_.UpdateDolly(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		gl_world.camera_.StartMouseRotation(xpos, ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		gl_world.camera_.EndMouseRotation(xpos, ypos);
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		gl_world.camera_.StartMousePan(xpos, ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		gl_world.camera_.EndMousePan(xpos, ypos);
	}
}

int lastx = 0;
int lasty = 0;
int xrot = 0;
int yrot = 0;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int diffx = xpos - lastx; //check the difference between the current x and the last x position
	int diffy = ypos - lasty; //check the difference between the current y and the last y position
	lastx = xpos; //set lastx to the current x position
	lasty = ypos; //set lasty to the current y position
	xrot += (float)diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float)diffx;// set the xrot to yrot with the addition of the difference in the x position

	gl_world.camera_.ProcessMouseMotion(xpos, ypos);
}

//bool leftMouseButtonDown = false;
// Camera. Params: location, rotation (degrees), window width & height
//Camera camera(vec3(0.0f), vec3(0.0f), windowWidth, windowHeight);
// Callback function to handle mouse movement
//void handleMouseMove(GLFWwindow *window, double mouseX, double mouseY)
//{
//	 We'll only look around when the left mouse button is down
//	if (leftMouseButtonDown)
//	{
//		camera.handleMouseMove(window, mouseX, mouseY);
//	}
//}

//////////////////////////////////////////////////////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	//////////////////////////////////////
	if (key == GLFW_KEY_Q) {
		gl_world.camera_.pan_.x += 0.01;
		std::cout << "x " << gl_world.camera_.pan_.x << '\n';
		std::cout << "y " << gl_world.camera_.pan_.y << '\n';
		std::cout << "z " << gl_world.camera_.pan_.z << '\n';

		std::cout << "dx " << gl_world.camera_.dolly_.x << '\n';
		std::cout << "dy " << gl_world.camera_.dolly_.y << '\n';
		std::cout << "dz " << gl_world.camera_.dolly_.z << '\n';
		//gl_world.camera_.
	}

	if (key == GLFW_KEY_E) {
		//pressE = true;
	


		ps.advanceOneTimeStep(0.009f);

		if (ps.count < 2000) {
			ps.count++; 
			ps_1.count++;
			ps_2.count++;
		}

		ps_1.advanceOneTimeStep(0.009f);
		if (ps_1.count < 2000) {
			ps.count++;
			ps_1.count++;
			ps_2.count++;
		}

		ps_2.advanceOneTimeStep(0.009f);
		if (ps_2.count < 2000) {
			ps.count++;
			ps_1.count++;
			ps_2.count++;
		}
	}
	//////////////////////////////////////
	//dolly
	//촬영기가 앞뒤로 이동할 수 있도록 바퀴를 부착한 이동용 촬영대
	//촬영대가 이동하는 코드. 
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		//gl_world.camera_.dolly_.z+=0.1;
		if (!pressW) {
			pressW = true;
			gl_obj1.initPhongSurface(surface1);
			gl_obj1.mat_.setBlue();
			gl_obj_mario_stand.initPhongSurface(surface1);
			gl_obj_mario_stand.mat_.setGold();
			gl_obj_mario_move.initPhongSurface(surface1);
			gl_obj_mario_move.mat_.setGold();
			begin = clock();        // 시간설정
			generateBOX();
		}
		else {
			if (finish_count > 0) {
				ground_move_W = true;
				finish_count--;
				std :: cout << "f co " << finish_count << '\n';
				MoveBox();// move turtle
				//MoveGround();  //move  ground
				mario_move_time = clock(); // 마리오가 움직인 시간
			}
			else { // finish
				
			}
		}
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (move_count > 1) {
			//gl_world.camera_.dolly_.x -= 0.5;
			move_count--;
			 pressA = true;/////////A Press
		}
		if (!pressW) {
			pressW = true;
			gl_obj1.initPhongSurface(surface1);
			gl_obj1.mat_.setBlue();
			gl_obj_mario_stand.initPhongSurface(surface1);
			gl_obj_mario_stand.mat_.setGold();
			gl_obj_mario_move.initPhongSurface(surface1);
			gl_obj_mario_move.mat_.setGold();
			begin = clock();        // 시간설정
			generateBOX();
		}
		else {
			mario_move_time = clock(); // 마리오가 움직인 시간
		}
	}
	if (key == GLFW_KEY_S) {
		//gl_world.camera_.dolly_.z -= 0.1;
		if (!pressW) {
			pressW = true;
			gl_obj1.initPhongSurface(surface1);
			gl_obj1.mat_.setBlue();
			gl_obj_mario_stand.initPhongSurface(surface1);
			gl_obj_mario_stand.mat_.setGold();
			gl_obj_mario_move.initPhongSurface(surface1);
			gl_obj_mario_move.mat_.setGold();
			begin = clock();        // 시간설정
			generateBOX();
		}
		else {
			mario_move_time = clock(); // 마리오가 움직인 시간
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (move_count < 5) {
			//gl_world.camera_.dolly_.x += 0.5;
			move_count++;
			pressD = true; /////////Press D
		}
		if (!pressW) {
			pressW = true;
			gl_obj1.initPhongSurface(surface1);
			gl_obj1.mat_.setBlue();
			gl_obj_mario_stand.initPhongSurface(surface1);
			gl_obj_mario_stand.mat_.setGold();
			gl_obj_mario_move.initPhongSurface(surface1);
			gl_obj_mario_move.mat_.setGold();
			begin = clock();        // 시간설정
			generateBOX();
		}
		else {
			mario_move_time = clock(); // 마리오가 움직인 시간
		}
	}
	//if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
	//	gl_world.camera_.dolly_.y -= 0.1;
	//}
}
///////////////////////////////////////////////////////////////


int main(void)
{


	//////////////////////////////////
	std::queue<TV> ground_q; // 땅 색깔 30개 저장
	for (int i = 0; i < 30; i++) {
		float rand_ground1 = (float)rand() / RAND_MAX;
		float rand_ground2 = (float)rand() / RAND_MAX;
		float rand_ground3 = (float)rand() / RAND_MAX;
		ground_q.push(TV (rand_ground1, rand_ground2, rand_ground3));
	}
	/////////////////////////////////
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_SAMPLES, 32);

	// window resolution
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width_window = mode->width * 0.8f;
	height_window = mode->height * 0.8f;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Avoid turtle !", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	////////////////////////////////////////////////////////////////////////
	glfwSetKeyCallback(window, key_callback);
	////////////////////////////////////////////////////////////////////////
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(1, 1, 1, 1); // while background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	const float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glOrtho(-1.2*aspect, 1.2*aspect, -1.2, 1.2, -100.0, 100.0);
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0, 1, 0);//camera takes care of it

	const float zNear = 0.001, zFar = 100.0, fov = 45.0;			// UI
	gl_world.camera_.Resize(width, height, fov, zNear, zFar);
	gl_world.initShaders();

	//	glEnable(GL_MULTISAMPLE);
	///
	StaticTriangularSurface surface;
	///



	mario_stand_surface.readObj("mario_stand.obj", true, true);
	mario_move_surface.readObj("mario_move.obj", true, true);
    
	///////////////
	//
	turtle_1_surface.readObj("turtle.obj", true, true);
	turtle_2_surface.readObj("turtle.obj", true, true);
	turtle_3_surface.readObj("turtle.obj", true, true);
	turtle_4_surface.readObj("turtle.obj", true, true);
	turtle_5_surface.readObj("turtle.obj", true, true);
	turtle_6_surface.readObj("turtle.obj", true, true);
	turtle_7_surface.readObj("turtle.obj", true, true);
	turtle_8_surface.readObj("turtle.obj", true, true);
	turtle_9_surface.readObj("turtle.obj", true, true);
	turtle_10_surface.readObj("turtle.obj", true, true);
	turtle_11_surface.readObj("turtle.obj", true, true);
	turtle_12_surface.readObj("turtle.obj", true, true);
	///////////////////////
	//start 위치 setting //
	//1팀
	gl_obj_turtle_1.mat_.setEmerald();
	gl_obj_turtle_2.mat_.setBlack();
	gl_obj_turtle_3.mat_.setGold();
	turtle_1_surface.translate(TV(-2, 0, -2));
	turtle_2_surface.translate(TV(-1, 0, -2));
	turtle_3_surface.translate(TV(0, 0, -2));
	//
	detection.push(std:: make_pair(-2, -2));
	detection.push(std::make_pair(-1, -2));
	detection.push(std::make_pair(0, -2));
	//2팀
	gl_obj_turtle_4.mat_.setBlue();
	gl_obj_turtle_5.mat_.setRed();
	gl_obj_turtle_6.mat_.setGreen();
	turtle_4_surface.translate(TV(-1, 0, -4));
	turtle_5_surface.translate(TV(0,  0, -4));
	turtle_6_surface.translate(TV(1,  0, -4));
	//	
	detection.push(std::make_pair(-1, -4));
	detection.push(std::make_pair(-0, -4));
	detection.push(std::make_pair(1, -4));
	//3팀
	gl_obj_turtle_7.mat_.setGold();
	gl_obj_turtle_8.mat_.setEmerald();
	gl_obj_turtle_9.mat_.setWhite();
	turtle_7_surface.translate(TV(0, 0, -6));
	turtle_8_surface.translate(TV(1, 0, -6));
	turtle_9_surface.translate(TV(2, 0, -6));
	//
	detection.push(std::make_pair(0, -6));
	detection.push(std::make_pair(1, -6));
	detection.push(std::make_pair(2, -6));
	//4팀
	gl_obj_turtle_10.mat_.setPerl();
	gl_obj_turtle_11.mat_.setRed();
	gl_obj_turtle_12.mat_.setGreen();
	turtle_10_surface.translate(TV(-2, 0, -8));
	turtle_11_surface.translate(TV(0, 0, -8));
	turtle_12_surface.translate(TV(2, 0, -8));
	//
	detection.push(std::make_pair(-2, -8));
	detection.push(std::make_pair(0, -8));
	detection.push(std::make_pair(2, -8));
	//
	//////////////


	//mario_stand_surface.vertex_uv_.init(mario_stand_surface.vertex_positions_.num_elements_);/////

	//GLuint textures[2];
	//glGenTextures(2, textures);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textures[0]);

	//int texture_width, texture_height;
	//unsigned char *rgb_array = nullptr;
	//readBMP24("apple.bmp", &texture_width, &texture_height, &rgb_array);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_width, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_array);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	///////////////////////////////////////////////////////////////////////////////

	//surface.readObj("BuddhaSculpture.obj", true, true);
	//surface.readObj("BuddhaSculpture.obj", true, true);
	///////////////
	///	
	surface_box.readObj("box.obj", true, true);
	surface_box.translate(TV(-3, 0, 0));
	///
	////////////////////////////////////
	mario_stand_surface.translate(TV(0, 0.59, 0));
	mario_move_surface.translate(TV(0, 0.54, 0));
	mario_stand_surface.rotate(3.0, TV(0, 1, 0));
	mario_move_surface.rotate(1.6, TV(0, 1, 0));

	surface1.readObj("CluT.obj", true, true);

	////////////////////////////////////////////////////////////
	////_CRT_SECURE_NO_WARNINGS - preprocessor에 추가  // Texture
	////mario_stand_surface.vertex_uv_.init(mario_stand_surface.vertex_positions_.num_elements_);
	//for (int i = 0; i < mario_stand_surface.vertex_positions_.num_elements_; ++i)
	//{// we use 실린더 space 
	//	glm::vec2 ray_xy(mario_stand_surface.vertex_positions_[i].x_, mario_stand_surface.vertex_positions_[i].z_);
	//	glm::vec2 x_axis(1.0f, 0.0f);
	//	float theta = acos(dot(glm::normalize(ray_xy), x_axis));

	//	if (ray_xy.y < 0.0) theta *= -1;  // simple tric for noise part 

	//	mario_stand_surface.vertex_uv_[i].x_ = theta / 3.141592f + 0.5f;
	//	mario_stand_surface.vertex_uv_[i].y_ = mario_stand_surface.vertex_positions_[i].y_ + 0.5f;
	//}
	/////////////////////////////////////////	////////////


	//gl_obj.mat_.setRed();

	/////////////////////
	///initPhongSurface(surface1);
	//gl_obj1.mat_.setRed();



	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_COLOR_MATERIAL);


	glLoadIdentity();

	GL2_Light light;






	//
	gl_obj_turtle_1.initPhongSurface(turtle_1_surface);
	gl_obj_turtle_2.initPhongSurface(turtle_2_surface);
	gl_obj_turtle_3.initPhongSurface(turtle_3_surface);
	gl_obj_turtle_4.initPhongSurface(turtle_4_surface);
	gl_obj_turtle_5.initPhongSurface(turtle_5_surface);
	gl_obj_turtle_6.initPhongSurface(turtle_6_surface);
	gl_obj_turtle_7.initPhongSurface(turtle_7_surface);
	gl_obj_turtle_8.initPhongSurface(turtle_8_surface);
	gl_obj_turtle_9.initPhongSurface(turtle_9_surface);
	gl_obj_turtle_10.initPhongSurface(turtle_10_surface);
	gl_obj_turtle_11.initPhongSurface(turtle_11_surface);
	gl_obj_turtle_12.initPhongSurface(turtle_12_surface);
	///

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		gl_world.camera_.ContinueRotation();

		//	gl_obj_mario_stand.updatePhongSurfaceWithTexture(surface);

		glm::mat4 vp = gl_world.camera_.GetWorldViewMatrix();


		static float time = 0.0;
		time += 0.01f;

		glm::mat4 m_mat = glm::mat4();


		const glm::mat4 mvp = vp * m_mat;


		// don't need to update if there is no change
		// gl_obj.updatePhongSurface(surface); 

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(gl_world.shaders_.program_id_);

		//gl_world.shaders_.sendUniform(vp, "mvp");e
		gl_world.shaders_.sendUniform(mvp, "mvp");

		//gl_obj.drawPhongSurface();
		//gl_obj.applyLighting(light);
		//	gl_obj.drawWithShader(gl_world.shaders_);

		//GLint loc = glGetUniformLocation(gl_world.shaders_.program_id_, "my_texture");
		//if (loc != -1)
		//{
		//	//glUniformMatrix4fv(loc, 1, false, &matrix4[0][0]);
		//	glUniform1i(loc, 0);  // 0 is the index of our first texture
		//}
		//glUniform1i ( glGetUniformLocation(gl_world.shaders_.program_id_, "my_texture"),0;

		//gl_obj.drawPhongSurface();

		//gl_obj.drawWithShader(gl_world.shaders_);



		////////////////////
		if (pressW) {
			

			//GL2_Light box_light = light;
			//box_light.diffuse_ = glm::vec4(1, 1, 1, 1);
			//box_light.position_ = glm::vec4 (-1, 0.3, 0 ,0);
			//gl_box.applyLighting(box_light);
			//gl_box.drawWithShader(gl_world.shaders_);

			gl_obj1.applyLighting(light);
			gl_obj1.drawWithShader(gl_world.shaders_);
			if (clock() / CLOCKS_PER_SEC % 6 < 3) { // 계속 내려가기
				mario_stand_surface.translate(TV(0, -0.001, 0));;
				mario_move_surface.translate(TV(0, -0.001, 0));;
				surface1.translate(TV(0, -0.001, 0));
				gl_obj1.updatePhongSurface(surface1);
				if ((clock() - mario_move_time) / CLOCKS_PER_SEC > 0.1) { // false 이면 stand 이면
					gl_obj_mario_stand.applyLighting(light);
					gl_obj_mario_stand.drawWithShader(gl_world.shaders_);
					gl_obj_mario_stand.updatePhongSurface(mario_stand_surface);
				}
				else {
					gl_obj_mario_move.applyLighting(light);
					gl_obj_mario_move.drawWithShader(gl_world.shaders_);
					gl_obj_mario_move.updatePhongSurface(mario_move_surface);
				}
			}
			else {
				mario_stand_surface.translate(TV(0, +0.001, 0));;
				mario_move_surface.translate(TV(0, +0.001, 0));;
				surface1.translate(TV(0, +0.001, 0));
				gl_obj1.updatePhongSurface(surface1);
				if ((clock() - mario_move_time) / CLOCKS_PER_SEC > 0.1) { // false 이면 stand 이면
					gl_obj_mario_stand.applyLighting(light);
					gl_obj_mario_stand.drawWithShader(gl_world.shaders_);
					gl_obj_mario_stand.updatePhongSurface(mario_stand_surface);
				}
				else {
					gl_obj_mario_move.applyLighting(light);
					gl_obj_mario_move.drawWithShader(gl_world.shaders_);
					gl_obj_mario_move.updatePhongSurface(mario_move_surface);
				}
			}
			//gl_obj_mario_stand.applyLighting(light);
			//gl_obj_mario_stand.drawWithShader(gl_world.shaders_);
		}

		if (pressW) {
			gl_obj_turtle_1.applyLighting(light);
			gl_obj_turtle_1.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_2.applyLighting(light);
			gl_obj_turtle_2.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_3.applyLighting(light);
			gl_obj_turtle_3.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_4.applyLighting(light);
			gl_obj_turtle_4.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_5.applyLighting(light);
			gl_obj_turtle_5.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_6.applyLighting(light);
			gl_obj_turtle_6.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_7.applyLighting(light);
			gl_obj_turtle_7.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_8.applyLighting(light);
			gl_obj_turtle_8.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_9.applyLighting(light);
			gl_obj_turtle_9.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_10.applyLighting(light);
			gl_obj_turtle_10.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_11.applyLighting(light);
			gl_obj_turtle_11.drawWithShader(gl_world.shaders_);

			gl_obj_turtle_12.applyLighting(light);
			gl_obj_turtle_12.drawWithShader(gl_world.shaders_);
		}
		if (ground_move_W || pressD  || pressA ) {//////게임 시작!! // Turtle z ++ 로 이동
			if (ground_move_W)
			{
				turtle_1_surface.translate(TV(0, 0, +1));
				turtle_2_surface.translate(TV(0, 0, +1));
				turtle_3_surface.translate(TV(0, 0, +1));

				turtle_4_surface.translate(TV(0, 0, +1));
				turtle_5_surface.translate(TV(0, 0, +1));
				turtle_6_surface.translate(TV(0, 0, +1));
				
				turtle_7_surface.translate(TV(0, 0, +1));
				turtle_8_surface.translate(TV(0, 0, +1));
				turtle_9_surface.translate(TV(0, 0, +1));
				
				turtle_10_surface.translate(TV(0, 0, +1));
				turtle_11_surface.translate(TV(0, 0, +1));
				turtle_12_surface.translate(TV(0, 0, +1));
				for (int i = 0; i < detection.size(); i++) {
					std::pair<int, int> temp = detection.front();
					detection.pop();
					temp.second += 1;
					detection.push(temp);
				}
			}
			else if (pressD) {
				if (draw_ground_centor_x > -5) {
					turtle_1_surface.translate(TV(-1, 0, 0));
					turtle_2_surface.translate(TV(-1, 0, 0));
					turtle_3_surface.translate(TV(-1, 0, 0));
					turtle_4_surface.translate(TV(-1, 0, 0));
					turtle_5_surface.translate(TV(-1, 0, 0));
					turtle_6_surface.translate(TV(-1, 0, 0));
					turtle_7_surface.translate(TV(-1, 0, 0));
					turtle_8_surface.translate(TV(-1, 0, 0));
					turtle_9_surface.translate(TV(-1, 0, 0));
					turtle_10_surface.translate(TV(-1, 0, 0));
					turtle_11_surface.translate(TV(-1, 0, 0));
					turtle_12_surface.translate(TV(-1, 0, 0));
					for (int i = 0; i < detection.size(); i++) {
						std::pair<int, int> temp = detection.front();
						detection.pop();
						temp.first -= 1;
						detection.push(temp);
					}
				}
			}
			else {
				if (draw_ground_centor_x < 5) {
					turtle_1_surface.translate(TV(1, 0, 0));
					turtle_2_surface.translate(TV(1, 0, 0));
					turtle_3_surface.translate(TV(1, 0, 0));
					turtle_4_surface.translate(TV(1, 0, 0));
					turtle_5_surface.translate(TV(1, 0, 0));
					turtle_6_surface.translate(TV(1, 0, 0));
					turtle_7_surface.translate(TV(1, 0, 0));
					turtle_8_surface.translate(TV(1, 0, 0));
					turtle_9_surface.translate(TV(1, 0, 0));
					turtle_10_surface.translate(TV(1, 0, 0));
					turtle_11_surface.translate(TV(1, 0, 0));
					turtle_12_surface.translate(TV(1, 0, 0));
					for (int i = 0; i < detection.size(); i++) {
						std::pair<int, int> temp = detection.front();
						detection.pop();
						temp.first += 1;
						detection.push(temp);
					}
				}
			}
			gl_obj_turtle_1.applyLighting(light);
			gl_obj_turtle_1.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_1.updatePhongSurface(turtle_1_surface);
			//
			gl_obj_turtle_2.applyLighting(light);
			gl_obj_turtle_2.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_2.updatePhongSurface(turtle_2_surface);
			//
			gl_obj_turtle_3.applyLighting(light);
			gl_obj_turtle_3.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_3.updatePhongSurface(turtle_3_surface);
			//
			gl_obj_turtle_4.applyLighting(light);
			gl_obj_turtle_4.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_4.updatePhongSurface(turtle_4_surface);
			//
			gl_obj_turtle_5.applyLighting(light);
			gl_obj_turtle_5.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_5.updatePhongSurface(turtle_5_surface);
			//
			gl_obj_turtle_6.applyLighting(light);
			gl_obj_turtle_6.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_6.updatePhongSurface(turtle_6_surface);
			//
			gl_obj_turtle_7.applyLighting(light);
			gl_obj_turtle_7.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_7.updatePhongSurface(turtle_7_surface);
			//
			gl_obj_turtle_8.applyLighting(light);
			gl_obj_turtle_8.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_8.updatePhongSurface(turtle_8_surface);
			//
			gl_obj_turtle_9.applyLighting(light);
			gl_obj_turtle_9.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_9.updatePhongSurface(turtle_9_surface);
			//
			gl_obj_turtle_10.applyLighting(light);
			gl_obj_turtle_10.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_10.updatePhongSurface(turtle_10_surface);
			//
			gl_obj_turtle_11.applyLighting(light);
			gl_obj_turtle_11.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_11.updatePhongSurface(turtle_11_surface);
			//
			gl_obj_turtle_12.applyLighting(light);
			gl_obj_turtle_12.drawWithShader(gl_world.shaders_);
			gl_obj_turtle_12.updatePhongSurface(turtle_12_surface);
			//
			//충돌탐지
			int move_count_turtle = 0;
			for (int i = 0; i < detection.size();i++) {
				std::pair<int, int> temp = detection.front();
				detection.pop();

				if (temp.first == 0 && temp.second == 0) {
					finish_count = 0; // 게임 끝냄
					break;
				}
				//뒤로 보내기
				if (temp.second == 1) {
					if (finish_count > 3) {
						which_move++;
						int rand_num = ((int)rand() % 5) - 2;
						if (pressD ){
							rand_num += 1;
						}
					if (pressA) {
						rand_num -= 1;
					}
						int now_posi = -temp.first;
						temp.first = rand_num; 
						temp.second = -8; // 8 로 go
						////
						if (which_move <= 3) {
							if (move_count_turtle == 0) {
								move_count_turtle++;
								turtle_1_surface.translate(TV(temp.first + now_posi, 0, -9));
								gl_obj_turtle_1.applyLighting(light);
								gl_obj_turtle_1.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_1.updatePhongSurface(turtle_1_surface);
							}
							else if (move_count_turtle == 1) {
								move_count_turtle++;
								turtle_2_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_2.applyLighting(light);
								gl_obj_turtle_2.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_2.updatePhongSurface(turtle_2_surface);
							}
							else if (move_count_turtle == 2)
							turtle_3_surface.translate(TV(temp.first+ now_posi, 0, -9));
							gl_obj_turtle_3.applyLighting(light);
							gl_obj_turtle_3.drawWithShader(gl_world.shaders_);
							gl_obj_turtle_3.updatePhongSurface(turtle_3_surface);
						}
						else if (4 <= which_move && which_move <=6 ) {
							if (move_count_turtle == 0) {
								move_count_turtle++;
								turtle_4_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_4.applyLighting(light);
								gl_obj_turtle_4.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_4.updatePhongSurface(turtle_4_surface);
							}
							else if (move_count_turtle == 1) {
								move_count_turtle++;
								turtle_5_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_5.applyLighting(light);
								gl_obj_turtle_5.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_5.updatePhongSurface(turtle_5_surface);
							}
							else if (move_count_turtle == 2)
								turtle_6_surface.translate(TV(temp.first+ now_posi, 0, -9));
							gl_obj_turtle_6.applyLighting(light);
							gl_obj_turtle_6.drawWithShader(gl_world.shaders_);
							gl_obj_turtle_6.updatePhongSurface(turtle_6_surface);
						}
						else if (7 <= which_move && which_move <= 9) {
							if (move_count_turtle == 0) {
								move_count_turtle++;
								turtle_7_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_7.applyLighting(light);
								gl_obj_turtle_7.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_7.updatePhongSurface(turtle_7_surface);
							}
							else if (move_count_turtle == 1) {
								move_count_turtle++;
								turtle_8_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_8.applyLighting(light);
								gl_obj_turtle_8.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_8.updatePhongSurface(turtle_8_surface);
							}
							else if (move_count_turtle == 2)
								turtle_9_surface.translate(TV(temp.first+ now_posi, 0, -9));
							gl_obj_turtle_9.applyLighting(light);
							gl_obj_turtle_9.drawWithShader(gl_world.shaders_);
							gl_obj_turtle_9.updatePhongSurface(turtle_9_surface);
						}
						else if (10 <= which_move && which_move <=12) {
							if (move_count_turtle == 0) {
								move_count_turtle++;
								turtle_10_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_10.applyLighting(light);
								gl_obj_turtle_10.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_10.updatePhongSurface(turtle_10_surface);
							}
							else if (move_count_turtle == 1) {
								move_count_turtle++;
								turtle_11_surface.translate(TV(temp.first+ now_posi, 0, -9));
								gl_obj_turtle_11.applyLighting(light);
								gl_obj_turtle_11.drawWithShader(gl_world.shaders_);
								gl_obj_turtle_11.updatePhongSurface(turtle_11_surface);
							}
							else if(move_count_turtle == 2)
							turtle_12_surface.translate(TV(temp.first, 0, -9));
							gl_obj_turtle_12.applyLighting(light);
							gl_obj_turtle_12.drawWithShader(gl_world.shaders_);
							gl_obj_turtle_12.updatePhongSurface(turtle_12_surface);
						}
						if (which_move == 12) {
							which_move = 0;//init
						}
						//
					}
				}
				detection.push(temp);
			}
			///////////////////////////////////////////
			//충돌 detection & 뒤로보내기 랜덤 뒤로 ~ ///
			///////////////////////////////////////////
		}
	
		glUseProgram(0);


		//////////////////////////////
		if (finish_count == 0) {
			ps.advanceOneTimeStep(0.0012f);
			ps_1.advanceOneTimeStep(0.0012f);
			ps_2.advanceOneTimeStep(0.0012f);
			if (ps.count < 2000) {
				ps.count++;
				ps_1.count++;
				ps_2.count++;
			}
		}
		/////////////////////////////

		glLoadMatrixf(&vp[0][0]);

		glLineWidth(2);
		gl_world.drawAxes();

		//////////////////////////
		glDisable(GL_LIGHTING);
		glPointSize(10.0f);
		glBegin(GL_POINTS);
		for (int p = 0; p < ps.particles_.size(); ++p)
		{
			const TV3 color1 = TV3(1.0f, 0.0f, 0.0f), color2 = TV3(0.0, 0.0, 1.0f);
			const TV3 color1_1 = TV3(1.0f, 0.0f, 0.0f), color2_1 = TV3(0.0, 0.0, 1.0f);
			const TV3 color1_2 = TV3(1.0f, 0.0f, 0.0f), color2_2 = TV3(0.0, 0.0, 1.0f);

			const float alpha   = ps.particles_[p].vel_.getMagnitude() * 0.5f;
			const float alpha_1 = ps_1.particles_[p].vel_.getMagnitude() * 0.5f;
			const float alpha_2 = ps_2.particles_[p].vel_.getMagnitude() * 0.5f;

			const TV3 blenced_color = alpha * color1 + (1.0f - alpha) * color2;
			const TV3 blenced_color_1 = alpha_1 * color1_1 + (1.0f - alpha_1) * color2_1;
			const TV3 blenced_color_2 = alpha_2 * color1_2 + (1.0f - alpha_2) * color2_2;
			
			glColor3fv(blenced_color.values_);
			glVertex3fv(ps.particles_[p].pos_.values_);
			
			glColor3fv(blenced_color_1.values_);
			glVertex3fv(ps_1.particles_[p].pos_.values_);

			glColor3fv(blenced_color_2.values_);
			glVertex3fv(ps_2.particles_[p].pos_.values_);
		}
		glEnd();
		/////////////////////////////
		///색칠할 큐관리
		if (ground_move_W) {
			ground_move_W = false;  // init grount_move_W
			ground_q.pop(); // 맨앞꺼 삭제
			if (finish_count > 28 ) {///지금땅 삭제 후 랜덤한 색깔 뒤로 넣기
				float rand_ground1 = (float)rand() / RAND_MAX;
				float rand_ground2 = (float)rand() / RAND_MAX;
				float rand_ground3 = (float)rand() / RAND_MAX;
				ground_q.push(TV(rand_ground1, rand_ground2, rand_ground3));
			}
			else {//마지막 부분 들어갈차례면 마지막 부분 인풋
				ground_q.push(TV(1, 1, 1)); // 마지막 부분이면 White 
			}
		}


		//////////////////////
		glBegin(GL_QUADS);


		if (pressD) {
			pressD = false;
			if (draw_ground_centor_x > -5) {
				draw_ground_centor_x -= 1;
			}
		}
		if (pressA) {
			pressA = false;
			if (draw_ground_centor_x < 5) {
				draw_ground_centor_x += 1;
			}
		}

		

		float draw_ground_centor_x_now = draw_ground_centor_x;
		float draw_ground_centor_z_now = draw_ground_centor_z;
		for (int i = 0; i < ground_q.size(); i++) {
			float dx[] = { -0.5,+0.5,+0.5,-0.5 };
			float dz[] = { +0.5,+0.5,-0.5,-0.5 };
			// 큐한바퀴 순회
			TV ground_C = ground_q.front();
			ground_q.pop();
			ground_q.push(ground_C);
			
			//ground_C 칠해야할 땅 색깔
			for (int k = 0; k < 5; k++) {
				glColor3f(ground_C.x_, ground_C.y_, ground_C.z_);
				for (int s = 0; s < 4; s++) {
					glVertex3f(draw_ground_centor_x_now +dx[s], -0.5, draw_ground_centor_z_now + dz[s]);///땅위치
				}
				draw_ground_centor_x_now += 1;
			}
			draw_ground_centor_x_now -= 5;
			draw_ground_centor_z_now -= 1;
			////////////땅 색칠
		}
		glEnd();
		////////////////
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	glfwTerminate();

	return 0;
}

