#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QImageReader>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->label, SIGNAL(myLabelClicked(bool,int ,int )),
            this     , SLOT(slotLabelClicked(bool,int ,int ))    );
    cnt_border = 0;
    cnt_values  = 0;
}


void MainWindow::slotLabelClicked(bool t,int x, int y)
{

    if(t == false)
    {
        if(ui->listWidget->count()<2)
        {
            ui->listWidget->addItem(QString("[%1,%2],[%3,%4]").
                                    arg(x).
                                    arg(y).
                                    arg(.0).
                                    arg(.0)
                                    );
        }
        else
        {
            cnt_border = ui->listWidget->selectionModel()->selectedIndexes()[0].row();
            ui->listWidget->item(cnt_border)->setText(QString("[%1,%2],[%3,%4]").
                                    arg(x).
                                    arg(y).
                                    arg(.0).
                                    arg(.0)
                                    );
            cnt_border++;
            if(cnt_border==4)
            {
                cnt_border = 0;
            }
        }
        qDebug() << "Left Clicked Label : [" << x << " , " << y << "]";
    }
    else
    {
        if(ui->listWidget->count()<2) return;


        float p1,p2;
        findValue(x,y,&p1,&p2);

        ui->listWidget_2->addItem(QString("[%1,%2],[%3,%4]").
                                arg(x).
                                arg(y).
                                arg(p1).
                                arg(p2)
                                );
        qDebug() << "Right Clicked Label : [" << x << " , " << y <<  " , " << p1 <<  " , " << p2 << "]";
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "c:\\", tr("Image Files (*.png *.jpg *.bmp)"));

    qDebug()<<fileName;

    QImageReader read(fileName);
    QImage image = read.read();
    QPixmap pixmap;
//    pixmap.fromImage(image);


//    if(  ==false)
//    {
//        this->setWindowTitle(QString("loaded image [%0] {Failed}").
//                             arg(fileName) );
//    }
//    else
//    this->setWindowTitle(QString("loaded image[%0] [%1,%2]   %3").
//                         arg(fileName).
//                         arg(pixmap.width()).
//                         arg(pixmap.height()).
//                         arg(pixmap.depth())
//                         );

    ui->label->setPixmap( pixmap.fromImage(image) );
//    ui->label->setPixmap( image. );
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->label->repaint();
}



void MainWindow::on_pushButton_2_clicked()
{
    float x = ui->lineEdit->text().toFloat();
    float y = ui->lineEdit_2->text().toFloat();
    int posX = ui->listWidget->selectedItems()[0]->text().remove('[').remove(']').split(',')[0].toInt();
    int posY = ui->listWidget->selectedItems()[0]->text().remove('[').remove(']').split(',')[1].toInt();
    cnt_border = ui->listWidget->selectionModel()->selectedIndexes()[0].row();
    ui->listWidget->item(cnt_border)->setText(QString("[%1,%2],[%3,%4]").
                            arg(posX).
                            arg(posY).
                            arg(x).
                            arg(y)
                            );
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    float x = current->text().remove('[').remove(']').split(',')[2].toFloat();
    float y = current->text().remove('[').remove(']').split(',')[3].toFloat();
    ui->lineEdit->setText(QString::number(x));
    ui->lineEdit_2->setText(QString::number(y));
}

void MainWindow::findValue(int x, int y, float *p1, float *p2)
{
    int minX=10000;
    int minY=10000;
    int maxX=0;
    int maxY=0;

    float tx;
    float ty;
    float txprime;
    float typrime;

    minX = ui->listWidget->item(0)->text().remove('[').remove(']').split(',')[0].toInt();
    minY = ui->listWidget->item(0)->text().remove('[').remove(']').split(',')[1].toInt();
    maxX = ui->listWidget->item(1)->text().remove('[').remove(']').split(',')[0].toInt();
    maxY = ui->listWidget->item(1)->text().remove('[').remove(']').split(',')[1].toInt();

    tx = ui->listWidget->item(0)->text().remove('[').remove(']').split(',')[2].toFloat();
    ty = ui->listWidget->item(0)->text().remove('[').remove(']').split(',')[3].toFloat();
    txprime = ui->listWidget->item(1)->text().remove('[').remove(']').split(',')[2].toFloat();
    typrime = ui->listWidget->item(1)->text().remove('[').remove(']').split(',')[3].toFloat();

    *p1 = tx+(txprime - tx) / (float)(maxX-minX) *  (x-minX);
    *p2 = ty+(typrime - ty) / (float)(maxY-minY) *  (y-minY);


    qDebug()<<" borders : " << minX << "," << maxX << " | " <<  *p1 << "," << *p2 ;

}

