#include "opengl_widget.h"

namespace s21 {

void OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  emit Initialized();
}

void OpenGLWidget::resizeGL(int width, int height) {
  emit Resized((float)width / (float)height);
}

void OpenGLWidget::paintGL() {
  emit Painted();

  frame_buffer_ = grabFramebuffer();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e) {
  QApplication::setOverrideCursor(Qt::ClosedHandCursor);

  if (e->button() == Qt::LeftButton) {
    rotating_ = true;
    last_pointer_x_pos_ = e->pos().x();
    last_pointer_y_pos_ = e->pos().y();
  }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e) {
  QApplication::restoreOverrideCursor();

  if (e->button() == Qt::LeftButton) {
    rotating_ = false;
  }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e) {
  if (rotating_) {
    double y_value = 1 / M_PI * (e->pos().y() - last_pointer_y_pos_);
    double x_value = 1 / M_PI * (e->pos().x() - last_pointer_x_pos_);

    emit Rotated(y_value, x_value);

    last_pointer_x_pos_ = e->pos().x();
    last_pointer_y_pos_ = e->pos().y();
  }
}

void OpenGLWidget::wheelEvent(QWheelEvent *e) {
  emit Scaled(e->angleDelta().y() > 0 ? 0.01 : -0.01);
}

}  // namespace s21
