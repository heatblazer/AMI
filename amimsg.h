#ifndef AMIMSG_H
#define AMIMSG_H

class AmiClient;

class AmiMsg
{

public:
    explicit AmiMsg();
    virtual ~AmiMsg();


private:
    // on call, call my function
    AmiClient* m_callee; // who called me?

};

#endif // AMIMSG_H
