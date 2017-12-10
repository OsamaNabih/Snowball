#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/SceneObject.h>
#include <iostream>

enum ModelIndeces {
	BallIndex,
	TreeTrunkIndex,
	TreeIndex,
	FoxIndex,
	SnowSceneIndex,
	SceneIndex,
	SnowmanIndex,
	ObjectsCount
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(8.2f, 5.0f, -0.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float orientation = 0.0;
float const pi = 22.0f / 7;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	Shader ourShader("1.model_loading.vs", "1.model_loading.fs");

	// load models
	// -----------
	vector<SceneObject* > AllSceneObjects(ObjectsCount);
	SceneObject Ball("resources/objects/Project/ball01/ball_set.obj", ourShader);
	SceneObject Scene("resources/objects/project/scene/scene_set.obj", ourShader);
	SceneObject Snowman("resources/objects/project/snowman/baked_snowman.obj", ourShader);
	SceneObject Tree("resources/objects/Project/Tree/model(4).obj", ourShader);
	SceneObject Fox("resources/objects/Project/Fox/ArcticFox_Posed.obj", ourShader);
	SceneObject TreeTrunk("resources/objects/Project/tree trunk/tree_trunkfinal.obj", ourShader);
	SceneObject SnowScene("resources/objects/Project/tree trunk/snowScene.obj", ourShader);
	AllSceneObjects[BallIndex] = &Ball;
	AllSceneObjects[TreeTrunkIndex] = &TreeTrunk;
	AllSceneObjects[TreeIndex] = &Tree;
	AllSceneObjects[FoxIndex] = &Fox;
	AllSceneObjects[SnowSceneIndex] = &SnowScene;
	AllSceneObjects[SceneIndex] = &Scene;
	AllSceneObjects[SnowmanIndex] = &Snowman;
	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		orientation += 3.14159f / 2.0f * deltaTime;


		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);


		TreeTrunk.setRotation(pi / 2, glm::vec3(0.0f, 1.0f, 0.0f));
		TreeTrunk.setScaling(glm::vec3(2.0f, 1.0f, 2.0f));
		TreeTrunk.setTranslation(glm::vec3(0.2f, -1.05f, -3.0f));
		TreeTrunk.Draw();

		Scene.ResetRotation();
		Scene.setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
		Scene.setScaling(glm::vec3(0.5f, 0.2f, 0.5f));
		Scene.Draw();

		Scene.ResetRotation();
		Scene.setRotation(pi, glm::vec3(0.0f, 1.0f, 0.0f));
		Scene.setTranslation(glm::vec3(-9.8f, 0.0f, 0.0f));
		Scene.setScaling(glm::vec3(0.5f, 0.2f, 0.5f));
		Scene.Draw();

		Snowman.setRotation(-7 * pi / 9, glm::vec3(0.0f, 1.0f, 0.0f));
		Snowman.addRotation(pi / 2, glm::vec3(-1.0f, 0.0f, 0.0f));
		Snowman.setScaling(glm::vec3(0.2f, 0.2f, 0.2f));
		Snowman.setTranslation(glm::vec3(0.0f, -0.91f, 3.5f));
		Snowman.Draw();

	

		Tree.setScaling(glm::vec3(0.5f, 0.8f, 0.5f));
		Tree.setTranslation(glm::vec3(-3.0f, -0.88f, -1.0f));
		Tree.Draw();

		Fox.setRotation(7 * pi / 9, glm::vec3(0.0f, 1.0f, 0.0f));
		Fox.setScaling(glm::vec3(0.06f, 0.06f, 0.06f));
		Fox.setTranslation(glm::vec3(-1.4f, 0.82f, -1.6f));
		Fox.Draw();

		Ball.setScaling(glm::vec3(0.15f, 0.15f, 0.15f));
		Ball.setTranslation(glm::vec3(0.8f - orientation, 0.23f, -0.6f));
		Ball.Draw();
		//camera.MoveForwards(orientation, deltaTime);
		camera.setX(7.4f - orientation);

		SnowScene.setRotation(-pi / 4, glm::vec3(0.0f, 1.0f, 0.0f));
		SnowScene.setScaling(glm::vec3(0.2f, 0.2f, 0.2f));
		SnowScene.setTranslation(glm::vec3(-2.0f, -0.8f, 1.8f));



	
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
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
