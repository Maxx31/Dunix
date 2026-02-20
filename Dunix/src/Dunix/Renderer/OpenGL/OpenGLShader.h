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

        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetFloat(const std::string& name, float v) override;
        virtual void SetFloat3(const std::string& name, float x, float y, float z) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

    private:
        std::string ReadFile(const std::string& path);

        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        unsigned int CompileShader(unsigned int type, const std::string& source);

    private:
        unsigned int m_Program = 0;
    };
}