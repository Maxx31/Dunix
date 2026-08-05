#include "dxpch.h"
#include "Framebuffer.h"

#include "Dunix/Renderer/OpenGL/OpenGLFrameBuffer.h"
namespace Dunix
{
    SharedPtr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        return std::make_shared<OpenGLFramebuffer>(spec);
    }
}
