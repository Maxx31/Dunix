#pragma once

#include "Dunix/Renderer/Framebuffer.h"

namespace Dunix
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();
        
    private:
        uint32_t m_RendererID;
        FramebufferSpecification m_Specification;
    };
}
