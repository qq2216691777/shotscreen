#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveScreenSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shotScreenSlot()
{
    this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    ui->screenLabel->setPixmap((this->pixmap.scaled(ui->screenLabel->size())));
    this->show();
    this->timer->stop();
}

void MainWindow::on_newButton_clicked()
{
    this->hide();
    if( ui->spinBox->value()>0)     //Determine whether to wait for a while
    {
        this->timer = new QTimer;
        QObject::connect(this->timer,SIGNAL(timeout()),SLOT(shotScreenSlot()));
        this->timer->start(ui->spinBox->value()*1000);
    }
    else
    {
        this->pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());   //Get the picture
        ui->screenLabel->setPixmap((this->pixmap.scaled(ui->screenLabel->size())));
        this->show();
    }

    return ;
}

void MainWindow::saveScreenSlot()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save File","./");
    this->pixmap.save((filename));
}
