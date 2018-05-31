#ifndef USER_H
#define USER_H
#include <QObject>
#include <QString>

class User
{

public:
    User(int id, QString prenom, QString nom, QString photo);
    int getId() const;
    QString getPrenom() const;
    QString getNom() const;
    QString getPhoto() const;
private:
    int id;
    QString prenom;
    QString nom;
    QString photo;
};

#endif // USER_H
