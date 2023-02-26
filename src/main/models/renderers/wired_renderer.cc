#include "wired_renderer.h"

#include "settings/settings.h"

namespace s21 {

WiredRenderer::WiredRenderer() {
  glEnable(GL_PROGRAM_POINT_SIZE);
  glLineStipple(4, 0xAAAA);

  InitShaders();
}

void WiredRenderer::Render(Mesh* mesh, QMatrix4x4 mvp_matrix) {
  Settings& settings = Settings::GetInstance();

  // setting background color
  QColor color = settings.GetBackgroundColor();
  glClearColor(color.redF(), color.greenF(), color.blueF(), 1.f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_.bind();

  // setting model-view-projection matrix to shader
  program_.setUniformValue(mvp_matrix_loc_, mvp_matrix);

  glVertexPointer(3, GL_FLOAT, 0, mesh->vertices.data());
  glEnableClientState(GL_VERTEX_ARRAY);

  RenderLines(mesh);
  if (settings.GetVerticesType() != Settings::VerticesType::kNone) {
    RenderPoints(mesh);
  }

  glDisableClientState(GL_VERTEX_ARRAY);

  program_.release();
}

void WiredRenderer::InitShaders() {
  program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                   ":/shaders/vshader.glsl");
  program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                   ":/shaders/fshader.glsl");
  program_.link();

  size_loc_ = program_.uniformLocation("qt_PointSize");
  color_loc_ = program_.uniformLocation("qt_Color");
  mvp_matrix_loc_ = program_.uniformLocation("qt_MVPMatrix");
}

void WiredRenderer::RenderLines(Mesh* mesh) {
  Settings& settings = Settings::GetInstance();

  // setting color
  QColor color = settings.GetLinesColor();
  program_.setUniformValue(color_loc_, color.redF(), color.greenF(),
                           color.blueF(), 1.0f);

  // setting type (solid or dashed)
  if (settings.GetLinesType() == Settings::LinesType::kDashed)
    glEnable(GL_LINE_STIPPLE);
  else
    glDisable(GL_LINE_STIPPLE);

  // setting thickness
  glLineWidth(settings.GetLinesThickness());

  for (QList<uint> facet : mesh->faces) {
    glDrawElements(GL_LINE_LOOP, facet.size(), GL_UNSIGNED_INT, facet.data());
  }
}

void WiredRenderer::RenderPoints(Mesh* mesh) {
  Settings& settings = Settings::GetInstance();

  // setting size
  program_.setUniformValue(size_loc_, (float)settings.GetVerticesSize());

  // setting type (circle or square)
  if (settings.GetVerticesType() == Settings::VerticesType::kCircle)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);

  // setting vertices color to shader
  QColor color = settings.GetVerticesColor();
  program_.setUniformValue(color_loc_, color.redF(), color.greenF(),
                           color.blueF(), 1.0f);

  glDrawArrays(GL_POINTS, 0, mesh->vertices.size() / 3);
}

}  // namespace s21
