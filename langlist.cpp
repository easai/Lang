#include "langlist.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>


LangList::LangList(QObject *parent)
    : QObject{parent}
{

}

LangList::LangList(const LangList &o) : m_list(o.m_list) {}

LangList &LangList::operator=(const LangList &o) {
    if (this != &o) {
        m_list = o.m_list;
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
            Lang lang(this, en, ja);
            m_list.append(lang);
        }
    }
    db->close();
    return m_list.size();
}


QList<Lang> LangList::list() const
{
    return m_list;
}

void LangList::setList(const QList<Lang> &newList)
{
    m_list = newList;
}