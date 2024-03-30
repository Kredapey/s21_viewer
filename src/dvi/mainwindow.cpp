#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_open_obj_clicked() {
  str_1 = QFileDialog::getOpenFileName(
      0, "Open file", QDir::homePath(),
      "Файлы формата .obj (*.obj)");  // получаем имя файла const char * str =

  qPrintable(str_1);
  QByteArray byteArray = str_1.toUtf8();
  char *str_3 = byteArray.data();
  printf("%s str_3\n", str_3);
  if (!str_1.isEmpty()) {
    if (this->ui && this->ui->GLwidget) {
      if (!(this->ui->GLwidget->obj_path == nullptr)) {
        delete[] this->ui->GLwidget->obj_path;
        this->ui->GLwidget->obj_path = nullptr;
      }
      this->ui->GLwidget->obj_path = new char[strlen(str_3) + 1];
      remove_data(&(this->ui->GLwidget->data1));

      main_parser(str_3, &(this->ui->GLwidget->data1), 1);
      int lastIndex = str_1.lastIndexOf('/');

      ui->file_name->setText("Название: " + str_1.mid(lastIndex + 1));

      ui->count_vertex->setText(
          "Кол-во вершин: " +
          QString::number(this->ui->GLwidget->data1.count_vertexes));
      ui->count_facets->setText(
          "Кол-во ребер: " +
          QString::number(this->ui->GLwidget->data1.count_facets));

      ui->lineSizeSpin->setValue(ui->GLwidget->lineSize);
      ui->vertexSizeSpin->setValue(ui->GLwidget->vertexSize);
      //      ui->lineSize->setValue(ui->GLwidget->lineSize);
      //      ui->vertexSize->setValue(ui->GLwidget->vertexSize);
      ui->projectionType->setCurrentIndex(ui->GLwidget->projectionType);
      ui->lineType->setCurrentIndex(ui->GLwidget->lineType);
      ui->vertexType->setCurrentIndex(ui->GLwidget->vertexType);
    }
  }
}

// void MainWindow::on_move_x_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->move_x = arg1;
//   ui->move_x_Box->setValue(arg1);
// }

// void MainWindow::on_move_y_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->move_y = arg1;
//   ui->move_y_Box->setValue(arg1);
// }

// void MainWindow::on_move_z_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->move_z = arg1;
//   ui->move_z_Box->setValue(arg1);
// }

// void MainWindow::on_rotation_x_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->rotation_x = arg1;
//   ui->rotation_x_Box->setValue(arg1);
// }

// void MainWindow::on_rotation_y_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->rotation_y = arg1;
//   ui->rotation_y_Box->setValue(arg1);
// }

// void MainWindow::on_rotation_z_slider_valueChanged(int arg1) {
//   this->ui->GLwidget->rotation_z = arg1;
//   ui->rotation_z_Box->setValue(arg1);
// }

// void MainWindow::on_scale_obj_slider_valueChanged(int value) {
//   ui->scale_obj_Box->setValue(value);
//   this->ui->GLwidget->scale_obj = value;
// }

void MainWindow::on_lineColor_clicked() {
  ui->GLwidget->lineColor = QColorDialog::getColor(QColor(255, 255, 255, 255));
  ui->GLwidget->colorLineRed = ui->GLwidget->lineColor.redF();
  ui->GLwidget->colorLineGreen = ui->GLwidget->lineColor.greenF();
  ui->GLwidget->colorLineBlue = ui->GLwidget->lineColor.blueF();
  ui->GLwidget->colorLineAlpha = ui->GLwidget->lineColor.alphaF();
}

void MainWindow::on_vertexColor_clicked() {
  ui->GLwidget->vertexColor =
      QColorDialog::getColor(QColor(255, 255, 255, 255));
  ui->GLwidget->colorVertexRed = ui->GLwidget->vertexColor.redF();
  ui->GLwidget->colorVertexGreen = ui->GLwidget->vertexColor.greenF();
  ui->GLwidget->colorVertexBlue = ui->GLwidget->vertexColor.blueF();
  ui->GLwidget->colorVertexAlpha = ui->GLwidget->vertexColor.alphaF();
}

void MainWindow::on_backgroundColor_clicked() {
  ui->GLwidget->backgroundColor =
      QColorDialog::getColor(QColor(255, 255, 255, 255));
  ui->GLwidget->colorBGRed = ui->GLwidget->backgroundColor.redF();
  ui->GLwidget->colorBGGreen = ui->GLwidget->backgroundColor.greenF();
  ui->GLwidget->colorBGBlue = ui->GLwidget->backgroundColor.blueF();
  ui->GLwidget->colorBGAlpha = ui->GLwidget->backgroundColor.alphaF();
}

void MainWindow::on_screenshot_clicked() {
  QFileDialog dialogPhoto(this);
  QString name_photo = dialogPhoto.getSaveFileName(
      this, "Save as...", "Untitled", "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->GLwidget->grabFramebuffer().save(name_photo);
}

void MainWindow::on_lineSize_valueChanged(int value) {
  ui->GLwidget->lineSize = value;
  ui->lineSizeSpin->setValue(value);
}

void MainWindow::on_lineType_currentIndexChanged(int value) {
  switch (value) {
    case 0:
      ui->GLwidget->lineType = 0;
      break;
    case 1:
      ui->GLwidget->lineType = 1;
      break;
  }
}

void MainWindow::on_vertexType_currentIndexChanged(int value) {
  switch (value) {
    case 0:
      ui->GLwidget->vertexType = 0;
      break;
    case 1:
      ui->GLwidget->vertexType = 1;
      break;
    case 2:
      ui->GLwidget->vertexType = 2;
      break;
  }
}

void MainWindow::on_vertexSize_valueChanged(int value) {
  ui->GLwidget->vertexSize = value;
  ui->vertexSizeSpin->setValue(value);
}

void MainWindow::on_projectionType_currentIndexChanged(int value) {
  switch (value) {
    case 0:
      ui->GLwidget->projectionType = 0;
      break;
    case 1:
      ui->GLwidget->projectionType = 1;
      break;
  }
}

void MainWindow::connector_time() {
  qInfo() << "on GIF clicked\n";
  timer->start(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(take_gif()));
}

void MainWindow::on_GIF_clicked() {
  filename = QFileDialog::getSaveFileName(this, "Save as...", "untitled.gif",
                                          "GIF (*.gif)");
  connector_time();
  GIF_helper();
  timer_ready = false;
}

void MainWindow::GIF_helper() {
  time++;
  QImage image = ui->GLwidget->grabFramebuffer().scaled(640, 480);

  gif->setDefaultDelay(10);
  gif->addFrame(image);

  if (time == 50) {
    QMessageBox::warning(this, "INFO", "GIF completed");
    time = 0;
    timer->stop();
    gif->save(filename);
    image.QImage::bits();
    timer_ready = true;
    delete timer;
    delete gif;
  }
}
