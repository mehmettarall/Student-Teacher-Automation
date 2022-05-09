#ifndef NOTLAR_H
#define NOTLAR_H

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
class notlar;
}

class notlar : public QDialog
{
    Q_OBJECT

public:
    explicit notlar(QSqlDatabase ,QWidget *parent = nullptr);
    ~notlar();
    void Come_On();

private slots:
    void on_tableView_Tum_ogrenciler_clicked(const QModelIndex &index);

    void on_tableView_tumdersler_clicked(const QModelIndex &index);

    void on_btn_kayt_ekle_clicked();

private:
    Ui::notlar *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;
};

#endif // NOTLAR_H
