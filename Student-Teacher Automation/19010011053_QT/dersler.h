#ifndef DERSLER_H
#define DERSLER_H

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
class dersler;
}

class dersler : public QDialog
{
    Q_OBJECT

public:
    explicit dersler(QSqlDatabase, QWidget *parent = nullptr);
    ~dersler();
    void Tekrar_cagir();

private slots:
    void on_tableView_tumdersler_clicked(const QModelIndex &index);

    void on_btn_ekle_clicked();

    void on_btn_gncelle_clicked();

    void on_btn_sil_clicked();

private:
    Ui::dersler *ui;
    QSqlQuery *sorgu;
    QSqlQueryModel *model;
    QSqlTableModel *model2;
    QSqlQueryModel *model3;


};

#endif // DERSLER_H
