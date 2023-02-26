#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>

namespace s21 {

class Settings {
 public:
  enum class RendererType { kWired, kFilled, kShaded };
  enum class ProjectionType { kCentral, kParallel };
  enum class VerticesType { kNone, kCircle, kSquare };
  enum class LinesType { kSolid, kDashed };

  static Settings& GetInstance() {
    static Settings instance;
    return instance;
  }

  void LoadFromFile();
  void SaveToFile();

  ProjectionType GetProjectionType();
  void SetProjectionType(ProjectionType type);

  VerticesType GetVerticesType();
  void SetVerticesType(VerticesType type);

  LinesType GetLinesType();
  void SetLinesType(LinesType type);

  int GetVerticesSize();
  void SetVerticesSize(int size);

  int GetLinesThickness();
  void SetLinesThickness(int thickness);

  QColor GetBackgroundColor();
  void SetBackgroundColor(QColor color);

  QColor GetVerticesColor();
  void SetVerticesColor(QColor color);

  QColor GetLinesColor();
  void SetLinesColor(QColor color);

 protected:
  Settings() = default;
  ~Settings() = default;
  Settings(const Settings&) = delete;
  Settings(Settings&&) = delete;
  Settings& operator=(const Settings&) = delete;
  Settings& operator=(Settings&&) = delete;

 private:
  struct SettingsData {
    ProjectionType projection_type = ProjectionType::kCentral;
    VerticesType vertices_type = VerticesType::kNone;
    LinesType lines_type = LinesType::kSolid;
    int vertices_size = 1;
    int lines_thickness = 1;
    QColor background_color = QColor::fromRgbF(1, 1, 1);
    QColor vertices_color = QColor::fromRgbF(0, 0, 0);
    QColor lines_color = QColor::fromRgbF(0, 0, 0);
  };

  SettingsData data_;
};

}  // namespace s21

#endif  // SETTINGS_H
