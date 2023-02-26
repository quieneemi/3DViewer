#ifndef SRC_MAIN_CONTROLLER_H_
#define SRC_MAIN_CONTROLLER_H_

#include "viewer.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Viewer* viewer) : viewer_(viewer) {}
  ~Controller() = default;
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;

  QPair<uint, uint> ImportFile(QString path) {
    return viewer_->ImportMesh(path);
  }

  void ExportImage(QString path, QImage* frame_buffer) {
    viewer_->ExportImage(path, frame_buffer);
  }

  void InitRenderers() { viewer_->InitRenderers(); }
  void RenderMesh() { viewer_->RenderMesh(); }
  void SetAspectRatio(float value) { viewer_->SetAspectRatio(value); }

  // transformations
  void MoveByX(float value) { viewer_->MoveByX(value); }
  void MoveByY(float value) { viewer_->MoveByY(value); }
  void MoveByZ(float value) { viewer_->MoveByZ(value); }
  void RotateByX(float value) { viewer_->RotateByX(value); }
  void RotateByY(float value) { viewer_->RotateByY(value); }
  void RotateByZ(float value) { viewer_->RotateByZ(value); }
  void Scale(float value) { viewer_->Scale(value); }

 private:
  Viewer* viewer_;
};

}  // namespace s21

#endif  // SRC_MAIN_CONTROLLER_H_
