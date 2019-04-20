#pragma once
#include <System/System.h>

using namespace System;
namespace BS {
	namespace Player {
		class PlayerResource : public abstract virtual Object
		{
			private:
				bool dirty;
			public:
				int getCurrent();
			public:
				void setCurrent(int value);
			public:
				int getMax();
			public:
				void setMax(int value);
			public:
				bool getDirty();
			public:
				void setDirty(bool value);
			public:
			virtual int Current_var;
			public:
			virtual int Max_var;
			public:
				PlayerResource();
		};
	}
}
