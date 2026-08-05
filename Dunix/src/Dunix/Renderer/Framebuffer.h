#pragma once

namespace Dunix
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;
        
        bool SwapChainTarget = false;
    };
    
    
    class Framebuffer
    {
    public:
        virtual const FramebufferSpecification& GetSpecification() const ;
        
        static SharedPtr<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}
