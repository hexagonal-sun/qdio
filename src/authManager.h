#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>

namespace AuthManager {
    const QString getAuthToken();
    void setAuthToken(const QString authToken);
}

#endif // AUTHMANAGER_H
