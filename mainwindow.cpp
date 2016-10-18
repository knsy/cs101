#include "wineProcess.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

//#include <QCoreApplication>
//#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wineProcessor.processListFile(wineList);//get the array populated from the file

    setUpTable(ui->tableWidget, wineList.size()); //initialize the table
}

MainWindow::~MainWindow()
{
    delete ui;
}


/**
   Sets up the QTableWidget and fills it with cells
   @param table is a QTableWidget pointer to the table you want to setup
*/
void MainWindow::setUpTable(QTableWidget* table, unsigned int size)
{
    const int rows(size), columns(6); //initializing the size of the table

    table->setRowCount(rows);
    table->setColumnCount(columns);

    for(int row = 0; row < rows; row++)
    {for(int column = 0; column < columns; column++)
        {
            //filling each cell of the table with an object
            table->setItem(row,column, new QTableWidgetItem("C"));

        };

    };
}


/**
   QTableWidget doesn't clear itself so this function overwrites the cells to clear it
   @param table is a QTableWidget pointer to the table you want to setup
*/

void MainWindow::clearTable(QTableWidget* table, unsigned int size)
{
    const int rows(size), columns(6); //initializing the size of the table


    for(int row = 0; row < rows; row++)
    {for(int column = 0; column < columns; column++)
        {
            //filling each cell of the table with an object
            table->item(row,column)->setText("");
        };

    };
}

void MainWindow::populateTable(QTableWidget* table)
{
    //wineProcessor.processListFile(wineList);//get the array populated from the file

    int priceTotal = 0;

    for(unsigned int i=0;i<wineList.size();i++)
    {
        priceTotal += wineList[i].getWinePrice();

        table->item(i,0)->setText
                (QString::fromStdString(wineList[i].getWineName()));
        table->item(i,1)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWineVintage())));
        table->item(i,2)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWineRating())));
        table->item(i,3)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWinePrice())));
        table->item(i,4)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWineUpc())));
        table->item(i,5)->setText
                (QString::fromStdString(wineList[i].getWineLocation()));


    }


    ui->avgPriceLabel->setText("Average Price: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                       priceTotal/wineList.size())));

    ui->numberOfWinesLabel ->setText("Wines Selected: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                             wineList.size())));
}

void MainWindow::populateRow(QTableWidget* table, const QModelIndex &index)
{

        wineList[index.row()].setWineName(ui->inputWineName->text().toStdString());

        wineList[index.row()].setWineVintage(ui->inputWineVintage->text().toInt());

        wineList[index.row()].setWineRating(ui->inputWineRating->text().toInt());

        wineList[index.row()].setWinePrice(ui->inputWinePrice->text().toDouble());

        wineList[index.row()].setWineUpc(ui->inputWineUpc->text().toInt());

        wineList[index.row()].setWineLocation(ui->inputWineLocation->text().toStdString());

        populateTable(ui->tableWidget);

}


dataProcessing MainWindow::wineProcessor; //static member initialization
vector<Wine> MainWindow::wineList(100);  //static member intialization


/**
   Displays all the wines from the list in the table upon pressing the "All Wines" button
*/
void MainWindow::on_inputBtnAllWines_clicked()
{

    clearTable(ui->tableWidget, wineList.size()); //clear the table

    populateTable(ui->tableWidget);

}


/**
   Sorts and displays the wines within a specified rating range
*/
void MainWindow::on_inputBtnRateWines_clicked()
{
    //wineProcessor.processListFile(wineList);//get the array populated from the file

    int minRating(ui->inputMinRating->text().toInt());
    int maxRating(ui->inputMaxRating->text().toInt());
    int currentListing = 0;
    int winesSelected = 0;
    int priceTotal = 0;

    clearTable(ui->tableWidget, wineList.size()); //clear the table


    for(unsigned int i = 0; i < wineList.size(); i++)
        {

            if(wineList[currentListing].getWineRating() >= minRating &&
                wineList[currentListing].getWineRating() <= maxRating)
            {
                priceTotal += wineList[currentListing].getWinePrice();


                ui->tableWidget->item(winesSelected,0)->setText
                        (QString::fromStdString(wineList[currentListing].getWineName()));

                ui->tableWidget->item(winesSelected,1)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineVintage())));

                ui->tableWidget->item(winesSelected,2)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineRating())));

                ui->tableWidget->item(winesSelected,3)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWinePrice())));

                ui->tableWidget->item(winesSelected,4)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineUpc())));

                ui->tableWidget->item(winesSelected,5)->setText
                        (QString::fromStdString(wineList[currentListing].getWineLocation()));

                winesSelected++;


            }
            currentListing++;
        }
    ui->avgPriceLabel->setText("Average Price: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                       priceTotal/winesSelected)));

    ui->numberOfWinesLabel ->setText("Wines Selected: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                             winesSelected)));


}


/**
   Sorts and displays the wines within a certain price range
*/
void MainWindow::on_inputBtnPriceWines_clicked()
{

    //wineProcessor.processListFile(wineList);//get the array populated from the file

    int minPrice(ui->inputMinPrice->text().toInt());
    int maxPrice(ui->inputMaxPrice->text().toInt());
    int currentListing = 0;
    int winesSelected = 0;
    int priceTotal = 0;

    clearTable(ui->tableWidget, wineList.size()); //clear the table

    for(unsigned int i = 0; i < wineList.size(); i++)
        {

            if(wineList[currentListing].getWinePrice() >= minPrice &&
                wineList[currentListing].getWinePrice() <= maxPrice)
            {
                priceTotal += wineList[currentListing].getWinePrice();


                ui->tableWidget->item(winesSelected,0)->setText
                        (QString::fromStdString(wineList[currentListing].getWineName()));

                ui->tableWidget->item(winesSelected,1)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineVintage())));

                ui->tableWidget->item(winesSelected,2)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineRating())));

                ui->tableWidget->item(winesSelected,3)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWinePrice())));

                ui->tableWidget->item(winesSelected,4)->setText
                        (QString::fromStdString(wineProcessor.double_to_string
                                                (wineList[currentListing].getWineUpc())));

                ui->tableWidget->item(winesSelected,5)->setText
                        (QString::fromStdString(wineList[currentListing].getWineLocation()));


                winesSelected++;


            }
            currentListing++;
        }
    ui->avgPriceLabel->setText("Average Price: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                       priceTotal/winesSelected)));

    ui->numberOfWinesLabel ->setText("Wines Selected: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                             winesSelected)));


}


/**
   Sorts and displays the wines by rating
*/
void MainWindow::on_inputBtnSortRatingWines_clicked()
{

    Sorter wineSorter;
    //wineProcessor.processListFile(wineList);//get the array populated from the file
    vector<Wine> sortedWines(wineList.size());

    wineSorter.sortWines(wineList, sortedWines) ;



    int priceTotal = 0;

    clearTable(ui->tableWidget, wineList.size()); //clear the table

    for(unsigned int i=0;i<sortedWines.size();i++)
    {
        priceTotal += sortedWines[i].getWinePrice();

        ui->tableWidget->item(i,0)->setText
                (QString::fromStdString(sortedWines[i].getWineName()));
        ui->tableWidget->item(i,1)->setText
                (QString::fromStdString(wineProcessor.double_to_string(sortedWines[i].getWineVintage())));
        ui->tableWidget->item(i,2)->setText
                (QString::fromStdString(wineProcessor.double_to_string(sortedWines[i].getWineRating())));
        ui->tableWidget->item(i,3)->setText
                (QString::fromStdString(wineProcessor.double_to_string(sortedWines[i].getWinePrice())));
        ui->tableWidget->item(i,4)->setText
                (QString::fromStdString(wineProcessor.double_to_string(sortedWines[i].getWineUpc())));

        ui->tableWidget->item(i,5)->setText
                (QString::fromStdString(sortedWines[i].getWineLocation()));



    }


    ui->avgPriceLabel->setText("Average Price: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                       priceTotal/sortedWines.size())));

    ui->numberOfWinesLabel ->setText("Wines Selected: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                             sortedWines.size())));
}

/**
   Sorts and displays the wines by price
*/
void MainWindow::on_inputBtnSortPriceWines_clicked()
{

    Sorter wineSorter;
    //wineProcessor.processListFile(wineList);//get the array populated from the file

    wineSorter.sortWinesByPrice(wineList) ;



    int priceTotal = 0;

    clearTable(ui->tableWidget, wineList.size()); //clear the table

    for(unsigned int i=0;i<wineList.size();i++)
    {
        priceTotal += wineList[i].getWinePrice();

        ui->tableWidget->item(i,0)->setText
                (QString::fromStdString(wineList[i].getWineName()));
        ui->tableWidget->item(i,1)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWineVintage())));
        ui->tableWidget->item(i,2)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWineRating())));
        ui->tableWidget->item(i,3)->setText
                (QString::fromStdString(wineProcessor.double_to_string(wineList[i].getWinePrice())));
        ui->tableWidget->item(i,4)->setText
                (QString::fromStdString(wineProcessor.double_to_string
                                        (wineList[i].getWineUpc())));

        ui->tableWidget->item(i,5)->setText
                (QString::fromStdString(wineList[i].getWineLocation()));



    }


    ui->avgPriceLabel->setText("Average Price: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                       priceTotal/wineList.size())));

    ui->numberOfWinesLabel ->setText("Wines Selected: " +
                               QString::fromStdString(
                                   wineProcessor.double_to_string(
                                             wineList.size())));
}

/**
   Adds a new wine object to the vector
*/
void MainWindow::on_inputBtnAddWine_clicked()
{

    string newWineNameTemp(ui->inputWineName->text().toStdString());
    int newWineVintageTemp(ui->inputWineVintage->text().toInt());
    int newWineRatingTemp(ui->inputWineRating->text().toInt());
    double newWinePriceTemp(ui->inputWinePrice->text().toDouble());
    int newWineUpcTemp(ui->inputWineUpc->text().toInt());
    string newWineLocationTemp(ui->inputWineLocation->text().toStdString());

    Wine newWine(newWineNameTemp, newWineVintageTemp, newWineRatingTemp, newWinePriceTemp,
                 newWineUpcTemp, newWineLocationTemp);
    wineList.push_back(newWine);


    //clearTable(ui->tableWidget, wineList.size()); //clear the table
    setUpTable(ui->tableWidget, wineList.size());
    populateTable(ui->tableWidget);

}

/**
   Outputs the contents of the vector into a ";"-deleniated file
*/
void MainWindow::saveTable(){

    ofstream saveWineFile;
    saveWineFile.open("winelistsave.txt");
    for(unsigned int i = 0; i < wineList.size(); i++){
    saveWineFile << wineList[i].getWineName() << " ; "
           << wineList[i].getWineVintage() << " ; "
           << wineList[i].getWineRating() << " ; "
           << wineList[i].getWinePrice() << " ; "
           << wineList[i].getWineUpc() << " ; "
           << wineList[i].getWineLocation() << " ; " << endl;
    }


    saveWineFile.close();
}

void MainWindow::reloadTable(){
    wineProcessor.processProperListFile(wineList);//get the array populated from the file
    populateTable(ui->tableWidget);
}

void MainWindow::expandList(){
    string newWineNameTemp = "PushDemo";
    int newWineVintageTemp = 6;
    int newWineRatingTemp = 66;
    double newWinePriceTemp = 66.6;
    int newWineUpcTemp = 696969;
    string newWineLocationTemp = "Atlantis";

    Wine newWine(newWineNameTemp, newWineVintageTemp, newWineRatingTemp, newWinePriceTemp,
                 newWineUpcTemp, newWineLocationTemp);
    wineList.push_back(newWine);

    //clearTable(ui->tableWidget, wineList.size()); //clear the table
    setUpTable(ui->tableWidget, wineList.size());
    populateTable(ui->tableWidget);
}

void MainWindow::on_inputBtnSaveWines_clicked()
{
    saveTable();
}

void MainWindow::on_inputBtnReloadWines_clicked()
{
    if(wineProcessor.checkFileSize() > wineList.size()){
        for(int i = 0; i <= (wineProcessor.checkFileSize()-wineList.size()); i++)
        {
            expandList();
        }
    }

    reloadTable();

}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    ui->debugLabel->setText(QString::fromStdString(
                                wineProcessor.double_to_string(
                                    index.row()+1)));

    ui->inputWineName->setText(QString::fromStdString(wineList[index.row()].getWineName()));

    ui->inputWineVintage->setText(QString::fromStdString(
                wineProcessor.double_to_string(wineList[index.row()].getWineVintage())));

    ui->inputWineRating->setText(QString::fromStdString(
                wineProcessor.double_to_string(wineList[index.row()].getWineRating())));

    ui->inputWinePrice->setText(QString::fromStdString(
                wineProcessor.double_to_string(wineList[index.row()].getWinePrice())));

    ui->inputWineUpc->setText(QString::fromStdString(
                wineProcessor.double_to_string(wineList[index.row()].getWineUpc())));

    ui->inputWineLocation->setText(QString::fromStdString(wineList[index.row()].getWineLocation()));



}

void MainWindow::on_inputBtnEditWine_clicked()
{
    populateRow(ui->tableWidget, ui->tableWidget->currentIndex());
}


//TESTING THE DB CONNECTIVITY

bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("password");
    if (!db.open()) {
        qDebug() << "Database error occurred";
        return false;
    }
    return true;
}

void MainWindow::on_inputBtnMysqlSearch_clicked()
{

    if (!createConnection()){

        qDebug() << "Not connected!";

    }
    else{

        qDebug() << "Connected!";

        QSqlQuery query;

        query.exec("use wine");

        query.exec(ui->inputMysqlSearch->text());

        QString data;

        int i=0;

        while (query.next()) {
            //get/set Wine Name
                data = query.value(0).toString();
                ui->tableWidget->item(i,0)->setText
                        (data);

            //get/set Vintage
                data = query.value(1).toString();
                ui->tableWidget->item(i,1)->setText
                        (data);

            //get/set Rating
                data = query.value(2).toString();
                ui->tableWidget->item(i,2)->setText
                        (data);

            //get/set Price
                data = query.value(3).toString();
                ui->tableWidget->item(i,3)->setText
                        (data);

            //get/set field 2
                data = query.value(4).toString();
                ui->tableWidget->item(i,4)->setText
                        (data);

            //get/set Country
                data = query.value(5).toString();
                ui->tableWidget->item(i,5)->setText
                        (data);

            i++;



        }


    }







}

void MainWindow::on_inputBtnMysqlAll_clicked()
{
    if (!createConnection()){

        qDebug() << "Not connected!";

    }
    else{

        qDebug() << "Connected!";

        QSqlQuery query;

        query.exec("use wine");
        query.exec("SELECT * FROM wineInfo");

        QString data;

        int i=0;

        while (query.next()) {
            //get/set Wine Name
                data = query.value(0).toString();
                ui->tableWidget->item(i,0)->setText
                        (data);

            //get/set Vintage
                data = query.value(1).toString();
                ui->tableWidget->item(i,1)->setText
                        (data);

            //get/set Rating
                data = query.value(2).toString();
                ui->tableWidget->item(i,2)->setText
                        (data);

            //get/set Price
                data = query.value(3).toString();
                ui->tableWidget->item(i,3)->setText
                        (data);

            //get/set field 2
                data = query.value(4).toString();
                ui->tableWidget->item(i,4)->setText
                        (data);

            //get/set Country
                data = query.value(5).toString();
                ui->tableWidget->item(i,5)->setText
                        (data);

            i++;


        }


    }
}
