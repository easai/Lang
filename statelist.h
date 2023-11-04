#ifndef STATELIST_H
#define STATELIST_H

#include "state.h"
#include <QObject>
#include <QSqlDatabase>

class StateList : public QObject {
  Q_OBJECT
public:
  explicit StateList(QObject *parent = nullptr);
  StateList(const StateList &);
  StateList &operator=(const StateList &);

  int retrieve(QSqlDatabase *db);
  void updateItem(QSqlDatabase *db, const QString &exp, const QString &field,
                  int id);
  void createItem(QSqlDatabase *db, const QString &exp, const QString &field);
  void sort();
  static bool comparetaor(State a, State b);

  QList<State> list() const;
  void setList(const QList<State> &newList);

signals:
private:
  QList<State> m_list;
};

#endif // STATELIST_H
