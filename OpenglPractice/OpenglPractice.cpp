
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow*, int width, int height);
static void processInput(GLFWwindow* window);


//Vertext Shader source
const char* vertexShaderSource = R"(
                #version 330 core
                layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec3 aColor;
					
				out vec3 ourColor;

                void main() {
                    gl_Position = vec4(aPos, 1.0);
					ourColor = aColor;
                }
            )";

//Fragment Shader source
const char* fragmentShaderSource = R"(
                #version 330 core
                out vec4 FragColor;
				in vec3 ourColor;

                void main()
                {	
					FragColor = vec4(ourColor, 1.0f);	
                } 
            )";



int main(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "OpenGL Baby", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Create Shaders and setup shader program
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Set vertices and create Buffer object
	float triangleOne[] = {
		//positions
		-0.5f,  0.5f, 0.0f,
		-0.9f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,

		//color
		1.0f, 0.0f,0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	float triangleTwo[] = {
		//positions
		0.5f,  0.5f, 0.0f,
		0.9f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,

		//color
		1.0f, 0.0f,0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f,0.0f, 1.0f
	};


	float triangleThree[] = {
		//positions
		0.0f,  0.9f, 0.0f,
		0.1f, 0.8f, 0.0f,
		-0.1f, 0.8f, 0.0f,

		//color
		0.0f, 0.0f,0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f,0.0f, 0.0f
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	unsigned int VBO[3], VAO[3];
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleThree), triangleThree, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/*Process input*/
		processInput(window);
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteVertexArrays(1, &VAO[1]);
	glDeleteVertexArrays(1, &VAO[2]);
	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);
	glDeleteBuffers(1, &VBO[2]);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;

}


static void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "Window resized";
}
