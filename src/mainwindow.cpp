#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "street.h"
#include "stop.h"
#include "drawable.h"
#include "vehicle.h"
#include "line.h"

#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QAnimationGroup>
#include <QVariantAnimation>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainTime = 0;

    connect(ui->ZoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->ZoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(ui->changeTimeButton,&QPushButton::clicked,this,&MainWindow::setTimer);
    connect(ui->stopPlayButton,&QPushButton::clicked,this,&MainWindow::stopPlay);
    connect(ui->resetButton,&QPushButton::clicked,this,&MainWindow::resetTime);
    connect(ui->lineEdit, &QLineEdit::textEdited,this,&MainWindow::setTime);

    QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QPointF* c1 = new QPointF(0,0);
    QPointF* c2 = new QPointF(100,0);
    QPointF* c3 = new QPointF(200,100);
    QPointF* c4 = new QPointF(200,200);
    QPointF* c5 = new QPointF(20,0);
    QPointF* c6 = new QPointF(200,180);
    QPointF* c7 = new QPointF(180,80);

    Street* str1 = new Street("str1",c1,c2);
    Street* str2 = new Street("str2",c2,c3);
    Street* str3 = new Street("str3",c3,c4);

    Stop* s1 = new Stop("s1",c5);
    Stop* s2 = new Stop("s2",c6);
    Stop* s3 = new Stop("s3",c7);

    str1->addStop(s1);
    str3->addStop(s2);
    str2->addStop(s3);

    Drawable* draw = new Drawable(scene,this);

    draw->drawStreet(str1);
    draw->drawStreet(str2);
    draw->drawStreet(str3);

    draw->drawStop(s1);
    draw->drawStop(s2);
    draw->drawStop(s3);

    Line* line = new Line("Line");

    line->addStreet(str1);
    line->addStreet(str2);
    line->addStreet(str3);

    line->addStop(s1);
    line->addStop(s3);
    line->addStop(s2);
    line->draw = draw;

    std::vector<QString> v1 = {"00:00", "00:02", "00:03"};
    std::vector<QString> v2 = {"00:02", "00:05", "00:07"};
    std::vector<QString> v3 = {"00:04", "00:05", "00:06"};
    std::vector<QString> v4 = {"00:05", "00:06", "00:08"};

    line->addToTimeTable(v1);
    line->addToTimeTable(v2);
    line->addToTimeTable(v3);
    line->addToTimeTable(v4);

    this->mainLine = line;

    timer = new QTimer();
    connect(timer, &QTimer::timeout, line, &Line::touch);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatemainTime);
    connect(timer, &QTimer::timeout, draw, &Drawable::update);

    timer->setInterval(1000);
    timer->start();



}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::zoomIn()
{
    ui->graphicsView->scale(1.25, 1.25);
}

void MainWindow::zoomOut()
{
    ui->graphicsView->scale(0.8, 0.8);
}


void MainWindow::restart()
{
    ui->graphicsView->scale(0.8, 0.8);
}

void MainWindow::showVehicleRoute(Vehicle *vehicle)
{
    ui->listWidget->clear();

    if(vehicle->isDead()){
        return;
    }

    auto stops = vehicle->getStops();
    auto times = vehicle->getStopTimes();

    ui->listWidget->addItem(vehicle->getId());

    for(unsigned i = 0; i < stops.size(); i++){

        auto t =  times.at(i);
        QTime time;
        time.setHMS(0,0,0);
        time = time.addSecs(t);

        QString str = time.toString() + "\t" + stops.at(i)->getId();

        ui->listWidget->addItem(str);

    }

    int nextStop = 1 + static_cast<int>(vehicle->getNextStopN());

    if(nextStop < ui->listWidget->count()){
        ui->listWidget->item(nextStop)->setBackgroundColor(Qt::red);
    }

}


void MainWindow::setTimer()
{

    int t[9] = {1000,500,200,100,50,20,10,5,2};

    static int speed = 0;
    speed += 1;

    if(speed > 8){
        speed = 0;
    }

    this->timer->setInterval(t[speed]);
    ui->changeTimeButton->setText("Speed 1:" + QString::number(1000/t[speed]) );
}


void MainWindow::stopPlay()
{
    if(this->timer->isActive()){
        this->timer->stop();
        ui->stopPlayButton->setText("Play");
    }else{
        this->timer->start();
        ui->stopPlayButton->setText("Stop");
    }
}


void MainWindow::updatemainTime()
{
    mainTime += 1;
    QTime time;
    time.setHMS(0,0,0);
    time = time.addSecs(mainTime);

    ui->TimeLabel->setText(time.toString());
}

void MainWindow::resetTime()
{
    mainTime = 0;
    mainLine->reset();
}

void MainWindow::setTime()
{
    resetTime();

    QString str = ui->lineEdit->text();

    int t = str.toInt();

    for(int i = 0; i < t; i++){
        mainLine->touch();
    }
}



