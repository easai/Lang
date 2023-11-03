#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

#define AUTHOR "easai"
#define APPNAME "Lang"
#define GENERAL "General"
#define GEOM "Geometry"

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    Config(const Config &);
    Config &operator=(const Config &);

    void load();
    void save();

    QByteArray geom() const;
    void setGeom(const QByteArray &newGeom);

signals:
private:
    QByteArray m_geom;

};

#endif // CONFIG_H
