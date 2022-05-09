#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dersler.h"
#include "notlar.h"
#include "ogrenci.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("C:/Proje_QT/SQlDERS/ogrencioto.db");
    if(!db.open())
        ui->statusbar->showMessage("Durum: Veritbanı bağlantısı başarısız...!");
    else
        ui->statusbar->showMessage("Durum: Veritbanı bağlantısı BAŞARILI...!");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_ogrenci_islem_clicked()
{
    ogrenci *ogr = new ogrenci(db);
    ogr->show();
}

void MainWindow::on_btn_ders_islem_clicked()
{
    dersler *ders = new dersler(db);
    ders->show();
}

void MainWindow::on_btn_not_islem_clicked()
{
    notlar *nots = new notlar(db);
    nots->show();
}
