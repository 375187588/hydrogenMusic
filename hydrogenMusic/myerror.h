#ifndef MYERROR_H
#define MYERROR_H

#include <string>
#include <stdexcept>

class MyError
{
    std::string m_errInfo;
public:
    MyError(std::string msg)
        :m_errInfo(msg)
    {

    }
    std::string what()
    {
        return m_errInfo;
    }
    void setErrInfo(const std::string &value)
    {
        m_errInfo = value;
    }
};

#endif // MYERROR_H
