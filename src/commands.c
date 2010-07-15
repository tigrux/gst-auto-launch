/* commands.c generated by valac, the Vala compiler
 * generated from commands.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <float.h>
#include <math.h>
#include <gst/base/gstbasesrc.h>


#define TYPE_AUTO_PIPELINE (auto_pipeline_get_type ())
#define AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUTO_PIPELINE, AutoPipeline))
#define AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUTO_PIPELINE, AutoPipelineClass))
#define IS_AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUTO_PIPELINE))
#define IS_AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUTO_PIPELINE))
#define AUTO_PIPELINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUTO_PIPELINE, AutoPipelineClass))

typedef struct _AutoPipeline AutoPipeline;
typedef struct _AutoPipelineClass AutoPipelineClass;

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;

#define TYPE_COMMAND (command_get_type ())
typedef struct _Command Command;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _gst_event_unref0(var) ((var == NULL) ? NULL : (var = (gst_event_unref (var), NULL)))
#define _gst_iterator_free0(var) ((var == NULL) ? NULL : (var = (gst_iterator_free (var), NULL)))

typedef void (*CommandFunc) (AutoPipeline* ctx, Task* task, void* user_data);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};



GType auto_pipeline_get_type (void) G_GNUC_CONST;
GType task_get_type (void) G_GNUC_CONST;
void command_play (AutoPipeline* ctx, Task* task);
static void _command_play_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_pause (AutoPipeline* ctx, Task* task);
static void _command_pause_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_ready (AutoPipeline* ctx, Task* task);
static void _command_ready_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_null (AutoPipeline* ctx, Task* task);
static void _command_null_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_eos (AutoPipeline* ctx, Task* task);
static void _command_eos_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_quit (AutoPipeline* ctx, Task* task);
static void _command_quit_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_set (AutoPipeline* ctx, Task* task);
static void _command_set_command_func (AutoPipeline* ctx, Task* task, gpointer self);
void command_seek (AutoPipeline* ctx, Task* task);
static void _command_seek_command_func (AutoPipeline* ctx, Task* task, gpointer self);
GType command_get_type (void) G_GNUC_CONST;
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
void auto_pipeline_set_state (AutoPipeline* self, GstState value);
GValueArray* task_get_arguments (Task* self);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
static void _lambda2_ (void* data);
static void __lambda2__gfunc (void* data, gpointer self);
void scanner_register_symbols (GScanner* scanner, guint scope);

const Command COMMANDS[10] = {{"play", "Change pipeline state to PLAYING", "", _command_play_command_func}, {"pause", "Change pipeline state to PAUSED", "", _command_pause_command_func}, {"ready", "Change pipeline state to READY", "", _command_ready_command_func}, {"stop", "Change pipeline state to READY", "", _command_ready_command_func}, {"null", "Change pipeline state to NULL", "", _command_null_command_func}, {"eos", "Send eos to the source elements", "", _command_eos_command_func}, {"quit", "Quit the event loop", "", _command_quit_command_func}, {"set", "Set properties of an object", "ssv", _command_set_command_func}, {"seek", "Seek to the specified time", "t", _command_seek_command_func}, {NULL}};


static void _command_play_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_play (ctx, task);
}


static void _command_pause_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_pause (ctx, task);
}


static void _command_ready_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_ready (ctx, task);
}


static void _command_null_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_null (ctx, task);
}


static void _command_eos_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_eos (ctx, task);
}


static void _command_quit_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_quit (ctx, task);
}


static void _command_set_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_set (ctx, task);
}


static void _command_seek_command_func (AutoPipeline* ctx, Task* task, gpointer self) {
	command_seek (ctx, task);
}


void command_play (AutoPipeline* ctx, Task* task) {
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	auto_pipeline_set_state (ctx, GST_STATE_PLAYING);
}


void command_pause (AutoPipeline* ctx, Task* task) {
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	auto_pipeline_set_state (ctx, GST_STATE_PAUSED);
}


void command_ready (AutoPipeline* ctx, Task* task) {
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	auto_pipeline_set_state (ctx, GST_STATE_READY);
}


void command_null (AutoPipeline* ctx, Task* task) {
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	auto_pipeline_set_state (ctx, GST_STATE_NULL);
}


void command_quit (AutoPipeline* ctx, Task* task) {
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	g_signal_emit_by_name (ctx, "quit");
}


void command_set (AutoPipeline* ctx, Task* task) {
	GValue _tmp0_;
	GValue _tmp1_;
	char* element_name;
	GValue _tmp2_;
	GValue _tmp3_;
	char* prop_name;
	GstElement* element;
	GValue _tmp4_ = {0};
	GValue prop_value;
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	if (task_get_arguments (task)->n_values != 3) {
		g_printerr ("Command 'set' takes exactly 3 arguments (got %u)\n", task_get_arguments (task)->n_values);
		return;
	}
	if (!G_VALUE_HOLDS ((_tmp0_ = task_get_arguments (task)->values[0], &_tmp0_), G_TYPE_STRING)) {
		g_printerr ("Element name (arg 0) for command 'set' must be a string\n");
		return;
	}
	element_name = g_strdup (g_value_get_string ((_tmp1_ = task_get_arguments (task)->values[0], &_tmp1_)));
	if (!G_VALUE_HOLDS ((_tmp2_ = task_get_arguments (task)->values[1], &_tmp2_), G_TYPE_STRING)) {
		g_printerr ("Property name (arg 1) for command 'set' must be a string\n");
		_g_free0 (element_name);
		return;
	}
	prop_name = g_strdup (g_value_get_string ((_tmp3_ = task_get_arguments (task)->values[1], &_tmp3_)));
	element = gst_bin_get_by_name (auto_pipeline_get_pipeline (ctx), element_name);
	if (element == NULL) {
		g_printerr ("There is no element named '%s'\n", element_name);
		_gst_object_unref0 (element);
		_g_free0 (prop_name);
		_g_free0 (element_name);
		return;
	}
	prop_value = G_IS_VALUE (&task_get_arguments (task)->values[2]) ? (g_value_init (&_tmp4_, G_VALUE_TYPE (&task_get_arguments (task)->values[2])), g_value_copy (&task_get_arguments (task)->values[2], &_tmp4_), _tmp4_) : task_get_arguments (task)->values[2];
	if (G_VALUE_HOLDS (&prop_value, G_TYPE_STRING)) {
		GParamSpec* prop;
		prop = g_object_class_find_property (G_OBJECT_GET_CLASS ((GObject*) element), prop_name);
		if (prop != NULL) {
			GEnumClass* e_class;
			char* prop_string;
			GEnumValue* e_value;
			e_class = (GEnumClass*) g_type_class_peek (prop->value_type);
			prop_string = g_strdup (g_value_get_string (&prop_value));
			e_value = g_enum_get_value_by_name (e_class, prop_string);
			if (e_value != NULL) {
				GValue _tmp6_;
				GValue _tmp5_ = {0};
				prop_value = (_tmp6_ = (g_value_init (&_tmp5_, G_TYPE_INT), g_value_set_int (&_tmp5_, e_value->value), _tmp5_), G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL, _tmp6_);
			}
			_g_free0 (prop_string);
		}
	}
	g_object_set_property ((GObject*) element, prop_name, &prop_value);
	G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL;
	_gst_object_unref0 (element);
	_g_free0 (prop_name);
	_g_free0 (element_name);
}


static gpointer _gst_event_ref0 (gpointer self) {
	return self ? gst_event_ref (self) : NULL;
}


void command_seek (AutoPipeline* ctx, Task* task) {
	GValue position_value = {0};
	GValue _tmp0_;
	double position_seconds;
	gint64 position_useconds;
	GstEvent* seek_event;
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	if (task_get_arguments (task)->n_values != 1) {
		g_printerr ("Command 'seek' takes exactly 1 argument\n");
		return;
	}
	g_value_init (&position_value, G_TYPE_DOUBLE);
	g_value_transform ((_tmp0_ = task_get_arguments (task)->values[0], &_tmp0_), &position_value);
	position_seconds = g_value_get_double (&position_value);
	position_useconds = (gint64) (position_seconds * GST_SECOND);
	seek_event = gst_event_new_seek (1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, GST_SEEK_TYPE_SET, position_useconds, GST_SEEK_TYPE_NONE, (gint64) 0);
	gst_element_send_event ((GstElement*) auto_pipeline_get_pipeline (ctx), _gst_event_ref0 (seek_event));
	_gst_event_unref0 (seek_event);
	G_IS_VALUE (&position_value) ? (g_value_unset (&position_value), NULL) : NULL;
}


static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


static gboolean string_contains (const char* self, const char* needle) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (needle != NULL, FALSE);
	result = strstr (self, needle) != NULL;
	return result;
}


static void _lambda2_ (void* data) {
	void* _tmp0_;
	GstElement* elem;
	gboolean _tmp1_ = FALSE;
	elem = _gst_object_ref0 ((_tmp0_ = data, GST_IS_ELEMENT (_tmp0_) ? ((GstElement*) _tmp0_) : NULL));
	if (string_contains (gst_object_get_name ((GstObject*) elem), "src")) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = GST_IS_BASE_SRC (elem);
	}
	if (_tmp1_) {
		gst_element_send_event (elem, gst_event_new_eos ());
	}
	_gst_object_unref0 (elem);
}


static void __lambda2__gfunc (void* data, gpointer self) {
	_lambda2_ (data);
}


void command_eos (AutoPipeline* ctx, Task* task) {
	GstIterator* _tmp0_;
	g_return_if_fail (ctx != NULL);
	g_return_if_fail (task != NULL);
	gst_iterator_foreach (_tmp0_ = gst_bin_iterate_elements (auto_pipeline_get_pipeline (ctx)), __lambda2__gfunc, NULL);
	_gst_iterator_free0 (_tmp0_);
}


void scanner_register_symbols (GScanner* scanner, guint scope) {
	Command* command;
	g_return_if_fail (scanner != NULL);
	command = &COMMANDS[0];
	while (TRUE) {
		if (!((*command).name != NULL)) {
			break;
		}
		g_scanner_scope_add_symbol (scanner, scope, (*command).name, command);
		command++;
	}
}




