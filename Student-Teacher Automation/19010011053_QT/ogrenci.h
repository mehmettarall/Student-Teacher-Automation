#ifndef OGRENCI_H
#define OGRENCI_H

#include <QDialog>
#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class ogrenci;
}

class ogrenci : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenci(QSqlDatabase ,QWidget *parent = nullptr);
    ~ogrenci();
    void Tekrar_Getir();

private slots:
    void on_btn_ekle_clicked();

    void on_tableView_tumogrenci_clicked(const QModelIndex &index);

    void on_btn_guncelle_clicked();

    void on_btn_sil_clicked();

private:
    Ui::ogrenci *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlTableModel *model2;
    QSqlQueryModel *model3;
};

#endif // OGRENCI_H
