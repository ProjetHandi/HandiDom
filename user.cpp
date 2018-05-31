#include "user.h"
#include <QObject>
#include <QString>

User::User(int id, QString prenom, QString nom, QString photo)
{
    this->id = id;
    this->prenom = prenom;
    this->nom = nom;
    this->photo = photo;
}

int User::getId() const {
    return id;
}

QString User::getPrenom() const {
    return prenom;
}

QString User::getNom() const {
    return nom;
}

QString User::getPhoto() const {
    return photo;
}

