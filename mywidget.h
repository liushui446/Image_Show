#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qsettings.h>


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
    void iniUI();
    void GetIniFile();
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
        QString("Enhanced.jpg"),
        QString("openedIntersection.jpg"),
        QString("mask.jpg"),
        QString("commonRegion.jpg"),
        QString("maxContourImg.jpg"),
        QString("11.jpg"),
    };
    QString n_2 = QString("Enhanced.jpg");
    QString n_3 = QString("openedIntersection.jpg");
    QString n_4 = QString("mask.jpg");
    QString n_5 = QString("commonRegion.jpg");
    QString n_6 = QString("maxContourImg.jpg");
    QString n_7 = QString("11.jpg");
    QString m_origin_path;

    QSettings *m_settings = nullptr;
};

#endif // MYWIDGET_H
