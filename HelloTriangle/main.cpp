#include "App.hpp"

int main(int argc, char* argv[])
{	
	// SDL Initiliazing
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("Error: SDL_Init" + std::string(SDL_GetError()));
	atexit(SDL_Quit);

	// Window Initiliazing
	const auto _width = M_WINDOW_WIDTH;
	const auto _height = M_WINDOW_HEIGHT;
	auto _window = std::shared_ptr<SDL_Window>(
		SDL_CreateWindow(
			M_WINDOW_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_width, _height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
		),
		SDL_DestroyWindow
	);

	if (!_window)
		throw std::runtime_error("Error: SDL_CreateWindow()" + std::string(SDL_GetError()));

	// OpenGL Context Initiliazing
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	auto _context = std::shared_ptr<void>(
		SDL_GL_CreateContext(_window.get()),
		SDL_GL_DeleteContext
	);

	SDL_GL_MakeCurrent(_window.get(), _context.get());
	SDL_GL_SetSwapInterval(1);

	if (!_context)
		throw std::runtime_error("Error: SDL_GL_CreateContext()" + std::string(SDL_GetError()));

	// GLEW Initiliazing
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Error: glewInit()");

	// OpenGL Information
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;

	glViewport(0, 0, _width, _height); M_GL_LASTERROR;

	glClear(GL_COLOR_BUFFER_BIT); M_GL_LASTERROR;
	glClearColor(0.2, 0.2, 0.2, 1.0); M_GL_LASTERROR;

	// Create Shaders (Vertex, Fragment)
	ShaderProg shaderProg;
	shaderProg.attach("Shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	shaderProg.attach("Shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
	shaderProg.link();

	// Vertex Buffer, Vertex Array (Attributes), Element Buffer Object
	//float vertices[] = {
	//	// first triangle
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f,  0.5f, 0.0f,  // top left 
	//	// second triangle
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left
	//};

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenBuffers(1, &EBO); M_GL_LASTERROR; M_GL_LASTERROR;
	glGenBuffers(1, &VBO); M_GL_LASTERROR;
	glGenVertexArrays(1, &VAO); M_GL_LASTERROR;
	glBindVertexArray(VAO); M_GL_LASTERROR;
	glBindBuffer(GL_ARRAY_BUFFER, VBO); M_GL_LASTERROR;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); M_GL_LASTERROR;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); M_GL_LASTERROR;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); M_GL_LASTERROR;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0); M_GL_LASTERROR;
	glEnableVertexAttribArray(0); M_GL_LASTERROR;
	glBindBuffer(GL_ARRAY_BUFFER, 0); M_GL_LASTERROR;

	// Game Loop
	bool run = true;
	unsigned int lastTime = 0,
		currTime = 0,
		deltaTime = 0;
	bool wireframe = false;
	SDL_Event event;
	for (;;)
	{
		lastTime = currTime;
		currTime = SDL_GetTicks64();
		deltaTime = currTime - lastTime;

		if (!run)
			break;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				run = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					run = false;
					break;
				default:
					wireframe = !wireframe;
					break;
				}
			default:
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT); M_GL_LASTERROR;
		glClearColor(0.2, 0.2, 0.2, 1.0); M_GL_LASTERROR;

		shaderProg.use();
		//glBindVertexArray(VAO); M_GL_LASTERROR;
		//glDrawArrays(GL_TRIANGLES, 0, 3); M_GL_LASTERROR;
		//glDrawArrays(GL_TRIANGLES, 0, 6); M_GL_LASTERROR;

		if (wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); M_GL_LASTERROR;
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); M_GL_LASTERROR;
		}


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); M_GL_LASTERROR;
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); M_GL_LASTERROR;

		SDL_GL_SwapWindow(_window.get());
	}

	glDeleteBuffers(1, &VBO); M_GL_LASTERROR;
	glDeleteVertexArrays(1, &VAO); M_GL_LASTERROR;

	return EXIT_SUCCESS;
}
