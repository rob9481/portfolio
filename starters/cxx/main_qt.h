#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow() override {}

private:
  QPushButton *exitButton_;
};

#endif // !MAIN_H
