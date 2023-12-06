
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
#include <QOpenGLFunctions>

class LightMapping : public QWidget
{
    Q_OBJECT
public:
    explicit LightMapping(QWidget *parent = nullptr);

//    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
//    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum EffectType
    {   type0, type1, type2, type3 ,type4, type5, type6, type7};

// diaglog btn color
    void setColor1(QColor color1){
        mColor1 = color1.isValid() ? color1 : QColor(255, 0, 0);}
    QColor color1() const { return mPen.color(); }

    void setColor2(QColor color2) {
        mColor2 = color2.isValid() ? color2 : QColor(0, 255, 0);}
    QColor color2() const { return mPen.color(); }

    void setColor3(QColor color3) {
        mColor3 = color3.isValid() ? color3 : QColor(0, 0, 255);}
    QColor color3() const { return mPen.color(); }

// set position
    void setPoint_X(int point_x) { mPoint_X = point_x; repaint();}
    int point_x() const { return mPoint_X;}

    void setPoint_Y(int point_y) { mPoint_Y = point_y; repaint();}
    int point_y() const { return mPoint_Y;}

    void setSideLength(float length) { mSideLength = length; repaint();}
    float sideLength () const { return mSideLength;}

    void setStart(bool start) { mStart = start; repaint();}
    bool start () const { return mStart;}

    void setPenW(int penW) { mPenW = penW; repaint();}
    int penW () const { return mPenW;}

    void initializeTimers();

protected:
   void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void changeEffect();

    void setupEffectDurations(int duration);

    void updateEffectType1();
    void updateEffectType2();
    void updateEffectType3();
    void updateEffectType5();
    void updateEffectType4();
    void updateEffectType6();

    void effect_type0(QPainter *painter); // deafault
    void effect_type1(QPainter *painter); // border
    void effect_type2(QPainter *painter); //
    void effect_type3(QPainter *painter); // shadow
    void effect_type4(QPainter *painter); // linear
    void effect_type5(QPainter *painter); // rotate
    void effect_type6(QPainter *painter); // conical
    void effect_type7(QPainter *painter);
    void effect(QPainter *painter);

    void calculatePoint(int posX, int posY);
    void calculatePointScale(int posX, int posY, float scale);

    void drawPyramid(QPainter *painter, int posX, int posY);
    void drawShadow(QPainter *painter, int posX, int posY);
    void drawSixPyramid(QPainter *painter);

    void drawPyramid_Color(QPainter *painter, int posX, int posY,QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);
    void drawSixPyramid_Color(QPainter *painter,QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);
    void discoloration(QPainter *event, QColor colorLeft, QColor colorRight, QColor colorBottom, QColor colorShadowLeft, QColor colorShadowRight, QColor colorShadowBottom);

    void drawPyramid_LinearGradient(QPainter *painter, int posX, int posY, QColor color1, QColor color2, QColor color3);
    void drawSixPyramid_LinearGradients(QPainter *painter,QColor color1, QColor color2, QColor color3);
    void discoloration_LinearGradient(QPainter *painter, QColor color1, QColor color2, QColor color3);

    void drawPyramid_ConicalGradient(QPainter *painter, int posX, int posY, QColor color1, QColor color2, QColor color3);
    void drawSixPyramid_ConicalGradients(QPainter *painter, QColor color1, QColor color2, QColor color3);
    void discoloration_ConicalGradient(QPainter *painter, QColor color1, QColor color2, QColor color3);

    void drawPyramid_RadialGradient(QPainter *painter, int posX, int posY, QColor color1, QColor color2, QColor color3);
    void drawSixPyramid_RadialGradients(QPainter *painter, QColor color1, QColor color2, QColor color3);
    void discoloration_RadialGradient(QPainter *event, QColor color1, QColor color2, QColor color3);

    void drawPyramid_Rotated(QPainter *painter, int posX, int posY, int rotationAngle);
    void drawSixPyramid_Rotated(QPainter *painter, int angle);

    void drawBorderLine(QPainter *painter, const QPoint &start, const QPoint &end);
    void drawPyramid_Border(QPainter *painter, int posX, int posY);
    void drawSixPyramid_Border(QPainter *painter);

private:
    EffectType mEffect;
    QMap<EffectType, int> mEffectDurations;

    int mEffectIndex;
    QVector<EffectType> mEffectsList;

    QColor mColor1 = QColor(255, 0, 0);
    QColor mColor2 = QColor(0, 255, 0);
    QColor mColor3 = QColor(0, 0, 255);

    bool mStart = false;
    int currentAngle = 0;

    int lineIndex = 0;
    int countChangeColor = 0;
    int countChangeLinear = 0;
    int countChangeConical = 0;
    int countChangeRadial = 0;

    QPainterPath pathLeft, pathRight, pathBottom;
    QPoint topPoint, leftPoint, rightPoint, centerPoint, topLeftPoint, topRightPoint, leftRightPoint;
    QPoint topPoint2, leftPoint2, rightPoint2;

    int mPoint_X, mPoint_Y;
    float mSideLength;
    QPen mPen;
    int mPenW;

signals:

};

#endif // LIGHTMAPPING_H
