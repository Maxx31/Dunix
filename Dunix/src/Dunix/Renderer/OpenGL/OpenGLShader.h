#pragma once

#include "Dunix/Renderer/Shader.h"

namespace Dunix
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vsPath, const std::string& fsPath);

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetFloat(const char* name, float v) override;
        virtual void SetFloat3(const char* name, float x, float y, float z) override;

        virtual void SetMat4(const char* name, const glm::mat4& value) override;

    private:
        std::string ReadFile(const std::string& path);

        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        unsigned int CompileShader(unsigned int type, const std::string& source);

    private:
        unsigned int m_Program = 0;
    };
}