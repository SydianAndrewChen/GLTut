#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

#include "Camera.h"

#include "stb_image.h"

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera & camera);
void mouse_call_back(GLFWwindow* window, double xpos, double ypos);
void scroll_back(GLFWwindow* window, double xoffset, double yoffset);

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
};

glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

int screenWidth = 800;
int screenHeight = 600;
float lastX = screenWidth / 2;
float lastY = screenHeight / 2;

glm::vec3 cameraPos = glm::vec3(-3.19, 2.35, 4.68);
glm::vec3 cameraFront = glm::vec3(0.68f, -0.45, -0.56);
Camera camera(cameraPos, cameraFront);

struct Material {
	float shininess;
};

struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

Material objectMaterial = {
	32.0f
};

Light light = {
	glm::vec3(1.2f, 1.0f, 2.0f),
	glm::vec3(0.2f, 0.2f, 0.2f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(1.0f, 1.0f, 1.0f)
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_call_back);

	glfwSetScrollCallback(window, scroll_back);

	{
		Texture boxTex("./textures/container2.png");
		Texture borderTex("./textures/container2_specular.png");

		VertexArray lighterVa;
		VertexBuffer lighterVb(vertices, sizeof(vertices));
		VertexBufferLayout lighterLayout;
		lighterLayout.push<float>(3);
		lighterLayout.push<float>(3);
		lighterLayout.push<float>(2);
		lighterVa.addBuffer(lighterVb, lighterLayout);
		lighterVa.unbind();
		lighterVb.unbind();
		Shader lighterShader("./src/shaders/lighter.vs", "./src/shaders/lighter.fs");

		VertexArray objectVa;

		VertexBuffer objectVb(vertices, sizeof(vertices));
		VertexBufferLayout objectLayout;
		objectLayout.push<float>(3);
		objectLayout.push<float>(3); // Normals
		objectLayout.push<float>(2); // TexCoords
		objectVa.addBuffer(objectVb, objectLayout);
		objectVa.unbind();
		objectVb.unbind();

		Shader objectShader("./src/shaders/shader.vs", "./src/shaders/shader.fs");

		Renderer renderer;
		glEnable(GL_DEPTH_TEST);

		ImGui::CreateContext();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			float cameraSpeed = 2.5f * deltaTime;
			camera.setSpeed(cameraSpeed);

			processInput(window, camera);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			renderer.clear();


			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			objectVa.bind();
			glm::mat4 view = camera.getLookAt();
			glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)screenWidth / screenHeight, 0.1f, 100.0f);

			objectShader.use();
			objectShader.setFloat4_4("view", view);
			objectShader.setFloat4_4("perspProj", projection);

			
			glm::mat4 model;

			//float angle = (float) i * 20;
			//model = glm::rotate(model, glm::radians((float) glfwGetTime() * 10 + angle), glm::vec3(1.0f, 0.0f, 1.0f));
			objectShader.setFloat4_4("model", model);
			objectShader.setFloatv3("cameraPos", camera.pos);
			objectShader.setFloat("material.shininess", objectMaterial.shininess);

			boxTex.bind(0);
			objectShader.setInt("material.diffuseMap", 0);

			borderTex.bind(1);
			objectShader.setInt("material.specularMap", 1);

			objectShader.setFloatv3("light.position", light.position);
			objectShader.setFloatv3("light.specular", light.specular);
			objectShader.setFloatv3("light.ambient", light.ambient);
			objectShader.setFloatv3("light.diffuse", light.diffuse);

			renderer.draw(objectVa, 36, objectShader);
			borderTex.unbind();
			boxTex.unbind();


			lighterVa.bind();
			model = glm::translate(model, light.position);
			model = glm::scale(model, glm::vec3(0.2f));
			lighterShader.use();
			lighterShader.setFloat4_4("model", model);
			lighterShader.setFloat4_4("view", view);
			lighterShader.setFloat4_4("perspProj", projection);
			lighterShader.setFloatv3("lighterColor", light.specular);
			renderer.draw(lighterVa, 36, lighterShader);


			{
				ImGui::SliderFloat("speed", &cameraSpeed, 0.5f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::Text("Up vector: %f %f %f", camera.up.x, camera.up.y, camera.up.z);
				ImGui::Text("Right vector: %f %f %f", camera.right.x, camera.right.y, camera.right.z);
				ImGui::Text("Pos vector: %f %f %f", camera.pos.x, camera.pos.y, camera.pos.z);
				ImGui::Text("Front vector: %f %f %f", camera.front.x, camera.front.y, camera.front.z);
				ImGui::Text("Yaw: %f Pitch: %f", camera.yaw, camera.pitch );
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				ImGui::SliderFloat("material.shininess", &objectMaterial.shininess, 32, 256);            // Edit 1 float using a slider from 0.0f to 1.0f
				
				ImGui::ColorEdit3("light.pos", (float*)&light.position);
				ImGui::ColorEdit3("light.specular", (float*)&light.specular);
				ImGui::ColorEdit3("light.ambient", (float*)&light.ambient);
				ImGui::ColorEdit3("light.diffuse", (float*)&light.diffuse);
				
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();

		}
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void processInput(GLFWwindow* window, Camera & camera) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveForward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveBack();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight();


	camera.setEnable(glfwGetKey(window, GLFW_KEY_E) != GLFW_PRESS);
}

void scroll_back(GLFWwindow* window, double xoffset, double yoffset) { camera.zoom(yoffset); }

bool firstCamera = true;
void mouse_call_back(GLFWwindow* window, double xpos, double ypos)
{
	if (firstCamera) {
		lastX = xpos;
		lastY = ypos;
		firstCamera = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.rotate(xoffset, yoffset);
}