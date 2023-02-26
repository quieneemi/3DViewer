#ifndef RENDERER_H
#define RENDERER_H

#include "base_renderer.h"

namespace s21 {

class Renderer {
 public:
  inline void SetRenderer(BaseRenderer* renderer) { renderer_ = renderer; }

  void Render(Mesh* mesh, QMatrix4x4 mvp_matrix) {
    renderer_->Render(mesh, mvp_matrix);
  }

 private:
  BaseRenderer* renderer_ = nullptr;
};

}  // namespace s21

#endif  // RENDERER_H
