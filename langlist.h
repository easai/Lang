#ifndef LANGLIST_H
#define LANGLIST_H

#include "Lang.h"

#include <QObject>
#include <QSqlDatabase>

class LangList : public QObject
{
    Q_OBJECT
public:
    explicit LangList(QObject *parent = nullptr);
    LangList(const LangList &);
    LangList &operator=(const LangList &);

    int retrieve(QSqlDatabase* db);

    QList<Lang> list() const;
    void setList(const QList<Lang> &newList);

signals:
private:
    QList<Lang> m_list;

};

#endif // LANGLIST_H
