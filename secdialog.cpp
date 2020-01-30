#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_buttonBox_accepted()
{
    accept();
}

void SecDialog::on_buttonBox_rejected()
{
    reject();
}

QString SecDialog::return_first_name()
{
    return ui->label_first_name_2->text();
}
QString SecDialog::return_last_name()
{
   return ui->label_last_name_2->text();
}
QString SecDialog::return_gender()
{
   return ui->label_gender_2->text();
}
QString SecDialog::return_country()
{
    return ui->label_country_2->text();
}
QString SecDialog::return_phone()
{
    return ui->label_phone_number_2->text();
}
QString SecDialog::return_money()
{
    return ui->label_money_2->text();
}
