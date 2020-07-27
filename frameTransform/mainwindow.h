#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QTextStream>

#include <iostream>
#include <random>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void GenerateDots();
  void RedrawWindow();
  void UpdateIndents();

 private slots:
  void ChooseFile();

 private:
  void resizeEvent(QResizeEvent*);

 private:
  QVBoxLayout* button_layout_;
  QPushButton* choose_file_button_;
  Ui::MainWindow* ui_;

  uint64_t dots_count_;
  int view_height_;
  int view_width_;
  int height_indent_;
  int width_indent_;

  QString file_name_;
};
#endif  // MAINWINDOW_H
