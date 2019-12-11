#include "ess_physics_query.h"

ESSPhysicsQuery *ESSPhysicsQuery::_instance;

ESSPhysicsQuery *ESSPhysicsQuery::get_instance() {
	return _instance;
}

//void ESSPhysicsQuery::queue_intersect_ray(Object *p_id, const StringName &p_prop, const Vector3 &p_from, const Vector3 &p_to, const Vector<RID> &p_exclude, uint32_t p_collision_mask) {
void ESSPhysicsQuery::queue_intersect_ray(Object *p_id, const StringName &p_prop, const Vector3 &p_from, const Vector3 &p_to, const Vector<RID> &p_exclude) {

}

void ESSPhysicsQuery::_notification(int p_what) {
	switch (p_what) {

		case NOTIFICATION_ENTER_TREE: {
			//set_physics_process_internal(true);
		} break;
		case NOTIFICATION_EXIT_TREE: {
		} break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
			//flush();
		} break;
	}
}

void ESSPhysicsQuery::flush() {
	if (_buffer_end > _buffer_max_used) {
		_buffer_max_used = _buffer_end;
	}

	uint32_t read_pos = 0;

	//using reverse locking strategy
	_THREAD_SAFE_LOCK_

	ERR_FAIL_COND(_flushing); //already flushing, you did something odd

	_flushing = true;

	while (read_pos < _buffer_end) {

		//lock on each iteration, so a call can re-add itself to the message queue

		QueryData *message = (QueryData *)&_buffer[read_pos];

		uint32_t advance = sizeof(QueryData);

		//pre-advance so this function is reentrant
		read_pos += advance;

		_THREAD_SAFE_UNLOCK_

		Object *target = ObjectDB::get_instance(message->instance_id);

		if (target != NULL) {

			//query
			//call
			//_call_function(target, message->target, args, message->args, message->type & FLAG_SHOW_ERROR);
		}

		message->~QueryData();

		_THREAD_SAFE_LOCK_
	}

	_buffer_end = 0; // reset buffer
	_flushing = false;

	_THREAD_SAFE_UNLOCK_
}

void ESSPhysicsQuery::_bind_methods() {
	ClassDB::bind_method(D_METHOD("queue_intersect_ray", "from", "to", "exclude", "collision_mask"), &ESSPhysicsQuery::queue_intersect_ray, DEFVAL(Array()));
}

ESSPhysicsQuery::ESSPhysicsQuery() {
	ERR_FAIL_COND_MSG(_instance != NULL, "ESSPhysicsQuery singleton already exist.");

	_instance = this;

	_flushing = false;

	_buffer_end = 0;
	_buffer_max_used = 0;

	_buffer_size = GLOBAL_DEF_RST("memory/limits/ess_physics_query_queue/max_size_kb", DEFAULT_QUEUE_SIZE_KB);
	ProjectSettings::get_singleton()->set_custom_property_info("memory/limits/ess_physics_query_queue/max_size_kb", PropertyInfo(Variant::INT, "memory/limits/message_queue/max_size_kb", PROPERTY_HINT_RANGE, "0,2048,1,or_greater"));

	_buffer_size *= 1024;
	_buffer = memnew_arr(uint8_t, _buffer_size);
}

ESSPhysicsQuery::~ESSPhysicsQuery() {
	uint32_t read_pos = 0;

	while (read_pos < _buffer_end) {

		QueryData *message = (QueryData *)&_buffer[read_pos];
		message->~QueryData();

		read_pos += sizeof(QueryData);
	}

	_instance = NULL;
	memdelete_arr(_buffer);
}
