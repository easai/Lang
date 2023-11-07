#ifndef OFFICIALDIALOG_H
#define OFFICIALDIALOG_H

#include <QDialog>
#include "statelist.h"
#include "langlist.h"

namespace Ui {
class OfficialDialog;
}

class OfficialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OfficialDialog(QWidget *parent = nullptr);
    ~OfficialDialog();

    int state() const;

    int lang() const;

    StateList stateList() const;
    void setStateList(const StateList &newStateList);

    LangList langList() const;
    void setLangList(const LangList &newLangList);

private slots:
    void setState();
    void setLang();

private:
    StateList m_stateList;
    LangList m_langList;
    int m_state;
    int m_lang;
    Ui::OfficialDialog *ui;
};

#endif // OFFICIALDIALOG_H
