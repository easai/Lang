#ifndef STATE_H
#define STATE_H

#include <QObject>

class State : public QObject {
  Q_OBJECT
public:
  explicit State(QObject *parent = nullptr, int id=0, const QString &en = "",
                   const QString &ja = "");
  State(const State &);
  State &operator=(const State &);

  int id() const;
  void setId(int newId);

  QString en() const;
  void setEn(const QString &newEn);

  QString ja() const;
  void setJa(const QString &newJa);

signals:
private:
  int m_id;
  QString m_en;
  QString m_ja;
};

#endif // STATE_H
