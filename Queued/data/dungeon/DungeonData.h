#ifndef DUNGEON_DATA_H
#define DUNGEON_DATA_H

#include "MobGroup.h"

class DungeonData 
{
    private:
        int id;
        String* dungeonAssetAssetBundleName;
        String* dungeonAssetAssetname;
        String* materialAssetBundleName;
        String* materialAssetName;
        String* textureAssetBundleName;
        String* textureAssetName;
        List_T<int>* mobIds;
        List_T<MobGroup>* mobGroups;
        Color* overlayColor;
        Material* sharedMaterial;
        Texture2D* sharedTexture;
        DungeonData::LoadFinishedAction* onMaterialLoaded;
        DungeonData::LoadFinishedAction* onTextureLoaded;
        RenderTexture* rt;
        float timer;
        void OnMaterialLoaded(BaseAssetBundleHelper* h);
        void OnTextureLoaded(BaseAssetBundleHelper* h);
        void AfterMaterialLoaded(DungeonData* d);

    public:
        DELEGATE(void, DungeonData*) LoadFinishedAction;
        int getId();
        void setId(int value);
        String* getDungeonAssetAssetBundleName();
        void setDungeonAssetAssetBundleName(String* value);
        String* getDungeonAssetAssetName();
        void setDungeonAssetAssetName(String* value);
        String* getMaterialAssetBundleName();
        void setMaterialAssetBundleName(String* value);
        String* getMaterialAssetName();
        void setMaterialAssetName(String* value);
        String* getTextureAssetBundleName();
        void setTextureAssetBundleName(String* value);
        String* getTextureAssetName();
        void setTextureAssetName(String* value);
        List_T<int>* getMobIds();
        List_T<MobGroup>* getMobGroups();
        Color* getOverlayColor();
        void setOverlayColor(Color* value);
        void Set(int id, String* dungeonAssetAssetBundleName, String* dungeonAssetAssetname, String* materialAssetBundleName, String* materialAssetName, String* textureAssetBundleName, String* textureAssetName, List_T<int>* mobIds, List_T<MobGroup>* mobGroups, Color* overlayColor);
        void LoadMaterial(DungeonData::LoadFinishedAction* action);
        void RemoveMaterialCallback(DungeonData::LoadFinishedAction* action);
        void ApplyEffectsToMaterial();
        int GetRandomMob();
        MobGroup* GetRandomMobGroup();
        void ReleaseRenderTexture();
        DungeonData();
};

#endif
