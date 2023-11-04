#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "config.h"
#include "langlist.h"

#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowIcon(QIcon("://images/favicon.ico"));
  m_db = QSqlDatabase::addDatabase("QODBC", "linguistics");
  m_db.setDatabaseName("linguistics");

  connect(ui->action_About_Lang, &QAction::triggered, this, &MainWindow::about);
  connect(ui->action_Quit, &QAction::triggered, this, &QApplication::quit);
  m_config.load();
  restoreGeometry(m_config.geom());
  m_langHeader << "id"
               << "en"
               << "ja";
  m_stateHeader << "id"
                << "en"
                << "ja";
  m_officialHeader <<"Language"
                   << "States";
  setLangTable();
  setStateTable();
  setOfficialTable();
  connect(ui->tableWidget, &QTableWidget::cellChanged, this,
          &MainWindow::updateLangItem);
  connect(ui->pushButton_add, &QPushButton::clicked, this,
          &MainWindow::createLangItem);
  connect(ui->tableWidget_states, &QTableWidget::cellChanged, this,
          &MainWindow::updateStateItem);
  connect(ui->pushButton_add_state, &QPushButton::clicked, this,
          &MainWindow::createStateItem);
}

MainWindow::~MainWindow() {
  m_config.setGeom(saveGeometry());
  m_config.save();
  delete ui;
}

void MainWindow::setLangTable() {
  int nItems = m_langList.retrieve(&m_db);
  ui->tableWidget->setRowCount(0);
  if (nItems <= 0) {
    return;
  }
  m_langList.sort();

  ui->tableWidget->setColumnCount(m_langHeader.count());
  ui->tableWidget->setHorizontalHeaderLabels(m_langHeader);
  ui->tableWidget->horizontalHeader()->hideSection(0);
  ui->tableWidget->verticalHeader()->setVisible(false);

  QList<Lang> lst = m_langList.list();
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
  }
}

void MainWindow::setStateTable() {
  int nItems = m_stateList.retrieve(&m_db);
  ui->tableWidget_states->setRowCount(0);
  if (nItems <= 0) {
    return;
  }
  m_stateList.sort();

  ui->tableWidget_states->setColumnCount(m_stateHeader.count());
  ui->tableWidget_states->setHorizontalHeaderLabels(m_stateHeader);
  ui->tableWidget_states->horizontalHeader()->hideSection(0);
  ui->tableWidget_states->verticalHeader()->setVisible(false);

  QList<State> lst = m_stateList.list();
  for (int i = 0; i < lst.count(); i++) {
    State item = lst.at(i);

    ui->tableWidget_states->insertRow(i);

    int cnt = -1;
    QTableWidgetItem *idItem =
        new QTableWidgetItem(QVariant(item.id()).toString());
    ui->tableWidget_states->setItem(i, ++cnt, idItem);
    idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

    QTableWidgetItem *targetItem = new QTableWidgetItem(item.en());
    ui->tableWidget_states->setItem(i, ++cnt, targetItem);

    QTableWidgetItem *descItem = new QTableWidgetItem(item.ja());
    ui->tableWidget_states->setItem(i, ++cnt, descItem);
  }
}

void MainWindow::setOfficialTable()
{
  int nItems = m_official.retrieve(&m_db);
  ui->tableWidget_official->setRowCount(0);
  if (nItems <= 0) {
    return;
  }

  ui->tableWidget_official->setColumnCount(m_officialHeader.count());
  ui->tableWidget_official->setHorizontalHeaderLabels(m_officialHeader);
  ui->tableWidget_official->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);
  ui->tableWidget_official->verticalHeader()->setVisible(false);

  QMultiHash<int, QString> hash = m_official.langTable();
  QList<int> lst=hash.uniqueKeys();
  for (int i = 0; i < lst.count(); i++) {
    int idx = lst.at(i);

    QStringList stateList;
    QMultiHash<int, QString>::const_iterator iter = hash.find(idx);
    while (iter != hash.end() && iter.key() == idx) {
        stateList.append(iter.value());
        ++iter;
    }
    ui->tableWidget_official->insertRow(i);
    int cnt = -1;
    QTableWidgetItem *targetItem = new QTableWidgetItem(m_langList.getEn(idx));
    ui->tableWidget_official->setItem(i, ++cnt, targetItem);

    QTableWidgetItem *descItem = new QTableWidgetItem(stateList.join(", "));
    ui->tableWidget_official->setItem(i, ++cnt, descItem);
  }
}

void MainWindow::updateLangItem() {
  QList<QTableWidgetItem *> lst = ui->tableWidget->selectedItems();
  for (QTableWidgetItem *pItem : lst) {
    QString exp = pItem->text();
    int row = pItem->row();
    int col = pItem->column();
    QTableWidgetItem *pId = ui->tableWidget->item(row, 0);
    int id = pId->text().toInt();
    QString field = m_langHeader.at(col);
    m_langList.updateItem(&m_db, exp, field, id);
  }
}

void MainWindow::updateStateItem() {
  QList<QTableWidgetItem *> lst = ui->tableWidget_states->selectedItems();
  for (QTableWidgetItem *pItem : lst) {
    QString exp = pItem->text();
    int row = pItem->row();
    int col = pItem->column();
    QTableWidgetItem *pId = ui->tableWidget_states->item(row, 0);
    int id = pId->text().toInt();
    QString field = m_stateHeader.at(col);
    m_stateList.updateItem(&m_db, exp, field, id);
  }
}

void MainWindow::createLangItem() {
  bool ok;
  QString exp = QInputDialog::getText(this, tr("Add new language"), tr("en"),
                                      QLineEdit::Normal, "", &ok);
  if (ok) {
    m_langList.createItem(&m_db, exp, "en");
    setLangTable();
  }
}

void MainWindow::createStateItem() {
  bool ok;
  QString exp = QInputDialog::getText(this, tr("Add new state"), tr("en"),
                                      QLineEdit::Normal, "", &ok);
  if (ok) {
    m_stateList.createItem(&m_db, exp, "en");
    setStateTable();
  }
}

void MainWindow::about() {
  AboutDialog *dlg = new AboutDialog(this);
  dlg->exec();
}
