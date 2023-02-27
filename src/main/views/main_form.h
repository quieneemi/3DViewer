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
  void OnActionOpenTriggered();
  void OnActionQuitTriggered();
  void OnActionResetTriggered();
  void OnActionJpegTriggered();
  void OnActionBmpTriggered();
  void OnActionGifTriggered();

  void OnOpenGLWidgetInitialized();
  void OnOpenGLWidgetResized(float);
  void OnOpenGLWidgetPainted();
  void OnOpenGLWidgetRotated(double, double);
  void OnOpenGLWidgetScaled(double);

  void OnMoveByXSpinBoxValueChanged(int);
  void OnMoveByYSpinBoxValueChanged(int);
  void OnMoveByZSpinBoxValueChanged(int);
  void OnRotateByXSpinBoxValueChanged(double);
  void OnRotateByYSpinBoxValueChanged(double);
  void OnRotateByZSpinBoxValueChanged(double);
  void OnScaleSpinBoxValueChanged(double);

  void OnProjectionTypeComboBoxCurrentIndexChanged(int);
  void OnBackgroundColorButtonCliked();
  void OnLinesTypeComboBoxCurrentIndexChanged(int);
  void OnLinesThicknessSpinBoxValueChanged(int);
  void OnLinesColorButtonClicked();
  void OnVerticesTypeComboBoxCurrentIndexChanged(int);
  void OnVerticesSizeSpinBoxValueChanged(int);
  void OnVerticesColorButtonClicked();

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
