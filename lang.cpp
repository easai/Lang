#include "lang.h"

Lang::Lang(QObject *parent, const QString& en, const QString& ja) : QObject{parent}, m_en(en), m_ja(ja) {}

Lang::Lang(const Lang &o) : m_en(o.m_en), m_ja(o.m_ja) {}

Lang &Lang::operator=(const Lang &o) {
  if (this != &o) {
    m_en = o.m_en;
    m_ja = o.m_ja;
  }
  return *this;
}


// Getters/Setters
QString Lang::en() const { return m_en; }

void Lang::setEn(const QString &newEn) { m_en = newEn; }

QString Lang::ja() const { return m_ja; }

void Lang::setJa(const QString &newJa) { m_ja = newJa; }
