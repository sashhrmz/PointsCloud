#include <QGLViewer/qglviewer.h>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QTextStream>
#include <QVBoxLayout>
#include <QVector>

#include <random>
#include <set>

const float EPS = 0.0000000001f;

struct Dot {
  float x;
  float y;
  float z;
  bool operator=(const Dot& dot) {
    return (this->x - dot.x) < EPS && (this->y - dot.y) < EPS &&
           (this->z - dot.z) < EPS;
  }
};

class PointsCloud : public QGLViewer {
  Q_OBJECT
 public:
  PointsCloud(QWidget* parent = nullptr);

 protected:
  virtual void draw();
  virtual void init();

  void GenerateDots();
  void RedrawWindow();
  void UpdateIndents();
  void DrawColorScale();
  void Triangulate();

 private Q_SLOTS:
  void ChooseFile();

 private:
  virtual void resizeEvent(QResizeEvent*);

 private:
  QPushButton* choose_file_button_;
  QVBoxLayout* button_layout_;

  uint64_t dots_count_;
  uint64_t max_dot_coordinate_;

  QVector<Dot>* dots_;
  QVBoxLayout* rectangle_layout_;
  QRect* rectangle_;
  QLabel* min_z_label_;
  QLabel* max_z_label_;

  int view_height_;
  int view_width_;
  int height_indent_;
  int width_indent_;

  QString file_name_;
};
