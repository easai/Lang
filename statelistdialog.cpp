#include "statelistdialog.h"
#include "ui_statelistdialog.h"

StateListDialog::StateListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateListDialog)
{
    ui->setupUi(this);
    m_header << "id"
                  << "en"
                  << "ja";

}

StateListDialog::~StateListDialog()
{
    delete ui;
}

void StateListDialog::setTable()
{
    QList<State> lst = m_stateList.list();
    int nItems=lst.size();
    ui->tableWidget_statelist_dialog->setRowCount(0);
    if (nItems <= 0) {
        return;
    }
    m_stateList.sort();

    ui->tableWidget_statelist_dialog->setColumnCount(m_header.count());
    ui->tableWidget_statelist_dialog->setHorizontalHeaderLabels(m_header);
    ui->tableWidget_statelist_dialog->horizontalHeader()->hideSection(0);
    ui->tableWidget_statelist_dialog->verticalHeader()->setVisible(false);

    for (int i = 0; i < lst.count(); i++) {
        State item = lst.at(i);

        ui->tableWidget_statelist_dialog->insertRow(i);

        int cnt = -1;
        QTableWidgetItem *idItem =
            new QTableWidgetItem(QVariant(item.id()).toString());
        ui->tableWidget_statelist_dialog->setItem(i, ++cnt, idItem);
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *targetItem = new QTableWidgetItem(item.en());
        ui->tableWidget_statelist_dialog->setItem(i, ++cnt, targetItem);

        QTableWidgetItem *descItem = new QTableWidgetItem(item.ja());
        ui->tableWidget_statelist_dialog->setItem(i, ++cnt, descItem);
    }
}

StateList StateListDialog::stateList() const
{
    return m_stateList;
}

void StateListDialog::setStateList(const StateList &newStateList)
{
    m_stateList = newStateList;
}
