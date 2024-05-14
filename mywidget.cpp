#include "mywidget.h"
#include "ui_mywidget.h"


MyWidget::MyWidget(QWidget *parent) :
    QMainWindow(parent)
//  ,image_scene(new QGraphicsScene(this))
//  ,image_graphicsView(new QGraphicsView(this))
  ,ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_1_clicked()
{

}

void MyWidget::on_pushButton_2_clicked()
{

}

void MyWidget::on_pushButton_3_clicked()
{

}

void MyWidget::on_pushButton_4_clicked()
{

}

void MyWidget::on_pushButton_5_clicked()
{

}

void MyWidget::on_pushButton_6_clicked()
{

}

void MyWidget::on_pushButton_7_clicked()
{

}
