/* gst-auto-launch.c generated by valac 0.10.0, the Vala compiler
 * generated from gst-auto-launch.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <signal.h>
#include <float.h>
#include <math.h>
#include <glib/gstdio.h>


#define TYPE_AUTO_PIPELINE (auto_pipeline_get_type ())
#define AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUTO_PIPELINE, AutoPipeline))
#define AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUTO_PIPELINE, AutoPipelineClass))
#define IS_AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUTO_PIPELINE))
#define IS_AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUTO_PIPELINE))
#define AUTO_PIPELINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUTO_PIPELINE, AutoPipelineClass))

typedef struct _AutoPipeline AutoPipeline;
typedef struct _AutoPipelineClass AutoPipelineClass;
#define _g_option_context_free0(var) ((var == NULL) ? NULL : (var = (g_option_context_free (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

#define TYPE_TASK_SCANNER (task_scanner_get_type ())
#define TASK_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK_SCANNER, TaskScanner))
#define TASK_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK_SCANNER, TaskScannerClass))
#define IS_TASK_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK_SCANNER))
#define IS_TASK_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK_SCANNER))
#define TASK_SCANNER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK_SCANNER, TaskScannerClass))

typedef struct _TaskScanner TaskScanner;
typedef struct _TaskScannerClass TaskScannerClass;
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;
#define __g_list_free_g_free0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_free (var), NULL)))
#define __g_list_free_g_object_unref0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_object_unref (var), NULL)))

#define TYPE_COMMAND (command_get_type ())
typedef struct _Command Command;
#define _command_free0(var) ((var == NULL) ? NULL : (var = (command_free (var), NULL)))
typedef struct _AutoPipelinePrivate AutoPipelinePrivate;
#define _g_main_loop_unref0(var) ((var == NULL) ? NULL : (var = (g_main_loop_unref (var), NULL)))

#define TYPE_XML_PARSER (xml_parser_get_type ())
#define XML_PARSER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_XML_PARSER, XmlParser))
#define XML_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_XML_PARSER, XmlParserClass))
#define IS_XML_PARSER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_XML_PARSER))
#define IS_XML_PARSER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_XML_PARSER))
#define XML_PARSER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_XML_PARSER, XmlParserClass))

typedef struct _XmlParser XmlParser;
typedef struct _XmlParserClass XmlParserClass;

typedef void (*CommandFunc) (AutoPipeline* auto_pipeline, Task* task, void* user_data);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};

struct _AutoPipeline {
	GObject parent_instance;
	AutoPipelinePrivate * priv;
	gint return_status;
};

struct _AutoPipelineClass {
	GObjectClass parent_class;
};


extern gboolean output_messages;
gboolean output_messages = FALSE;
extern gboolean force_eos;
gboolean force_eos = FALSE;
extern AutoPipeline* auto_pipeline;
AutoPipeline* auto_pipeline = NULL;
extern guint how_many_control_c_pressed;
guint how_many_control_c_pressed = (guint) 0;

GType auto_pipeline_get_type (void) G_GNUC_CONST;
void on_control_c (void);
void auto_pipeline_send_eos (AutoPipeline* self);
gint _vala_main (char** args, int args_length1);
AutoPipeline* auto_pipeline_new (void);
AutoPipeline* auto_pipeline_construct (GType object_type);
static void _on_control_c_sighandler_t (gint signal);
#define LOG_FILENAME "gst-auto-launch.log"
void auto_pipeline_set_output_messages_enabled (AutoPipeline* self, gboolean value);
void auto_pipeline_log (AutoPipeline* self, const char* format, ...);
TaskScanner* task_scanner_new (void);
TaskScanner* task_scanner_construct (GType object_type);
GType task_scanner_get_type (void) G_GNUC_CONST;
void task_scanner_print_description (TaskScanner* self);
GType task_get_type (void) G_GNUC_CONST;
Task* task_scanner_get_task_from_arg (TaskScanner* self, const char* arg);
static void _g_list_free_g_free (GList* self);
static void _g_list_free_g_object_unref (GList* self);
GType command_get_type (void) G_GNUC_CONST;
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
Command* task_scanner_lookup_command (TaskScanner* self, const char* command_name);
Task* task_new (double seconds, Command* command);
Task* task_construct (GType object_type, double seconds, Command* command);
gboolean try_to_get_desc_from_xml (char** args, int args_length1, char** pipeline_desc);
void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
void auto_pipeline_set_state (AutoPipeline* self, GstState value);
guint auto_pipeline_exec_task (AutoPipeline* self, Task* task);
static void _g_main_loop_quit_auto_pipeline_quit (AutoPipeline* _sender, gpointer self);
XmlParser* xml_parser_new (void);
XmlParser* xml_parser_construct (GType object_type);
GType xml_parser_get_type (void) G_GNUC_CONST;
gboolean xml_parser_parse_file (XmlParser* self, const char* filename, GError** error);
char* xml_parser_get (XmlParser* self, const char* key);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);

const GOptionEntry options[3] = {{"gst-messages", 'm', 0, G_OPTION_ARG_NONE, &output_messages, "Output messages", NULL}, {"eos-on-shutdown", 'e', 0, G_OPTION_ARG_NONE, &force_eos, "Force EOS on sources before shutting the pipeline down", NULL}, {NULL}};


void on_control_c (void) {
	if (auto_pipeline == NULL) {
		return;
	}
	if (how_many_control_c_pressed == 0) {
		auto_pipeline_send_eos (auto_pipeline);
	} else {
		g_signal_emit_by_name (auto_pipeline, "quit");
	}
	how_many_control_c_pressed++;
}


static void _on_control_c_sighandler_t (gint signal) {
	on_control_c ();
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _g_list_free_g_free (GList* self) {
	g_list_foreach (self, (GFunc) g_free, NULL);
	g_list_free (self);
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


static void _g_main_loop_quit_auto_pipeline_quit (AutoPipeline* _sender, gpointer self) {
	g_main_loop_quit (self);
}


gint _vala_main (char** args, int args_length1) {
	gint result = 0;
	GOptionContext* opt_context;
	AutoPipeline* _tmp1_;
	GTimeVal tv = {0};
	TaskScanner* scanner;
	GList* tasks;
	GList* effective_args_list;
	gboolean should_parse_xml;
	char* pipeline_desc;
	GMainLoop* loop;
	GError * _inner_error_ = NULL;
	opt_context = NULL;
	{
		GOptionContext* _tmp0_;
		opt_context = (_tmp0_ = g_option_context_new ("- Build pipelines and run commands on them"), _g_option_context_free0 (opt_context), _tmp0_);
		g_option_context_set_help_enabled (opt_context, TRUE);
		g_option_context_add_main_entries (opt_context, options, "messages");
		g_option_context_add_group (opt_context, gst_init_get_option_group ());
		g_option_context_parse (opt_context, &args_length1, &args, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_OPTION_ERROR) {
				goto __catch0_g_option_error;
			}
			_g_option_context_free0 (opt_context);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return 0;
		}
	}
	goto __finally0;
	__catch0_g_option_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_printerr ("Option parsing failed: %s\n", e->message);
			result = -1;
			_g_error_free0 (e);
			_g_option_context_free0 (opt_context);
			return result;
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		_g_option_context_free0 (opt_context);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	auto_pipeline = (_tmp1_ = auto_pipeline_new (), _g_object_unref0 (auto_pipeline), _tmp1_);
	if (force_eos) {
		signal (SIGINT, _on_control_c_sighandler_t);
	}
	if (output_messages) {
		g_printerr ("Logging message to '%s'\n", LOG_FILENAME);
		auto_pipeline_set_output_messages_enabled (auto_pipeline, output_messages);
	}
	if (output_messages) {
		GTimeVal _tmp2_ = {0};
		auto_pipeline_log (auto_pipeline, "{\n", NULL);
		tv = (g_get_current_time (&_tmp2_), _tmp2_);
		auto_pipeline_log (auto_pipeline, " 'start' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec, NULL);
	}
	scanner = task_scanner_new ();
	if (args_length1 < 2) {
		char* _tmp3_;
		g_printerr ("%s", _tmp3_ = g_option_context_get_help (opt_context, TRUE, NULL));
		_g_free0 (_tmp3_);
		g_printerr ("Commands are of the form <seconds>:<command>\n");
		g_printerr ("Supported commands are:\n");
		task_scanner_print_description (scanner);
		g_printerr ("\n" \
"If no xml file can be parsed, it will get the pipeline from the comman" \
"d line\n" \
"\n");
		g_printerr ("Examples:\n");
		g_printerr ("  %s pipelines.xml videotest 0:pause 1:play +5:eos\n", args[0]);
		g_printerr ("  %s videotestsrc ! autovideosink 0:pause 1:play +5:eos\n", args[0]);
		result = 1;
		_g_object_unref0 (scanner);
		_g_option_context_free0 (opt_context);
		return result;
	}
	tasks = NULL;
	effective_args_list = NULL;
	{
		gint _tmp4_;
		char** _tmp5_ = NULL;
		char** arg_collection;
		int arg_collection_length1;
		int arg_it;
		arg_collection = (_tmp5_ = args + 1, _tmp4_ = args_length1 - 1, _tmp5_);
		arg_collection_length1 = _tmp4_;
		for (arg_it = 0; arg_it < _tmp4_; arg_it = arg_it + 1) {
			char* arg;
			arg = g_strdup (arg_collection[arg_it]);
			{
				Task* task;
				task = task_scanner_get_task_from_arg (scanner, arg);
				if (task != NULL) {
					tasks = g_list_append (tasks, _g_object_ref0 (task));
				} else {
					if (!g_str_has_prefix (arg, "--")) {
						effective_args_list = g_list_append (effective_args_list, g_strdup (arg));
					} else {
						result = 1;
						_g_object_unref0 (task);
						_g_free0 (arg);
						__g_list_free_g_free0 (effective_args_list);
						__g_list_free_g_object_unref0 (tasks);
						_g_object_unref0 (scanner);
						_g_option_context_free0 (opt_context);
						return result;
					}
				}
				_g_object_unref0 (task);
				_g_free0 (arg);
			}
		}
	}
	if (g_list_length (tasks) == 0) {
		char* auto_symbol;
		Command* auto_command;
		auto_symbol = g_strdup ("play");
		g_printerr ("No commands given, will exec '%s' automatically\n", auto_symbol);
		auto_command = task_scanner_lookup_command (scanner, auto_symbol);
		if (auto_command != NULL) {
			Task* auto_task;
			auto_task = task_new ((double) 0, auto_command);
			tasks = g_list_append (tasks, _g_object_ref0 (auto_task));
			_g_object_unref0 (auto_task);
		} else {
			g_printerr ("Could not find a command named '%s'\n", auto_symbol);
		}
		_command_free0 (auto_command);
		_g_free0 (auto_symbol);
	}
	should_parse_xml = FALSE;
	if (g_list_length (effective_args_list) == 2) {
		should_parse_xml = TRUE;
	}
	pipeline_desc = NULL;
	if (should_parse_xml) {
		should_parse_xml = try_to_get_desc_from_xml (args, args_length1, &pipeline_desc);
		if (!should_parse_xml) {
			g_printerr ("Could not get pipeline description from xml file\n");
		}
	}
	if (!should_parse_xml) {
		guint i;
		gint effective_args_length1;
		gint _effective_args_size_;
		char** _tmp7_;
		gint _tmp6_;
		char** effective_args;
		char* _tmp9_;
		g_printerr ("Getting pipeline description from the command line\n");
		i = (guint) 0;
		effective_args = (_tmp7_ = g_new0 (char*, (_tmp6_ = g_list_length (effective_args_list)) + 1), effective_args_length1 = _tmp6_, _effective_args_size_ = effective_args_length1, _tmp7_);
		{
			GList* arg_collection;
			GList* arg_it;
			arg_collection = effective_args_list;
			for (arg_it = arg_collection; arg_it != NULL; arg_it = arg_it->next) {
				char* arg;
				arg = g_strdup ((const char*) arg_it->data);
				{
					char* _tmp8_;
					effective_args[i] = (_tmp8_ = g_strdup (arg), _g_free0 (effective_args[i]), _tmp8_);
					i++;
					_g_free0 (arg);
				}
			}
		}
		pipeline_desc = (_tmp9_ = g_strjoinv (" ", effective_args), _g_free0 (pipeline_desc), _tmp9_);
		effective_args = (_vala_array_free (effective_args, effective_args_length1, (GDestroyNotify) g_free), NULL);
	}
	{
		if (output_messages) {
			GTimeVal _tmp10_ = {0};
			tv = (g_get_current_time (&_tmp10_), _tmp10_);
			auto_pipeline_log (auto_pipeline, " 'description' : '%s',\n", pipeline_desc, NULL);
		}
		auto_pipeline_parse_launch (auto_pipeline, pipeline_desc, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch1_g_error;
		}
		if (output_messages) {
			GTimeVal _tmp11_ = {0};
			tv = (g_get_current_time (&_tmp11_), _tmp11_);
			auto_pipeline_log (auto_pipeline, " 'launch' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec, NULL);
		}
	}
	goto __finally1;
	__catch1_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_printerr ("Error: %s\n", e->message);
			if (auto_pipeline_get_pipeline (auto_pipeline) != NULL) {
				auto_pipeline_set_state (auto_pipeline, GST_STATE_NULL);
			}
			result = 1;
			_g_error_free0 (e);
			_g_free0 (pipeline_desc);
			__g_list_free_g_free0 (effective_args_list);
			__g_list_free_g_object_unref0 (tasks);
			_g_object_unref0 (scanner);
			_g_option_context_free0 (opt_context);
			return result;
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		_g_free0 (pipeline_desc);
		__g_list_free_g_free0 (effective_args_list);
		__g_list_free_g_object_unref0 (tasks);
		_g_object_unref0 (scanner);
		_g_option_context_free0 (opt_context);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
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
	loop = g_main_loop_new (NULL, FALSE);
	g_signal_connect (auto_pipeline, "quit", (GCallback) _g_main_loop_quit_auto_pipeline_quit, loop);
	if (output_messages) {
		auto_pipeline_log (auto_pipeline, " 'message' : [\n", NULL);
	}
	g_main_loop_run (loop);
	if (output_messages) {
		auto_pipeline_log (auto_pipeline, " ],\n", NULL);
	}
	auto_pipeline_set_state (auto_pipeline, GST_STATE_NULL);
	if (output_messages) {
		GTimeVal _tmp12_ = {0};
		tv = (g_get_current_time (&_tmp12_), _tmp12_);
		auto_pipeline_log (auto_pipeline, " 'end' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec, NULL);
		auto_pipeline_log (auto_pipeline, "}\n", NULL);
	}
	result = auto_pipeline->return_status;
	_g_main_loop_unref0 (loop);
	_g_free0 (pipeline_desc);
	__g_list_free_g_free0 (effective_args_list);
	__g_list_free_g_object_unref0 (tasks);
	_g_object_unref0 (scanner);
	_g_option_context_free0 (opt_context);
	return result;
}


int main (int argc, char ** argv) {
	g_thread_init (NULL);
	g_type_init ();
	return _vala_main (argv, argc);
}


gboolean try_to_get_desc_from_xml (char** args, int args_length1, char** pipeline_desc) {
	gboolean result = FALSE;
	char* xml_file;
	XmlParser* parser;
	gboolean parsed;
	char* pipeline_id;
	char* _tmp1_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (pipeline_desc != NULL, FALSE);
	xml_file = g_strdup (args[1]);
	if (!g_file_test (xml_file, G_FILE_TEST_IS_REGULAR)) {
		g_printerr ("'%s' is not a regular file\n", xml_file);
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
			goto __catch2_g_error;
		}
		parsed = _tmp0_;
	}
	goto __finally2;
	__catch2_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_printerr ("Error: %s\n", e->message);
			result = FALSE;
			_g_error_free0 (e);
			_g_object_unref0 (parser);
			_g_free0 (xml_file);
			return result;
		}
	}
	__finally2:
	if (_inner_error_ != NULL) {
		_g_object_unref0 (parser);
		_g_free0 (xml_file);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	if (!parsed) {
		g_printerr ("Could not parse file '%s'\n", xml_file);
		result = FALSE;
		_g_object_unref0 (parser);
		_g_free0 (xml_file);
		return result;
	}
	pipeline_id = g_strdup (args[2]);
	*pipeline_desc = (_tmp1_ = xml_parser_get (parser, pipeline_id), _g_free0 (*pipeline_desc), _tmp1_);
	if ((*pipeline_desc) == NULL) {
		g_printerr ("No pipeline found for id '%s'\n", pipeline_id);
		result = FALSE;
		_g_free0 (pipeline_id);
		_g_object_unref0 (parser);
		_g_free0 (xml_file);
		return result;
	}
	g_printerr ("Getting pipeline description from file '%s'\n", xml_file);
	result = TRUE;
	_g_free0 (pipeline_id);
	_g_object_unref0 (parser);
	_g_free0 (xml_file);
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




