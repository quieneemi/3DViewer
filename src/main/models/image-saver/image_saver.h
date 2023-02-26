#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

#include <QImage>

namespace s21 {

class ImageSaver {
 public:
  static void Save(QString path, QImage* frame_buffer);

 private:
  static void RecordGif(QString path, QImage* frame_buffer);
  static void OpenImageFile(QString path);
};

}  // namespace s21

#endif  // IMAGE_SAVER_H
