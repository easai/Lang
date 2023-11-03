#ifndef LANG_H
#define LANG_H

#include <QObject>

class Lang : public QObject {
  Q_OBJECT
public:
  explicit Lang(QObject *parent = nullptr, int id=0, const QString &en = "",
                const QString &ja = "");
  Lang(const Lang &);
  Lang &operator=(const Lang &);

  // Getters/Setters
  QString en() const;
  void setEn(const QString &newEn);

  QString ja() const;
  void setJa(const QString &newJa);

  int id() const;
  void setId(int newId);

signals:
private:
  int m_id;
  QString m_en;
  QString m_ja;
};

#endif // LANG_H
