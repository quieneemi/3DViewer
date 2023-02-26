#include <QApplication>

#include "main_form.h"
#include "settings/settings.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Settings::GetInstance().LoadFromFile();
  Viewer model;
  Controller controller(&model);
  MainForm form(&controller);
  form.show();

  return app.exec();
}
