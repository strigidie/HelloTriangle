#pragma once

// STL
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <map>

// Windows OS
#include <windows.h>

// Window Manager
#include "SDL.h"
#undef main

// Load OpenGL Extensions
#include "GL/GLEW.h"

// OpenGL and OpenGL Utility
#include "GL/GL.h"
#include "GL/GLU.h"

// Macros
#define M_WINDOW_NAME "Hello Triangle"
#define M_WINDOW_WIDTH 800
#define M_WINDOW_HEIGHT 600

// Application
#include "ShaderProg.hpp"

// Check OpenGL Errors
static void App_glClearAllErrors(void)
{
	while (glGetError() != GL_NO_ERROR) { }
}

static bool App_glCheckError(const char* funcName, const int line)
{
	GLenum glErrorCode = glGetError();
	if (glErrorCode)
	{
		std::string errorMessage;
		switch (glErrorCode)
		{
		case GL_INVALID_ENUM:
			errorMessage = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorMessage = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorMessage = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			errorMessage = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			errorMessage = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			errorMessage = "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorMessage = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_CONTEXT_LOST:
			errorMessage = "GL_CONTEXT_LOST";
			break;
		case GL_TABLE_TOO_LARGE:
			errorMessage = "GL_TABLE_TOO_LARGE1";
			break;
		default:
			errorMessage = std::to_string(glErrorCode);
			break;
		}
		std::cout << "OpenGL Error Code: " << errorMessage << std::endl;
		std::cout << "OpenGL Function: " << funcName << std::endl;
		std::cout << "Line: " << line << std::endl;
		return true;
	}

	return false;
}

static bool App_glLastError(const char* errorFile, const int errorLine)
{
	GLenum lastErr = GL_NO_ERROR;
	GLenum currErr = GL_NO_ERROR;
	while ((currErr = glGetError()) != GL_NO_ERROR)
	{
		lastErr = currErr;
	}

	if (lastErr)
	{
		std::string errorMessage;
		switch (lastErr)
		{
		case GL_INVALID_ENUM:
			errorMessage = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorMessage = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorMessage = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			errorMessage = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			errorMessage = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			errorMessage = "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorMessage = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_CONTEXT_LOST:
			errorMessage = "GL_CONTEXT_LOST";
			break;
		case GL_TABLE_TOO_LARGE:
			errorMessage = "GL_TABLE_TOO_LARGE1";
			break;
		default:
			errorMessage = std::to_string(lastErr);
			break;
		}

		std::cout << "OpenGL Error Code: " << errorMessage << std::endl;
		std::cout << "Function File: " << errorFile << std::endl;
		std::cout << "Function Line: " << errorLine << std::endl;

		return true;
	}

	return false;

	
}

#define M_GL_LASTERROR App_glLastError(__FILE__, __LINE__)
