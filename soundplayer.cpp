#include "soundplayer.h"

SoundPlayer::SoundPlayer()
{
    sound = new QSound(":resources/bell.wav");
}

SoundPlayer::~SoundPlayer()
{
    delete sound;
}

void SoundPlayer::play()
{
    sound->play();
}

bool SoundPlayer::isPlaying()
{
    return !sound->isFinished();
}


