#ifndef LANGLIST_H
#define LANGLIST_H

#include "Lang.h"

#include <QObject>
#include <QSqlDatabase>
#include <QHash>

class LangList : public QObject
{
    Q_OBJECT
public:
    explicit LangList(QObject *parent = nullptr);
    LangList(const LangList &);
    LangList &operator=(const LangList &);

    int retrieve(QSqlDatabase* db);
    void updateItem(QSqlDatabase *db, const QString& exp, const QString& field, int id);
    void createItem(QSqlDatabase *db, const QString& exp, const QString& field);
    void sort();
    static bool comparetaor(Lang a, Lang b);
    QString getEn(int lang_id);

    QList<Lang> list() const;
    void setList(const QList<Lang> &newList);

signals:
private:
    QList<Lang> m_list;
    QHash<int, QString> m_hashEn;
};

#endif // LANGLIST_H
