#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMouseEvent>>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <cstring>

extern "C" {
#include "../back/s21_viewer.h"
}

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  QSettings settings;
  GLWidget(QWidget *parent = 0);
  ~GLWidget();
  void loadSettings();
  void saveSettings();
  void initializeGL();
  void paintGL();
  void paint_model();
  void resizeGL(int w, int h);
  void MoveObj();
  void RoteObj();
  void ScaleObj();
  void customizeLineDisplay();
  void customizeVertexDisplay();
  void SetupPerspective();

  QColor vertexColor = nullptr;
  QColor lineColor = nullptr;
  QColor backgroundColor = nullptr;

  float colorVertexRed = 0.0;
  float colorVertexGreen = 0.0;
  float colorVertexBlue = 0.0;
  float colorVertexAlpha = 0.0;

  float colorLineRed = 0.0;
  float colorLineGreen = 0.0;
  float colorLineBlue = 0.0;
  float colorLineAlpha = 0.0;

  float colorBGRed = 0.0;
  float colorBGGreen = 0.0;
  float colorBGBlue = 0.0;
  float colorBGAlpha = 0.0;

  data_struct data1 = {0};
  char *obj_path = nullptr;
  double count = 0.0;

  double move_x_old = 0.0;
  double move_x = 0.0;

  double move_y = 0.0;
  double move_y_old = 0.0;

  double move_z = 0.0;
  double move_z_old = 0.0;

  double rotation_x = 0.0;
  double rotation_x_old = 0.0;

  double rotation_y = 0.0;
  double rotation_y_old = 0.0;

  double rotation_z = 0.0;
  double rotation_z_old = 0.0;

  double scale_obj = 0.0;
  double scale_obj_old = 0.0;

  int lineType = 0;
  int lineSize = 0;

  int vertexType = 0;
  int vertexSize = 0;

  int projectionType = 0;

 public slots:

 private:
  void mousePressEvent(QMouseEvent *mouse);
  void mouseMoveEvent(QMouseEvent *mouse);
  float rotate_mouse_x, rotate_mouse_y;
  QPoint mouse_pos;
};

#endif  // GLWIDGET_H
