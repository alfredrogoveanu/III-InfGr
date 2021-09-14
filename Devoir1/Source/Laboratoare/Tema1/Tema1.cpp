#include "Tema1.h"
#include <time.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
//#include "Circle.h"

using namespace std;

int movedGreenBar = 584;
bool clicked = false;
float speed = 2.5, movX, movY, fX = 0, fY = 1, recX, recY;
int bricksOkay [10][12], powerup = 0, fm = -1, lives = 2;
float scaleB [10][12];
int powers[10][12] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} 
};
clock_t t;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	translateX = 0;
	translateY = 0;

	scaleX = 1;
	scaleY = 1;

	angularStep = 1;

	Mesh* windowBarUp = Object2D::CreateSquare("barUp", corner, 1280, 25, glm::vec3(1, 0, 0), true);
	AddMeshToList(windowBarUp);

	Mesh* windowBarLeft = Object2D::CreateSquare("barL", corner, 25, 640, glm::vec3(1, 0, 0), true);
	AddMeshToList(windowBarLeft);

	Mesh* windowBarRight = Object2D::CreateSquare("barR", corner, 25, 640, glm::vec3(1, 0, 0), true);
	AddMeshToList(windowBarRight);

	int x=1;
	while (x<=120) {
		char stra[10];
		strcpy(stra, "brick");
		string strbi = to_string(x);
		const char *strbf = strbi.c_str();
		strcat(stra, strbf);
		Mesh* brick = Object2D::CreateSquare(stra, corner, 50, 30, glm::vec3(1, 0, 0), true);
		AddMeshToList(brick);
		x++;
}

	int x1, y1;
	for (x1 = 0; x1 < 10; x1++) {
		for (y1 = 0; y1 < 12; y1++) {
			bricksOkay[x1][y1] = 1;
			scaleB[x1][y1] = 1;
		}
	}

	Mesh* greenStick = Object2D::CreateSquare("greenStick", corner, 200, 10, glm::vec3(0, 1, 0), true);
	AddMeshToList(greenStick);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, 20, 20, glm::vec3(1, 1, 1), true);
	AddMeshToList(square3);

	Mesh* life = Object2D::CreateSquare("life", corner, 10, 10, glm::vec3(1, 1, 1), true);
	AddMeshToList(life);

	Mesh* square4 = Object2D::CreateSquare("power", corner, 30, 30, glm::vec3(0, 0, 1), true);
	AddMeshToList(square4);
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 695);
	RenderMesh2D(meshes["barUp"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, 55);
	RenderMesh2D(meshes["barL"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(1255, 55);
	RenderMesh2D(meshes["barR"], shaders["VertexColor"], modelMatrix);

	int xx = 230, yy = 600;
	int x = 1;
	while (x <= 120) {
		char stra[10];
		strcpy(stra, "brick");
		string strbi = to_string(x);
		const char *strbf = strbi.c_str();
		strcat(stra, strbf);
		
		if (bricksOkay[(yy - 600) * (-1) / 40][(xx - 230) / 70] == 1) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(xx, yy);
			RenderMesh2D(meshes[stra], shaders["VertexColor"], modelMatrix);
		}

		if (bricksOkay[(yy - 600) * (-1) / 40][(xx - 230) / 70] == 0) {
			float sF = 0, yF = 0;
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(xx, yy);
				modelMatrix *= Transform2D::Scale(scaleB[(yy - 600) * (-1) / 40][(xx - 230) / 70], scaleB[(yy - 600) * (-1) / 40][(xx - 230) / 70]);
				RenderMesh2D(meshes[stra], shaders["VertexColor"], modelMatrix);
				//bricksOkay[(yy - 600) * (-1) / 40][(xx - 230) / 70] = -1;
					scaleB[(yy - 600) * (-1) / 40][(xx - 230) / 70] /= 1.1;
/*				} while (scaleB[(yy - 600) * (-1) / 40][(xx - 230) / 70] > 0.001);/*/
		}

/*		if (scaleX < 0.0001) {
			scaleX = scaleY = 1;
		}
		*/
		xx += 70;
		if (x % 12 == 0) {
			yy -= 40;
			xx = 230;
		}
		x++;
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(movedGreenBar, 20);
	RenderMesh2D(meshes["greenStick"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(movX, movY);
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	if (clicked == true) {

		if (movY <= -20) {
			clicked = false;
			lives = lives - 1;
		}

		movX = movX + fX * speed;
		movY = movY + fY * speed;
		if (movX >= 1235) {
			fX = fX * (-1);
		}
		if (movX <= 25) {
			fX = fX * (-1);
		}
		if (movY >= 675) {
			fY = fY * (-1);
		}
		if (movY <= 30 && (movX + 20 > movedGreenBar && movX < movedGreenBar + 200)) {
			fY = fY * (-1);
			fX = (float)(movX - movedGreenBar + 10) / 100 - 1;
			fY = sin(acos(fX));
		}

		if (movY > 220 && movY <= 630 && movX >= 230-19 && movX < 1050 && ((int)movX + 19 - 230) % 70 <= 69) {
			if (bricksOkay[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] == 1 && fY > 0) {
				bricksOkay[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] = 0;
				fY = fY * fm;
				if (powers[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] == 1) {
					powerup = 1;
					recX = movX;
					recY = movY;
				}
				}
			else if (bricksOkay[(600 - (int)movY + 30) / 40][((int)movX - 230) / 70] == 1 && fY < 0) {
				bricksOkay[(600 - (int)movY + 30) / 40][((int)movX - 230) / 70] = 0;
				fY = fY * fm;
				if (powers[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] == 1) {
					powerup = 1;
					recX = movX;
					recY = movY;
				}
			}
		}

		if (movX > 210 && movX < 1050 && movY > 220 && movY < 630 && (600 - (int)movY + 19) % 49 <= 48 && fX > 0) {
			if (bricksOkay[(600 - (int)movY) / 40][((int)movX + 20 - 230) / 70] == 1) {
				bricksOkay[(600 - (int)movY) / 40][((int)movX + 20 - 230) / 70] = 0;
				fX = fX * fm;
				if (powers[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] == 1) {
					powerup = 1;
					recX = movX;
					recY = movY;
				}
				}
			else if (bricksOkay[(600 - (int)movY) / 40][((int)movX - 230 + 50) / 70] == 1 && fX < 0) {
				bricksOkay[(600 - (int)movY + 30) / 40][((int)movX - 230 + 50) / 70] = 0;
				fX = fX * fm;
				if (powers[(600 - (int)movY + 20) / 40][((int)movX - 230) / 70] == 1) {
					powerup = 1;
					recX = movX;
					recY = movY;
				}
			}
		}

		if (powerup == 1) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(recX, recY);
			modelMatrix *= Transform2D::Rotate(angularStep);
			RenderMesh2D(meshes["power"], shaders["VertexColor"], modelMatrix);
			recY--;
			angularStep *= 1.009;
			if (recX - 30 > movedGreenBar && recX < movedGreenBar + 200 && recY<=30 && recY>=20) {
				powerup = 0;
				fm = 1;
				t = clock();
				cout << ((float)t)/CLOCKS_PER_SEC;
			}
		}

		clock_t t2 = clock();

		if (((float)t2) / CLOCKS_PER_SEC - ((float)t) / CLOCKS_PER_SEC > 30) {
			fm = -1;
		}
	}
	else {
		movX = movedGreenBar + 90;
		if (lives >= 0) {
			movY = 50;
			fY = 1, fX = 0;
		}
		else {
			movY = -30;
		}
	}

	if (lives == 2) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(10, 10);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(25, 10);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	if (lives == 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(10, 10);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{	
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (mouseX >= 100 && mouseX <= 1180) {
		movedGreenBar = mouseX - 100;
	}
	else
	{
		if (mouseX >= 0 && mouseX < 100) {
			movedGreenBar = 0;
		}
		if (mouseX > 1180 && mouseX <= 1280) {
			movedGreenBar = 1080;
		}
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		clicked = true;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
