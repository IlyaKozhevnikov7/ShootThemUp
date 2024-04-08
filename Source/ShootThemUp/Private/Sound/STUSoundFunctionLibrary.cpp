// Shoot Them Up Yata. All Rights Reserved.

#include "STUSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

void USTUSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if (!SoundClass) return;

    SoundClass->Properties.Volume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
}

