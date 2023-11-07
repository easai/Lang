#ifndef STATELIST_H
#define STATELIST_H

#include "state.h"
#include <QObject>
#include <QSqlDatabase>
#include <QHash>

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
  void deleteItem(QSqlDatabase *db, int id);
  void sort();
  static bool comparetaor(State a, State b);
  int getIndex(QString state);

  QList<State> list() const;
  void setList(const QList<State> &newList);

signals:
private:
  QList<State> m_list;
    QHash<QString, int> m_hash;
};

#endif // STATELIST_H
