#include "viewer.h"

#include <QtConcurrent>

namespace s21 {

QPair<uint, uint> Viewer::ImportMesh(QString path) {
  return mesh_loader_.Load(&mesh_, path);
}

void Viewer::ExportImage(QString path, QImage* frame_buffer) {
  QFuture<void> future =
      QtConcurrent::run(image_saver_.Save, path, frame_buffer);
}

void Viewer::InitRenderers() {
  wired_renderer_ = new WiredRenderer();
  SetRenderer(Settings::RendererType::kWired);
}

void Viewer::SetRenderer(Settings::RendererType renderer) {
  if (renderer == Settings::RendererType::kWired) {
    renderer_.SetRenderer(wired_renderer_);
  }
}

void Viewer::RenderMesh() {
  if (mesh_.vertices.isEmpty() || mesh_.faces.isEmpty()) return;

  QMatrix4x4 mvp_matrix = transformer_.GetMVPMatrix();
  renderer_.Render(&mesh_, mvp_matrix);
}

}  // namespace s21
