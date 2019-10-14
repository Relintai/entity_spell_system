#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H

#include "core/vector.h"
#include "scene/main/node.h"

#include "class_profile.h"

class ProfileManager : public Node {
	GDCLASS(ProfileManager, Node);

public:
	static const String DEFAULT_PROFILE_FILE_NAME;

    static ProfileManager *get_instance();

    int get_last_used_class();
    void set_last_used_class(int value);

	int get_class_profile_count();
	Ref<ClassProfile> get_class_profile_index(int index);
	void add_class_profile(Ref<ClassProfile> profile);
	void clear_class_profiles();
	void remove_class_profile(int index);

    Vector<Ref<ClassProfile> > &get_class_profiles();
    Ref<ClassProfile> get_class_profile(int class_id);

	void save();
	void load();

	void save_profile(String name);
    void load_profile(String name);

    void load_defaults();

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

    ProfileManager();
	~ProfileManager();

protected:
    static void _bind_methods();

private:
    static ProfileManager* _instance;

	int _last_used_class;

    String _profile_name;

    Vector<Ref<ClassProfile> > _class_profiles;
};

#endif
