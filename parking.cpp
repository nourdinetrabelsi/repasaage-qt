#include "parking.h"

parking::parking()
{

}
parking::parking(int id,QString nom,QString emplacement)
{
    this->id=id;
    this->nom=nom;
    this->emplacement=emplacement;
}
bool parking::rech(int id)
{
    QString res=QString::number(id);
    QSqlQuery q("select * from parking where id="+res);
    return q.next();
}
bool parking::ajouter()
{
    QSqlQuery q;
    q.prepare("insert into parking values(:id,:nom,:emplacement)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":emplacement",emplacement);
    return q.exec();
}
bool parking::modifier(int id)
{
    QSqlQuery q;
    q.prepare("update parking set nom=:nom,emplacement=:emplacement where id=:id");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":emplacement",emplacement);
    q.exec();
    return rech(id);
}

bool parking::supprimer(int id)
{
    if(!rech(id)) return false;
    QSqlQuery q;
    q.prepare("delete from parking where id=:id");
    q.bindValue(":id",id);
    return q.exec();

}
QSqlQueryModel* parking::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from parking");
    return model;
}
QSqlQueryModel* parking::afficherTri(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from parking order by "+critere);
    return model;
}
QSqlQueryModel* parking::afficherRech(QString critere,QString rech)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from parking where "+critere+" like '"+rech+"%'");
    return model;
}


