#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QMatrix4x4>

namespace s21 {

class Transformer {
 public:
  QMatrix4x4 GetMVPMatrix();

  inline void SetAspectRatio(float value) { aspect_ratio_ = value; }
  inline void MoveByX(float value) { movement_.setX(value); }
  inline void MoveByY(float value) { movement_.setY(value); }
  inline void MoveByZ(float value) { movement_.setZ(value); }
  inline void RotateByX(float value) { rotation_.setX(value); }
  inline void RotateByY(float value) { rotation_.setY(value); }
  inline void RotateByZ(float value) { rotation_.setZ(value); }
  inline void Scale(float value) { scale_ = value; }

 private:
  QVector3D movement_;
  QVector3D rotation_;
  float scale_ = 1.f;
  float aspect_ratio_ = 1.777f;
};

}  // namespace s21

#endif  // TRANSFORMER_H
