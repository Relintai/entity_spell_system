#ifndef ACTION_BAR_PROFILE_H
#define ACTION_BAR_PROFILE_H

#include "core/reference.h"
#include "core/vector.h"
#include "core/dictionary.h"
#include "core/array.h"

#include "action_bar_entry.h"

class ActionBarProfile : public Reference {
	GDCLASS(ActionBarProfile, Reference);

public:
	String get_action_bar_profile_name();
	void set_action_bar_profile_name(String value);
	Vector<Ref<ActionBarEntry> > &get_action_bars();
	void load_defaults();

	int get_action_bar_count();
	void add_action_bar(Ref<ActionBarEntry> actionbar);
	Ref<ActionBarEntry> get_action_bar(int index);
	void remove_action_bar(int index);
	void clear_action_bars();

	Dictionary to_dict() const;
	void from_dict(const Dictionary &dict);

	ActionBarProfile();
	~ActionBarProfile();

protected:
	static void _bind_methods();

private:
	String _name;
	Vector<Ref<ActionBarEntry> > _action_bars;
};

#endif
