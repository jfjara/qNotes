#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QSound>
#include <QString>

class SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();

    void play();
    bool isPlaying();

private:
    QSound* sound;



};

#endif // SOUNDPLAYER_H
