#include "PlayerResource.h"
namespace BS {
	namespace Player {
		public:
			virtual int getCurrent() = 0;
		public:
			virtual void setCurrent(int value) = 0;
		public:
			virtual int getMax() = 0;
		public:
			virtual void setMax(int value) = 0;
		bool PlayerResource::getDirty(){
			return this->dirty;
		}
		void PlayerResource::setDirty(bool value)
		{
			this->dirty = value;
		}
		PlayerResource::PlayerResource()
		{
			Current_var = (int)(0);
			Max_var = (int)(0);
		}

	}
}
