#ifndef LANG_H
#define LANG_H

#include <QObject>

class Lang : public QObject
{
    Q_OBJECT
public:
    explicit Lang(QObject *parent = nullptr, const QString& en="", const QString& ja="");
    Lang(const Lang &);
    Lang &operator=(const Lang &);

    QString en() const;
    void setEn(const QString &newEn);

    QString ja() const;
    void setJa(const QString &newJa);

signals:
private:
    QString m_en;
    QString m_ja;
};

#endif // LANG_H
