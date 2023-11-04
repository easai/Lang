#include "state.h"

State::State(QObject *parent, int id, const QString &en, const QString &ja)
    : QObject{parent}, m_id(id), m_en(en), m_ja(ja) {}

State::State(const State &o) : m_id(o.m_id), m_en(o.m_en), m_ja(o.m_ja) {}

State &State::operator=(const State &o) {
  if (this != &o) {
    m_id = o.m_id;
    m_en = o.m_en;
    m_ja = o.m_ja;
  }
  return *this;
}

int State::id() const { return m_id; }

void State::setId(int newId) { m_id = newId; }

QString State::en() const { return m_en; }

void State::setEn(const QString &newEn) { m_en = newEn; }

QString State::ja() const { return m_ja; }

void State::setJa(const QString &newJa) { m_ja = newJa; }
