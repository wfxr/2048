#ifndef QTILE_H
#define QTILE_H

#include <QLabel>
#include <QString>

class QTile : public QLabel
{
    Q_OBJECT
public:
    QTile(int num);

    void setNum(int num);
private:
    void setQGraphicsDropShadowEffect(int blurRadius);
    void setStyle(const QString &background, const QString &color);
signals:

public slots:

};

#endif // QTILE_H
