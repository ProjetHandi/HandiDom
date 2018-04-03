#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QString>

class Contact
{
public:
    Contact(int id_contact, std::string nom, std::string prenom, std::string photo, std::string telephone, std::string frequence);

    std::string getNom() const;
    void setNom(const std::string &value);

    std::string getPrenom() const;
    void setPrenom(const std::string &value);

    std::string getTelephone() const;
    void setTelephone(const std::string &value);

    std::string getPhoto() const;
    void setPhoto(const std::string &value);

    std::string getFrequence() const;
    void setFrequence(const std::string &value);

    int getId_contact() const;

private:
    int id_contact;
    std::string nom;
    std::string prenom;
    std::string telephone;
    std::string photo;
    std::string frequence;

signals:

public slots:
};

#endif // CONTACT_H
