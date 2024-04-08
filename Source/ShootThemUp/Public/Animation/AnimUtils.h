#pragma once

#include "Animation/AnimMontage.h"

class AnimUtils
{

public:

	template<class T>
	static T* FindNotifyByClass(UAnimMontage* Animation)
	{
		if (!Animation) return nullptr;

		const auto Notifies = Animation->Notifies;

		for (auto Notify : Notifies)
		{
			if (auto EquipFinished = Cast<T>(Notify.Notify)) return EquipFinished;
		}

		return nullptr;
	}
};