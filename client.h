#ifndef client_H
#define client_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class client
{
public:
    client();
    client(int,QString,QString,int);
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherCal(QString);
    bool rech(int);
private:
    int id,id_parking;
    QString nom,adresse;
};

#endif // client_H
