#ifndef MESH_H
#define MESH_H

#include <QVector>

namespace s21 {

struct Mesh {
  QList<float> vertices;
  QList<QList<uint>> faces;
};

}  // namespace s21

#endif  // MESH_H
