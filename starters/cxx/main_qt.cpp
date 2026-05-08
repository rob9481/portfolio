#include "main_qt.h"

#include <QApplication>
#include <QLayout>
#include <QBoxLayout>

MainWindow::MainWindow() {
  auto *widget = new QWidget(this);
  exitButton_ = new QPushButton("exit", this);
  widget->setLayout(new QVBoxLayout);
  widget->layout()->addWidget(exitButton_);

  QObject::connect(exitButton_, &QPushButton::clicked, []() {
    qDebug("exiting now");
    QApplication::exit(0);
  });

  this->setCentralWidget(widget);
  this->setFixedWidth(640);
  this->setFixedHeight(480);
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
