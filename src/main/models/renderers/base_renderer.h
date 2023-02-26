#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

#include <QMatrix4x4>

#include "mesh.h"

namespace s21 {

class BaseRenderer {
 public:
  virtual ~BaseRenderer() = default;

  virtual void Render(Mesh* mesh, QMatrix4x4 mvp_matrix) = 0;
};

}  // namespace s21

#endif  // BASE_RENDERER_H
