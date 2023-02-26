#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <QString>

#include "mesh.h"

namespace s21 {

class MeshLoader {
 public:
  QPair<uint, uint> Load(Mesh* mesh, QString path);
};

}  // namespace s21

#endif  // MESH_LOADER_H
