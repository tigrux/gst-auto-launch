/* gst-auto-launch.c generated by valac, the Vala compiler
 * generated from gst-auto-launch.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <glib/gstdio.h>


#define TYPE_AUTO_PIPELINE (auto_pipeline_get_type ())
#define AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUTO_PIPELINE, AutoPipeline))
#define AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUTO_PIPELINE, AutoPipelineClass))
#define IS_AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUTO_PIPELINE))
#define IS_AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUTO_PIPELINE))
#define AUTO_PIPELINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUTO_PIPELINE, AutoPipelineClass))

typedef struct _AutoPipeline AutoPipeline;
typedef struct _AutoPipelineClass AutoPipelineClass;

#define TYPE_COMMAND (command_get_type ())
typedef struct _Command Command;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define __g_list_free_g_object_unref0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_object_unref (var), NULL)))
#define __g_list_free_g_free0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_free (var), NULL)))

#define TYPE_XML_PARSER (xml_parser_get_type ())
#define XML_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_XML_PARSER, XmlParser))
#define XML_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_XML_PARSER, XmlParserClass))
#define IS_XML_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_XML_PARSER))
#define IS_XML_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_XML_PARSER))
#define XML_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_XML_PARSER, XmlParserClass))

typedef struct _XmlParser XmlParser;
typedef struct _XmlParserClass XmlParserClass;

typedef void (*CommandFunc) (AutoPipeline* ctx, void* user_data);
struct _Command {
	char* name;
	char* description;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};



AutoPipeline* auto_pipeline_new (void);
AutoPipeline* auto_pipeline_construct (GType object_type);
GType auto_pipeline_get_type (void);
GScanner* auto_pipeline_get_scanner (AutoPipeline* self);
GType command_get_type (void);
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
static void _lambda2_ (void* key, void* val);
static void __lambda2__gh_func (void* key, void* value, gpointer self);
GType task_get_type (void);
GList* auto_pipeline_parse_tasks_from_args (AutoPipeline* self, char** args, int args_length1, char*** new_args, int* new_args_length1);
gboolean try_to_get_desc_from_xml (char** args, int args_length1, char** pipeline_desc);
void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
void auto_pipeline_set_state (AutoPipeline* self, GstState value);
static void _g_list_free_g_object_unref (GList* self);
static void _g_list_free_g_free (GList* self);
GTimer* auto_pipeline_get_timer (AutoPipeline* self);
guint auto_pipeline_exec_task (AutoPipeline* self, Task* task);
GMainLoop* auto_pipeline_get_loop (AutoPipeline* self);
gint _main (char** args, int args_length1);
XmlParser* xml_parser_new (void);
XmlParser* xml_parser_construct (GType object_type);
GType xml_parser_get_type (void);
gboolean xml_parser_parse_file (XmlParser* self, const char* filename, GError** error);
char* xml_parser_get (XmlParser* self, const char* key);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



static void _lambda2_ (void* key, void* val) {
	char* name;
	Command* command;
	name = g_strdup ((const char*) key);
	command = (Command*) val;
	g_print ("  %s:\n    %s\n", name, (*command).description);
	_g_free0 (name);
}


static void __lambda2__gh_func (void* key, void* value, gpointer self) {
	_lambda2_ (key, value);
}


static gboolean string_contains (const char* self, const char* needle) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (needle != NULL, FALSE);
	result = strstr (self, needle) != NULL;
	return result;
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


static void _g_list_free_g_free (GList* self) {
	g_list_foreach (self, (GFunc) g_free, NULL);
	g_list_free (self);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


gint _main (char** args, int args_length1) {
	gint result;
	GError * _inner_error_;
	AutoPipeline* auto_pipeline;
	gint remaining_args_size;
	gint remaining_args_length1;
	char** remaining_args;
	GList* tasks;
	GList* effective_args_list;
	gboolean should_parse_xml;
	char* pipeline_desc;
	_inner_error_ = NULL;
	auto_pipeline = auto_pipeline_new ();
	if (args_length1 < 2) {
		g_print ("Usage: %s <pipelines.xml> <pipeline_id> <commands>\n", args[0]);
		g_print ("Where each command is of the form <seconds>:<name>\n");
		g_print ("Supported commands are:\n");
		g_scanner_scope_foreach_symbol (auto_pipeline_get_scanner (auto_pipeline), (guint) 0, __lambda2__gh_func, NULL);
		g_print ("\n" \
"If no xml file can be parsed, it will get the pipeline from the comman" \
"d line\n" \
"\n");
		g_print ("Examples:\n");
		g_print ("  %s pipelines.xml videotest 0:pause 1:play +5:eos\n", args[0]);
		g_print ("  %s videotestsrc ! autovideosink 0:pause 1:play +5:eos\n", args[0]);
		result = 1;
		_g_object_unref0 (auto_pipeline);
		return result;
	}
	remaining_args = (remaining_args_length1 = 0, NULL);
	tasks = auto_pipeline_parse_tasks_from_args (auto_pipeline, args, args_length1, &remaining_args, &remaining_args_length1);
	effective_args_list = NULL;
	{
		char** arg_collection;
		int arg_collection_length1;
		int arg_it;
		arg_collection = remaining_args;
		arg_collection_length1 = remaining_args_length1;
		for (arg_it = 0; arg_it < remaining_args_length1; arg_it = arg_it + 1) {
			char* arg;
			arg = g_strdup (arg_collection[arg_it]);
			{
				if (!g_str_has_prefix (arg, "-")) {
					effective_args_list = g_list_append (effective_args_list, g_strdup (arg));
				}
				_g_free0 (arg);
			}
		}
	}
	should_parse_xml = FALSE;
	if (g_list_length (effective_args_list) == 3) {
		if (!string_contains ((const char*) g_list_nth_data (effective_args_list, (guint) 2), "=")) {
			should_parse_xml = TRUE;
		}
	}
	pipeline_desc = NULL;
	if (should_parse_xml) {
		should_parse_xml = try_to_get_desc_from_xml (args, args_length1, &pipeline_desc);
		if (!should_parse_xml) {
			g_print ("Could get pipeline description from xml file\n");
		}
	}
	if (!should_parse_xml) {
		guint i;
		char** _tmp1_;
		gint effective_args_size;
		gint effective_args_length1;
		gint _tmp0_;
		char** effective_args;
		char* _tmp5_;
		char** _tmp4_ = NULL;
		gint _tmp3_;
		g_print ("Getting pipeline description from the command line\n");
		i = (guint) 0;
		effective_args = (_tmp1_ = g_new0 (char*, (_tmp0_ = g_list_length (effective_args_list)) + 1), effective_args_length1 = _tmp0_, effective_args_size = effective_args_length1, _tmp1_);
		{
			GList* arg_collection;
			GList* arg_it;
			arg_collection = effective_args_list;
			for (arg_it = arg_collection; arg_it != NULL; arg_it = arg_it->next) {
				char* arg;
				arg = g_strdup ((const char*) arg_it->data);
				{
					char* _tmp2_;
					effective_args[i] = (_tmp2_ = g_strdup (arg), _g_free0 (effective_args[i]), _tmp2_);
					i++;
					_g_free0 (arg);
				}
			}
		}
		pipeline_desc = (_tmp5_ = g_strjoinv (" ", (_tmp4_ = effective_args + 1, _tmp3_ = effective_args_length1 - 1, _tmp4_)), _g_free0 (pipeline_desc), _tmp5_);
		effective_args = (_vala_array_free (effective_args, effective_args_length1, (GDestroyNotify) g_free), NULL);
	}
	gst_init (&remaining_args_length1, &remaining_args);
	{
		g_print ("Pipeline to use is:\n%s\n\n", pipeline_desc);
		auto_pipeline_parse_launch (auto_pipeline, pipeline_desc, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
		}
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_print ("Error: %s\n", e->message);
			if (auto_pipeline_get_pipeline (auto_pipeline) != NULL) {
				auto_pipeline_set_state (auto_pipeline, GST_STATE_NULL);
			}
			result = 1;
			_g_error_free0 (e);
			_g_object_unref0 (auto_pipeline);
			remaining_args = (_vala_array_free (remaining_args, remaining_args_length1, (GDestroyNotify) g_free), NULL);
			__g_list_free_g_object_unref0 (tasks);
			__g_list_free_g_free0 (effective_args_list);
			_g_free0 (pipeline_desc);
			return result;
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		_g_object_unref0 (auto_pipeline);
		remaining_args = (_vala_array_free (remaining_args, remaining_args_length1, (GDestroyNotify) g_free), NULL);
		__g_list_free_g_object_unref0 (tasks);
		__g_list_free_g_free0 (effective_args_list);
		_g_free0 (pipeline_desc);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	g_timer_start (auto_pipeline_get_timer (auto_pipeline));
	{
		GList* task_collection;
		GList* task_it;
		task_collection = tasks;
		for (task_it = task_collection; task_it != NULL; task_it = task_it->next) {
			Task* task;
			task = _g_object_ref0 ((Task*) task_it->data);
			{
				auto_pipeline_exec_task (auto_pipeline, task);
				_g_object_unref0 (task);
			}
		}
	}
	g_main_loop_run (auto_pipeline_get_loop (auto_pipeline));
	auto_pipeline_set_state (auto_pipeline, GST_STATE_NULL);
	result = 0;
	_g_object_unref0 (auto_pipeline);
	remaining_args = (_vala_array_free (remaining_args, remaining_args_length1, (GDestroyNotify) g_free), NULL);
	__g_list_free_g_object_unref0 (tasks);
	__g_list_free_g_free0 (effective_args_list);
	_g_free0 (pipeline_desc);
	return result;
}


int main (int argc, char ** argv) {
	g_type_init ();
	return _main (argv, argc);
}


gboolean try_to_get_desc_from_xml (char** args, int args_length1, char** pipeline_desc) {
	gboolean result;
	GError * _inner_error_;
	char* xml_file;
	XmlParser* parser;
	gboolean parsed;
	char* pipeline_id;
	char* _tmp1_;
	g_return_val_if_fail (pipeline_desc != NULL, FALSE);
	_inner_error_ = NULL;
	xml_file = g_strdup (args[1]);
	if (!g_file_test (xml_file, G_FILE_TEST_IS_REGULAR)) {
		g_print ("'%s' is not a regular file\n", xml_file);
		result = FALSE;
		_g_free0 (xml_file);
		return result;
	}
	parser = xml_parser_new ();
	parsed = FALSE;
	{
		gboolean _tmp0_;
		_tmp0_ = xml_parser_parse_file (parser, xml_file, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
		parsed = _tmp0_;
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_print ("Error: %s\n", e->message);
			result = FALSE;
			_g_error_free0 (e);
			_g_free0 (xml_file);
			_g_object_unref0 (parser);
			return result;
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		_g_free0 (xml_file);
		_g_object_unref0 (parser);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	if (!parsed) {
		g_print ("Could not parse file '%s'\n", xml_file);
		result = FALSE;
		_g_free0 (xml_file);
		_g_object_unref0 (parser);
		return result;
	}
	pipeline_id = g_strdup (args[2]);
	*pipeline_desc = (_tmp1_ = xml_parser_get (parser, pipeline_id), _g_free0 (*pipeline_desc), _tmp1_);
	if ((*pipeline_desc) == NULL) {
		g_print ("No pipeline found for id '%s'\n", pipeline_id);
		result = FALSE;
		_g_free0 (xml_file);
		_g_object_unref0 (parser);
		_g_free0 (pipeline_id);
		return result;
	}
	g_print ("Getting pipeline description from file '%s'\n", xml_file);
	result = TRUE;
	_g_free0 (xml_file);
	_g_object_unref0 (parser);
	_g_free0 (pipeline_id);
	return result;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}




