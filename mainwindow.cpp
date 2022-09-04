#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPieSeries *series = new QPieSeries();
    QSqlQuery q("select emplacement,count(*) from parking group by emplacement");
     while(q.next())
     {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques");
    chart->setBackgroundBrush(Qt::transparent);
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);
    chartview->resize(400,300);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    series->setLabelsVisible(true);
    QSqlQuery q1("select * from parking");
    while (q1.next()) {
        ui->comboBox_idP->addItem(q.value(0).toString());
    }
     ui->tab_parking->setModel(p.afficher());
    ui->tab_client->setModel(c.afficher());
    connect(ui->lineEditRech, SIGNAL(textChanged(QString)), this, SLOT(affrech()));
    QIntValidator *roll = new QIntValidator(100000,999999);

 ui->ID_2->setValidator(roll);
    ui->ID->setValidator(roll);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NomP->text();
    QString emplacement=ui->Emplacement->text();
    parking pa(id,nom,emplacement);
    bool test=pa.ajouter();
    if(test){
         ui->tab_parking->setModel(p.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"no";
}


void MainWindow::on_pushButton_4_clicked()
{
    int id=ui->ID->text().toInt();
    QString nom=ui->NomP->text();
    QString emplacement=ui->Emplacement->text();
    parking pa(id,nom,emplacement);
    bool test=pa.modifier(id);
    if(test){
         ui->tab_parking->setModel(p.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"no";
}


void MainWindow::on_pushButton_5_clicked()
{
    int row =ui->tab_parking->selectionModel()->currentIndex().row();
    int id=ui->tab_parking->model()->index(row,0).data().toInt();
    bool test=p.supprimer(id);
    if(test){
         ui->tab_parking->setModel(p.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"NO";

}
void MainWindow::affrech(){
ui->tab_parking->setModel(p.afficherRech(ui->comboBox_2->currentText(),ui->lineEditRech->text()));
}

void MainWindow::on_pushButton_6_clicked()
{
   ui->tab_parking->setModel(p.afficherTri(ui->comboBoxTri->currentText()));
}


void MainWindow::on_pushButton_7_clicked()
{
    int id=ui->ID_2->text().toInt();
    QString nom=ui->NomC->text();
    QString adresse=ui->adresse->text();
    int id_parking=ui->comboBox_idP->currentText().toInt();
    client cl(id,nom,adresse,id_parking);
    bool test=cl.ajouter();



    if(test){
         ui->tab_client->setModel(c.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"no";
}


void MainWindow::on_pushButton_8_clicked()
{
    int id=ui->ID_2->text().toInt();
    QString nom=ui->NomC->text();
    QString adresse=ui->adresse->text();
    int id_parking=ui->comboBox_idP->currentText().toInt();
    client cl(id,nom,adresse,id_parking);
    bool test=cl.modifier(id);
    if(test){
         ui->tab_client->setModel(c.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"no";
}


void MainWindow::on_pushButton_9_clicked()
{
    int row =ui->tab_client->selectionModel()->currentIndex().row();
    int id=ui->tab_client->model()->index(row,0).data().toInt();
    bool test=c.supprimer(id);
    if(test){
         ui->tab_client->setModel(c.afficher());
        qDebug()<<"OK";
    }
    else
        qDebug()<<"NO";

}


void MainWindow::on_pushButton_10_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);

                    const int rowCount = ui->tab_client->model()->rowCount();
                    const int columnCount = ui->tab_client->model()->columnCount();
                   out <<  "<html>\n"
                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                    <<  QString("<title>%1</title>\n").arg("strTitle")
                                    <<  "</head>\n"
                                    "<body bgcolor=#ffffff link=#5000A0>\n"

                                   //     "<align='right'> " << datefich << "</align>"
                                    "<center> <H1>Liste des formations</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                out<<"<cellspacing=10 cellpadding=3>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->tab_client->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->tab_client->isColumnHidden(column)) {
                                            QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
                                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                        }
                                    }
                                    out << "</tr>\n";
                                }
                                out <<  "</table> </center>\n"
                                    "</body>\n"
                                    "</html>\n";

                          QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                           QPrinter printer (QPrinter::PrinterResolution);
                            printer.setOutputFormat(QPrinter::PdfFormat);

                          printer.setOutputFileName(fileName);

                           QTextDocument doc;
                            doc.setHtml(strStream);

                            doc.print(&printer);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



