# Qt-Client-Interface

The present program acts as a table view list which can be created from scratch. Adding new clients one by one (Client -> New Client) and modifying at will the variables that each one of them can hold: first_name, last_name, gender, country, phone, money. To be clear, those variables serve only as an example, since a Client information would requiere a lot more variables and complexity (and also much more planning), but suffice for this particular case.
The program also allows the user to delete individual clients (after selection of the row in the table) or clear the full list with one click.

Through the program we can also import a .csv file (comma separated values file, and beware that will only work with such files). After all the information is imported (File -> New File) it will be printed accordingly in the table. The same operations as before are possible: changing the first_name of a client, his or her gender, their country or their phone number and pressing "Save Changes" after having the "Editable" box checked.

At the bottom of the window we have some simple stats about the whole list: number of males, females and the average money for each gender. 

When we are finished with the modifications or creations of clients we can export the information of our table (File -> Save File) as a csv file.

//

Qt Creator 4.11 (Community). 

Qt is a cross-platform application development framework for desktop, embedded and mobile. Supported Platforms include Linux, OS X, Windows, VxWorks, QNX, Android, iOS, OS and others.
Qt is not a programming language on its own. It is a framework written in C++. A preprocessor, the MOC (Meta-Object Compiler), is used to extend the C++ language with features like signals and slots.

Link: https://www.qt.io/

//


The main source code can be located in the file of name: mainwindow.cpp

In the folder I have also included a csv file called "MOCK_DATA.csv" that contais 1000 clients with all their data for it's use through the program and visualization. That data was randomly generated using a realistic data generator that can be found here: https://mockaroo.com/.

The EASY_DATA file is just a .csv file that contains between 3-5 clients, put there just in case that importing 1000 clients would obscure things.


The aim of this proyect was to put to practice some C++ concepts and also examine the features that the Qt Library has to offer.

I've uploaded a video to youtube where you can see the program in action! --> https://youtu.be/aB3o8_kQMlo
