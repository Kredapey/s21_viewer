#include "glwidget.h"

GLWidget::~GLWidget() {
  saveSettings();
  remove_data(&data1);
  delete[] obj_path;
}

void GLWidget::saveSettings() {
  this->settings.setValue("lineType", this->lineType);
  this->settings.setValue("lineSize", this->lineSize);

  this->settings.setValue("vertexSize", this->vertexSize);
  this->settings.setValue("vertexType", this->vertexType);

  this->settings.setValue("projectionType", this->projectionType);

  this->settings.setValue("colorBGRed", this->colorBGRed);
  this->settings.setValue("colorBGGreen", this->colorBGGreen);
  this->settings.setValue("colorBGBlue", this->colorBGBlue);
  this->settings.setValue("colorBGAlpha", this->colorBGAlpha);

  this->settings.setValue("colorLineRed", this->colorLineRed);
  this->settings.setValue("colorLineGreen", this->colorLineGreen);
  this->settings.setValue("colorLineBlue", this->colorLineBlue);
  this->settings.setValue("colorLineAlpha", this->colorLineAlpha);

  this->settings.setValue("colorVertexRed", this->colorVertexRed);
  this->settings.setValue("colorVertexGreen", this->colorVertexGreen);
  this->settings.setValue("colorVertexBlue", this->colorVertexBlue);
  this->settings.setValue("colorVertexAlpha", this->colorVertexAlpha);
}

void GLWidget::initializeGL() {
  QOpenGLWidget::initializeGL();
  initializeOpenGLFunctions();
  loadSettings();
}

void GLWidget::loadSettings() {
  this->lineType = settings.value("lineType", 0).toInt();
  this->lineSize = settings.value("lineSize", 0).toInt();

  this->vertexSize = settings.value("vertexSize", 0).toInt();
  this->vertexType = settings.value("vertexType", 0).toInt();

  this->projectionType = settings.value("projectionType", 0).toInt();

  this->colorBGRed = settings.value("colorBGRed", 0.0).toFloat();
  this->colorBGGreen = settings.value("colorBGGreen", 0.0).toFloat();
  this->colorBGBlue = settings.value("colorBGBlue", 0.0).toFloat();
  this->colorBGAlpha = settings.value("colorBGAlpha", 1.0).toFloat();

  this->colorLineRed = settings.value("colorLineRed", 0.0).toFloat();
  this->colorLineGreen = settings.value("colorLineGreen", 0.0).toFloat();
  this->colorLineBlue = settings.value("colorLineBlue", 0.0).toFloat();
  this->colorLineAlpha = settings.value("colorLineAlpha", 1.0).toFloat();

  this->colorVertexRed = settings.value("colorVertexRed", 0.0).toFloat();
  this->colorVertexGreen = settings.value("colorVertexGreen", 0.0).toFloat();
  this->colorVertexBlue = settings.value("colorVertexBlue", 0.0).toFloat();
  this->colorVertexAlpha = settings.value("colorVertexAlpha", 1.0).toFloat();
}

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void GLWidget::paintGL() {
  makeCurrent();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  MoveObj();
  RoteObj();
  initializeOpenGLFunctions();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetupPerspective();
  customizeLineDisplay();
  customizeVertexDisplay();
  glOrtho(data1.min_x * 1.5, data1.min_x * 1.5, data1.max_x * 1.5,
          data1.max_y * 1.5, data1.min_z * 100, data1.max_z * 100);
  glEnableClientState(GL_VERTEX_ARRAY);
  glRotatef(rotate_mouse_x, 1, 0, 0);
  glRotatef(rotate_mouse_y, 0, 1, 0);
  glVertexPointer(3, GL_DOUBLE, 0, data1.coord_vert);
  glDrawElements(GL_LINES, data1.num_vert_in_pol, GL_UNSIGNED_INT,
                 data1.polygons);
  glDisableClientState(GL_VERTEX_ARRAY);
  glClearColor(this->colorBGRed, this->colorBGGreen, this->colorBGBlue, 1.0);
  glColor3d(this->colorVertexRed, this->colorVertexGreen,
            this->colorVertexBlue);
  glColor3d(this->colorLineRed, this->colorLineGreen, this->colorLineBlue);
  glEnableVertexAttribArray(0);
  paint_model();
  update();
}

void GLWidget::resizeGL(int w, int h)  // Вызывается при изменение размеров окна
{
  glViewport(0, 0, w, h);  // Облость видемости нашего окна
  glMatrixMode(GL_PROJECTION);  // устанавливаем перспективную проекцию
  glLoadIdentity();
}

void GLWidget::paint_model() {
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, data1.coord_vert);

  glColor3d(this->colorVertexRed, this->colorVertexGreen,
            this->colorVertexBlue);
  if (vertexType != 0) glDrawArrays(GL_POINTS, 0, data1.count_vertexes);

  glColor3d(this->colorLineRed, this->colorLineGreen, this->colorLineBlue);
  if (lineType != 0)
    glDrawElements(GL_LINES, data1.count_facets, GL_UNSIGNED_INT,
                   data1.polygons);

  glDisable(GL_BLEND);
}

void GLWidget::MoveObj() {
  if (move_x != move_x_old) {
    transition(&data1, -(move_x_old - move_x) / 100, 0);
    move_x_old = move_x;
  }
  if (move_y != move_y_old) {
    transition(&data1, -(move_y_old - move_y) / 100, 1);
    move_y_old = move_y;
  }
  if (move_z != move_z_old) {
    transition(&data1, -(move_z_old - move_z) / 100, 2);
    move_z_old = move_z;
  }
}

void GLWidget::RoteObj() {
  if (rotation_x != rotation_x_old) {
    rotation_by_x(&data1, -(rotation_x_old - rotation_x));
    rotation_x_old = rotation_x;
  }
  if (rotation_y != rotation_y_old) {
    rotation_by_y(&data1, -(rotation_y_old - rotation_y));
    rotation_y_old = rotation_y;
  }
  if (rotation_z != rotation_z_old) {
    rotation_by_z(&data1, -(rotation_z_old - rotation_z));
    rotation_z_old = rotation_z;
  }
}

void GLWidget::ScaleObj() { scale_data(&data1, scale_obj); }

void GLWidget::customizeLineDisplay() {
  glLineWidth(lineSize);
  if (lineType == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else if (lineType == 1) {
    glLineStipple(5, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  }
}

void GLWidget::customizeVertexDisplay() {
  glPointSize(vertexSize);
  if (vertexType == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertexType == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void GLWidget::SetupPerspective() {
  if (projectionType == 1) {
    glOrtho(data1.min_x * 1.5, data1.min_x * 1.5, data1.max_x * 1.5,
            data1.max_y * 1.5, data1.min_z * 100, data1.max_z * 100);
  } else if (projectionType == 0) {
    if (data1.max_vert < 1) {
      data1.max_vert = 2;
    }
    GLdouble zNear = data1.max_vert * 0.001;
    GLdouble zFar = data1.max_vert * 2;
    GLdouble angle = 90;
    GLdouble fH = tan(angle / 360 * M_PI) * zNear;
    GLdouble fW = fH;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    glTranslatef(0, 0, -1);
  }
}

void GLWidget::mousePressEvent(QMouseEvent *mouse) { mouse_pos = mouse->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent *mouse) {
  rotate_mouse_x = 1 / M_PI * (mouse->pos().y() - mouse_pos.y());
  rotate_mouse_y = 1 / M_PI * (mouse->pos().x() - mouse_pos.x());
  update();
}
