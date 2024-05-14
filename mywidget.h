#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MyWidget;
}

class MyWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MyWidget *ui;

    QGraphicsScene* image_scene;          // 场景
    QGraphicsView* image_graphicsView;    // 视窗
};

#endif // MYWIDGET_H
