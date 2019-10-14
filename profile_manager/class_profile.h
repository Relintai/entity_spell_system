#ifndef CLASS_PROFILE_H
#define CLASS_PROFILE_H


#include "core/ustring.h"
#include "core/reference.h"
#include "core/dictionary.h"

#include "actionbar/action_bar_profile.h"
#include "input/input_profile.h"

class ClassProfile : public Reference {
	GDCLASS(ClassProfile, Reference);

public:
    int get_class_id();
    void set_class_id(int value);
    String get_character_class_name();
    void set_character_class_name(String value);
    int get_level();
    void set_level(int value);
    int get_xp();
    void set_xp(int value);
	bool get_actionbar_locked();
	void set_actionbar_locked(bool value);
    Ref<InputProfile> get_input_profile();
    Ref<ActionBarProfile> get_action_bar_profile();

	Dictionary get_custom_data();
	void set_custom_data(const Dictionary &dict);

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

    ClassProfile();
    ClassProfile(int class_id);
    ClassProfile(String class_name, int class_id, int level, int xp, bool locked, bool load_defaults);
    void load_defaults();

protected:
	static void _bind_methods();

private:
    String _character_class_name;
    int _class_id;
    int _level;
    int _xp;
	bool _actionbar_locked;

    Ref<InputProfile> _input_profile;
    Ref<ActionBarProfile> _action_bar_profile;

	Dictionary _custom_data;
};

#endif
