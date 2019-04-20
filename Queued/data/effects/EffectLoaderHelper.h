#ifndef EFFECT_LOADER_HELPER_H
#define EFFECT_LOADER_HELPER_H

class EffectLoaderHelper : public virtual Object{
	public:
		DELEGATE(void, EffectLoaderHelper*) AssetLoadedAction;
		int id;
		String* bundle;
		String* file;
		GameObject* asset;

	public:
		void addOnAssetLoadedEvent(EffectLoaderHelper::AssetLoadedAction* value);
		void removeOnAssetLoadedEvent(EffectLoaderHelper::AssetLoadedAction* value);
		int getID();
		void setID(int value);
		String* getBundle();
		void setBundle(String* value);
		String* getFile();
		void setFile(String* value);
		GameObject* getAsset();
		void setAsset(GameObject* value);
		EffectLoaderHelper();
		EffectLoaderHelper(int id, String* bundle, String* file);
		void RegisterOnAssetLoaded(EffectLoaderHelper::AssetLoadedAction* callback);
		void OnAssetLoaded(BaseAssetBundleHelper* h);
		void Load();
};

#endif
