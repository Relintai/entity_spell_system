#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

class AnimationData 
{
    private:
        int id;
        bool animStop;
        float animStopTime;
        int weaponType;
        String* animationName;
        int priority;

    public:
        int getId();
        void setId(int value);
        bool getAnimStop();
        void setAnimStop(bool value);
        float getAnimStopTime();
        void setAnimStopTime(float value);
        int getWeaponType();
        void setWeaponType(int value);
        String* getAnimationName();
        void setAnimationName(String* value);
        int getPriority();
        void setPriority(int value);
        static void FromJSON();
        static void ToJSON();
};

#endif
