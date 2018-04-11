#ifndef __ICE_OBJECT_H__
#define __ICE_OBJECT_H__

#include <iostream>
#include <string>
#include <cstring>

class IceObject
{
protected:
    void *value;
    std::string type;

public:
    virtual ~IceObject() {}
    virtual void show() = 0;
};

class IceIntegerObject : public IceObject
{
public:
    IceIntegerObject(long value);
    virtual ~IceIntegerObject() {}
    virtual void show();
};

#endif // __ICE_OBJECT_H__