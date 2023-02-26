#include "mesh_loader.h"

#include <QFile>
#include <QTextStream>

namespace s21 {

QPair<uint, uint> MeshLoader::Load(Mesh* mesh, QString path) {
  if (!path.endsWith(".obj")) return QPair<uint, uint>(0, 0);

  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    mesh->vertices.clear();
    mesh->faces.clear();

    float max_value = std::numeric_limits<float>::min();

    QTextStream stream(&file);
    while (stream.atEnd() == false) {
      QString line = stream.readLine();
      QStringList tokens = line.split(" ", Qt::SkipEmptyParts);

      // read vertex
      if (tokens.startsWith("v") && tokens.size() == 4) {
        for (int i = 0; i < 3; i++) {
          float point = tokens[i + 1].toFloat();
          if (fabs(point) > max_value) max_value = fabs(point);
          mesh->vertices.append(point);
        }
      }

      // read facet
      if (tokens.startsWith("f") && tokens.size() >= 4) {
        QList<uint> fragment;
        for (uint i = 1; i < tokens.size(); i++) {
          uint index = tokens[i].split("/", Qt::SkipEmptyParts)[0].toUInt() - 1;
          fragment.append(index);
        }
        mesh->faces.append(fragment);
      }
    }

    // post processing
    const float kScale = 1.f / max_value;
    std::transform(mesh->vertices.begin(), mesh->vertices.end(),
                   mesh->vertices.begin(),
                   [=](float point) { return point * kScale; });

    file.close();
  }

  return QPair<uint, uint>(mesh->vertices.size() / 3, mesh->faces.size());
}

}  // namespace s21
