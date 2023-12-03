
#ifndef LIGHTMAPPING_H
#define LIGHTMAPPING_H

#include <QWidget>
#include <QColor>
#include <QPen>
#include <QMap>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QElapsedTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QTime>
#include <QPolygon>

class LightMapping : public QWidget
{
    Q_OBJECT
public:
    explicit LightMapping(QWidget *parent = nullptr);

//    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
//    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum EffectType
    {   type0,
        type1, type2, type3 ,type4, type5, type6, type7, type8,
        type9, type10, type11 ,type12, type13, type14, type15, type16
    };

// diaglog btn color
    void setColor1(QColor color) { mPen.setColor(color); }
    QColor color1 () const { return mPen.color(); }

    void setColor2(QColor color) { mPen.setColor(color); }
    QColor color2 () const { return mPen.color(); }

// set position
    void setPoint_X(int point_x) { mPoint_X = point_x; repaint();}
    int point_x() const { return mPoint_X;}

    void setPoint_Y(int point_y) { mPoint_Y = point_y; repaint();}
    int point_y() const { return mPoint_Y;}

    void setSideLength(float length) { mSideLength = length; repaint();}
    float sideLength () const { return mSideLength;}

    void setStart(bool start) { mStart = start; repaint();}
    bool start () const { return mStart;}

    void setTimes(int times) { mTimes = times; repaint();}
    int times () const { return mTimes;}

    void setPenW(int penW) { mPenW = penW; repaint();}
    int penW () const { return mPenW;}

protected:
   void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void changeEffect();

    void setupEffectDurations(int duration);
    void initializeTimers();


    void updateEffectType1();
    void updateEffectType3();
    void updateEffectType5();
    void updateEffectType6();

    void effect_type0(QPainter *painter);
    void effect_type1(QPainter *painter); //
    void effect_type2(QPainter *painter); //
    void effect_type3(QPainter *painter); //
    void effect_type4(QPainter *painter); //
    void effect_type5(QPainter *painter);
    void effect_type6(QPainter *painter);
    void effect_type7(QPainter *painter);
    void effect_type16(QPainter *painter);
    void effect(QPainter *painter);

    void calculatePoint(int posX, int posY);
    void calculatePointScale(int posX, int posY, float scale);

    void drawPyramid(QPainter *painter, int posX, int posY);
    void drawSixPyramid(QPainter *painter);

    void discoloration(QPainter *event, QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);
    void drawPyramid_Color(QPainter *painter, int posX, int posY,QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);
    void drawSixPyramid_Color(QPainter *painter,QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);

    void drawPyramid_Gradient(QPainter *painter, int posX, int posY, QColor colorLeft, QColor colorRight, QColor colorBottom);
    void drawSixPyramid_Gradients(QPainter *painter,QColor colorLeft, QColor colorRight, QColor colorBottom);

    void drawPyramid_Rotated(QPainter *painter, int posX, int posY, int rotationAngle);
    void drawSixPyramid_Rotated(QPainter *painter, int angle);

    void drawBorderLine(QPainter *painter, const QPoint &start, const QPoint &end);
    void drawPyramid_Border(QPainter *painter, int posX, int posY);
    void drawSixPyramid_Border(QPainter *painter);

    void drawPyramid_Size2(QPainter *painter, int posX, int posY, float scaleLength);
    void drawSixPyramid_Size2(QPainter *painter, float scaleLength);

private:
    EffectType mEffect;
    QMap<EffectType, int> mEffectDurations;

    int mEffectIndex;
    QVector<EffectType> mEffectsList;

    bool mStart = false;
    int flag_change;
    int currentAngle = 0;

    int lineIndex;
    int countChangeColor;
    int countChangeColor6;

    QPainterPath pathLeft, pathRight, pathBottom;
    QPoint topPoint, leftPoint, rightPoint, centerPoint, topLeftPoint, topRightPoint, leftRightPoint;

    int mPoint_X, mPoint_Y;
    float mSideLength;
    int mTimes;
    QPen mPen;
    int mPenW;

signals:

};

#endif // LIGHTMAPPING_H
