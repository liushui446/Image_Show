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

    void OpenFiles();
    void ShowLabel_last(QImage img);
    void ShowLabel_Now(QImage img);
    void Files_Parser(QString path);
    void LoadImage(int index,bool show_type);
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
    QString m_common_path;
    QStringList image_name = {
        QString("640.jpg"),
        QString("641.jpg"),
        QString("642.jpg"),
        QString("643.jpg"),
        QString("644.jpg"),
        QString("645.jpg"),
    };
    QString m_origin_path;
};

#endif // MYWIDGET_H
