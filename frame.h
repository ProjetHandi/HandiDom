#ifndef FRAME_H
#define FRAME_H

#include <QMainWindow>
#include <QPushButton>
#include <contact.h>


class Frame : public QWidget
{
   Q_OBJECT

public:
    Frame();
    void query(QString query);
    bool queryHasMore(int last);
    void getContacts(int last);
    void closeEvent(QCloseEvent *event);
    ~Frame();
private slots:
    void suivant();
    void precedent();
private:

};

#endif // FRAME_H
