#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>

class COM
{
public:
    COM();
    void setUpPIN();
    void call(QString number);
    void hangup();
};

#endif // COMMUNICATION_H
