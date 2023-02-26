#include "settings.h"

#include <fstream>

namespace s21 {

void Settings::LoadFromFile() {
  std::ifstream stream;
  stream.open("settings.3dv");
  stream.read((char*)&data_, sizeof(SettingsData));
  stream.close();
}

void Settings::SaveToFile() {
  std::ofstream stream;
  stream.open("settings.3dv");
  stream.write((char*)&data_, sizeof(SettingsData));
  stream.close();
}

Settings::ProjectionType Settings::GetProjectionType() {
  return data_.projection_type;
}

void Settings::SetProjectionType(ProjectionType type) {
  data_.projection_type = type;
  SaveToFile();
}

Settings::VerticesType Settings::GetVerticesType() {
  return data_.vertices_type;
}

void Settings::SetVerticesType(VerticesType type) {
  data_.vertices_type = type;
  SaveToFile();
}

Settings::LinesType Settings::GetLinesType() { return data_.lines_type; }

void Settings::SetLinesType(LinesType type) {
  data_.lines_type = type;
  SaveToFile();
}

int Settings::GetVerticesSize() { return data_.vertices_size; }

void Settings::SetVerticesSize(int size) {
  data_.vertices_size = size;
  SaveToFile();
}

int Settings::GetLinesThickness() { return data_.lines_thickness; }

void Settings::SetLinesThickness(int thickness) {
  data_.lines_thickness = thickness;
  SaveToFile();
}

QColor Settings::GetBackgroundColor() { return data_.background_color; }

void Settings::SetBackgroundColor(QColor color) {
  data_.background_color = color;
  SaveToFile();
}

QColor Settings::GetVerticesColor() { return data_.vertices_color; }

void Settings::SetVerticesColor(QColor color) {
  data_.vertices_color = color;
  SaveToFile();
}

QColor Settings::GetLinesColor() { return data_.lines_color; }

void Settings::SetLinesColor(QColor color) {
  data_.lines_color = color;
  SaveToFile();
}

}  // namespace s21
