#include "mainwindow.h"

#include <QApplication>
#include "field.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;

    qint32 width = 20, height = 20, blockSize = 20;
    Field field(&w, {width, height}, blockSize);
    w.setWindowTitle("Snake");
    w.setFixedSize(width*blockSize, height*blockSize);
    w.show();
    return a.exec();
}
