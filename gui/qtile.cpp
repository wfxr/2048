#include "qtile.h"

#include <QString>
#include <QGraphicsDropShadowEffect>

using std::string;

QTile::QTile(int num) {
    setAlignment(Qt::AlignCenter);
    setValue(num);
}

void QTile::setValue(int num) {
    if (num == 0)
        setText("");
    else
        setNum(num);

    switch (num) {
    case 0:
        setStyle("204,192,179", "119,110,101");
        setQGraphicsDropShadowEffect(0);
        break;
    case 2:
        setStyle("238,228,218", "119,110,101");
        setQGraphicsDropShadowEffect(0);
        break;
    case 4:
        setStyle("237,224,200", "119,110,101");
        setQGraphicsDropShadowEffect(0);
        break;
    case 8:
        setStyle("242,177,121", "255,255,255");
        setQGraphicsDropShadowEffect(0);
        break;
    case 16:
        setStyle("245,150,100", "255,255,255");
        setQGraphicsDropShadowEffect(0);
        break;
    case 32:
        setStyle("245,125,95", "255,255,255");
        setQGraphicsDropShadowEffect(0);
        break;
    case 64:
        setStyle("245,95,60", "255,255,255");
        setQGraphicsDropShadowEffect(0);
        break;
    case 128:
        setStyle("237,207,114", "255,255,255");
        setQGraphicsDropShadowEffect(0);
        break;
    case 256:
        setStyle("237,204,97", "255,255,255");
        setQGraphicsDropShadowEffect(20);
        break;
    case 512:
        setStyle("237,204,97", "255,255,255");
        setQGraphicsDropShadowEffect(30);
        break;
    case 1024:
        setStyle("237,204,97", "255,255,255");
        setQGraphicsDropShadowEffect(40);
        break;
    case 2048:
        setStyle("237,204,97", "255,255,255");
        setQGraphicsDropShadowEffect(50);
        break;
    default:
        setStyle("238,228,218", "119,110,101");
        setQGraphicsDropShadowEffect(0);
        break;
    }
}

void QTile::setQGraphicsDropShadowEffect(int blurRadius) {
    if (blurRadius == 0)
        setGraphicsEffect(nullptr);
    else {
    QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
    dse->setColor(Qt::yellow);
    dse->setBlurRadius(blurRadius);
    dse->setOffset(-1);
    setGraphicsEffect(dse);
    }
}

void QTile::setStyle(const QString &background, const QString &color)
{
    setStyleSheet("QTile { background: rgb(" + background + "); color: rgb(" + color + "); font: bold; border-radius: 10px; font: 40pt; }");
}
