#include "officialdialog.h"
#include "ui_officialdialog.h"
#include <QInputDialog>

OfficialDialog::OfficialDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::OfficialDialog) {
  ui->setupUi(this);
  connect(ui->pushButton_official_lang, &QPushButton::clicked, this,
          &OfficialDialog::setLang);
  connect(ui->pushButton_official_state, &QPushButton::clicked, this,
          &OfficialDialog::setState);
}

OfficialDialog::~OfficialDialog() { delete ui; }

int OfficialDialog::state() const { return m_state; }

int OfficialDialog::lang() const { return m_lang; }

void OfficialDialog::setState() {
  QList<State> stateList = m_stateList.list();
  QStringList lst;
  for (const State &state : stateList) {
    QString title = state.en();
    lst.append(title);
  }
  bool ok;
  QString state = QInputDialog::getItem(this, tr("Select state"), tr("en"), lst,
                                        0, false, &ok);
  if (ok) {
    m_state = m_stateList.getIndex(state);
    ui->label_official_state->setText(state);
  }
}

void OfficialDialog::setLang() {
  QList<Lang> langList = m_langList.list();
  QStringList lst;
  for (const Lang &lang : langList) {
    QString title = lang.en();
    lst.append(title);
  }
  bool ok;
  QString lang = QInputDialog::getItem(this, tr("Select language"), tr("en"),
                                       lst, 0, false, &ok);
  if (ok) {
    m_lang = m_langList.getIndex(lang);
    ui->label_official_language->setText(lang);
  }
}

LangList OfficialDialog::langList() const { return m_langList; }

void OfficialDialog::setLangList(const LangList &newLangList) {
  m_langList = newLangList;
}

StateList OfficialDialog::stateList() const { return m_stateList; }

void OfficialDialog::setStateList(const StateList &newStateList) {
  m_stateList = newStateList;
}
