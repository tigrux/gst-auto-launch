/* task-scanner.c generated by valac, the Vala compiler
 * generated from task-scanner.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef GScanner TaskScanner;

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_COMMAND (command_get_type ())

#define TYPE_AUTO_PIPELINE (auto_pipeline_get_type ())
#define AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUTO_PIPELINE, AutoPipeline))
#define AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUTO_PIPELINE, AutoPipelineClass))
#define IS_AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUTO_PIPELINE))
#define IS_AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUTO_PIPELINE))
#define AUTO_PIPELINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUTO_PIPELINE, AutoPipelineClass))

typedef struct _AutoPipeline AutoPipeline;
typedef struct _AutoPipelineClass AutoPipelineClass;
typedef struct _Command Command;
#define __g_list_free_g_free0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_free (var), NULL)))
#define __g_list_free_g_object_unref0(var) ((var == NULL) ? NULL : (var = (_g_list_free_g_object_unref (var), NULL)))

typedef void (*CommandFunc) (AutoPipeline* ctx, void* user_data);
struct _Command {
	char* name;
	char* description;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};



void scanner_register_symbols (GScanner* scanner, guint scope);
TaskScanner* task_scanner_new (void);
TaskScanner* task_scanner_new (void);
GType task_get_type (void);
GType command_get_type (void);
GType auto_pipeline_get_type (void);
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
Task* task_new (double seconds, Command* command);
Task* task_construct (GType object_type, double seconds, Command* command);
static void _g_list_free_g_free (GList* self);
static void _g_list_free_g_object_unref (GList* self);
GList* task_scanner_get_tasks_from_args (TaskScanner* self, char** args, int args_length1, char*** new_args, int* new_args_length1);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



TaskScanner* task_scanner_new (void) {
	TaskScanner* self;
	self = (TaskScanner*) g_scanner_new (NULL);
	(*((GScanner*) self)->config).scan_identifier_1char = FALSE;
	(*((GScanner*) self)->config).int_2_float = TRUE;
	scanner_register_symbols ((GScanner*) self, (guint) 0);
	return self;
}


static glong string_get_length (const char* self) {
	glong result;
	g_return_val_if_fail (self != NULL, 0L);
	result = g_utf8_strlen (self, -1);
	return result;
}


static void _g_list_free_g_free (GList* self) {
	g_list_foreach (self, (GFunc) g_free, NULL);
	g_list_free (self);
}


static void _g_list_free_g_object_unref (GList* self) {
	g_list_foreach (self, (GFunc) g_object_unref, NULL);
	g_list_free (self);
}


GList* task_scanner_get_tasks_from_args (TaskScanner* self, char** args, int args_length1, char*** new_args, int* new_args_length1) {
	GList* result = NULL;
	double last_time_seconds;
	GList* remaining_args;
	GList* tasks;
	char** _tmp1_;
	gint _tmp0_;
	guint i;
	g_return_val_if_fail (self != NULL, NULL);
	if (new_args != NULL) {
		*new_args = NULL;
	}
	last_time_seconds = (double) 0;
	remaining_args = NULL;
	tasks = NULL;
	{
		char** arg_collection;
		int arg_collection_length1;
		int arg_it;
		arg_collection = args;
		arg_collection_length1 = args_length1;
		for (arg_it = 0; arg_it < args_length1; arg_it = arg_it + 1) {
			char* arg;
			arg = g_strdup (arg_collection[arg_it]);
			{
				gint relative = 0;
				GTokenType tok_type;
				double seconds;
				Command* p_command;
				if (g_str_has_prefix (arg, "--")) {
					remaining_args = g_list_append (remaining_args, g_strdup (arg));
					_g_free0 (arg);
					continue;
				}
				g_scanner_input_text ((GScanner*) self, arg, (guint) string_get_length (arg));
				tok_type = g_scanner_peek_next_token ((GScanner*) self);
				if (tok_type == G_TOKEN_EOF) {
					_g_free0 (arg);
					break;
				}
				if (tok_type == '+') {
					relative = 1;
				} else {
					if (tok_type == '-') {
						relative = -1;
					} else {
						relative = 0;
					}
				}
				if (relative != 0) {
					g_scanner_get_next_token ((GScanner*) self);
				}
				if (g_scanner_peek_next_token ((GScanner*) self) != G_TOKEN_FLOAT) {
					remaining_args = g_list_append (remaining_args, g_strdup (arg));
					_g_free0 (arg);
					continue;
				}
				g_scanner_get_next_token ((GScanner*) self);
				seconds = ((GScanner*) self)->value.v_float;
				if (relative != 0) {
					seconds = last_time_seconds + (relative * seconds);
				}
				if (g_scanner_peek_next_token ((GScanner*) self) != ':') {
					remaining_args = g_list_append (remaining_args, g_strdup (arg));
					_g_free0 (arg);
					continue;
				}
				g_scanner_get_next_token ((GScanner*) self);
				if (g_scanner_peek_next_token ((GScanner*) self) != G_TOKEN_SYMBOL) {
					remaining_args = g_list_append (remaining_args, g_strdup (arg));
					_g_free0 (arg);
					continue;
				}
				g_scanner_get_next_token ((GScanner*) self);
				p_command = (Command*) ((GScanner*) self)->value.v_symbol;
				tasks = g_list_append (tasks, task_new (seconds, p_command));
				last_time_seconds = seconds;
				_g_free0 (arg);
			}
		}
	}
	*new_args = (_tmp1_ = g_new0 (char*, (_tmp0_ = g_list_length (remaining_args)) + 1), *new_args = (_vala_array_free (*new_args, *new_args_length1, (GDestroyNotify) g_free), NULL), *new_args_length1 = _tmp0_, _tmp1_);
	i = (guint) 0;
	{
		GList* arg_collection;
		GList* arg_it;
		arg_collection = remaining_args;
		for (arg_it = arg_collection; arg_it != NULL; arg_it = arg_it->next) {
			char* arg;
			arg = g_strdup ((const char*) arg_it->data);
			{
				char* _tmp2_;
				(*new_args)[i] = (_tmp2_ = g_strdup (arg), _g_free0 ((*new_args)[i]), _tmp2_);
				i++;
				_g_free0 (arg);
			}
		}
	}
	result = tasks;
	__g_list_free_g_free0 (remaining_args);
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




