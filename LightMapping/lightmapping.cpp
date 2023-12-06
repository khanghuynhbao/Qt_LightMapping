
#include "lightmapping.h"

LightMapping::LightMapping(QWidget *parent)
    : QWidget{parent},
    mEffect(type0),
    mPoint_X(200),
    mPoint_Y(100),
    mSideLength(200),
    mPenW(1),
    mEffectIndex(-1)
{
    mEffectsList << type0 << type1 << type2 << type3 << type4 << type5 << type6 << type7;
//    QTimer *updateEffect5Timer = new QTimer(this);
//    connect(updateEffect5Timer, &QTimer::timeout, this, &LightMapping::updateEffectType5);
//    updateEffect5Timer->start(1000);
}

void LightMapping::setupEffectDurations(int duration)
{
    mEffectDurations[type0] = 2000;
    mEffectDurations[type1] = 8000;
    mEffectDurations[type2] = 7000;
    mEffectDurations[type3] = 7000;
    mEffectDurations[type4] = 7000;
    mEffectDurations[type5] = 7000;
    mEffectDurations[type6] = 2400;
    mEffectDurations[type7] = 240000;
}
void LightMapping::initializeTimers()
{
    setupEffectDurations(1000);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LightMapping::changeEffect);
    timer->start(mEffectDurations[mEffect]);

    QTimer *updateEffect1Timer = new QTimer(this);
    connect(updateEffect1Timer, &QTimer::timeout, this, &LightMapping::updateEffectType1);
    updateEffect1Timer->start(1000);

    QTimer *updateEffect2Timer = new QTimer(this);
    connect(updateEffect2Timer, &QTimer::timeout, this, &LightMapping::updateEffectType2);
    updateEffect2Timer->start(1000);

    QTimer *updateEffect3Timer = new QTimer(this);
    connect(updateEffect3Timer, &QTimer::timeout, this, &LightMapping::updateEffectType3);
    updateEffect3Timer->start(1000);

    QTimer *updateEffect4Timer = new QTimer(this);
    connect(updateEffect4Timer, &QTimer::timeout, this, &LightMapping::updateEffectType4);
    updateEffect4Timer->start(1000);

    QTimer *updateEffect5Timer = new QTimer(this);
    connect(updateEffect5Timer, &QTimer::timeout, this, &LightMapping::updateEffectType5);
    updateEffect5Timer->start(1000);

    QTimer *updateEffect6Timer = new QTimer(this);
    connect(updateEffect6Timer, &QTimer::timeout, this, &LightMapping::updateEffectType6);
    updateEffect6Timer->start(100);
}
void LightMapping::updateEffectType1()
{
    if (mEffect == type1) {
        if (lineIndex <= 7) {
            lineIndex += 1;
            //            qDebug() << "lineIndex" << lineIndex;
        }
        else if (lineIndex > 7) {
            lineIndex = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType2()
{
    if (mEffect == type2) {
        if (countChangeColor <= 6) {
            countChangeColor += 1;
            //            qDebug() << "count change color" << countChangeColor;
        }
        else if (countChangeColor >= 7) {
            countChangeColor = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType3()
{
    if (mEffect == type3) {
        if (countChangeRadial <= 3) {
            countChangeRadial += 1;
            //            qDebug() << "count change radial" << countChangeRadial;
        }
        else if (countChangeRadial > 4) {
            countChangeRadial = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType4()
{
    if (mEffect == type4) {
        if (countChangeLinear <= 3) {
            countChangeLinear += 1;
            //            qDebug() << "count change linear" << countChangeLinear;
        }
        else if (countChangeLinear >= 4) {
            countChangeLinear = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType5()
{
    if (mEffect == type5) {
        if (countChangeConical <= 3) {
            countChangeConical += 1;
                        qDebug() << "count change conical" << countChangeConical;
        }
        else if (countChangeConical >= 4) {
            countChangeConical = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType6()
{
    if (mEffect == type6 && currentAngle < 360) {
        currentAngle += 15;
        update();
    } else if (mEffect == type6) {
        currentAngle = 0;
        update();
    }
}

void LightMapping::changeEffect()
{
    int numEffects = mEffectsList.size();
    mEffectIndex = (mEffectIndex + 1) % numEffects;
    mEffect = mEffectsList[mEffectIndex];

    QTimer *timer = qobject_cast<QTimer*>(sender());
    if (timer) {
        timer->start(mEffectDurations[mEffect]);
    }
    update();
}

void LightMapping::effect(QPainter *event)
{
    switch (mEffect) {
    case type0:
        return effect_type0(event);
    case type1:
        return effect_type1(event);
    case type2:
        return effect_type2(event);
    case type3:
        return effect_type3(event);
    case type4:
        return effect_type4(event);
    case type5:
        return effect_type5(event);
    case type6:
        return effect_type6(event);
    default:
        break;
    }
}

void LightMapping::effect_type0(QPainter *event)
{
    QColor backgroundColor, borderColor;
    backgroundColor = QColor(255, 255, 255);
    borderColor = QColor(211,211,211);
    event->setBrush(backgroundColor);
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid(event);
}
void LightMapping::effect_type1(QPainter *event)
{
    QColor borderColor = QColor(255, 255, 255);
    QColor backgroundColor = QColor(000, 000, 000);
    event->setBrush(backgroundColor);
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid_Border(event);
}
void LightMapping::effect_type2(QPainter *event)
{
    QColor colorLeft = QColor(169, 169, 169);
    QColor colorRight = QColor(245, 245, 245);
    QColor colorBottom = QColor(245, 245, 245);
    QColor colorShadowLeft = QColor(32, 32, 32);
    QColor colorShadowRight = QColor(0, 0, 0);
    QColor colorShadowBottom = QColor(0, 0, 0);
    QColor borderColor = QColor(0, 0, 0);
    mPen.setBrush(borderColor);
    event->setPen(mPen);

    discoloration(event, colorLeft, colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
}
void LightMapping::effect_type3(QPainter *event)
{
//    QColor borderColor;
//    borderColor = Qt::gray;
//    mPen.setBrush(borderColor);
//    mPen.setWidth(mPenW);
//    event->setPen(mPen);
    event->setPen(Qt::transparent);
    discoloration_RadialGradient(event, mColor1, mColor2, mColor3);
}

void LightMapping::effect_type4(QPainter *event)
{
//    QColor borderColor;
//    borderColor = Qt::gray;
//    mPen.setBrush(borderColor);
//    mPen.setWidth(mPenW);
//    event->setPen(mPen);
    event->setPen(Qt::transparent);
    discoloration_LinearGradient(event, mColor1, mColor2, mColor3);
}
void LightMapping::effect_type5(QPainter *event)
{
//    QColor borderColor;
//    borderColor = Qt::gray;
//    mPen.setBrush(borderColor);
//    mPen.setWidth(mPenW);
//    event->setPen(mPen);
    event->setPen(Qt::transparent);
    discoloration_ConicalGradient(event, mColor1, mColor2, mColor3);
}
void LightMapping::effect_type6(QPainter *event)
{
    QColor borderColor = Qt::gray;
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid_Rotated(event, currentAngle);
}
void LightMapping::effect_type7(QPainter *event)
{
    QColor borderColor = Qt::gray;
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

}
void LightMapping::calculatePoint(int posX, int posY){
    float height = mSideLength * sqrt(3)/2;
    topPoint.setX(mPoint_X + mSideLength / 2 + posX);
    topPoint.setY(mPoint_Y + posY);
    leftPoint.setX(mPoint_X + posX);
    leftPoint.setY(mPoint_Y + height + posY);
    rightPoint.setX(mPoint_X + mSideLength + posX);
    rightPoint.setY(mPoint_Y + height + posY);
    centerPoint.setX((topPoint.x() + leftPoint.x() + rightPoint.x()) / 3);
    centerPoint.setY((topPoint.y() + leftPoint.y() + rightPoint.y()) / 3);
    topLeftPoint.setX(mPoint_X +  + posX);
    topLeftPoint.setY(mPoint_Y + height / 3 + posY);
    topRightPoint.setX(mPoint_X + mSideLength + posX);
    topRightPoint.setY(mPoint_Y + height / 3 + posY);
    leftRightPoint.setX(mPoint_X + mSideLength / 2 + posX);
    leftRightPoint.setY(mPoint_Y + height + height / 3 + posY) ;
}

void LightMapping::drawPyramid(QPainter *event, int posX, int posY)
{
    calculatePoint(posX, posY);
    QPolygon polygonLeft, polygonRight, polygonBottom;
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;

    event->drawPolygon(polygonLeft);
    event->drawPolygon(polygonRight);
    event->drawPolygon(polygonBottom);
}
void LightMapping::drawSixPyramid(QPainter *event)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid(event, mSideLength, 0);
    drawPyramid(event, mSideLength / 2, height);
    drawPyramid(event, mSideLength * 1.5, height);
    drawPyramid(event, 0, 2 * height);
    drawPyramid(event, mSideLength, 2 * height);
    drawPyramid(event, mSideLength * 2 , 2 * height);
}

void LightMapping::drawPyramid_Color(QPainter *event, int posX, int posY, QColor colorLeft, QColor colorRight, QColor colorBottom,
                                     QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    calculatePoint(posX, posY);
    QPolygon polygonLeft, polygonRight, polygonBottom, polygonTopLeft, polygonTopRight, polygonLeftRight;
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;
    polygonTopLeft << topPoint << leftPoint << topLeftPoint;
    polygonTopRight << topPoint << rightPoint <<  topRightPoint;
    polygonLeftRight << leftPoint << rightPoint << leftRightPoint;

    event->setBrush(QBrush(colorLeft));
    event->drawPolygon(polygonLeft);

    event->setBrush(QBrush(colorRight));
    event->drawPolygon(polygonRight);

    event->setBrush(QBrush(colorBottom));
    event->drawPolygon(polygonBottom);

    event->setBrush(QBrush(colorShadowLeft));
    event->drawPolygon(polygonTopLeft);

    event->setBrush(QBrush(colorShadowRight));
    event->drawPolygon(polygonTopRight);

    event->setBrush(QBrush(colorShadowBottom));
    event->drawPolygon(polygonLeftRight);
}
void LightMapping::drawSixPyramid_Color(QPainter *event, QColor color1, QColor color2, QColor color3,
                                        QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Color(event, mSideLength, 0, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength / 2, height, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength * 1.5, height, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, 0, 2 * height, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom) ;
    drawPyramid_Color(event, mSideLength, 2 * height, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength * 2 , 2 * height, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
}
void LightMapping::discoloration(QPainter *event, QColor color1, QColor color2, QColor color3,
                                 QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    switch (countChangeColor) {
    case 1:
        drawSixPyramid_Color(event, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 2:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(32, 32, 32);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event,  color3, color1 , color2, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 3:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(32, 32, 32);
        drawSixPyramid_Color(event, color2, color3, color1, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 4:
        colorShadowLeft = QColor(32, 32, 32);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event, color1 , color2, color3, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 5:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(32, 32, 32);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event, color3, color1 , color2, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 6:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(32, 32, 32);
        drawSixPyramid_Color(event, color2, color3, color1, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    default:
        break;
    }
}

void LightMapping::drawPyramid_LinearGradient(QPainter *event, int posX, int posY, QColor color1, QColor color2, QColor color3)
{
    calculatePoint(posX, posY);
    QPolygon polygonLeft, polygonRight, polygonBottom;
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;

    QLinearGradient gradientLeft(topPoint, leftPoint);
    gradientLeft.setColorAt(0, color1);
    gradientLeft.setColorAt(1, color2);
    QLinearGradient gradientRight(topPoint, rightPoint);
    gradientRight.setColorAt(0, color1);
    gradientRight.setColorAt(1, color3);
    QLinearGradient gradientBottom(leftPoint, rightPoint);
    gradientBottom.setColorAt(0, color2);
    gradientBottom.setColorAt(1, color3);

    event->setBrush(gradientLeft);
    event->drawPolygon(polygonLeft);
    event->setBrush(gradientRight);
    event->drawPolygon(polygonRight);
    event->setBrush(gradientBottom);
    event->drawPolygon(polygonBottom);
}
void LightMapping::drawSixPyramid_LinearGradients(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_LinearGradient(event, mSideLength, 0, color1 , color2, color3);
    drawPyramid_LinearGradient(event, mSideLength / 2, height, color1 , color2, color3);
    drawPyramid_LinearGradient(event, mSideLength * 1.5, height, color1 , color2, color3);
    drawPyramid_LinearGradient(event, 0, 2 * height, color1 , color2, color3);
    drawPyramid_LinearGradient(event, mSideLength, 2 * height, color1 , color2, color3);
    drawPyramid_LinearGradient(event, mSideLength * 2 , 2 * height, color1 , color2, color3);
}
void LightMapping::discoloration_LinearGradient(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    int currentIndex = (countChangeLinear - 1) % 3;
    drawSixPyramid_LinearGradients(event,
                            (currentIndex == 0) ? color1 : ((currentIndex == 1) ? color3 : color2),
                                (currentIndex == 0) ? color2 : ((currentIndex == 1) ? color1 : color3),
                                   (currentIndex == 0) ? color3 : ((currentIndex == 1) ? color2 : color1)
                                   );
}

void LightMapping::drawPyramid_ConicalGradient(QPainter *event, int posX, int posY, QColor color1, QColor color2, QColor color3)
{
    calculatePoint(posX, posY);
    QPolygon polygon;
    polygon << topPoint << leftPoint << rightPoint;

    QConicalGradient gradient(centerPoint, 90);
    gradient.setColorAt(0, color1);
    gradient.setColorAt(0.2, color2);
    gradient.setColorAt(0.4, color2);
    gradient.setColorAt(0.6, color3);
    gradient.setColorAt(0.8, color3);
    gradient.setColorAt(1, color1);

    event->setBrush(gradient);
    event->drawPolygon(polygon);
}
void LightMapping::drawSixPyramid_ConicalGradients(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_ConicalGradient(event, mSideLength, 0, color1 , color2, color3);
    drawPyramid_ConicalGradient(event, mSideLength / 2, height, color1 , color2, color3);
    drawPyramid_ConicalGradient(event, mSideLength * 1.5, height, color1 , color2, color3);
    drawPyramid_ConicalGradient(event, 0, 2 * height, color1 , color2, color3);
    drawPyramid_ConicalGradient(event, mSideLength, 2 * height, color1 , color2, color3);
    drawPyramid_ConicalGradient(event, mSideLength * 2 , 2 * height, color1 , color2, color3);
}
void LightMapping::discoloration_ConicalGradient(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    int currentIndex = (countChangeConical - 1) % 3;
    drawSixPyramid_ConicalGradients(event,
                            (currentIndex == 0) ? color1 : ((currentIndex == 1) ? color3 : color2),
                                (currentIndex == 0) ? color2 : ((currentIndex == 1) ? color1 : color3),
                                   (currentIndex == 0) ? color3 : ((currentIndex == 1) ? color2 : color1)
                                   );
}

void LightMapping::drawPyramid_RadialGradient(QPainter *event, int posX, int posY, QColor color1, QColor color2, QColor color3)
{
    calculatePoint(posX, posY);
    float height = mSideLength * sqrt(3)/2;
    float radius = 2 * height / 3;
    QPolygon polygon;
    polygon << topPoint << leftPoint << rightPoint;

    QRadialGradient gradient(centerPoint, radius, centerPoint);
    gradient.setColorAt(0, color1);
    gradient.setColorAt(1, color2);

    event->setBrush(gradient);
    event->drawPolygon(polygon);
}
void LightMapping::drawSixPyramid_RadialGradients(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_RadialGradient(event, mSideLength, 0, color1 , color2, color3);
    drawPyramid_RadialGradient(event, mSideLength / 2, height, color1 , color2, color3);
    drawPyramid_RadialGradient(event, mSideLength * 1.5, height, color1 , color2, color3);
    drawPyramid_RadialGradient(event, 0, 2 * height, color1 , color2, color3);
    drawPyramid_RadialGradient(event, mSideLength, 2 * height, color1 , color2, color3);
    drawPyramid_RadialGradient(event, mSideLength * 2 , 2 * height, color1 , color2, color3);
}
void LightMapping::discoloration_RadialGradient(QPainter *event, QColor color1, QColor color2, QColor color3)
{
    int currentIndex = (countChangeRadial - 1) % 3;
    drawSixPyramid_RadialGradients(event,
                            (currentIndex == 0) ? color1 : ((currentIndex == 1) ? color3 : color2),
                               (currentIndex == 0) ? color2 : ((currentIndex == 1) ? color1 : color3),
                                   (currentIndex == 0) ? color3 : ((currentIndex == 1) ? color2 : color1)
                                   );
}

void LightMapping::drawPyramid_Rotated(QPainter *event, int posX, int posY, int rotationAngle)
{
    QPolygon polygonLeft, polygonRight, polygonBottom;
    calculatePoint(posX, posY);
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;

    QTransform transform;
    transform.translate(centerPoint.x(), centerPoint.y());
    transform.rotate(rotationAngle);
    transform.translate(-centerPoint.x(), -centerPoint.y());

    polygonLeft = transform.map(polygonLeft);
    polygonRight = transform.map(polygonRight);
    polygonBottom = transform.map(polygonBottom);

    event->drawPolygon(polygonLeft);
    event->drawPolygon(polygonRight);
    event->drawPolygon(polygonBottom);
}
void LightMapping::drawSixPyramid_Rotated(QPainter *event, int angle)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Rotated(event, mSideLength, 0, angle);
    drawPyramid_Rotated(event, mSideLength / 2, height , angle);
    drawPyramid_Rotated(event, mSideLength * 1.5, height , angle);
    drawPyramid_Rotated(event, 0, 2 * height, angle) ;
    drawPyramid_Rotated(event, mSideLength, 2 * height , angle);
    drawPyramid_Rotated(event, mSideLength * 2 , 2 * height , angle);
}
void LightMapping::drawBorderLine(QPainter *event, const QPoint &start, const QPoint &end)
{
    QColor borderColor = QColor(255, 255, 255);
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);
    event->drawLine(start, end);
}
void LightMapping::drawPyramid_Border(QPainter *event, int posX, int posY)
{
    calculatePoint(posX, posY);
    switch (lineIndex) {
    case 1:
        drawBorderLine(event, centerPoint, topPoint);
        break;
    case 2:
        drawBorderLine(event, centerPoint, leftPoint);
        break;
    case 3:
        drawBorderLine(event, centerPoint, rightPoint);
        break;
    case 4:
        drawBorderLine(event, topPoint, leftPoint);;
        break;
    case 5:
        drawBorderLine(event, topPoint, rightPoint);
        break;
    case 6:
        drawBorderLine(event, leftPoint, rightPoint);
        break;
    case 7:
        drawBorderLine(event, centerPoint, topPoint);
        drawBorderLine(event, centerPoint, leftPoint);
        drawBorderLine(event, centerPoint, rightPoint);
        drawBorderLine(event, topPoint, leftPoint);;
        drawBorderLine(event, topPoint, rightPoint);
        drawBorderLine(event, leftPoint, rightPoint);
        break;
    default:
        break;
    }
}
void LightMapping::drawSixPyramid_Border(QPainter *event)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Border(event, mSideLength, 0);
    drawPyramid_Border(event, mSideLength / 2, height);
    drawPyramid_Border(event, mSideLength * 1.5, height);
    drawPyramid_Border(event, 0, 2 * height);
    drawPyramid_Border(event, mSideLength, 2 * height);
    drawPyramid_Border(event, mSideLength * 2 , 2 * height);
}


void LightMapping::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(mStart == true) {
        effect(&painter);
    }
    effect_type7(&painter);
}

