#include "main_form.h"

#include <QFileDialog>

#include "settings/settings.h"
#include "ui_mainform.h"

namespace s21 {

MainForm::MainForm(Controller* controller)
    : QMainWindow(nullptr), ui(new Ui::MainForm), controller_(controller) {
  ui->setupUi(this);
  InitSettingsUI();
}

MainForm::~MainForm() { delete ui; }

void MainForm::OnActionOpenTriggered() {
  QFileDialog dialog(this, "", "", "*.obj");
  if (dialog.exec() == QFileDialog::Accepted) {
    setCursor(Qt::WaitCursor);

    QString path = dialog.selectedFiles().at(0);
    QPair<uint, uint> mesh_info = controller_->ImportFile(path);
    UpdateTitle(path, mesh_info);
    ui->openglWidget->update();

    setCursor(Qt::ArrowCursor);
  }
}

void MainForm::OnActionQuitTriggered() { QCoreApplication::quit(); }

void MainForm::OnActionResetTriggered() {
  ui->moveByXSpinBox->setValue(0);
  ui->moveByYSpinBox->setValue(0);
  ui->moveByZSpinBox->setValue(0);
  ui->rotateByXSpinBox->setValue(0);
  ui->rotateByYSpinBox->setValue(0);
  ui->rotateByZSpinBox->setValue(0);
  ui->scaleSpinBox->setValue(1);
}

void MainForm::OnActionJpegTriggered() { ExportImage("jpeg"); }

void MainForm::OnActionBmpTriggered() { ExportImage("bmp"); }

void MainForm::OnActionGifTriggered() { ExportImage("gif"); }

void MainForm::OnOpenGLWidgetInitialized() { controller_->InitRenderers(); }

void MainForm::OnOpenGLWidgetResized(float value) {
  controller_->SetAspectRatio(value);
}

void MainForm::OnOpenGLWidgetPainted() { controller_->RenderMesh(); }

void MainForm::OnOpenGLWidgetRotated(double y_value, double x_value) {
  ui->rotateByXSpinBox->setValue(ui->rotateByXSpinBox->value() + y_value);
  ui->rotateByYSpinBox->setValue(ui->rotateByYSpinBox->value() + x_value);
}

void MainForm::OnOpenGLWidgetScaled(double value) {
  ui->scaleSpinBox->setValue(ui->scaleSpinBox->value() + value);
}

void MainForm::OnMoveByXSpinBoxValueChanged(int value) {
  controller_->MoveByX(value);
  ui->openglWidget->update();
}

void MainForm::OnMoveByYSpinBoxValueChanged(int value) {
  controller_->MoveByY(value);
  ui->openglWidget->update();
}

void MainForm::OnMoveByZSpinBoxValueChanged(int value) {
  controller_->MoveByZ(value);
  ui->openglWidget->update();
}

void MainForm::OnRotateByXSpinBoxValueChanged(double value) {
  controller_->RotateByX(value);
  ui->openglWidget->update();
}

void MainForm::OnRotateByYSpinBoxValueChanged(double value) {
  controller_->RotateByY(value);
  ui->openglWidget->update();
}

void MainForm::OnRotateByZSpinBoxValueChanged(double value) {
  controller_->RotateByZ(value);
  ui->openglWidget->update();
}

void MainForm::OnScaleSpinBoxValueChanged(double value) {
  controller_->Scale(value);
  ui->openglWidget->update();
}

void MainForm::OnProjectionTypeComboBoxCurrentIndexChanged(int index) {
  Settings::GetInstance().SetProjectionType(
      static_cast<Settings::ProjectionType>(index));
  ui->openglWidget->update();
}

void MainForm::OnBackgroundColorButtonCliked() {
  QColorDialog dialog(Settings::GetInstance().GetBackgroundColor(), this);
  if (dialog.exec() == QColorDialog::Accepted) {
    Settings::GetInstance().SetBackgroundColor(dialog.selectedColor());
    UpdateColorButtons();
    ui->openglWidget->update();
  }
}

void MainForm::OnLinesTypeComboBoxCurrentIndexChanged(int index) {
  Settings::GetInstance().SetLinesType(static_cast<Settings::LinesType>(index));
  ui->openglWidget->update();
}

void MainForm::OnLinesThicknessSpinBoxValueChanged(int value) {
  Settings::GetInstance().SetLinesThickness(value);
  ui->openglWidget->update();
}

void MainForm::OnLinesColorButtonClicked() {
  QColorDialog dialog(Settings::GetInstance().GetLinesColor(), this);
  if (dialog.exec() == QColorDialog::Accepted) {
    Settings::GetInstance().SetLinesColor(dialog.selectedColor());
    UpdateColorButtons();
    ui->openglWidget->update();
  }
}

void MainForm::OnVerticesTypeComboBoxCurrentIndexChanged(int index) {
  Settings::GetInstance().SetVerticesType(
      static_cast<Settings::VerticesType>(index));
  ui->openglWidget->update();
}

void MainForm::OnVerticesSizeSpinBoxValueChanged(int value) {
  Settings::GetInstance().SetVerticesSize(value);
  ui->openglWidget->update();
}

void MainForm::OnVerticesColorButtonClicked() {
  QColorDialog dialog(Settings::GetInstance().GetVerticesColor(), this);
  if (dialog.exec() == QColorDialog::Accepted) {
    Settings::GetInstance().SetVerticesColor(dialog.selectedColor());
    UpdateColorButtons();
    ui->openglWidget->update();
  }
}

void MainForm::InitSettingsUI() {
  Settings& settings = Settings::GetInstance();

  ui->projectionTypeComboBox->setCurrentIndex(
      static_cast<int>(settings.GetProjectionType()));

  ui->linesTypeComboBox->setCurrentIndex(
      static_cast<int>(settings.GetLinesType()));

  ui->verticesTypeComboBox->setCurrentIndex(
      static_cast<int>(settings.GetVerticesType()));

  ui->linesThicknessSpinBox->setValue(settings.GetLinesThickness());

  ui->verticesSizeSpinBox->setValue(settings.GetVerticesSize());

  UpdateColorButtons();
}

void MainForm::UpdateColorButtons() {
  Settings& settings = Settings::GetInstance();

  QString common_style =
      "border-style: outset; border-width: 3px; border-radius: 5px; "
      "border-color: gray;";

  ui->backgroundColorButton->setStyleSheet(
      common_style +
      "background-color: " + settings.GetBackgroundColor().name());

  ui->linesColorButton->setStyleSheet(
      common_style + "background-color: " + settings.GetLinesColor().name());

  ui->verticesColorButton->setStyleSheet(
      common_style + "background-color:" + settings.GetVerticesColor().name());
}

void MainForm::UpdateTitle(QString path, QPair<uint, uint> mesh_info) {
  QString title =
      path.section("/", -1) + QString(" - Vertices: %1 - Fragments: %2")
                                  .arg(mesh_info.first)
                                  .arg(mesh_info.second);
  setWindowTitle(title);
}

void MainForm::ExportImage(QString extension) {
  QFileDialog dialog(this, "", "image." + extension);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  dialog.setFileMode(QFileDialog::AnyFile);
  dialog.setDefaultSuffix(extension);
  dialog.setMimeTypeFilters({"image/" + extension});

  if (dialog.exec() == QDialog::Accepted) {
    const QString file = dialog.selectedFiles().at(0);
    controller_->ExportImage(file, ui->openglWidget->GetFrameBuffer());
  }
}

}  // namespace s21
