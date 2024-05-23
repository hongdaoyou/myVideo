#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget *widget1 = new QWidget(this);

    ui->setupUi(this);

    // 设置,主窗口的的大小
    this->resize(600, 500);

    // 创建,视频窗口,和媒体播放器
    this->videoWidget = new QVideoWidget();
    this->mediaPlayer = new QMediaPlayer();


    // 设置,媒体播放器输出到视频窗口
    this->mediaPlayer->setVideoOutput(this->videoWidget);

    // 打开视频文件
    // QString videoFilePath = "/home/hdy/视频/a.wav";
    // QString videoFilePath = "/home/hdy/视频/a1.mp4";
    // this->mediaPlayer->setMedia(QUrl::fromLocalFile(videoFilePath));

    // 创建,垂直布局
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(this->videoWidget);

    // 开始,按钮
    QPushButton *selectFileBtn= new QPushButton("选择,播放的文件", this); 
    connect(selectFileBtn, &QPushButton::clicked, this, &MainWindow::selectFilePush);
    
    layout1->addWidget(selectFileBtn);

    // 开始,按钮
    QPushButton *startBtn= new QPushButton("开始", this); 
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::startPush);
    layout1->addWidget(startBtn);

    QPushButton *stopBtn= new QPushButton("暂停", this); 
    connect(stopBtn, &QPushButton::clicked, this, &MainWindow::stopPush );
    layout1->addWidget(stopBtn);

    // 设置,布局

    widget1->setLayout(layout1);

    // 将centralWidget, 设置为, QMainWindow的中央部件
    this->setCentralWidget(widget1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPush() {
    qDebug() << "start clicked";
    
    // 播放视频
    this->mediaPlayer->play();

}

void MainWindow::stopPush() {
    qDebug() << "stop clicked";

    this->mediaPlayer->pause();
}

void MainWindow::selectFilePush() {
    qDebug() << "select file clicked";

    // 选择文件
    QString filePath = QFileDialog::getOpenFileName(nullptr, "选择文件", QDir::homePath());

    if (filePath.isEmpty()) {
        qDebug() << "没有选中";
        return;
    }
    qDebug() << "选中 " << filePath;
    
    // QString videoFilePath = "/home/hdy/视频/a1.mp4";
    this->mediaPlayer->setMedia(QUrl::fromLocalFile( filePath) );

}
