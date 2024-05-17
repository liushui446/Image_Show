#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFileDialog>
#include <string>

using std::string;


MyWidget::MyWidget(QWidget *parent) :
    QMainWindow(parent)
  //,image_scene(new QGraphicsScene(this))
  //,image_graphicsView(new QGraphicsView(this))
  ,ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    iniUI();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::iniUI()
{
//    QLabel* label_bg = new QLabel(this);
//    label_bg->setStyleSheet("background-image: url(:/bg.jpg); background-repeat: no-repeat; background-position: center;");
//    label_bg->setScaledContents(true);
//    label_bg->resize(this->size());

//    // 将QLabel添加到QHBoxLayout中
//    ui->horizontalLayout->addWidget(label_bg);
    //this->setStyleSheet("QWidget#Widget{border-image:url(:/bg.jpg)}");
    m_settings = new QSettings("./setting.ini",QSettings::IniFormat);
    GetIniFile();
    setAutoFillBackground(true);
    QPalette palette = this->palette();
    //palette.setColor(QPalette::Window, Qt::red);
    //palette.setBrush(this->backgroundRole(), Qt::black);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/bg.jpg").scaled(
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));
    this->setPalette(palette);

    //this->setStyleSheet("border-image: url(:/bg.jpg); background-position: center;");
//    image_scene->setSceneRect(QRectF(-0.005, -0.005, 0.01, 0.01));
//    image_graphicsView->setStyleSheet("QGraphicsView{background-color: rgb(0, 0, 0);}");
//    image_graphicsView->fitInView(image_graphicsView->sceneRect(), Qt::KeepAspectRatio);
//    image_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    image_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    image_graphicsView->setFrameShape(QFrame::NoFrame);
//    image_graphicsView->setScene(image_scene);//view,scene
//    image_graphicsView->setSceneRect(image_scene->itemsBoundingRect());
//    image_graphicsView->setAlignment(Qt::AlignCenter);
//    ui->verticalLayout_6->addWidget(image_graphicsView);

    QImage image(":arrow_down_s.png");
    QPixmap pixmap;
    image = image.scaled(ui->label_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap = QPixmap::fromImage(image);
    ui->label_1->clear();
    ui->label_1->setPixmap(pixmap);
    ui->label_1->setAlignment(Qt::AlignCenter);
    ui->label_1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_2->clear();
    ui->label_2->setPixmap(pixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_3->clear();
    ui->label_3->setPixmap(pixmap);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_4->clear();
    ui->label_4->setPixmap(pixmap);
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->label_4->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_5->clear();
    ui->label_5->setPixmap(pixmap);
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_5->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QImage image_right(":arrow_right_s.png");
    QPixmap pixmap_right;
    image_right = image_right.scaled(ui->label_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap_right = QPixmap::fromImage(image_right);
    ui->label_left->clear();
    ui->label_left->setPixmap(pixmap_right);
    ui->label_left->setAlignment(Qt::AlignCenter);
    ui->label_left->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

}

void MyWidget::on_pushButton_1_clicked()
{
    OpenFiles();
}

void MyWidget::on_pushButton_2_clicked()
{
    LoadImage(0,false);
}

void MyWidget::on_pushButton_3_clicked()
{
    LoadImage(0,true);
    LoadImage(1,false);
}

void MyWidget::on_pushButton_4_clicked()
{
    LoadImage(1,true);
    LoadImage(2,false);
}

void MyWidget::on_pushButton_5_clicked()
{
    LoadImage(2,true);
    LoadImage(3,false);
}

void MyWidget::on_pushButton_6_clicked()
{
    LoadImage(3,true);
    LoadImage(4,false);
}

void MyWidget::on_pushButton_7_clicked()
{
    QImage img;
    img.load(m_origin_path);
    ShowLabel_last(img);
    LoadImage(5,false);
}

void MyWidget::OpenFiles()
{
    QString fileName = QCoreApplication::applicationDirPath();
    for (size_t i = 0; i < 3; i++)
        fileName = fileName.left(fileName.lastIndexOf('/'));

    QFileDialog* m_ImportDialog = new QFileDialog(this);
    m_ImportDialog->setViewMode(QFileDialog::Detail);

    QString filters = { "JPG Files(*.jpg);;" "JPG Files(*.JPG);;" "PNG Files(*.png);;" "PNG Files(*.PNG)"  };
    QString selectfile = m_ImportDialog->getOpenFileName(this, QString::fromLocal8Bit("Import Files"), fileName, filters);
    if (!selectfile.isNull())
    {
        m_origin_path = selectfile;
        QImage imgFile;
        imgFile.load(selectfile);
        ShowLabel_last(imgFile);
        Files_Parser(selectfile);
    }
}

void MyWidget::ShowLabel_last(QImage img)
{
    QImage image;
    QPixmap pixmap;

    image = img.scaled(ui->image_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap = QPixmap::fromImage(image);
    ui->image_1->clear();
    ui->image_1->setPixmap(pixmap);
    ui->image_1->setAlignment(Qt::AlignCenter);
    ui->image_1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void MyWidget::ShowLabel_Now(QImage img)
{
    QImage image;
    QPixmap pixmap;
    image = img.scaled(ui->image_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap = QPixmap::fromImage(image);
    ui->image_2->clear();
    ui->image_2->setPixmap(pixmap);
    ui->image_2->setAlignment(Qt::AlignCenter);
    ui->image_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

}

void MyWidget::Files_Parser(QString path)
{
//    string tmp_path;
//    unsigned int word_pos_;
//    if(!path.isNull()){
//        tmp_path = path.toStdString();
//        return;
//    }
//    word_pos_ = tmp_path.rfind('/');
//    tmp_path.substr(0,word_pos_);
    path = path.left(path.lastIndexOf('/'));
    m_common_path = path + "/";
}

void MyWidget::LoadImage(int index,bool show_type)
{
    /* show_type true:label_1  false:label_2*/
    QImage img;
    QString tmp_path = m_common_path + image_name[index];
    img.load(tmp_path);
//    switch (index) {
//    case 0:
//        img.load(m_common_path + image_name[0]);
//        break;
//    default:
//        break;
//    }
    if(show_type){
        ShowLabel_last(img);
    }
    else{
        ShowLabel_Now(img);
    }

}

void MyWidget::GetIniFile()
{
    if(m_settings != nullptr){
        //QString tmp = QString(m_settings->value("Path/path_1").toString());
        n_2 = QString(m_settings->value("Path/path_1").toString());
        n_3 = QString(m_settings->value("Path/path_2").toString());
        n_4 = QString(m_settings->value("Path/path_3").toString());
        n_5 = QString(m_settings->value("Path/path_4").toString());
        n_6 = QString(m_settings->value("Path/path_5").toString());
        n_7 = QString(m_settings->value("Path/path_6").toString());
    }
}
