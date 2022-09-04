#ifndef parking_H
#define parking_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class parking
{
public:
    parking();
    parking(int,QString,QString);
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherTri(QString);
    QSqlQueryModel* afficherRech(QString,QString);
    bool rech(int);
private:
    int id;
    QString nom,emplacement;
};

#endif // parking_H
