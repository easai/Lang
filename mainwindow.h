#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include "langlist.h"
#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void about();

private:
  Ui::MainWindow *ui;
  Config m_config;
  LangList m_list;
  QSqlDatabase m_db;


  void setTable();
};
#endif // MAINWINDOW_H
