#ifndef QTILE_H
#define QTILE_H

#include <QLabel>

class QTile : public QLabel
{
    Q_OBJECT
public:
    explicit QTile(int num);

    void setValue(int num);
private:
    void setQGraphicsDropShadowEffect(int blurRadius);
    void setStyle(const QString &background, const QString &color);
};

#endif // QTILE_H
