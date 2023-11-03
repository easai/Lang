#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "config.h"
#include "lang.h"
#include "langlist.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_db = QSqlDatabase::addDatabase("QODBC", "linguistics");
  m_db.setDatabaseName("linguistics");

  connect(ui->action_About_Lang, &QAction::triggered, this, &MainWindow::about);
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  m_config.load();
  restoreGeometry(m_config.geom());
  setTable();
}

MainWindow::~MainWindow() {
  m_config.setGeom(saveGeometry());
  m_config.save();
  delete ui;
}

void MainWindow::setTable() {
  int nItems = m_list.retrieve(&m_db);
  ui->tableWidget->setRowCount(0);
  if (nItems <= 0) {
    return;
  }
  //    m_list.sort();

  QStringList header;
  header << "id"
           << "en"
           << "ja";

  ui->tableWidget->setColumnCount(header.count());
  ui->tableWidget->setHorizontalHeaderLabels(header);
  ui->tableWidget->horizontalHeader()->hideSection(0);
  //  ui->tableWidget->horizontalHeader()->setSectionResizeMode(
  //      3, QHeaderView::Stretch);
  ui->tableWidget->verticalHeader()->setVisible(false);

  QList<Lang> lst = m_list.list();
  for (int i = 0; i < lst.count(); i++) {
    Lang item = lst.at(i);

    ui->tableWidget->insertRow(i);

    int cnt = -1;
    QTableWidgetItem *idItem =
        new QTableWidgetItem(QVariant(item.id()).toString());
    ui->tableWidget->setItem(i, ++cnt, idItem);
    idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *targetItem = new QTableWidgetItem(item.en());
    ui->tableWidget->setItem(i, ++cnt, targetItem);

    QTableWidgetItem *descItem = new QTableWidgetItem(item.ja());
    ui->tableWidget->setItem(i, ++cnt, descItem);

    //        QTableWidgetItem *commentaryItem = new
    //        QTableWidgetItem(item.commentary()); ui->tableWidget->setItem(i,
    //        ++cnt, commentaryItem);
  }
}

void MainWindow::about() {
  AboutDialog *dlg = new AboutDialog(this);
  dlg->exec();
}
