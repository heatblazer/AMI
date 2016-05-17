#ifndef AMIACTION_H
#define AMIACTION_H

class AmiMsg;

class AmiAction
{
public:
    explicit AmiAction(); // maybe construct the AmiMsg //
    virtual ~AmiAction(); // maybe destroy it //

private:
    AmiMsg* m_msg;

};


#endif // AMIACTION_H
