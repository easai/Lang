#include "langlist.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

LangList::LangList(QObject *parent) : QObject{parent} {}

LangList::LangList(const LangList &o)
    : m_list(o.m_list), m_hash(o.m_hash), m_hashEn(o.m_hashEn) {}

LangList &LangList::operator=(const LangList &o) {
  if (this != &o) {
    m_list = o.m_list;
    m_hash = o.m_hash;
    m_hashEn = o.m_hashEn;
  }
  return *this;
}

int LangList::retrieve(QSqlDatabase *db) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return 0;
  }
  QSqlQuery query(*db);
  QString sql = "SELECT ID, en, ja commentary FROM `languages`";
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
      Lang lang(this, id, en, ja);
      m_list.append(lang);
      m_hashEn.insert(id, en);
      m_hash.insert(en, id);
    }
  }
  db->close();
  return m_list.size();
}

void LangList::updateItem(QSqlDatabase *db, const QString &exp,
                          const QString &field, int id) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "UPDATE `languages` SET `" + field + "`=:exp WHERE id=:id ";
  query.prepare(sql);
  query.bindValue(":id", id);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void LangList::createItem(QSqlDatabase *db, const QString &exp,
                          const QString &field) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "INSERT INTO `languages` (" + field + ") VALUES (:exp)";
  query.prepare(sql);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void LangList::sort() { std::sort(m_list.begin(), m_list.end(), comparetaor); }

QList<int> LangList::sort(const QList<int> &lst) {
  QList<Lang> langList;
  for (int i = 0; i < lst.length(); i++) {
    int idx = lst.at(i);
    Lang lang(this, idx, getEn(idx), "");
    langList.append(lang);
  }
  std::sort(langList.begin(), langList.end(), comparetaor);
  QList<int> newList;
  for (int i = 0; i < langList.size(); i++) {
    newList.append(langList.at(i).id());
  }
  return newList;
}

bool LangList::comparetaor(Lang a, Lang b) { return a.en() < b.en(); }

QString LangList::getEn(int lang_id) { return m_hashEn[lang_id]; }

int LangList::getIndex(QString lang) { return m_hash[lang]; }

void LangList::deleteItem(QSqlDatabase *db, int id)
{
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "DELETE FROM `languages` WHERE `languages`.`ID` = :id";
  query.prepare(sql);
  query.bindValue(":id", id);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

QList<Lang> LangList::list() const { return m_list; }

void LangList::setList(const QList<Lang> &newList) { m_list = newList; }
