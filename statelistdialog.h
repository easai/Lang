#ifndef STATELISTDIALOG_H
#define STATELISTDIALOG_H

#include "statelist.h"
#include <QDialog>

namespace Ui {
class StateListDialog;
}

class StateListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StateListDialog(QWidget *parent = nullptr);
    ~StateListDialog();

    void setTable();

    StateList stateList() const;
    void setStateList(const StateList &newStateList);

private:
    Ui::StateListDialog *ui;

    StateList m_stateList;
    QStringList m_header;
};

#endif // STATELISTDIALOG_H
