#include "authManager.h"

namespace AuthManager {
static QString authToken_;

const QString getAuthToken()
{
    return authToken_;
}

void setAuthToken(const QString authToken)
{
    authToken_ = authToken;
}
}
