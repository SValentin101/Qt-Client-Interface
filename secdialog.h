#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

public:
    QString return_first_name();
    QString return_last_name();
    QString return_gender();
    QString return_country();
    QString return_phone();
    QString return_money();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
