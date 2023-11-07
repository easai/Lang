#include "official.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

Official::Official(QObject *parent) : QObject{parent} {}

int Official::retrieve(QSqlDatabase *db) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return 0;
  }
  QSqlQuery query(*db);
  QString sql =
      "SELECT languageID, en FROM `official` JOIN states ON stateID=states.ID";
  if (!query.exec(sql)) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  } else {
    m_langTable.clear();
    while (query.next()) {
      int cnt = -1;
      int lang_id = query.value(++cnt).toInt();
      QString en = query.value(++cnt).toString();
      m_langTable.insert(lang_id, en);
    }
  }
  db->close();
  return m_langTable.size();
}

QList<int> Official::getUniqueKeys() {
  QList<int> lst = m_langTable.uniqueKeys();
  return lst;
}

void Official::createItem(QSqlDatabase *db, int lang_id, int state_id) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "INSERT INTO `official` (languageID, stateID) VALUES "
                "(:lang_id, :state_id)";
  query.prepare(sql);
  query.bindValue(":lang_id", lang_id);
  query.bindValue(":state_id", state_id);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

QMultiHash<int, QString> Official::langTable() const { return m_langTable; }

void Official::setLangTable(const QMultiHash<int, QString> &newLangTable) {
  m_langTable = newLangTable;
}
