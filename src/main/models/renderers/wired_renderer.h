#ifndef WIRED_RENDERER_H
#define WIRED_RENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "base_renderer.h"

namespace s21 {

class WiredRenderer : public BaseRenderer {
 public:
  WiredRenderer();
  ~WiredRenderer() = default;
  WiredRenderer(const WiredRenderer&) = delete;
  WiredRenderer(WiredRenderer&&) = delete;
  WiredRenderer& operator=(const WiredRenderer&) = delete;
  WiredRenderer& operator=(WiredRenderer&&) = delete;

  void Render(Mesh* mesh, QMatrix4x4 mvp_matrix) override;

 private:
  QOpenGLShaderProgram program_;
  int size_loc_ = 0;
  int color_loc_ = 0;
  int mvp_matrix_loc_ = 0;

  void InitShaders();
  void RenderLines(Mesh* mesh);
  void RenderPoints(Mesh* mesh);
};

}  // namespace s21

#endif  // WIRED_RENDERER_H
