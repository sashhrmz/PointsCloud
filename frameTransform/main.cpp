#include <qapplication.h>
#include "pointsCloud.h"

int main(int argc, char **argv) {
  QApplication application(argc, argv);

  PointsCloud viewer;

  viewer.setWindowTitle("frameTransform");

  viewer.show();

  return application.exec();
}
