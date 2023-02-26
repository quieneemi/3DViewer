#include "transformer.h"

#include "settings/settings.h"

namespace s21 {

QMatrix4x4 Transformer::GetMVPMatrix() {
  QMatrix4x4 matrix;
  matrix.setToIdentity();

  if (Settings::GetInstance().GetProjectionType() ==
      Settings::ProjectionType::kCentral) {
    matrix.perspective(90.f, aspect_ratio_, 0.1f, 10.f);
  } else {
    const float kRange = 1.f;
    const float kComparator = 1.f;

    float x = kRange;  // left and right
    float y = kRange;  // bottom and top

    if (aspect_ratio_ >= kComparator)
      x *= aspect_ratio_;
    else
      y /= aspect_ratio_;

    matrix.ortho(-x, x, -y, y, 0.f, 10.f);
  }

  matrix.translate(0.f, 0.f, -1.f);
  matrix.translate(movement_);
  matrix.scale(scale_);
  matrix.rotate(rotation_.x(), 1.f, 0.f, 0.f);
  matrix.rotate(rotation_.y(), 0.f, 1.f, 0.f);
  matrix.rotate(rotation_.z(), 0.f, 0.f, 1.f);

  return matrix;
}

}  // namespace s21
