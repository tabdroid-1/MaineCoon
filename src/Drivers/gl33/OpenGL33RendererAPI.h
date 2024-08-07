#pragma once

#include "MaineCoon/Renderer/RendererAPI.h"

namespace MaineCoon {

class OpenGL33RendererAPI : public RendererAPI {
public:
    virtual void Init() override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    virtual void SetClearColor(const Vector4& color) override;
    virtual void Clear() override;
};

}
