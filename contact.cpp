#include "contact.h"

Contact::Contact(int id_contact, std::string nom, std::string prenom, std::string photo, std::string telephone, std::string frequence)
{
    this->id_contact = id_contact;
    this->nom = nom;
    this->prenom = prenom;
    this->photo = photo;
    this->telephone = telephone;
    this->frequence = frequence;
}

std::string Contact::getNom() const
{
    return nom;
}

std::string Contact::getPrenom() const
{
    return prenom;
}


std::string Contact::getTelephone() const
{
    return telephone;
}

std::string Contact::getPhoto() const
{
    return photo;
}

std::string Contact::getFrequence() const
{
    return frequence;
}

int Contact::getId_contact() const
{
    return id_contact;
}
