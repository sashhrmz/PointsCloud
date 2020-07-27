#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      button_layout_(new QVBoxLayout()),
      choose_file_button_(new QPushButton(tr("Choose File"), this)),
      ui_(new Ui::MainWindow),
      dots_count_(1000000) {
  ui_->setupUi(this);
  choose_file_button_->setParent(centralWidget());
  choose_file_button_->setGeometry({{50, 50}, choose_file_button_->sizeHint()});
  button_layout_->addWidget(choose_file_button_);
  connect(choose_file_button_, SIGNAL(clicked()), this, SLOT(ChooseFile()));
  GenerateDots();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::ChooseFile() {
  file_name_ = QFileDialog::getOpenFileName(this, tr("Choose file"), "",
                                            tr("File (*.txt);;All Files (*)"));
  //  if (fileName.isEmpty()) {
  //    return;
  //  }
  //  else {
  //    QFile file(fileName);
  //    if (!file.open(QIODevice::ReadOnly)) {
  //      QMessageBox::information(this, tr("Unable to open file"),
  //                               file.errorString());
  //      return;
  //    } else {
  //        QTextStream in(&file);
  //    }
  //  }
}

void MainWindow::RedrawWindow() {
  button_layout_->setSpacing(0.01 * view_height_);
  button_layout_->setGeometry(QRect(width_indent_ + 0.4 * view_width_,
                                    height_indent_ + 0.7 * view_height_,
                                    0.2 * view_width_, 0.4 * view_height_));
}

void MainWindow::UpdateIndents() {
  view_width_ = 4 * std::min(width() / 4, height() / 3);
  view_height_ = 3 * std::min(width() / 4, height() / 3);
  width_indent_ = (width() - view_width_) / 2;
  height_indent_ = (height() - view_height_) / 2;
}

void MainWindow::resizeEvent(QResizeEvent *) {
  UpdateIndents();
  RedrawWindow();
}

void MainWindow::GenerateDots() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  QFile file("input.txt");
  QTextStream out(&file);
  if (file.open(QIODevice::WriteOnly)) {
    for (uint64_t i = 0; i < dots_count_; ++i) {
      out << mersenne() % 100000 << " ";
      out << mersenne() % 100000 << " ";
      out << mersenne() % 100000 << '\n';
    }
  }
  file.close();
}
