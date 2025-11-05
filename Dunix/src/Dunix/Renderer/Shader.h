#pragma once 
#include <string>

namespace Dunix
{
    class Shader
    {
    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetFloat(const char* name, float v) = 0;
        virtual void SetFloat3(const char* name, float x, float y, float z) = 0;

        static Shader* CreateFromFile(const std::string& vsPath, const std::string fsPath);
    };
}