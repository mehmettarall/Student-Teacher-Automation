#include "ogrenci.h"
#include "ui_ogrenci.h"

ogrenci::ogrenci(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenci)
{
    ui->setupUi(this);
    model2 = new QSqlTableModel;
    model2->setTable("öğrenci");
    ui->tableView_tumogrenci->setModel(model2);
    model2->select();
    sorgu = new QSqlQuery(db);
    Tekrar_Getir();
}

ogrenci::~ogrenci()
{
    delete ui;
}

void ogrenci::Tekrar_Getir()
{
    model= new QSqlQueryModel();
    if(sorgu->exec("select * from öğrenci"))
    {
        model->setQuery(*sorgu);
        ui->tableView_tumogrenci->setModel(model);


    }
    else
    {
        qDebug() << sorgu->lastError();
    }
}

void ogrenci::on_btn_ekle_clicked()
{



    sorgu->prepare("insert into öğrenci(ogr_ad,ogr_soyad)values(?,?)");
    if(ui->edt_ograd->text().isEmpty() or ui->edt_ogrsoyad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }
    else
    {
        sorgu->addBindValue(ui->edt_ograd->text());
        sorgu->addBindValue(ui->edt_ogrsoyad->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Tekrar_Getir();
    }

}

void ogrenci::on_tableView_tumogrenci_clicked(const QModelIndex &index)
{
    ui->edt_ogrno->setText(model->index(index.row(),0).data().toString());
    ui->edt_ograd->setText(model->index(index.row(),1).data().toString());
    ui->edt_ogrsoyad->setText(model->index(index.row(),2).data().toString());

}

void ogrenci::on_btn_guncelle_clicked()
{
    sorgu->prepare("update öğrenci set ogr_ad=?, ogr_soyad=? where ogr_no=?");
    if(ui->edt_ograd->text().isEmpty() or ui->edt_ogrsoyad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }
    else
    {

        sorgu->addBindValue(ui->edt_ograd->text());
        sorgu->addBindValue(ui->edt_ogrsoyad->text());
        sorgu->addBindValue(ui->edt_ogrno->text().toInt());
        sorgu->exec();
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Tekrar_Getir();
    }

}

void ogrenci::on_btn_sil_clicked()
{
    sorgu->prepare("delete from öğrenci where ogr_no=?");
    QSqlQuery dnme;
    if(ui->edt_ograd->text().isEmpty() or ui->edt_ogrsoyad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }



    else if(dnme.prepare("delete from öğrenci where ogr_no=? in notlar"))
    {

        QMessageBox::critical(this,"Hata!","Öğrenci Dersi var !!");
    }
    else
    {
        sorgu->addBindValue(ui->edt_ogrno->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }

        Tekrar_Getir();
    }


}
