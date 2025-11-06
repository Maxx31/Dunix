#include "dxpch.h"

#include "OpenGLShader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>

namespace Dunix
{
	OpenGLShader::OpenGLShader(const std::string& vsPath, const std::string& fsPath)
	{
		const std::string vsrc = ReadFile(vsPath);
		const std::string fsrc = ReadFile(fsPath);
		m_Program = CreateShader(vsrc, fsrc);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_Program);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat(const char* name, float v)
	{
	}

	void OpenGLShader::SetFloat3(const char* name, float x, float y, float z)
	{
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::ifstream f(path, std::ios::binary);
		if (!f) { DX_CORE_ERROR("Failed to open shader: {0}", path); return {}; }
		std::ostringstream ss;
		ss << f.rdbuf();
		return ss.str();
	}

	unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(GL_VERTEX_SHADER);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> log(length);
			glGetShaderInfoLog(id, length, &length, log.data());
			DX_CORE_ERROR("Shader compile error:\n{0}", log.data());

			glDeleteShader(id);
			return 0;
		}

		return id;
	}
}