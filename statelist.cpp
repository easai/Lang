#include "statelist.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

StateList::StateList(QObject *parent) : QObject{parent} {}

StateList::StateList(const StateList &o) : m_list(o.m_list), m_hash(o.m_hash) {}

StateList &StateList::operator=(const StateList &o) {
  if (this != &o) {
    m_list = o.m_list;
    m_hash = o.m_hash;
  }
  return *this;
}

int StateList::retrieve(QSqlDatabase *db) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return 0;
  }
  QSqlQuery query(*db);
  QString sql = "SELECT ID, en, ja FROM `states`";
  if (!query.exec(sql)) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  } else {
    m_list.clear();
    while (query.next()) {
      int cnt = 0;
      int id = query.value(cnt).toInt();
      QString en = query.value(++cnt).toString();
      QString ja = query.value(++cnt).toString();
      //            int parent_id = query.value(++cnt).toInt();
      //            QString commentary = query.value(++cnt).toString();
      State State(this, id, en, ja);
      m_list.append(State);
      m_hash.insert(en, id);
    }
  }
  db->close();
  return m_list.size();
}

void StateList::updateItem(QSqlDatabase *db, const QString &exp,
                           const QString &field, int id) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "UPDATE `states` SET `" + field + "`=:exp WHERE id=:id ";
  query.prepare(sql);
  query.bindValue(":id", id);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void StateList::createItem(QSqlDatabase *db, const QString &exp,
                           const QString &field) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "INSERT INTO `states` (" + field + ") VALUES (:exp)";
  query.prepare(sql);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void StateList::deleteItem(QSqlDatabase *db, int id) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "DELETE FROM `states` WHERE `states`.`ID` = :id";
  query.prepare(sql);
  query.bindValue(":id", id);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void StateList::sort() { std::sort(m_list.begin(), m_list.end(), comparetaor); }

bool StateList::comparetaor(State a, State b) { return a.en() < b.en(); }

int StateList::getIndex(QString state) { return m_hash[state]; }

QList<State> StateList::list() const { return m_list; }

void StateList::setList(const QList<State> &newList) { m_list = newList; }
