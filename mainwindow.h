#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Statelist.h"
#include "config.h"
#include "langlist.h"
#include "official.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableWidgetItem>

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
  void updateLangItem();
  void deleteLang(const QPoint & pos);
  void deleteLangItem();
  void createLangItem();
  void updateStateItem();
  void deleteState(const QPoint & pos);
  void deleteStateItem();
  void createStateItem();
  void updateOfficialItem();
  void createOfficialItem();
  void about();

private:
  Ui::MainWindow *ui;
  Config m_config;
  LangList m_langList;
  StateList m_stateList;
  Official m_official;
  QSqlDatabase m_db;
  QStringList m_langHeader;
  QStringList m_stateHeader;
  QStringList m_officialHeader;
  int m_currentLang=-1;
  int m_currentState=-1;

  void setLangTable();
  void setStateTable();
  void setOfficialTable();
};
#endif // MAINWINDOW_H
