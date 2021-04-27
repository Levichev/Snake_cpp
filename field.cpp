#include "field.h"

Field::Field(QWidget *parent,  QPair<qint32, qint32> sizeField, qint32 sizeCell) : QWidget(parent), sizeField(sizeField), sizeCell(sizeCell) {
    setFocusPolicy(Qt::StrongFocus);
    restart();
}

void Field::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(lineColor, 1, Qt::SolidLine));

    for(int i = 0; i < color.size(); ++i) {
        for(int j = 0; j < color[i].size(); ++j) {
            if (snake.front().first == i && snake.front().second == j)
                painter.setBrush(QBrush(headSnakeColor));
            else
                painter.setBrush(QBrush(color[i][j]));

            painter.drawRect(i*sizeCell, j*sizeCell, sizeCell, sizeCell);
        }
    }


    //TODO: Fix fast repaint

//      if (redraw) {
//        redraw = false;
//       }
    /* else {
        qDebug() << "0";
        painter.setBrush(QBrush(headSnakeColor));
        qint32 i = snake.front().first, j = snake.front().second;
        painter.drawRect(i*sizeCell, j*sizeCell, sizeCell, sizeCell);
        painter.setBrush(QBrush(backgroundColor));
        if (snakeTile != ZERO){
            qint32 i = snakeTile.first, j = snakeTile.second;
            painter.drawRect(i*sizeCell, j*sizeCell, sizeCell, sizeCell);
        }
    }*/

}
void Field::restart(){
    color.clear();
    snake.clear();
    color.resize(sizeField.first, QVector<QColor>(sizeField.second, backgroundColor));
    resize(sizeCell*sizeField.first, sizeCell*sizeField.second);
    srand (time(NULL));
    food= {rand()%sizeField.first, rand()%sizeField.second};
    color[food.first][food.second] = bodySnakeColor;
    snake.push_front(food);
    snakeTile = {-1,-1};
    while(color[food.first][food.second] == bodySnakeColor) {
        food = {rand()%sizeField.first, rand()%sizeField.second};
    }
    color[food.first][food.second] = eatColor;
    redraw = true;
    repaint();
}
void Field::keyPressEvent(QKeyEvent * event) {


    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right ||
        event->key() == Qt::Key_A || event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_W || event->key() == Qt::Key_Up ||
        event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {

        auto coord =  snake.front();
        if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
            coord.first = (coord.first + 1)%sizeField.first;
        }
        if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
            coord.first = (coord.first - 1 + sizeField.first)%sizeField.first;
        }
        if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
            coord.second = (coord.second - 1 + sizeField.second)%sizeField.second;
        }
        if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
            coord.second = (coord.second + 1)%sizeField.second;
        }
        QPainter painter(this);

        if (color[coord.first][coord.second] == eatColor) {
            snake.push_front(coord);
            color[snake.front().first][snake.front().second] = bodySnakeColor;
            snakeTile = ZERO;
            //TODO: fix it if there is a bug with the transition to the end of the snake (&& coord != snake.back())
        } else if (color[coord.first][coord.second] == bodySnakeColor && coord != snake.back()) {
            if (coord == snake[1]) return;
            else restart();
        } else {
            color[snake.back().first][snake.back().second] = backgroundColor;
            snakeTile = snake.back();
            snake.pop_back();
            snake.push_front(coord);
            color[snake.front().first][snake.front().second] = bodySnakeColor;

        }
        while(color[food.first][food.second] == bodySnakeColor) {
            food = {rand()%sizeField.first, rand()%sizeField.second};
        }
        color[food.first][food.second] = eatColor;

        repaint();
    }
}
