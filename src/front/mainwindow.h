#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "3rdParty/giflib/gif_lib.h"
#include "gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString str_1 = nullptr;
  QString filepath = nullptr;
  bool timer_ready = true;
  QGifImage *gif = nullptr;
  int time = 0;
  QTimer *timer = nullptr;

 private slots:
  void connector_time();
  void GIF_helper();
  void on_GIF_clicked();

  void on_open_obj_clicked();
  void on_screenshot_clicked();

  void on_projectionType_currentIndexChanged(int value);

  void on_backgroundColor_clicked();
  void on_vertexColor_clicked();
  void on_lineColor_clicked();

  void on_rotation_x_Box_valueChanged(int arg1);
  void on_rotation_y_Box_valueChanged(int arg1);
  void on_rotation_z_Box_valueChanged(int arg1);

  void on_move_x_Box_valueChanged(int arg1);
  void on_move_y_Box_valueChanged(int arg1);
  void on_move_z_Box_valueChanged(int arg1);

  void on_scale_obj_Box_valueChanged(int value);

  void on_lineType_currentIndexChanged(int value);
  void on_lineSizeSpin_valueChanged(int value);

  void on_vertexSizeSpin_valueChanged(int value);
  void on_vertexType_currentIndexChanged(int value);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
