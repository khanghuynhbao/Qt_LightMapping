
#include "lightmapping.h"

LightMapping::LightMapping(QWidget *parent)
    : QWidget{parent},
//    mPen(Qt::black),
//    mEffect(type3),
    mPoint_X(200),
    mPoint_Y(100),
    mSideLength(200),
    mPenW(3),
    mTimes(1500),
    mEffectIndex(-1),
    lineIndex(0)
{
    initializeTimers();
    mEffectsList << type0 << type1 << type2 << type3 << type4 << type5 << type6;
}

void LightMapping::setupEffectDurations(int duration)
{
    mEffectDurations[type0] = 2000;
    mEffectDurations[type1] = 7000;
    mEffectDurations[type2] = duration;
    mEffectDurations[type3] = 7000;
    mEffectDurations[type4] = duration;
    mEffectDurations[type5] = 2400;
    mEffectDurations[type6] = 7000;
    mEffectDurations[type7] = 5000;
    mEffectDurations[type8] = duration;
    mEffectDurations[type16] = 1200000;
}

void LightMapping::initializeTimers()
{
    setupEffectDurations(mTimes);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LightMapping::changeEffect);
    timer->start(mEffectDurations[mEffect]);

    QTimer *updateEffect1Timer = new QTimer(this);
    connect(updateEffect1Timer, &QTimer::timeout, this, &LightMapping::updateEffectType1);
    updateEffect1Timer->start(1000);

    QTimer *updateEffect3Timer = new QTimer(this);
    connect(updateEffect3Timer, &QTimer::timeout, this, &LightMapping::updateEffectType3);
    updateEffect3Timer->start(1000);

    QTimer *updateEffect5Timer = new QTimer(this);
    connect(updateEffect5Timer, &QTimer::timeout, this, &LightMapping::updateEffectType5);
    updateEffect5Timer->start(50);

//    QTimer *updateEffect6Timer = new QTimer(this);
//    connect(updateEffect6Timer, &QTimer::timeout, this, &LightMapping::updateEffectType6);
//    updateEffect6Timer->start(1000);
}
void LightMapping::updateEffectType1()
{
    if (mEffect == type1) {
        if (lineIndex <= 7) {
            lineIndex += 1;
            qDebug() << "lineIndex" << lineIndex;
        }
        else if (lineIndex > 7) {
            lineIndex = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType3()
{
    if (mEffect == type3) {
        if (countChangeColor <= 6) {
            countChangeColor += 1;
            qDebug() << "count change" << countChangeColor;
        }
        else if (countChangeColor > 7) {
            countChangeColor = 0;
        }
        update();
    }
}
void LightMapping::updateEffectType5()
{
    if (mEffect == type5 && currentAngle < 360) {
        currentAngle += 15;
        update();
    } else if (mEffect == type5) {
        currentAngle = 0;
        update();
    }
}
void LightMapping::updateEffectType6()
{
//    if (mEffect == type6) {
//        if (countChangeColor <= 6) {
//            countChangeColor += 1;
//            qDebug() << "count change" << countChangeColor;
//        }
//        else if (countChangeColor > 7) {
//            countChangeColor = 0;
//        }
//        update();
//    }
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
    case type7:
        return effect_type7(event);
    case type16:
        return effect_type16(event);
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
    QColor backgroundColor, borderColor;
    backgroundColor = QColor(255, 255, 255);
    borderColor = QColor(224, 224, 224);
    event->setBrush(backgroundColor);
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid(event);
}
void LightMapping::effect_type3(QPainter *event)
{
    QColor colorLeft = QColor(169, 169, 169);
    QColor colorRight = QColor(245, 245, 245);
    QColor colorBottom = QColor(245, 245, 245);
    QColor colorShadowLeft = QColor(32, 32, 32);
    QColor colorShadowRight = QColor(0, 0, 0);
    QColor colorShadowBottom = QColor(0, 0, 0);
    event->setPen(mPen);

    discoloration(event, colorLeft, colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
}
void LightMapping::effect_type4(QPainter *event)
{
    QColor borderColor, colorLeft, colorRight, colorBottom;
    colorLeft = Qt::red;
    colorRight = Qt::blue;
    colorBottom = Qt::yellow;
    borderColor = Qt::gray;
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid_Gradients(event, colorLeft, colorRight, colorBottom);
}

void LightMapping::effect_type5(QPainter *event)
{
    QColor borderColor = Qt::gray;
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid_Rotated(event, currentAngle);
}

void LightMapping::effect_type6(QPainter *event)
{
//    event->setRenderHint(QPainter::Antialiasing, true);
//    mPen.setWidth(10);
//    event->setPen(mPen);

//    QColor colorLeft = QColor(169,169,169);
//    QColor colorRight = QColor(220,220,220);
//    QColor colorBottom = QColor(220,220,220);
//    discoloration(event, colorLeft, colorRight, colorBottom);
}

void LightMapping::effect_type7(QPainter *event)
{

}

void LightMapping::effect_type16(QPainter *event)
{
    QColor backgroundColor, borderColor;
    backgroundColor = QColor(255, 255, 255);
    borderColor = QColor(0, 0, 0);
    event->setBrush(backgroundColor);
    mPen.setBrush(borderColor);
    mPen.setWidth(mPenW);
    event->setPen(mPen);

    drawSixPyramid(event);
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
    QPolygon polygonLeft, polygonRight, polygonBottom;
    calculatePoint(posX, posY);
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



void LightMapping::discoloration(QPainter *event, QColor colorLeft, QColor colorRight, QColor colorBottom,
                                 QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    switch (countChangeColor) {
    case 1:
        drawSixPyramid_Color(event, colorLeft, colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 2:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(32, 32, 32);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event, colorBottom, colorLeft, colorRight, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 3:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(32, 32, 32);
        drawSixPyramid_Color(event, colorRight, colorBottom, colorLeft, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 4:
        colorShadowLeft = QColor(32, 32, 32);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event, colorLeft, colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 5:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(32, 32, 32);
        colorShadowBottom = QColor(0, 0, 0);
        drawSixPyramid_Color(event, colorBottom, colorLeft, colorRight, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    case 6:
        colorShadowLeft = QColor(0, 0, 0);
        colorShadowRight = QColor(0, 0, 0);
        colorShadowBottom = QColor(32, 32, 32);
        drawSixPyramid_Color(event, colorRight, colorBottom, colorLeft, colorShadowLeft, colorShadowRight, colorShadowBottom);
        break;
    default:
        break;
    }
}
void LightMapping::drawPyramid_Color(QPainter *event, int posX, int posY, QColor colorLeft, QColor colorRight, QColor colorBottom,
                                     QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    QPolygon polygonLeft, polygonRight, polygonBottom, polygonTopLeft, polygonTopRight, polygonLeftRight;
    calculatePoint(posX, posY);
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
void LightMapping::drawSixPyramid_Color(QPainter *event, QColor colorLeft, QColor colorRight, QColor colorBottom,
                                                            QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Color(event, mSideLength, 0, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength / 2, height, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength * 1.5, height, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, 0, 2 * height, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom) ;
    drawPyramid_Color(event, mSideLength, 2 * height, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
    drawPyramid_Color(event, mSideLength * 2 , 2 * height, colorLeft , colorRight, colorBottom, colorShadowLeft, colorShadowRight, colorShadowBottom);
}



void LightMapping::drawPyramid_Gradient(QPainter *event, int posX, int posY, QColor colorLeft, QColor colorRight, QColor colorBottom)
{
    calculatePoint(posX, posY);

    QPolygon polygonLeft, polygonRight, polygonBottom;
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;

    QLinearGradient gradientLeft(topPoint, leftPoint);
    gradientLeft.setColorAt(0, colorLeft);
    gradientLeft.setColorAt(0.5, colorRight);
    gradientLeft.setColorAt(1, colorBottom);

    QLinearGradient gradientRight(topPoint, rightPoint);
    gradientRight.setColorAt(0, colorRight);
    gradientRight.setColorAt(0.5, colorLeft);
    gradientRight.setColorAt(1, colorBottom);

    QLinearGradient gradientBottom(leftPoint, rightPoint);
    gradientBottom.setColorAt(0, colorLeft);
    gradientBottom.setColorAt(0.5, colorBottom);
    gradientBottom.setColorAt(1, colorRight);

    event->setBrush(gradientLeft);
    event->drawPolygon(polygonLeft);

    event->setBrush(gradientRight);
    event->drawPolygon(polygonRight);

    event->setBrush(gradientBottom);
    event->drawPolygon(polygonBottom);
}
void LightMapping::drawSixPyramid_Gradients(QPainter *event, QColor colorLeft, QColor colorRight, QColor colorBottom)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Gradient(event, mSideLength, 0, colorLeft , colorRight, colorBottom);
    drawPyramid_Gradient(event, mSideLength / 2, height, colorLeft , colorRight, colorBottom);
    drawPyramid_Gradient(event, mSideLength * 1.5, height, colorLeft , colorRight, colorBottom);
    drawPyramid_Gradient(event, 0, 2 * height, colorLeft , colorRight, colorBottom) ;
    drawPyramid_Gradient(event, mSideLength, 2 * height, colorLeft , colorRight, colorBottom);
    drawPyramid_Gradient(event, mSideLength * 2 , 2 * height, colorLeft , colorRight, colorBottom);
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
//    switch (lineIndex) {
//    case 1:
//        drawPyramid_Border(event, mSideLength, 0);
//        break;
//    case 2:
//        drawPyramid_Border(event, mSideLength / 2, height);
//        break;
//    case 3:
//        drawPyramid_Border(event, mSideLength * 1.5, height);
//        break;
//    case 4:
//        drawPyramid_Border(event, 0, 2 * height);
//        break;
//    case 5:
//        drawPyramid_Border(event, mSideLength, 2 * height);
//        break;
//    case 6:
//        drawPyramid_Border(event, mSideLength * 2 , 2 * height);
//        break;
//    default:
//        break;
//    }
}

void LightMapping::calculatePointScale(int posX, int posY, float scaleLength)
{
    float height = mSideLength * sqrt(3)/2;

    topPoint.setX(mPoint_X + mSideLength / 2 + posX);
    topPoint.setY(mPoint_Y + posY);
    leftPoint.setX(mPoint_X + posX);
    leftPoint.setY(mPoint_Y + height + posY);
    rightPoint.setX(mPoint_X + mSideLength + posX);
    rightPoint.setY(mPoint_Y + height + posY);
    centerPoint.setX((topPoint.x() + leftPoint.x() + rightPoint.x()) / 3);
    centerPoint.setY((topPoint.y() + leftPoint.y() + rightPoint.y()) / 3);

    mSideLength *= scaleLength;
    topPoint.setX(mPoint_X + mSideLength / 2 + posX);
    topPoint.setY(mPoint_Y + posY);
    leftPoint.setX(mPoint_X + posX);
    leftPoint.setY(mPoint_Y + height + posY);
    rightPoint.setX(mPoint_X + mSideLength + posX);
    rightPoint.setY(mPoint_Y + height + posY);
}

void LightMapping::drawPyramid_Size2(QPainter *event, int posX, int posY, float scaleLength)
{
    QPolygon polygonLeft, polygonRight, polygonBottom;
    calculatePointScale(posX, posY, scaleLength);
    polygonLeft << topPoint << leftPoint << centerPoint;
    polygonRight << topPoint << rightPoint << centerPoint;
    polygonBottom << leftPoint << rightPoint << centerPoint;

    event->drawPolygon(polygonLeft);
    event->drawPolygon(polygonRight);
    event->drawPolygon(polygonBottom);
}

void LightMapping::drawSixPyramid_Size2(QPainter *event, float scaleLength)
{
    float height = mSideLength * sqrt(3)/2;
    drawPyramid_Size2(event, mSideLength, 0, scaleLength);
    //    drawPyramid_Size2(event, mSideLength / 2, height, scaleLength);
    //    drawPyramid_Size2(event, mSideLength * 1.5, height, scaleLength);
    //    drawPyramid_Size2(event, 0, 2 * height, scaleLength);
    //    drawPyramid_Size2(event, mSideLength, 2 * height, scaleLength);
    //    drawPyramid_Size2(event, mSideLength * 2 , 2 * height, scaleLength);
}


void LightMapping::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(mStart == true) {
        effect(&painter);
    }
    effect_type3(&painter);

}

