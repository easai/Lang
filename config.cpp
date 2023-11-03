#include "config.h"
#include <QSettings>

Config::Config(QObject *parent)
    : QObject{parent}
{

}

Config::Config(const Config &o) : m_geom(o.m_geom) {}

Config &Config::operator=(const Config &o) {
    if (this != &o) {
        m_geom = o.m_geom;
    }
    return *this;
}

void Config::load() {
    QSettings settings(AUTHOR, APPNAME);
    settings.beginGroup(GENERAL);
    m_geom = settings.value(GEOM).toByteArray();
    settings.endGroup();
}

void Config::save() {
    QSettings settings(AUTHOR, APPNAME);
    settings.beginGroup(GENERAL);
    settings.setValue(GEOM, m_geom);
    settings.endGroup();
}

QByteArray Config::geom() const
{
    return m_geom;
}

void Config::setGeom(const QByteArray &newGeom)
{
    m_geom = newGeom;
}
