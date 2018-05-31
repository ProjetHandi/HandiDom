#include "user.h"
#include <QObject>
#include <QString>

User::User(int id, QString prenom, QString nom)
{
    this->id = id;
    this->prenom = prenom;
    this->nom = nom;
}

User::getId() const {
    return id;
}

User::getPrenom() const {
    return prenom;
}

User::getNom() const {
    return nom;
}

