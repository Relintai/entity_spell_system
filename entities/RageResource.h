#pragma once
#include <System/System.h>
#include "PlayerResource.h"
#include "JsonWriter.h"
#include "JsonReader.h"
#include "JsonToken.h"

using namespace Newtonsoft::Json;
using namespace System;
namespace BS {
	namespace Player {
		class RageResource : public virtual PlayerResource, public virtual Object
		{
			private:
				int current;
			private:
				int max;
			public:
			virtual int getCurrent();
			public:
			virtual void setCurrent(int value);
			public:
			virtual int getMax();
			public:
			virtual void setMax(int value);
			public:
				RageResource();
			public:
			static void ToJSON(RageResource* rr, JsonWriter* w);
			public:
			static void FromJSON(RageResource* rr, JsonReader* r);
		};
	}
}
