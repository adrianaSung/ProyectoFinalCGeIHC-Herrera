/*---------------------------------------------------------*/
/* --------------  Proyecto Final CGeIHC      -------------*/
/*-----------------    2022-1   ---------------------------*/
/*-----------------    Alumno:  ---------------------------*/
/*------------ Herrera Godina Adriana Jocelyn -------------*/
/*-------------     No. Cuenta: 315289576------------------*/
/*Profesor: Ing.Carlos Aldair Roman Balbuena---------------*/
/*-----------------------  ---------- ----- ---------------*/
/*---------------------------------------------------------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(118.0f, 16.0f, 430.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;

//JET VARS
float	movJet_x = 0.0f,
movJet_y = 0.0f,
movJet_z = 0.0f,
orienta = 0.0f;

bool	animacion = false,
route1 = true,
route2 = false,
route3 = false,
route4 = false,
route5 = false;

//CHAIR VARS
float	movChair_x = 0.0f,
movChair_z = 0.0f,
chairRotation = 0.0f,
seatRotation = 0.0f,
temp = 0.0f;

bool	animacion1 = false,
animacion2 = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;

//MAIN DOOR VARS
float	mainDoorRotation = 0.0f;

bool	openAnimation = false,
closeAnimation = false;

//SWINGS VARS
float	swinging = 0.0f;

bool	swingsAnimation = false,
onForward = true,
backward = false;

//CRICKET VARS
float	movGrillo_x = 0.0f,
movGrillo_y = 0.0f,
movGrillo_z = 0.0f,
orientacionGrillo = 0.0f;

bool	recorrido1_g = true,
animaciongrillo = false,
recorrido2_g = false,
recorrido3_g = false,
recorrido4_g = false,
recorrido5_g = false,
recorrido6_g = false,
recorrido7_g = false,
recorrido8_g = false,
recorrido9_g = false,
recorrido10_g = false,
recorrido11_g = false,
recorrido12_g = false;

//LAPTOP VARS
bool
animacionLaptopOpen = false,
animacionLaptopClose = false,
recorrido1_lap = false,
recorrido2_lap = false,
recorrido3_lap = false,
recorrido4_lap = false;

float
movLap_x = 0.0f,
movLap_y = 0.0,
movLap_z = 0.0f;

//DRON VARS
float	movDron_x = 0.0f,
movDron_y = 0.0f,
movDron_z = 0.0f,
orientacionDron = 0.0f;
bool
animacionDron = false,
recorrido1_dron = true,
recorrido2_dron = false,
recorrido3_dron = false,
recorrido4_dron = false,
recorrido5_dron = false,
recorrido6_dron = false,
recorrido7_dron = false,
recorrido8_dron = false;


//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,
movBrazoIzq = 0.0f,
movBrazoDer = 0.0f,
movCabeza = 0.0f,
movCabecita_dog = 0.0f,
movColita_dog = 0.0f,
posZ_p = 0.0f,
movPiernaDer = 0.0f;
float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f,
movBrazoIzqInc = 0.0f,
movBrazoDerInc = 0.0f,
movCabezaInc = 0.0f,
movPiernaDerInc = 0.0f,
movCabecita_dogInc = 0.0f,
movColita_dogInc = 0.0f,
incZ_p = 0.0f;


#define MAX_FRAMES 9
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;
	float movBrazoIzq;
	float movBrazoDer;
	float movCabeza;
	float movPiernaDer;
	float movCabecita_dog;
	float movColita_dog;
	float posZ_p;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 9;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].posZ_p = posZ_p;

	KeyFrame[FrameIndex].movCabecita_dog = movCabecita_dog;
	KeyFrame[FrameIndex].movColita_dog = movColita_dog;

	KeyFrame[FrameIndex].movBrazoIzq = movBrazoIzq;
	KeyFrame[FrameIndex].movBrazoDer = movBrazoDer;
	KeyFrame[FrameIndex].movCabeza = movCabeza;

	KeyFrame[FrameIndex].movPiernaDer = movPiernaDer;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	posZ_p = KeyFrame[0].posZ_p;

	movCabecita_dog = KeyFrame[0].movCabecita_dog;
	movColita_dog = KeyFrame[0].movColita_dog;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazoIzq = KeyFrame[0].movBrazoIzq;
	movBrazoDer = KeyFrame[0].movBrazoDer;
	movCabeza = KeyFrame[0].movCabeza;
	movPiernaDer = KeyFrame[0].movPiernaDer;

}


void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	incZ_p = (KeyFrame[playIndex + 1].posZ_p - KeyFrame[playIndex].posZ_p) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	movBrazoIzqInc = (KeyFrame[playIndex + 1].movBrazoIzq - KeyFrame[playIndex].movBrazoIzq) / i_max_steps;
	movBrazoDerInc = (KeyFrame[playIndex + 1].movBrazoDer - KeyFrame[playIndex].movBrazoDer) / i_max_steps;
	movCabezaInc = (KeyFrame[playIndex + 1].movCabeza - KeyFrame[playIndex].movCabeza) / i_max_steps;
	movPiernaDerInc = (KeyFrame[playIndex + 1].movPiernaDer - KeyFrame[playIndex].movPiernaDer) / i_max_steps;
	movCabecita_dogInc = (KeyFrame[playIndex + 1].movCabecita_dog - KeyFrame[playIndex].movCabecita_dog) / i_max_steps;
	movColita_dogInc = (KeyFrame[playIndex + 1].movColita_dog - KeyFrame[playIndex].movColita_dog) / i_max_steps;


}

void animate(void)
{
	seatRotation += 3.0f;

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			posZ_p += incZ_p;

			movCabecita_dog += movCabecita_dogInc;
			movColita_dog += movColita_dogInc;
			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;
			movBrazoIzq += movBrazoIzqInc;
			movBrazoDer += movBrazoDerInc;
			movCabeza += movCabezaInc;
			movPiernaDer += movBrazoDerInc;


			i_curr_steps++;
		}
	}

	//Chair
	if (animacion1)
	{
		if (recorrido1 == true)
		{
			movChair_z -= 1.0f;
			if (movChair_z <= -70.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2 == true)
		{
			movChair_x += 1.0f;
			if (movChair_x >= 28.0f)
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3 == true)
		{
			movChair_z += 1.0f;
			if (movChair_z >= 0.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4 == true)
		{
			movChair_x -= 1.0f;
			if (movChair_x <= 0.0f)
			{
				recorrido4 = false;
				recorrido1 = true;
			}
		}
	}

	//Jet
	if (animacion)
	{
		if (route1 == true)
		{
			movJet_x -= 1.0f;
			if (movJet_x <= -40.0f)
			{
				route1 = false;
				route2 = true;
			}
		}

		if (route2 == true)
		{
			movJet_y += 1.0f;
			movJet_x -= 1.0f;
			if (movJet_y >= 20.0f)
			{
				route2 = false;
				route3 = true;
			}
		}

		if (route3 == true)
		{
			movJet_x -= 1.0f;
			if (movJet_x <= -100.0f)
			{
				route3 = false;
				route4 = true;
			}
		}

		if (route4 == true)
		{
			orienta += 2.0f;
			if (orienta >= 180.0f)
			{
				route4 = false;
				route5 = true;
			}
		}

		if (route5 == true)
		{
			movJet_y -= 0.2381f;
			movJet_x += 1.0f;
			if (movJet_y <= 0.0f)
			{
				animacion = false;
			}
		}
	}

	//Main door
	if (openAnimation)
	{
		mainDoorRotation += 2.0f;
		if (mainDoorRotation >= 90.0f)
		{
			openAnimation = false;
		}
	}

	if (closeAnimation)
	{
		mainDoorRotation -= 2.0f;
		if (mainDoorRotation <= 0.0f)
		{
			closeAnimation = false;
		}
	}

	//Swinging
	if (swingsAnimation)
	{
		if (onForward == true)
		{
			swinging += 1.0f;
			if (swinging >= 45.0f)
			{
				onForward = false;
				backward = true;
			}
		}

		if (backward == true)
		{
			swinging -= 1.0f;
			if (swinging <= -45.0f)
			{
				onForward = true;
				backward = false;
			}
		}
	}

	//Cricket
	if (animaciongrillo)
	{

		if (recorrido1_g)
		{
			movGrillo_x += 1.0f;
			movGrillo_y += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y >= 11.2)
			{

				recorrido1_g = false;
				recorrido2_g = true;

			}
		}
		if (recorrido2_g)
		{

			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_x >= 10.0f)
			{
				recorrido2_g = false;
				recorrido3_g = true;
			}
		}
		if (recorrido3_g)
		{
			movGrillo_y -= 1.0f;
			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y <= 0) {
				recorrido3_g = false;
				recorrido4_g = true;
			}

		}
		if (recorrido4_g)
		{
			movGrillo_x += 1.0f;
			movGrillo_y += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y >= 14.2)
			{

				recorrido4_g = false;
				recorrido5_g = true;

			}
		}
		if (recorrido5_g)
		{

			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_x >= 10.0f)
			{
				recorrido5_g = false;
				recorrido6_g = true;
			}
		}
		if (recorrido6_g)
		{
			movGrillo_y -= 1.0f;
			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y <= 0) {
				recorrido6_g = false;
				recorrido7_g = true;
			}

		}

		if (recorrido7_g)
		{
			movGrillo_x += 1.0f;
			movGrillo_y += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y >= 16.2)
			{

				recorrido7_g = false;
				recorrido8_g = true;

			}
		}
		if (recorrido8_g)
		{

			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_x >= 10.0f)
			{
				recorrido8_g = false;
				recorrido9_g = true;
			}
		}
		if (recorrido9_g)
		{
			movGrillo_y -= 1.0f;
			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y <= 0) {
				recorrido9_g = false;
				recorrido10_g = true;
			}

		}
		if (recorrido10_g)
		{
			movGrillo_x += 1.0f;
			movGrillo_y += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y >= 16.2)
			{

				recorrido10_g = false;
				recorrido11_g = true;

			}
		}
		if (recorrido11_g)
		{

			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_x >= 10.0f)
			{
				recorrido11_g = false;
				recorrido12_g = true;
			}
		}
		if (recorrido12_g)
		{
			movGrillo_y -= 1.0f;
			movGrillo_x += 1.0f;
			orienta = 0.0f;
			if (movGrillo_y <= 0) {
				recorrido12_g = false;
				animaciongrillo = false;
			}

		}
	}//Animacion Laptop 
	if (animacionLaptopOpen) {
		movLap_x += 10.0f;
		if (movLap_x >= 90.0f)
		{

			animacionLaptopOpen = false;

		}


	}
	if (animacionLaptopClose) {
		movLap_x -= 10.0f;
		if (movLap_x <= 0.0f)
		{

			animacionLaptopClose = false;

		}


	}//Animacion Dron
	if (animacionDron)
	{

		if (recorrido1_dron)
		{
			movDron_z += 2.0f;
			//orientacionDron = 10.0f;
			if (movDron_z >= 20.2)
			{

				recorrido1_dron = false;
				recorrido2_dron= true;

			}
		}
		if (recorrido2_dron)
		{
			movDron_y += 2.0f;
			//orientacionDron = 10.0f;
			if (movDron_y >= 20.2)
			{

				recorrido2_dron = false;
				recorrido3_dron = true;

			}
		}
		if (recorrido3_dron)
		{
			movDron_z += 1.0f;
			//orientacionDron = 10.0f;
			if (movDron_z >= 100.2)
			{

				recorrido3_dron = false;
				recorrido4_dron = true;

			}
		}
		if (recorrido4_dron)
		{
			movDron_y += 1.0f;
			//orientacionDron = 10.0f;
			if (movDron_y >= 150.2)
			{

				recorrido4_dron = false;
				recorrido5_dron = true;

			}
		}
		if (recorrido5_dron)
		{
			movDron_x += 1.0f;
			//orientacionDron = 10.0f;
			if (movDron_x >= 24.2)
			{

				recorrido5_dron = false;
				recorrido6_dron = true;

			}
		}
		if (recorrido6_dron)
		{
			movDron_y -= 1.0f;
			//orientacionDron = 10.0f;
			if (movDron_y <= 0.0)
			{

				recorrido6_dron = false;
				animacionDron = false;

			}
		}


	}
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "315289576-Proyecto Final CGeIHC - Herrera Godina Adriana Jocelyn", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/Floor/Floor.obj");
	Model cuarto1("resources/objects/Cuartomio/cuarto1.obj");
	Model cuarto2("resources/objects/Salamia/cuarto2.obj");
	Model dron("resources/objects/dron/dron.obj");
	Model casita("resources/objects/CasaFinal/casitafinal.obj");
	Model cricket("resources/objects/Grillo/model.obj");
	Model roof("resources/objects/Techo/techito.obj");
	Model roof2("resources/objects/Techo/techito.obj");
	Model laptop1("resources/objects/Cuartomio/TapaLaptop.obj");
	Model laptop2("resources/objects/Cuartomio/tecladolap.obj");
	Model cuerpoperrito("resources/objects/Cuartomio/cuerpoperrito.obj");
	Model cabecita("resources/objects/Cuartomio/cabezaperrito.obj");
	Model colita("resources/objects/Cuartomio/colitaperrito.obj");
	

	//Inicialización de KeyFrames
	/*for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
	}*/
	KeyFrame[0].posZ_p = -5.0f;
	KeyFrame[0].movCabecita_dog = -6.0f;
	KeyFrame[0].movColita_dog = 15.0f;

	KeyFrame[1].posZ_p = -5.0f;
	KeyFrame[1].movCabecita_dog = 6.0f;
	KeyFrame[1].movColita_dog = -15.0f;

	KeyFrame[2].posZ_p = -5.0f;
	KeyFrame[2].movCabecita_dog = -6.0f;
	KeyFrame[2].movColita_dog = 15.0f;

	KeyFrame[3].posZ_p = -5.0f;
	KeyFrame[3].movCabecita_dog = 6.0f;
	KeyFrame[3].movColita_dog = -15.0f;
	

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setFloat("material_shininess", 32.0f);

		// -------------------------------------------------------------------------------------------------------------------------
		// Temporal matrixes
		// -------------------------------------------------------------------------------------------------------------------------
		glm::mat4 mainTemporalMatrix = glm::mat4(1.0f);
		glm::mat4 mainDoorMatrix = glm::mat4(1.0f);
		glm::mat4 chairMatrix = glm::mat4(1.0f);
		glm::mat4 swingMatrix = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		glm::mat4 tempDog = glm::mat4(1.0f);


		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------


		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Home
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(266.0f, 0.0f, 12.0f));
		model = glm::scale(model, glm::vec3(1.5));
		staticShader.setMat4("model", model);
		cuarto1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 130.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		cuarto2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(118.0f, 0.0f, 76.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		casita.Draw(staticShader);


		

		// -------------------------------------------------------------------------------------------------------------------------
		// Grillito
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -18.0f));
		model = glm::translate(model, glm::vec3(15.0f + movGrillo_x, movGrillo_y, movGrillo_z));
		tmp = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.03f));
		staticShader.setMat4("model", model);
		cricket.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Dron
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, -1.0f, 330.0f));
		model = glm::translate(model, glm::vec3(15.0f + movDron_x, movDron_y, movDron_z));
		model = glm::scale(model, glm::vec3(1.5));
		staticShader.setMat4("model", model);
		dron.Draw(staticShader);
		// -------------------------------------------------------------------------------------------------------------------------
		// Laptop
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(178.0f, 10.0f, 60.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp = model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.50f));
		staticShader.setMat4("model", model);
		laptop2.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(movLap_x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.50f));
		staticShader.setMat4("model", model);
		laptop1.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Perrito 
		// -------------------------------------------------------------------------------------------------------------------------

		model = glm::translate(glm::mat4(1.0f), glm::vec3(193.0f, 7.0f, 70.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ_p));
		tempDog = model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		cuerpoperrito.Draw(staticShader);

		//Colita
		model = glm::translate(tempDog, glm::vec3(0.0f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(movColita_dog), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		colita.Draw(staticShader);
		//Cabecita
		model = glm::translate(tempDog, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(movCabecita_dog), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		cabecita.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Roof
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(mainTemporalMatrix, glm::vec3(18.0f, -11.0f, 250.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.0f, 1.5f));
		staticShader.setMat4("model", model);
		roof.Draw(staticShader);

		/*model = glm::translate(mainTemporalMatrix, glm::vec3(-197.0f, -11.0f, 160.0f));
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 1.0f));
		staticShader.setMat4("model", model);
		roof2.Draw(staticShader);*/

		
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

	//Laptop
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		animacionLaptopOpen ^= true;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		animacionLaptopClose ^= true;
	

	if (key == GLFW_KEY_R && action == GLFW_PRESS && movJet_y <= 0.0f)
	{
		recorrido1_dron = true;
		recorrido2_dron = false;
		recorrido3_dron = false;
		recorrido4_dron = false;
		recorrido5_dron = false;
		recorrido6_dron = false;
		movDron_x = 0.0f;
		movDron_y = 0.0f;
		movDron_z = 0.0f;
		
		
	}

	//Cricket
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animaciongrillo ^= true;
	//Dron
	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		animacionDron ^= true;

	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}