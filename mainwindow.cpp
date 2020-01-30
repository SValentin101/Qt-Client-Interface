#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"

#include <QFileDialog>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <functional>
#include <QMessageBox>

class Client
{
public:
    Client() = default;
    Client(int i, QString a, QString b, QString c, QString d, QString e, QString f) : ident(i), first_name(a), second_name(b),
    gender(c), country(d), phone(e), money(f){}

    int ident;
    QString first_name;
    QString second_name;
    QString gender;
    QString country;
    QString phone;
    QString money;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Data Clients");
    // Avoid window resizes
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
    // Table
    QStringList col_list{"Fist Name", "Second Name", "Gender", "Country", "Phone Number", "Money"};
    int columns = 6;
    ui->tableWidget->setColumnCount(columns);
    ui->tableWidget->setHorizontalHeaderLabels(col_list);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);

    // Client Information Panel
    ui->label_first_name->setReadOnly(true);
    ui->label_last_name->setReadOnly(true);
    ui->label_gender->setReadOnly(true);
    ui->label_country->setReadOnly(true);
    ui->label_phone_number->setReadOnly(true);
    ui->label_money->setReadOnly(true);

    // Client List stats, so we can only read it.
    ui->label_total_clients->setReadOnly(true);
    ui->label_men_clients->setReadOnly(true);
    ui->label_woman_clients->setReadOnly(true);
    ui->label_total_average->setReadOnly(true);
    ui->label_men_average->setReadOnly(true);
    ui->label_women_average->setReadOnly(true);
    ui->label_countries_total->setReadOnly(true);
    ui->label_1_country->setReadOnly(true);
    ui->label_1_country_n->setReadOnly(true);
    ui->label_2_country->setReadOnly(true);
    ui->label_2_country_n->setReadOnly(true);
    ui->label_3_country->setReadOnly(true);
    ui->label_3_country_n->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_elements()
{
       int rows = static_cast<int>(vector_clients.size());

       ui->tableWidget->setRowCount(rows);

       for(auto iter = vector_clients.cbegin(); iter != vector_clients.cend(); iter++)
       {

          ui->tableWidget->setItem(iter->ident, 0, new QTableWidgetItem(iter->first_name));
          ui->tableWidget->setItem(iter->ident, 1, new QTableWidgetItem(iter->second_name));
          ui->tableWidget->setItem(iter->ident, 2, new QTableWidgetItem(iter->gender));
          ui->tableWidget->setItem(iter->ident, 3, new QTableWidgetItem(iter->country));
          ui->tableWidget->setItem(iter->ident, 4, new QTableWidgetItem(iter->phone));
          ui->tableWidget->setItem(iter->ident, 5, new QTableWidgetItem(iter->money));
       }

}


void MainWindow::import_csv()
{

   // Read the file:
    std::ifstream input_stream;
    const std::string file_name = imported_file_name.toStdString();

    QString file_name_message = QString::fromStdString(file_name);
    file_name_message += " imported successfully";

    input_stream.open(file_name);
    std::string line, word;
    int row = 0;

    if(input_stream.is_open())
    {
        while(std::getline(input_stream, line))
        {
            // Ignore first row because it contains the names of the columns.
            if (row >= 1)
            {
                std::istringstream string_stream(line);
                Client user;

                int index = 0;

                if (string_stream.good())
               {

                while(std::getline(string_stream, word, ','))  // Going word for word in the same row, separation between them = ','
                {

                    switch (index)
                    {
                    // We will always need to switch between QString and std::string. Same thing will hapen when exporting the modified file.
                    // Then will be from QString to std::string.
                    case 0: user.first_name = QString::fromStdString(word);
                        break;
                    case 1: user.second_name = QString::fromStdString(word);
                        break;
                    case 2: user.gender = QString::fromStdString(word);
                        break;
                    case 3: user.country = QString::fromStdString(word);
                        break;
                    case 4: user.phone = QString::fromStdString(word);
                        break;
                    case 5: user.money = QString::fromStdString(word);
                        break;
                    }
                    index++;
                }

                vector_clients.push_back(user);

               }
            }
            row++;

        }
        ui->statusbar->showMessage(file_name_message, 5000);

        input_stream.close();
    }
    else
    {
        qDebug("Could not open file\n");
    }

    // Add the ident variable to the elements of the vector_clients.
    int i = 0;
    if(!vector_clients.empty())
    {
        for (auto iter = vector_clients.begin(); iter != vector_clients.end(); iter++)
        {
            iter->ident = i;
            i++;

        }
    }
}

void MainWindow::on_actionNew_File_triggered()
{
    // Get to the location of the file that you want.
    imported_file_name = QFileDialog::getOpenFileName(this, "File Selection", "E:/Documentos/Qt Documents/Excel_List", "*.txt *.csv");
    import_csv();
    qDebug() << "Information Imported, vector size: " << vector_clients.size();
    add_elements();
    add_stats();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    // If a client from the table is selected all the info of that client will be displayed in the Client Information Panel.
    ui->label_first_name->setText(vector_clients[row].first_name);
    ui->label_last_name->setText(vector_clients[row].second_name);
    ui->label_gender->setText(vector_clients[row].gender);
    ui->label_country->setText(vector_clients[row].country);
    ui->label_phone_number->setText(vector_clients[row].phone);
    ui->label_money->setText(vector_clients[row].money);

    // Get the row selected, it will be needed in other functions to get the position of the client and then modify him or her.
    // that's why its a global variable.
    selected_row = row;

}

void MainWindow::on_button_clearall_clicked()
{
    // Delete all the rows
    ui->tableWidget->setRowCount(0);
    // Delete all the clients from the vector that contains them
    vector_clients.clear();
    // Erase all information from the Client Information Panel and the Stats Panel.
    ui->label_first_name->setText("");
    ui->label_last_name->setText("");
    ui->label_gender->setText("");
    ui->label_country->setText("");
    ui->label_phone_number->setText("");
    ui->label_money->setText("");
    ui->label_total_clients->setText("");
    ui->label_men_clients->setText("");
    ui->label_woman_clients->setText("");
    ui->label_total_average->setText("");
    ui->label_men_average->setText("");
    ui->label_women_average->setText("");
    ui->label_countries_total->setText("");
    ui->label_1_country->setText("");
    ui->label_1_country_n->setText("");
    ui->label_2_country->setText("");
    ui->label_2_country_n->setText("");
    ui->label_3_country->setText("");
    ui->label_3_country_n->setText("");

}



void MainWindow::on_button_saveClient_clicked()
{
    // Allow modifications to a Client only if the box checkBox_modifications is checked.
    if (ui->checkBox_modifications->isChecked())
    {
        // Get the data from the corresponding input boxes and set it to all the columns of the selected row.
        QString new_first_name = ui->label_first_name->text();
        ui->tableWidget->setItem(selected_row, 0, new QTableWidgetItem(new_first_name));
        QString new_last_name = ui->label_last_name->text();
        ui->tableWidget->setItem(selected_row, 1, new QTableWidgetItem(new_last_name));
        QString new_gender = ui->label_gender->text();
        ui->tableWidget->setItem(selected_row, 2, new QTableWidgetItem(new_gender));
        QString new_country = ui->label_country->text();
        ui->tableWidget->setItem(selected_row, 3, new QTableWidgetItem(new_country));
        QString new_phone = ui->label_phone_number->text();
        ui->tableWidget->setItem(selected_row, 4, new QTableWidgetItem(new_phone));
        QString new_money = ui->label_money->text();

        QString copy_new_money = new_money;
        copy_new_money.insert(0, "£");

        ui->tableWidget->setItem(selected_row, 5, new QTableWidgetItem(new_money));

        // Don't forget to save the changes in the vector_clients.
        vector_clients[selected_row].first_name = new_first_name;
        vector_clients[selected_row].second_name = new_last_name;
        vector_clients[selected_row].gender = new_gender;
        vector_clients[selected_row].country = new_country;
        vector_clients[selected_row].phone = new_phone;
        vector_clients[selected_row].money = new_money;

        ui->statusbar->showMessage("Client modified", 2500);

         add_stats();
    }

}

void MainWindow::on_actionSave_File_triggered()
{
    export_csv();
}

void MainWindow::export_csv()
{
    // Get to the location where you want to save the file and the file name.
    exported_file_name = QFileDialog::getSaveFileName(this, "Save Text File", "E:/Documentos/Qt Documents/Excel_List", "*.txt");

    std::ofstream output_stream;
    const std::string file_name = exported_file_name.toStdString();

    QString file_name_message = QString::fromStdString(file_name);
    file_name_message += " exported successfully";

    output_stream.open(file_name);

    if(output_stream.is_open())
    {
        // Write the first row with the name variables:
        output_stream << "first_name,last_name,gender,country,phone,money\n";

        while(output_stream.good())  // While there are no errors keep writing.
        {
                // Now the elements of the vector, each client.
                for (auto iter = vector_clients.begin(); iter != vector_clients.end(); iter++)
                {
                    // Again we need to convert the elements from QString to std::string in order for the output to work
                    std::string output_first_name = iter->first_name.toStdString();
                    std::string output_last_name = iter->second_name.toStdString();
                    std::string output_gender = iter->gender.toStdString();
                    std::string output_country = iter->country.toStdString();
                    std::string output_phone = iter->phone.toStdString();
                    std::string output_money = iter->money.toStdString();

                    // Now is when we write to the stream.
                    output_stream << output_first_name << "," << output_last_name << ","
                                  << output_gender << "," << output_country << ","
                                  << output_phone  << "," << output_money << "\n";
            }

            output_stream.close();
            ui->statusbar->showMessage(file_name_message, 5000);
        }
    }
    else
    {
        qDebug() << "Could not open output stream \n";
    }
}

void MainWindow::on_checkBox_modifications_clicked(bool checked)
{
    if(checked == false)
    {
        // Client Information Panel won't be clickleable nor modifiable
            ui->label_first_name->setReadOnly(true);
            ui->label_last_name->setReadOnly(true);
            ui->label_gender->setReadOnly(true);
            ui->label_country->setReadOnly(true);
            ui->label_phone_number->setReadOnly(true);
            ui->label_money->setReadOnly(true);
    }
    else
    {
            ui->label_first_name->setReadOnly(false);
            ui->label_last_name->setReadOnly(false);
            ui->label_gender->setReadOnly(false);
            ui->label_country->setReadOnly(false);
            ui->label_phone_number->setReadOnly(false);
            ui->label_money->setReadOnly(false);
    }

}

void MainWindow::add_stats()
{
    int total_clients = static_cast<int>(vector_clients.size());
    int men_clients = 0, women_clients = 0;
    double total_money = 0, men_money = 0, women_money = 0;

    // Give the number of clients of each gender and also their money.
    for (auto &elemen : vector_clients)
    {
        // Money has the pound currency symbol in the [0] position, we take it out first but we leave our vector alone, using only a local copy
        // then transform it to double and add.
        QString money_copy = elemen.money;
        money_copy[0] = ' ';
        total_money += money_copy.toDouble();

        // By gender.
        if(elemen.gender == 'F')
        {
            women_clients++;
            // Money is defined as a QString type of data, so it needs conversion.
            women_money += money_copy.toDouble();
        }
        else
        {
            men_clients++;
            men_money += money_copy.toDouble();
        }
    }

    // Money Average
    double total_average = total_money / total_clients;
    double men_average = men_money / men_clients;
    double women_average = women_money / women_clients;

    // Transform them to QString type and Set the labels accordingly.
    ui->label_total_clients->setText(QString::number(total_clients));
    ui->label_men_clients->setText(QString::number(men_clients));
    ui->label_woman_clients->setText(QString::number(women_clients));
    ui->label_total_average->setText(QString::number(total_average));
    ui->label_men_average->setText(QString::number(men_average));
    ui->label_women_average->setText(QString::number(women_average));

    // Now for the countries:
    count_countries();
}

void MainWindow::on_actionNew_Client_triggered()
{
    SecDialog Dialog(this);
    Dialog.setWindowTitle("New Client Addition");
    int answer, new_user_row;
    answer = Dialog.exec();

    Client new_user;
    // We will deal with Accept and Cancel buttons.

      if(answer == QDialog::Rejected)
        {
            return;  // Get out of this function and terminate the second window if the answer is cancel.
        }

     // Take all the data from that window.
      new_user.first_name = Dialog.return_first_name();
      new_user.second_name = Dialog.return_last_name();
      new_user.gender = Dialog.return_gender();
      new_user.country = Dialog.return_country();
      new_user.phone = Dialog.return_phone();
      new_user.money = Dialog.return_money();




      new_user.money.insert(0, "£");
      // Null data will be rejected.
        if (new_user.first_name != "" && new_user.second_name != "" && new_user.gender != "" &&
            new_user.country != "" && new_user.phone != "" && new_user.money != "")
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());  // A new row will be inserted in our table.
            new_user_row = ui->tableWidget->rowCount() - 1;   // The row where we are going to write.

            // All the information is added to the table
            ui->tableWidget->setItem(new_user_row, 0, new QTableWidgetItem(new_user.first_name));
            ui->tableWidget->setItem(new_user_row, 1, new QTableWidgetItem(new_user.second_name));
            ui->tableWidget->setItem(new_user_row, 2, new QTableWidgetItem(new_user.gender));
            ui->tableWidget->setItem(new_user_row, 3, new QTableWidgetItem(new_user.country));
            ui->tableWidget->setItem(new_user_row, 4, new QTableWidgetItem(new_user.phone));
            ui->tableWidget->setItem(new_user_row, 5, new QTableWidgetItem(new_user.money));

            // Now we update the vector that holds all the data of the clients, but only if the client is not null.
              vector_clients.push_back(new_user);
              add_stats();

              ui->statusbar->showMessage("New Client added", 2500);
            }


}

void MainWindow::on_button_delete_clicked()
{
    // Delete that information from the vector_clients.

    vector_clients.erase(vector_clients.begin() + selected_row);

    // Delete the information from the table.
     ui->tableWidget->removeRow(selected_row);

    // Update the information in the Stats Panel
     add_stats();

    // Erase all information from the Client Information Panel;
     ui->label_first_name->setText("");
     ui->label_last_name->setText("");
     ui->label_gender->setText("");
     ui->label_country->setText("");
     ui->label_phone_number->setText("");
     ui->label_money->setText("");

     // If after deletion of all clients manually, all information from the Stats Panel should be erased.
     if(vector_clients.empty())
     {
         ui->label_countries_total->setText("");
         ui->label_total_clients->setText("");
         ui->label_total_average->setText("");
         ui->label_men_clients->setText("");
         ui->label_men_average->setText("");
         ui->label_woman_clients->setText("");
         ui->label_women_average->setText("");
     }
     ui->statusbar->showMessage("Client deleted", 1500);
}

void MainWindow::count_countries()
{
    std::vector<QString> vector_countries;
    for (auto iter = vector_clients.begin(); iter != vector_clients.end(); iter++)
    {
        vector_countries.push_back(iter->country);
    }

    // We create a vector to store all the unique matches.
    std::vector<QString> unique_vector_countries;
    for (auto iter = vector_countries.begin(); iter != vector_countries.end(); iter++)
    {
        if(unique_vector_countries.empty())
        {
            unique_vector_countries.push_back(*iter);
        }

        if(!is_in_vector_countries(*iter, unique_vector_countries))
        {
            unique_vector_countries.push_back(*iter);
        }


     }

    qDebug() << "Size of Vector Country: " << vector_countries.size();
    qDebug() << "Size of Unique Vector Country: " << unique_vector_countries.size();

    ui->label_countries_total->setText(QString::number(unique_vector_countries.size()));

    // How many times a country is repeated, we will store that data in another vector. Afterwards we will create a std::pair to hold
    // the country and the times it appears.
    std::vector<int> repetitions;
    for (auto iter = unique_vector_countries.begin(); iter != unique_vector_countries.end(); iter++)
    {
        int i = std::count(vector_countries.begin(), vector_countries.end(), *iter);
        repetitions.push_back(i);
    }

    // We create a vector that holds pairs, since each country will have an int associated.
    std::vector<std::pair<int, QString>> vector_country_pairs;
    for (int value = 0; value != unique_vector_countries.size(); value++)
    {
        std::pair<int, QString> MyPair(repetitions[value], unique_vector_countries[value]);
        vector_country_pairs.push_back(MyPair);
    }

    // Now we must arrange that vector that holds pairs in descending order. First must appear the countries that appear the most, etc.
    // We will use a function as a predicate to order them.
    std::sort(vector_country_pairs.begin(), vector_country_pairs.end(), sort_countries);

    // Now the vector that holds pairs: n_times - Country is arranged.
    if(vector_country_pairs.size() == 0)
    {
        // If size reaches 0 because the user has deleted the clients one by one, the information from the labels must be alse erased.
        ui->label_1_country->setText("");
        ui->label_1_country_n->setText("");

        ui->label_2_country->setText("");
        ui->label_2_country_n->setText("");

        ui->label_3_country->setText("");
        ui->label_3_country_n->setText("");
    }
    if(vector_country_pairs.size() == 1)
    {
        ui->label_1_country->setText(vector_country_pairs[0].second);
        ui->label_1_country_n->setText(QString::number(vector_country_pairs[0].first)); // Since it only accepts QString as text we must
        // transform the int (times the country appears) to QString.

        // We take into account that if the size is 1 the other two labels must be erased.
        ui->label_2_country->setText("");
        ui->label_2_country_n->setText("");

        ui->label_3_country->setText("");
        ui->label_3_country_n->setText("");
    }
    if(vector_country_pairs.size() == 2)
    {
        ui->label_1_country->setText(vector_country_pairs[0].second);
        ui->label_1_country_n->setText(QString::number(vector_country_pairs[0].first));

        ui->label_2_country->setText(vector_country_pairs[1].second);
        ui->label_2_country_n->setText(QString::number(vector_country_pairs[1].first));

        // If the size is 2 erase information from the third label.
        ui->label_3_country->setText("");
        ui->label_3_country_n->setText("");
    }
    if(vector_country_pairs.size() >= 3)
    {
        ui->label_1_country->setText(vector_country_pairs[0].second);
        ui->label_1_country_n->setText(QString::number(vector_country_pairs[0].first));

        ui->label_2_country->setText(vector_country_pairs[1].second);
        ui->label_2_country_n->setText(QString::number(vector_country_pairs[1].first));

        ui->label_3_country->setText(vector_country_pairs[2].second);
        ui->label_3_country_n->setText(QString::number(vector_country_pairs[2].first));
    }




}


 bool MainWindow::is_in_vector_countries(QString e, std::vector<QString> vector_countries)
 {
      bool is_in_vector = false;

      for (auto element : vector_countries)
         {
             if (element == e)
             {
                 is_in_vector = true;
             }
         }

         return is_in_vector;

 }

bool sort_countries(std::pair<int, QString>& A, std::pair<int, QString>& B)
 {
     return A.first > B.first;
 }
