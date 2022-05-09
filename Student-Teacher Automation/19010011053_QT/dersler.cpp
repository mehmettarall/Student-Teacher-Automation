#include "dersler.h"
#include "ui_dersler.h"

int kodudgstr;

dersler::dersler(QSqlDatabase db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dersler)
{

    ui->setupUi(this);
    kodudgstr = ui->edt_kod->text().toInt();

    model2 = new QSqlTableModel;
    model2->setTable("öğrenci");
    ui->tableView_tumdersler->setModel(model2);
    model2->select();
    sorgu = new QSqlQuery(db);


    Tekrar_cagir();

}

dersler::~dersler()
{
    delete ui;
}

void dersler::Tekrar_cagir()
{
    kodudgstr = ui->edt_kod->text().toInt();
    model= new QSqlQueryModel();
    if(sorgu->exec("select * from dersler"))
    {

        model->setQuery(*sorgu);
        ui->tableView_tumdersler->setModel(model);


    }
    else
    {
        qDebug() << sorgu->lastError();
    }
}

void dersler::on_tableView_tumdersler_clicked(const QModelIndex &index)
{
    ui->edt_kod->setText(model->index(index.row(),0).data().toString());
    ui->edt_ad->setText(model->index(index.row(),1).data().toString());

    QString indis = model->index(index.row(),0).data().toString();
    int dep_id = indis.toInt();
    QSqlQuery sorgu;
    sorgu.prepare("select * from notlar WHERE ders_kodu=?");
    sorgu.addBindValue(dep_id);
    sorgu.exec();

    model3 =new QSqlQueryModel();
    model3->setQuery(sorgu);
    ui->tableView_ogrders->setModel(model3);

}

void dersler::on_btn_ekle_clicked()
{
    sorgu->prepare("insert into dersler(ders_kodu,ders_adi)values(?,?)");
    if(ui->edt_kod->text().isEmpty() or ui->edt_ad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }
    else
    {
        sorgu->addBindValue(ui->edt_kod->text());
        sorgu->addBindValue(ui->edt_ad->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Tekrar_cagir();
    }
}

void dersler::on_btn_gncelle_clicked()
{

    if(ui->edt_kod->text().isEmpty() or ui->edt_ad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }
    else
    {
        QString s = QString::number(kodudgstr);
        QMessageBox::information(this,"Hata!",s);

        sorgu->prepare("update dersler set ders_kodu=?, ders_adi=? where ders_kodu=? ");
        sorgu->addBindValue(ui->edt_kod->text().toInt());
        sorgu->addBindValue(ui->edt_ad->text());
        sorgu->addBindValue(kodudgstr);
        QMessageBox::information(this,"Hata!",ui->edt_kod->text());


        sorgu->exec();
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Tekrar_cagir();
    }
}

void dersler::on_btn_sil_clicked()
{
    sorgu->prepare("delete from dersler where ders_kodu=?");
    if(ui->edt_kod->text().isEmpty() or ui->edt_ad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Gerekli Alanları Doldurunuz !!");
    }

    else
    {
        sorgu->addBindValue(ui->edt_kod->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!",sorgu->lastError().text());

        }
        Tekrar_cagir();
    }
}
