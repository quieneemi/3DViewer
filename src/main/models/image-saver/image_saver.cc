#include "image_saver.h"

#include <QThread>

#include "qgifimage.h"

namespace s21 {

void ImageSaver::Save(QString path, QImage* frame_buffer) {
  if (path.endsWith(".gif"))
    RecordGif(path, frame_buffer);
  else
    frame_buffer->save(path);

  OpenImageFile(path);
}

void ImageSaver::RecordGif(QString path, QImage* frame_buffer) {
  QThread::sleep(1);

  QGifImage gif(QSize(640, 480));
  gif.setDefaultDelay(100);

  for (int i = 0; i < 50; i++) {
    gif.addFrame(frame_buffer->scaled(640, 480));
    QThread::msleep(100);
  }

  gif.save(path);
}

void ImageSaver::OpenImageFile(QString path) {
#ifdef Q_OS_WINDOWS
  system(path.toStdString().c_str());
#else
  system(QString("open " + path).toStdString().c_str());
#endif
}

}  // namespace s21
