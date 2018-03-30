#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>

class AudioManager : public QObject
{
    Q_OBJECT
public:
    explicit AudioManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // AUDIOMANAGER_H