#pragma once

#include "MaineCoon/Renderer/RendererAPI.h"

namespace MaineCoon {

class RenderCommand {
public:
    static void Init()
    {
        s_RendererAPI->Init();
    }

    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetViewport(x, y, width, height);
    }

    static void SetClearColor(const Vector4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    static void Clear()
    {
        s_RendererAPI->Clear();
    }

private:
    static Scope<RendererAPI> s_RendererAPI;
};

}
