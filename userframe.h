#ifndef USERFRAME_H
#define USERFRAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMapIterator>
#include <user.h>
#include <QWidget>

class UserFrame : public QWidget
{
    Q_OBJECT
public:
    UserFrame();
    void query(QString query);
    void updateUserSuivant(int last);
    void getAllUser();
    void updateUserPrecedent();
private slots:
    void suivant();
    void precedent();
private:
    QGridLayout *layout = new QGridLayout;
};

#endif // USERFRAME_H
