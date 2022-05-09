#include "notlar.h"
#include "ui_notlar.h"

notlar::notlar(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notlar)
{
    ui->setupUi(this);
    model2 = new QSqlTableModel;
    model2->setTable("öğrenci");
    ui->tableView_Tum_ogrenciler->setModel(model2);
    model2->select();
    sorgu = new QSqlQuery(db);

    model3 = new QSqlTableModel;
    model3->setTable("dersler");
    ui->tableView_tumdersler->setModel(model3);
    model3->select();
    sorgu = new QSqlQuery(db);


    model4 = new QSqlTableModel;
    model4->setTable("notlar");
    ui->tableView_tumogr_derskayt->setModel(model4);
    model4->select();
    sorgu = new QSqlQuery(db);

}

notlar::~notlar()
{
    delete ui;
}

void notlar::Come_On()
{
    model= new QSqlQueryModel();
    if(sorgu->exec("select * from notlar"))
    {
        model->setQuery(*sorgu);
        ui->tableView_tumogr_derskayt->setModel(model);

    }
    else
    {
        qDebug() << sorgu->lastError();
    }

}

void notlar::on_tableView_Tum_ogrenciler_clicked(const QModelIndex &index)
{
    ui->edt_ogr_no->setText(model2->index(index.row(),0).data().toString());


}

void notlar::on_tableView_tumdersler_clicked(const QModelIndex &index)
{
    ui->edt_ders_kod->setText(model3->index(index.row(),0).data().toString());

}

void notlar::on_btn_kayt_ekle_clicked()
{
    int gecis = (ui->edt_vize_not->text().toInt()*0.4) + (ui->edt_final_not->text().toInt()*0.6);
    sorgu->prepare("insert into notlar(ogr_no,ders_kodu,vize_not,final_not,geçme_notu)values(?,?,?,?,?)");
    if(ui->edt_ogr_no->text().isEmpty() or ui->edt_ders_kod->text().isEmpty() or ui->edt_vize_not->text().isEmpty() or ui->edt_final_not->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }
    else
    {
        sorgu->addBindValue(ui->edt_ogr_no->text().toInt());
        sorgu->addBindValue(ui->edt_ders_kod->text().toInt());
        sorgu->addBindValue(ui->edt_vize_not->text().toInt());
        sorgu->addBindValue(ui->edt_final_not->text().toInt());
        sorgu->addBindValue(gecis);





        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Come_On();

    }
}
