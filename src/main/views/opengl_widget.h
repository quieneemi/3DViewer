#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QtOpenGLWidgets>

namespace s21 {

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}
  ~OpenGLWidget() = default;
  OpenGLWidget(const OpenGLWidget&) = delete;
  OpenGLWidget(OpenGLWidget&&) = delete;
  OpenGLWidget& operator=(const OpenGLWidget&) = delete;
  OpenGLWidget& operator=(OpenGLWidget&&) = delete;

  inline QImage* GetFrameBuffer() { return &frame_buffer_; }

 signals:
  void Initialized();
  void Resized(float);
  void Painted();

  void Rotated(double, double);
  void Scaled(double);

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

 private:
  QImage frame_buffer_;

  bool rotating_ = false;
  int last_pointer_x_pos_ = 0;
  int last_pointer_y_pos_ = 0;

  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
  void wheelEvent(QWheelEvent*) override;
};

}  // namespace s21

#endif  // OPENGL_WIDGET_H
