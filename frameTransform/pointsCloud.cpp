#include "pointsCloud.h"

bool operator<(const Dot& lhs, const Dot& rhs) {
  return lhs.x < rhs.x || lhs.y < rhs.y || lhs.z < rhs.z;
}

PointsCloud::PointsCloud(QWidget* parent)
    : QGLViewer(parent),
      choose_file_button_(new QPushButton(tr("Choose File"), this)),
      button_layout_(new QVBoxLayout()),
      dots_count_(1000000),
      max_dot_coordinate_(INT_MAX),
      dots_(new QVector<Dot>()),
      rectangle_layout_(new QVBoxLayout) {
  choose_file_button_->setGeometry({{50, 50}, choose_file_button_->sizeHint()});
  button_layout_->addWidget(choose_file_button_);
  connect(choose_file_button_, SIGNAL(clicked()), this, SLOT(ChooseFile()));
  GenerateDots();
  min_z_label_ = new QLabel("0", this);
  max_z_label_ =
      new QLabel("max height: " + QString::number(max_dot_coordinate_), this);
}

void PointsCloud::init() {
  restoreStateFromFile();
  setGridIsDrawn();
  setSceneRadius(max_dot_coordinate_);
  showEntireScene();
  setAxisIsDrawn();
  glDisable(GL_LIGHTING);
}

void PointsCloud::draw() {
  glBegin(GL_POINTS);
  for (const auto& dot : *dots_) {
    float color;
    color = dot.z;
    glColor3f(color / max_dot_coordinate_, 0.2f,
              1.0 - color / max_dot_coordinate_);
    glVertex3f(dot.x, dot.y, dot.z);
    glColor3f(0.2f, 0.8f, 0.2f);
  }
  glEnd();
  DrawColorScale();
  camera()->cameraCoordinatesOf(qglviewer::Vec(0, 0, 0));
}

void PointsCloud::GenerateDots() {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  std::set<Dot> set;
  QFile file("input.txt");
  QTextStream out(&file);
  if (file.open(QIODevice::WriteOnly)) {
    while (set.size() != dots_count_) {
      Dot dot;
      dot.x = mersenne() % max_dot_coordinate_;
      dot.y = mersenne() % max_dot_coordinate_;
      dot.z = mersenne() % max_dot_coordinate_;
      if (set.find(dot) == set.end()) {
        out << dot.x << " " << dot.y << " " << dot.z << '\n';
        set.insert(dot);
      }
    }
  }
  file.close();
}

void PointsCloud::RedrawWindow() {
  button_layout_->setSpacing(0.01 * view_height_);
  button_layout_->setGeometry(QRect(width_indent_ + 0.4 * view_width_,
                                    height_indent_ + 0.7 * view_height_,
                                    0.2 * view_width_, 0.4 * view_height_));
}

void PointsCloud::UpdateIndents() {
  view_width_ = 4 * std::min(width() / 4, height() / 3);
  view_height_ = 3 * std::min(width() / 4, height() / 3);
  width_indent_ = (width() - view_width_) / 2;
  height_indent_ = (height() - view_height_) / 2;
}

void PointsCloud::DrawColorScale() {
  rectangle_ = new QRect(width_indent_ / 2, width_indent_ / 2, view_width_ / 50,
                         view_height_ / 3);
  QPainter painter(this);
  QLinearGradient linearGrad(
      QPointF(rectangle_->left(), rectangle_->top()),
      QPointF(rectangle_->right(), rectangle_->bottom()));
  linearGrad.setColorAt(0, Qt::red);
  linearGrad.setColorAt(0.5, Qt::darkMagenta);
  linearGrad.setColorAt(1, Qt::blue);
  painter.fillRect(*rectangle_, linearGrad);
  min_z_label_->setGeometry(QRect(rectangle_->left(), rectangle_->bottom(),
                                  view_width_ / 50, view_width_ / 50));
  max_z_label_->setGeometry(QRect(rectangle_->left(), 6 * rectangle_->top() / 7,
                                  view_width_ / 6, view_width_ / 50));
}

void PointsCloud::ChooseFile() {
  file_name_ = QFileDialog::getOpenFileName(this, tr("Choose file"), "",
                                            tr("File (*.txt);;All Files (*)"));
  if (file_name_.isEmpty()) {
    return;
  } else {
    QFile file(file_name_);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
                               file.errorString());
      return;
    } else {
      QTextStream in(&file);
      while (!in.atEnd()) {
        Dot dot;
        in >> dot.x >> dot.y >> dot.z;
        dots_->push_back(dot);
      }
    }
  }
}

void PointsCloud::resizeEvent(QResizeEvent*) {
  UpdateIndents();
  RedrawWindow();
}
