#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QPair>
#include <QVector2D>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QString>
#include <random>
#include <deque>


class Field : public QWidget
{
    Q_OBJECT
public:
    Field(QWidget *parent = nullptr,  QPair<qint32, qint32> sizeField = {32,32}, qint32 sizeCell = 20);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent * event);
    void restart();
private:
    bool redraw = true;
    QColor backgroundColor = Qt::white;
    QColor lineColor = Qt::black;
    QColor eatColor = Qt::red;
    QColor bodySnakeColor = Qt::green;
    QColor headSnakeColor = Qt::darkGreen;
    std::deque<QPair<qint32,qint32>> snake;
    QPair<qint32,qint32> food;
    QPair<qint32, qint32> sizeField;
    QPair<qint32, qint32> snakeTile;
    qint32 sizeCell;
    QPair<qint32,qint32> ZERO = {-1,-1};
    QVector<QVector<QColor>> color;
signals:

};

#endif // FIELD_H
