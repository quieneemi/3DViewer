#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QMainWindow>

#include "controller.h"

namespace s21 {

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainForm(Controller* controller);
  ~MainForm();
  MainForm(const MainForm&) = delete;
  MainForm(MainForm&&) = delete;
  MainForm& operator=(const MainForm&) = delete;
  MainForm& operator=(MainForm&&) = delete;

 private slots:
  void OnOpenGLWidgetInitialized();
  void OnOpenGLWidgetResized(float);
  void OnOpenGLWidgetPainted();
  void OnOpenGLWidgetRotated(double, double);
  void OnOpenGLWidgetScaled(double);
  void on_moveByXSpinBox_valueChanged(int value);
  void on_moveByYSpinBox_valueChanged(int value);
  void on_moveByZSpinBox_valueChanged(int value);
  void on_scaleSpinBox_valueChanged(double value);
  void on_projectionTypeComboBox_currentIndexChanged(int index);
  void on_backgroundColorButton_clicked();
  void on_linesTypeComboBox_currentIndexChanged(int index);
  void on_linesThicknessSpinBox_valueChanged(int value);
  void on_linesColorButton_clicked();
  void on_verticesTypeComboBox_currentIndexChanged(int index);
  void on_verticesSizeSpinBox_valueChanged(int value);
  void on_verticesColorButton_clicked();
  void on_actionOpen_triggered();
  void on_actionReset_triggered();
  void on_rotateByXDoubleSpinBox_valueChanged(double arg1);
  void on_rotateByYDoubleSpinBox_valueChanged(double arg1);
  void on_rotateByZDoubleSpinBox_valueChanged(double arg1);

 private:
  Ui::MainForm* ui;

  Controller* controller_;

  void InitSettingsUI();
  void UpdateColorButtons();
  void UpdateTitle(QString path, QPair<uint, uint> mesh_info);
  void ExportImage(QString extension);
};

}  // namespace s21

#endif  // MAIN_FORM_H
