#ifndef VIEWER_H
#define VIEWER_H

#include <QImage>

#include "image-saver/image_saver.h"
#include "mesh-loader/mesh_loader.h"
#include "renderers/renderer.h"
#include "renderers/wired_renderer.h"
#include "settings/settings.h"
#include "transformer/transformer.h"

namespace s21 {

class Viewer {
 public:
  Viewer() = default;
  ~Viewer() { delete wired_renderer_; }
  Viewer(const Viewer&) = delete;
  Viewer(Viewer&&) = delete;
  Viewer& operator=(const Viewer&) = delete;
  Viewer& operator=(Viewer&&) = delete;

  QPair<uint, uint> ImportMesh(QString path);
  void ExportImage(QString path, QImage* frame_buffer);

  void InitRenderers();
  void RenderMesh();

  // transformations
  inline void MoveByX(float value) { transformer_.MoveByX(value / 10.f); }
  inline void MoveByY(float value) { transformer_.MoveByY(value / 10.f); }
  inline void MoveByZ(float value) { transformer_.MoveByZ(value / 10.f); }
  inline void RotateByX(float value) { transformer_.RotateByX(value); }
  inline void RotateByY(float value) { transformer_.RotateByY(value); }
  inline void RotateByZ(float value) { transformer_.RotateByZ(value); }
  inline void Scale(float value) { transformer_.Scale(value); }
  inline void SetAspectRatio(float value) {
    transformer_.SetAspectRatio(value);
  }

 private:
  Mesh mesh_;
  MeshLoader mesh_loader_;
  ImageSaver image_saver_;
  Transformer transformer_;

  // renderers
  Renderer renderer_;
  WiredRenderer* wired_renderer_;

  void SetRenderer(Settings::RendererType renderer);
};

}  // namespace s21

#endif  // VIEWER_H
