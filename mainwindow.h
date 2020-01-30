#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Client;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     QString imported_file_name;
     QString exported_file_name;
     int selected_row;

     void add_elements();
     void import_csv();
     void export_csv();
     void add_stats();
     void count_countries();
     bool is_in_vector_countries(QString, std::vector<QString>);


    ~MainWindow();

private slots:

    void on_actionNew_File_triggered();

    void on_tableWidget_cellClicked(int row, int column);

    void on_button_clearall_clicked();

    void on_button_saveClient_clicked();

    void on_actionSave_File_triggered();

    void on_checkBox_modifications_clicked(bool checked);

    void on_actionNew_Client_triggered();

    void on_button_delete_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Client> vector_clients;


};

// This function, in order to work as a predicate must be outside the class.
bool sort_countries(std::pair<int, QString>&, std::pair<int, QString>&);


#endif // MAINWINDOW_H
