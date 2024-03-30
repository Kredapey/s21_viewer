#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
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

  QColor vertexColor;
  QColor lineColor;
  QColor backgroundColor;

  float colorVertexRed;
  float colorVertexGreen;
  float colorVertexBlue;
  float colorVertexAlpha;

  float colorLineRed;
  float colorLineGreen;
  float colorLineBlue;
  float colorLineAlpha;

  float colorBGRed;
  float colorBGGreen;
  float colorBGBlue;
  float colorBGAlpha;

  data_struct data1;
  char *obj_path;
  double count;

  double move_x_old;
  double move_x;

  double move_y;
  double move_y_old;

  double move_z;
  double move_z_old;

  double rotation_x;
  double rotation_x_old;

  double rotation_y;
  double rotation_y_old;

  double rotation_z;
  double rotation_z_old;

  double scale_obj;
  double scale_obj_old;

  int lineType;
  int lineSize;

  int vertexType;
  int vertexSize;

  int projectionType;

 public slots:
};

#endif  // GLWIDGET_H
