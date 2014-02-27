#include "asteriskclient.h"

AsteriskClient::AsteriskClient(QObject *parent) :
    QObject(parent)
{

}

void AsteriskClient::setPassword(const QString &password)
{

}

void setUserName(const QString &userName)
{

}

void setServiceAddress(const QString &address)
{

}

void setSerivcePort(const int port)
{

}

void setDelayBeetwenRequestNotifyStatus(const int delayInMs)
{

}

void setDelayBeetwenAttempts(const int delay)
{

}

void setWaitTime(int waitTime)
{

}

void setMaxRetries(int maxRetries)
{

}

void createPredefinedNotify(const QString &context,
                            const QString &extension,
                            const QString &requestId)
{

}

void createCustomNotify(const QString &filePath,
                        const QString &requestId)
{

}

void cancelNotify(const QString &requestId)
{

}

bool addPhoneToNotify(const QString &requestId,
                      const QString &phoneNumber,
                      const QString &notifyId)
{

}
bool sendRequest(const QString &requestId)
{

}
