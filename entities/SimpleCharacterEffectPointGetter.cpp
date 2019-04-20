#include "SimpleCharacterEffectPointGetter.h"
namespace BS {
	namespace Player {
		Transform* SimpleCharacterEffectPointGetter::GetEffectPoint(EffectPoints bodyPartEffectPoint){
			return MonoBehaviour::transform;
		}

	}
}
