#include "client.h"
#include <QDateTime>
client::client()
{

}
client::client(int id,QString nom,QString adresse,int id_parking)
{
    this->id=id;
    this->nom=nom;
    this->adresse=adresse;
    this->id_parking=id_parking;

}
bool client::rech(int id)
{
    QString res=QString::number(id);
    QSqlQuery q("select * from client where id="+res);
    return q.next();
}
bool client::ajouter()
{
    QSqlQuery q;
    q.prepare("insert into client values(:id,:nom,:adresse,:id_parking)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":adresse",adresse);
    q.bindValue(":id_parking",id_parking);
    return q.exec();
}
bool client::modifier(int id)
{
    QSqlQuery q;
    q.prepare("update formateur set nom=:nom,adresse=:adresse,id_parking=:id_parking where id=:id");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":adresse",adresse);
    q.bindValue(":id_parking",id_parking);
    q.exec();
    return rech(id);
}

bool client::supprimer(int id)
{
    if(!rech(id)) return false;
    QSqlQuery q;
    q.prepare("delete from client where id=:id");
    q.bindValue(":id",id);
    return q.exec();

}
QSqlQueryModel* client::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from client");
    return model;
}



