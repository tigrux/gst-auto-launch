/* commands.c generated by valac 0.10.0, the Vala compiler
 * generated from commands.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <float.h>
#include <math.h>


#define TYPE_COMMAND (command_get_type ())

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
typedef struct _Command Command;
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _gst_event_unref0(var) ((var == NULL) ? NULL : (var = (gst_event_unref (var), NULL)))
#define _gst_structure_free0(var) ((var == NULL) ? NULL : (var = (gst_structure_free (var), NULL)))

typedef gint (*CommandFunc) (AutoPipeline* auto_pipeline, Task* task);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
};



GType command_get_type (void) G_GNUC_CONST;
GType auto_pipeline_get_type (void) G_GNUC_CONST;
GType task_get_type (void) G_GNUC_CONST;
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
gint command_play (AutoPipeline* auto_pipeline, Task* task);
static gint _command_play_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_pause (AutoPipeline* auto_pipeline, Task* task);
static gint _command_pause_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_ready (AutoPipeline* auto_pipeline, Task* task);
static gint _command_ready_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_null (AutoPipeline* auto_pipeline, Task* task);
static gint _command_null_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_eos (AutoPipeline* auto_pipeline, Task* task);
static gint _command_eos_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_quit (AutoPipeline* auto_pipeline, Task* task);
static gint _command_quit_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_set (AutoPipeline* auto_pipeline, Task* task);
static gint _command_set_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_seek (AutoPipeline* auto_pipeline, Task* task);
static gint _command_seek_command_func (AutoPipeline* auto_pipeline, Task* task);
gint command_navigation (AutoPipeline* auto_pipeline, Task* task);
static gint _command_navigation_command_func (AutoPipeline* auto_pipeline, Task* task);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
GValueArray* task_get_arguments (Task* self);
void auto_pipeline_send_eos (AutoPipeline* self);
void scanner_register_symbols (GScanner* scanner, guint scope);
static int _vala_strcmp0 (const char * str1, const char * str2);

const Command COMMANDS[11] = {{"play", "Change pipeline state to PLAYING", "", _command_play_command_func}, {"pause", "Change pipeline state to PAUSED", "", _command_pause_command_func}, {"ready", "Change pipeline state to READY", "", _command_ready_command_func}, {"stop", "Change pipeline state to READY", "", _command_ready_command_func}, {"null", "Change pipeline state to NULL", "", _command_null_command_func}, {"eos", "Send eos to the source elements", "", _command_eos_command_func}, {"quit", "Quit the event loop", "", _command_quit_command_func}, {"set", "Set properties of an object", "ssv", _command_set_command_func}, {"seek", "Seek to the specified time", "t", _command_seek_command_func}, {"navigation", "Send the specified navigation event name to an element in the given co" \
"ords", "ssii", _command_navigation_command_func}, {NULL}};


static gint _command_play_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_play (auto_pipeline, task);
	return result;
}


static gint _command_pause_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_pause (auto_pipeline, task);
	return result;
}


static gint _command_ready_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_ready (auto_pipeline, task);
	return result;
}


static gint _command_null_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_null (auto_pipeline, task);
	return result;
}


static gint _command_eos_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_eos (auto_pipeline, task);
	return result;
}


static gint _command_quit_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_quit (auto_pipeline, task);
	return result;
}


static gint _command_set_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_set (auto_pipeline, task);
	return result;
}


static gint _command_seek_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_seek (auto_pipeline, task);
	return result;
}


static gint _command_navigation_command_func (AutoPipeline* auto_pipeline, Task* task) {
	gint result;
	result = command_navigation (auto_pipeline, task);
	return result;
}


gint command_play (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GstStateChangeReturn status;
	gint _tmp0_ = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_print ("Passing to PLAYING\n");
	status = gst_element_set_state ((GstElement*) auto_pipeline_get_pipeline (auto_pipeline), GST_STATE_PLAYING);
	if (status != GST_STATE_CHANGE_FAILURE) {
		_tmp0_ = 0;
	} else {
		_tmp0_ = 1;
	}
	result = _tmp0_;
	return result;
}


gint command_pause (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GstStateChangeReturn status;
	gint _tmp0_ = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_print ("Passing to PAUSED\n");
	status = gst_element_set_state ((GstElement*) auto_pipeline_get_pipeline (auto_pipeline), GST_STATE_PAUSED);
	if (status != GST_STATE_CHANGE_FAILURE) {
		_tmp0_ = 0;
	} else {
		_tmp0_ = 1;
	}
	result = _tmp0_;
	return result;
}


gint command_ready (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GstStateChangeReturn status;
	gint _tmp0_ = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_print ("Passing to READY\n");
	status = gst_element_set_state ((GstElement*) auto_pipeline_get_pipeline (auto_pipeline), GST_STATE_READY);
	if (status != GST_STATE_CHANGE_FAILURE) {
		_tmp0_ = 0;
	} else {
		_tmp0_ = 1;
	}
	result = _tmp0_;
	return result;
}


gint command_null (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GstStateChangeReturn status;
	gint _tmp0_ = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_print ("Passing to NULL\n");
	status = gst_element_set_state ((GstElement*) auto_pipeline_get_pipeline (auto_pipeline), GST_STATE_NULL);
	if (status != GST_STATE_CHANGE_FAILURE) {
		_tmp0_ = 0;
	} else {
		_tmp0_ = 1;
	}
	result = _tmp0_;
	return result;
}


gint command_quit (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_print ("Quitting\n");
	g_signal_emit_by_name (auto_pipeline, "quit");
	result = 0;
	return result;
}


gint command_set (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GValue _tmp0_;
	char* element_name;
	GstElement* element;
	GValue _tmp1_;
	char* prop_name;
	GParamSpec* prop_spec;
	GType prop_type;
	GValue _tmp2_ = {0};
	GValue prop_value;
	GValue _tmp5_ = {0};
	GValue string_value;
	char* value_as_string;
	GValue converted_value = {0};
	char* _tmp6_;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	element_name = g_strdup (g_value_get_string ((_tmp0_ = task_get_arguments (task)->values[0], &_tmp0_)));
	element = gst_bin_get_by_name (auto_pipeline_get_pipeline (auto_pipeline), element_name);
	if (element == NULL) {
		g_printerr ("No element named '%s'\n", element_name);
		result = 1;
		_gst_object_unref0 (element);
		_g_free0 (element_name);
		return result;
	}
	prop_name = g_strdup (g_value_get_string ((_tmp1_ = task_get_arguments (task)->values[1], &_tmp1_)));
	prop_spec = g_object_class_find_property (G_OBJECT_GET_CLASS ((GObject*) element), prop_name);
	if (prop_spec == NULL) {
		g_printerr ("No property '%s' in element '%s'\n", prop_name, element_name);
		result = 1;
		_g_free0 (prop_name);
		_gst_object_unref0 (element);
		_g_free0 (element_name);
		return result;
	}
	prop_type = prop_spec->value_type;
	prop_value = G_IS_VALUE (&task_get_arguments (task)->values[2]) ? (g_value_init (&_tmp2_, G_VALUE_TYPE (&task_get_arguments (task)->values[2])), g_value_copy (&task_get_arguments (task)->values[2], &_tmp2_), _tmp2_) : task_get_arguments (task)->values[2];
	if (G_VALUE_HOLDS (&prop_value, G_TYPE_STRING)) {
		char* prop_string;
		prop_string = g_strdup (g_value_get_string (&prop_value));
		if (G_TYPE_IS_ENUM (prop_type)) {
			GEnumClass* enum_class;
			GEnumValue* enum_value;
			enum_class = (GEnumClass*) g_type_class_peek (prop_type);
			enum_value = g_enum_get_value_by_nick (enum_class, prop_string);
			if (enum_value != NULL) {
				GValue _tmp3_ = {0};
				GValue _tmp4_;
				prop_value = (_tmp4_ = (g_value_init (&_tmp3_, G_TYPE_INT), g_value_set_int (&_tmp3_, enum_value->value), _tmp3_), G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL, _tmp4_);
			} else {
				g_printerr ("'%s' is not a valid value for enum '%s'\n", prop_string, g_type_name (prop_type));
				result = 1;
				_g_free0 (prop_string);
				G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL;
				_g_free0 (prop_name);
				_gst_object_unref0 (element);
				_g_free0 (element_name);
				return result;
			}
		}
		_g_free0 (prop_string);
	}
	string_value = (g_value_init (&_tmp5_, G_TYPE_STRING), g_value_set_string (&_tmp5_, ""), _tmp5_);
	g_value_transform (&prop_value, &string_value);
	value_as_string = g_strdup (g_value_get_string (&string_value));
	g_value_init (&converted_value, prop_type);
	if (!g_param_value_convert (prop_spec, &prop_value, &converted_value, TRUE)) {
		g_print ("'%s' is not a valid value for property '%s' of type '%s'\n", value_as_string, prop_name, g_type_name (prop_type));
		result = 1;
		G_IS_VALUE (&converted_value) ? (g_value_unset (&converted_value), NULL) : NULL;
		_g_free0 (value_as_string);
		G_IS_VALUE (&string_value) ? (g_value_unset (&string_value), NULL) : NULL;
		G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL;
		_g_free0 (prop_name);
		_gst_object_unref0 (element);
		_g_free0 (element_name);
		return result;
	}
	g_print ("Setting property '%s' of element '%s' to '%s'\n", prop_name, _tmp6_ = gst_object_get_name ((GstObject*) element), value_as_string);
	_g_free0 (_tmp6_);
	g_object_set_property ((GObject*) element, prop_name, &converted_value);
	result = 0;
	G_IS_VALUE (&converted_value) ? (g_value_unset (&converted_value), NULL) : NULL;
	_g_free0 (value_as_string);
	G_IS_VALUE (&string_value) ? (g_value_unset (&string_value), NULL) : NULL;
	G_IS_VALUE (&prop_value) ? (g_value_unset (&prop_value), NULL) : NULL;
	_g_free0 (prop_name);
	_gst_object_unref0 (element);
	_g_free0 (element_name);
	return result;
}


static gpointer _gst_event_ref0 (gpointer self) {
	return self ? gst_event_ref (self) : NULL;
}


gint command_seek (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GValue position_value = {0};
	GValue _tmp0_;
	double position_seconds;
	gint64 position_useconds;
	GstEvent* seek_event;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	g_value_init (&position_value, G_TYPE_DOUBLE);
	g_value_transform ((_tmp0_ = task_get_arguments (task)->values[0], &_tmp0_), &position_value);
	position_seconds = g_value_get_double (&position_value);
	position_useconds = (gint64) (position_seconds * GST_SECOND);
	seek_event = gst_event_new_seek (1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, GST_SEEK_TYPE_SET, position_useconds, GST_SEEK_TYPE_NONE, (gint64) 0);
	g_print ("Seeking to second %lf\n", position_seconds);
	gst_element_send_event ((GstElement*) auto_pipeline_get_pipeline (auto_pipeline), _gst_event_ref0 (seek_event));
	result = 0;
	_gst_event_unref0 (seek_event);
	G_IS_VALUE (&position_value) ? (g_value_unset (&position_value), NULL) : NULL;
	return result;
}


gint command_eos (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	auto_pipeline_send_eos (auto_pipeline);
	result = 1;
	return result;
}


static gpointer _gst_structure_copy0 (gpointer self) {
	return self ? gst_structure_copy (self) : NULL;
}


gint command_navigation (AutoPipeline* auto_pipeline, Task* task) {
	gint result = 0;
	GValue _tmp0_;
	char* element_name;
	GValue _tmp1_;
	char* event_name;
	GValue _tmp2_;
	gint pointer_x;
	GValue _tmp3_;
	gint pointer_y;
	gint _tmp4_ = 0;
	gint button;
	GstElement* element;
	GstStructure* s;
	GstPad* src_pad;
	g_return_val_if_fail (auto_pipeline != NULL, 0);
	g_return_val_if_fail (task != NULL, 0);
	element_name = g_strdup (g_value_get_string ((_tmp0_ = task_get_arguments (task)->values[0], &_tmp0_)));
	event_name = g_strdup (g_value_get_string ((_tmp1_ = task_get_arguments (task)->values[1], &_tmp1_)));
	pointer_x = g_value_get_int ((_tmp2_ = task_get_arguments (task)->values[2], &_tmp2_));
	pointer_y = g_value_get_int ((_tmp3_ = task_get_arguments (task)->values[3], &_tmp3_));
	if (_vala_strcmp0 (event_name, "mouse-move") != 0) {
		_tmp4_ = 1;
	} else {
		_tmp4_ = 0;
	}
	button = _tmp4_;
	element = gst_bin_get_by_name (auto_pipeline_get_pipeline (auto_pipeline), element_name);
	if (element == NULL) {
		g_printerr ("No element named '%s'\n", element_name);
		result = 1;
		_gst_object_unref0 (element);
		_g_free0 (event_name);
		_g_free0 (element_name);
		return result;
	}
	s = gst_structure_new ("application/x-gst-navigation", "event", G_TYPE_STRING, event_name, "button", G_TYPE_INT, button, "pointer_x", G_TYPE_DOUBLE, (double) pointer_x, "pointer_y", G_TYPE_DOUBLE, (double) pointer_y, NULL, NULL);
	src_pad = gst_element_get_static_pad (element, "src");
	if (src_pad == NULL) {
		g_printerr ("No src pad in element %s", element_name);
		result = 1;
		_gst_object_unref0 (src_pad);
		_gst_structure_free0 (s);
		_gst_object_unref0 (element);
		_g_free0 (event_name);
		_g_free0 (element_name);
		return result;
	}
	gst_pad_send_event (src_pad, gst_event_new_navigation (_gst_structure_copy0 (s)));
	result = 0;
	_gst_object_unref0 (src_pad);
	_gst_structure_free0 (s);
	_gst_object_unref0 (element);
	_g_free0 (event_name);
	_g_free0 (element_name);
	return result;
}


void scanner_register_symbols (GScanner* scanner, guint scope) {
	g_return_if_fail (scanner != NULL);
	{
		gint i;
		i = 0;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				if (!_tmp0_) {
					i++;
				}
				_tmp0_ = FALSE;
				if (!(COMMANDS[i].name != NULL)) {
					break;
				}
				g_scanner_scope_add_symbol (scanner, scope, COMMANDS[i].name, &COMMANDS[i]);
			}
		}
	}
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




