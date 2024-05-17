#include "mywidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":SpyBot.qss");
    if(qss.open(QFile::ReadOnly)){
        a.setStyleSheet(qss.readAll());
    }
    qss.close();

    MyWidget w;
    w.show();

    return a.exec();
}
