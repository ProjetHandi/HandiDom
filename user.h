#ifndef USER_H
#define USER_H
#include <QObject>
#include <QString>

class User
{

public:
    User(int id, QString prenom, QString nom);
    int getId() const;
    QString getPrenom() const;
    QString getNom() const;
private:
    int id;
    QString prenom;
    QString nom;
};

#endif // USER_H
