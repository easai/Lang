#include "lang.h"

Lang::Lang(QObject *parent, int id, const QString &en, const QString &ja)
    : QObject{parent}, m_id(id), m_en(en), m_ja(ja) {}

Lang::Lang(const Lang &o) : m_id(o.m_id), m_en(o.m_en), m_ja(o.m_ja) {}

Lang &Lang::operator=(const Lang &o) {
  if (this != &o) {
    m_id = o.m_id;
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

int Lang::id() const { return m_id; }

void Lang::setId(int newId) { m_id = newId; }
