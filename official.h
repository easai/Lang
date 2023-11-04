#ifndef OFFICIAL_H
#define OFFICIAL_H

#include <QObject>
#include <QHash>
#include <QSqlDatabase>

class Official : public QObject
{
    Q_OBJECT
public:
    explicit Official(QObject *parent = nullptr);

    int retrieve(QSqlDatabase *db);
    QList<int> getUniqueKeys();

    QMultiHash<int, QString> langTable() const;
    void setLangTable(const QMultiHash<int, QString> &newLangTable);

signals:
private:
    QMultiHash<int, QString> m_langTable;
};

#endif // OFFICIAL_H
