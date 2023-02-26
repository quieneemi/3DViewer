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

void MainForm::OnOpenGLWidgetInitialized() { controller_->InitRenderers(); }

void MainForm::OnOpenGLWidgetResized(float value) {
  controller_->SetAspectRatio(value);
}

void MainForm::OnOpenGLWidgetPainted() { controller_->RenderMesh(); }

void MainForm::OnOpenGLWidgetRotated(double y_value, double x_value) {
  ui->rotateByXDoubleSpinBox->setValue(ui->rotateByXDoubleSpinBox->value() +
                                       y_value);
  ui->rotateByYDoubleSpinBox->setValue(ui->rotateByYDoubleSpinBox->value() +
                                       x_value);
}

void MainForm::OnOpenGLWidgetScaled(double value) {
  ui->scaleSpinBox->setValue(ui->scaleSpinBox->value() + value);
}

MainForm::~MainForm() { delete ui; }

// void MainForm::on_importButton_clicked() {
//   QFileDialog dialog(this, "", "", "*.obj");
//   if (dialog.exec() == QFileDialog::Accepted) {
//     setCursor(Qt::WaitCursor);

//    QString path = dialog.selectedFiles().at(0);
//    QPair<uint, uint> mesh_info = controller_->ImportFile(path);
//    UpdateTitle(path, mesh_info);
//    ui->openglWidget->update();

//    setCursor(Qt::ArrowCursor);
//  }
//}

// void MainForm::on_jpegExportButton_clicked() { ExportImage("jpeg"); }

// void MainForm::on_bmpExportButton_clicked() { ExportImage("bmp"); }

// void MainForm::on_gifExportButton_clicked() { ExportImage("gif"); }

void MainForm::on_moveByXSpinBox_valueChanged(int value) {
  controller_->MoveByX(value);
  ui->openglWidget->update();
}

void MainForm::on_moveByYSpinBox_valueChanged(int value) {
  controller_->MoveByY(value);
  ui->openglWidget->update();
}

void MainForm::on_moveByZSpinBox_valueChanged(int value) {
  controller_->MoveByZ(value);
  ui->openglWidget->update();
}

void MainForm::on_scaleSpinBox_valueChanged(double value) {
  controller_->Scale(value);
  ui->openglWidget->update();
}

void MainForm::on_projectionTypeComboBox_currentIndexChanged(int index) {
  Settings::GetInstance().SetProjectionType(
      static_cast<Settings::ProjectionType>(index));
  ui->openglWidget->update();
}

void MainForm::on_backgroundColorButton_clicked() {
  QColorDialog dialog(Settings::GetInstance().GetBackgroundColor(), this);
  if (dialog.exec() == QColorDialog::Accepted) {
    Settings::GetInstance().SetBackgroundColor(dialog.selectedColor());
    UpdateColorButtons();
    ui->openglWidget->update();
  }
}

void MainForm::on_linesTypeComboBox_currentIndexChanged(int index) {
  Settings::GetInstance().SetLinesType(static_cast<Settings::LinesType>(index));
  ui->openglWidget->update();
}

void MainForm::on_linesThicknessSpinBox_valueChanged(int value) {
  Settings::GetInstance().SetLinesThickness(value);
  ui->openglWidget->update();
}

void MainForm::on_linesColorButton_clicked() {
  QColorDialog dialog(Settings::GetInstance().GetLinesColor(), this);
  if (dialog.exec() == QColorDialog::Accepted) {
    Settings::GetInstance().SetLinesColor(dialog.selectedColor());
    UpdateColorButtons();
    ui->openglWidget->update();
  }
}

void MainForm::on_verticesTypeComboBox_currentIndexChanged(int index) {
  Settings::GetInstance().SetVerticesType(
      static_cast<Settings::VerticesType>(index));
  ui->openglWidget->update();
}

void MainForm::on_verticesSizeSpinBox_valueChanged(int value) {
  Settings::GetInstance().SetVerticesSize(value);
  ui->openglWidget->update();
}

void MainForm::on_verticesColorButton_clicked() {
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

void MainForm::on_actionOpen_triggered() {
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

void MainForm::on_actionReset_triggered() {
  ui->moveByXSpinBox->setValue(0);
  ui->moveByYSpinBox->setValue(0);
  ui->moveByZSpinBox->setValue(0);
  ui->rotateByXDoubleSpinBox->setValue(0);
  ui->rotateByYDoubleSpinBox->setValue(0);
  ui->rotateByZDoubleSpinBox->setValue(0);
  ui->scaleSpinBox->setValue(1);
}

void MainForm::on_rotateByXDoubleSpinBox_valueChanged(double value) {
  controller_->RotateByX(value);
  ui->openglWidget->update();
}

void MainForm::on_rotateByYDoubleSpinBox_valueChanged(double value) {
  controller_->RotateByY(value);
  ui->openglWidget->update();
}

void MainForm::on_rotateByZDoubleSpinBox_valueChanged(double value) {
  controller_->RotateByZ(value);
  ui->openglWidget->update();
}

}  // namespace s21
