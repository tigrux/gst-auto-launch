/* task-scanner.c generated by valac 0.10.0, the Vala compiler
 * generated from task-scanner.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_TASK_SCANNER (task_scanner_get_type ())
#define TASK_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK_SCANNER, TaskScanner))
#define TASK_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK_SCANNER, TaskScannerClass))
#define IS_TASK_SCANNER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK_SCANNER))
#define IS_TASK_SCANNER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK_SCANNER))
#define TASK_SCANNER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK_SCANNER, TaskScannerClass))

typedef struct _TaskScanner TaskScanner;
typedef struct _TaskScannerClass TaskScannerClass;
typedef struct _TaskScannerPrivate TaskScannerPrivate;
#define _g_scanner_destroy0(var) ((var == NULL) ? NULL : (var = (g_scanner_destroy (var), NULL)))

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;

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
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _command_free0(var) ((var == NULL) ? NULL : (var = (command_free (var), NULL)))

struct _TaskScanner {
	GObject parent_instance;
	TaskScannerPrivate * priv;
};

struct _TaskScannerClass {
	GObjectClass parent_class;
};

struct _TaskScannerPrivate {
	GScanner* scanner;
	double last_time_seconds;
};

typedef void (*CommandFunc) (AutoPipeline* ctx, Task* task, void* user_data);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};


static gpointer task_scanner_parent_class = NULL;

GType task_scanner_get_type (void) G_GNUC_CONST;
#define TASK_SCANNER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_TASK_SCANNER, TaskScannerPrivate))
enum  {
	TASK_SCANNER_DUMMY_PROPERTY
};
TaskScanner* task_scanner_new (void);
TaskScanner* task_scanner_construct (GType object_type);
void scanner_register_symbols (GScanner* scanner, guint scope);
GType task_get_type (void) G_GNUC_CONST;
Task* task_scanner_get_task_from_arg (TaskScanner* self, const char* arg);
static double task_scanner_get_seconds (TaskScanner* self, GTokenType* last_token);
GType command_get_type (void) G_GNUC_CONST;
GType auto_pipeline_get_type (void) G_GNUC_CONST;
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
Task* task_new (double seconds, Command* command);
Task* task_construct (GType object_type, double seconds, Command* command);
gchar command_get_arg_desc (Command *self, guint arg_i);
GValueArray* task_get_arguments (Task* self);
static double task_scanner_get_signed_number (TaskScanner* self, GTokenType* last_token);
guint command_get_n_args (Command *self);
static double task_scanner_get_number (TaskScanner* self, GTokenType* last_token, gint* relative);
void task_scanner_print_description (TaskScanner* self);
static void _lambda3_ (void* key, void* val, TaskScanner* self);
static void __lambda3__gh_func (void* key, void* value, gpointer self);
Command* task_scanner_lookup_command (TaskScanner* self, const char* command_name);
static void task_scanner_finalize (GObject* obj);
static int _vala_strcmp0 (const char * str1, const char * str2);



TaskScanner* task_scanner_construct (GType object_type) {
	TaskScanner * self;
	GScanner* _tmp0_;
	self = (TaskScanner*) g_object_new (object_type, NULL);
	self->priv->last_time_seconds = (double) 0;
	self->priv->scanner = (_tmp0_ = g_scanner_new (NULL), _g_scanner_destroy0 (self->priv->scanner), _tmp0_);
	(*self->priv->scanner->config).scan_identifier_1char = TRUE;
	(*self->priv->scanner->config).identifier_2_string = TRUE;
	scanner_register_symbols (self->priv->scanner, (guint) 0);
	(*self->priv->scanner->config).cset_identifier_nth = G_CSET_a_2_z G_CSET_A_2_Z " _-0123456789" G_CSET_LATINC G_CSET_LATINS;
	return self;
}


TaskScanner* task_scanner_new (void) {
	return task_scanner_construct (TYPE_TASK_SCANNER);
}


static gboolean string_contains (const char* self, const char* needle) {
	gboolean result = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (needle != NULL, FALSE);
	result = strstr (self, needle) != NULL;
	return result;
}


static glong string_get_length (const char* self) {
	glong result;
	g_return_val_if_fail (self != NULL, 0L);
	result = g_utf8_strlen (self, (gssize) (-1));
	return result;
}


static gpointer _command_dup0 (gpointer self) {
	return self ? command_dup (self) : NULL;
}


Task* task_scanner_get_task_from_arg (TaskScanner* self, const char* arg) {
	Task* result = NULL;
	GTokenType token = 0;
	double number;
	gboolean _tmp0_ = FALSE;
	Command* command;
	Task* task;
	guint arg_n;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (arg != NULL, NULL);
	if (!string_contains (arg, ":")) {
		result = NULL;
		return result;
	}
	g_scanner_input_text (self->priv->scanner, arg, (guint) string_get_length (arg));
	number = task_scanner_get_seconds (self, &token);
	if (token != G_TOKEN_INT) {
		_tmp0_ = token != G_TOKEN_FLOAT;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		result = NULL;
		return result;
	}
	self->priv->last_time_seconds = number;
	token = g_scanner_get_next_token (self->priv->scanner);
	if (token != ':') {
		g_printerr ("Expected ':' between seconds and command\n");
		result = NULL;
		return result;
	}
	token = g_scanner_get_next_token (self->priv->scanner);
	if (token != G_TOKEN_SYMBOL) {
		g_printerr ("Expected a valid command\n");
		result = NULL;
		return result;
	}
	command = _command_dup0 ((Command*) self->priv->scanner->value.v_symbol);
	task = task_new (number, command);
	arg_n = (guint) 0;
	while (TRUE) {
		gchar arg_desc;
		if (!((token = g_scanner_get_next_token (self->priv->scanner)) == ':')) {
			break;
		}
		arg_desc = command_get_arg_desc (command, arg_n);
		token = g_scanner_peek_next_token (self->priv->scanner);
		if (token == G_TOKEN_STRING) {
			char* s;
			g_scanner_get_next_token (self->priv->scanner);
			s = g_strdup (self->priv->scanner->value.v_string);
			if (_vala_strcmp0 (s, "true") == 0) {
				GValue _tmp1_ = {0};
				GValue _tmp2_;
				g_value_array_append (task_get_arguments (task), (_tmp2_ = (g_value_init (&_tmp1_, G_TYPE_BOOLEAN), g_value_set_boolean (&_tmp1_, TRUE), _tmp1_), &_tmp2_));
				G_IS_VALUE (&_tmp1_) ? (g_value_unset (&_tmp1_), NULL) : NULL;
			} else {
				if (_vala_strcmp0 (s, "false") == 0) {
					GValue _tmp3_ = {0};
					GValue _tmp4_;
					g_value_array_append (task_get_arguments (task), (_tmp4_ = (g_value_init (&_tmp3_, G_TYPE_BOOLEAN), g_value_set_boolean (&_tmp3_, FALSE), _tmp3_), &_tmp4_));
					G_IS_VALUE (&_tmp3_) ? (g_value_unset (&_tmp3_), NULL) : NULL;
				} else {
					GValue _tmp5_ = {0};
					GValue _tmp6_;
					g_value_array_append (task_get_arguments (task), (_tmp6_ = (g_value_init (&_tmp5_, G_TYPE_STRING), g_value_set_string (&_tmp5_, s), _tmp5_), &_tmp6_));
					G_IS_VALUE (&_tmp5_) ? (g_value_unset (&_tmp5_), NULL) : NULL;
				}
			}
			_g_free0 (s);
		} else {
			gboolean _tmp7_ = FALSE;
			gboolean _tmp8_ = FALSE;
			gboolean _tmp9_ = FALSE;
			if (token == G_TOKEN_INT) {
				_tmp9_ = TRUE;
			} else {
				_tmp9_ = token == G_TOKEN_FLOAT;
			}
			if (_tmp9_) {
				_tmp8_ = TRUE;
			} else {
				_tmp8_ = token == '+';
			}
			if (_tmp8_) {
				_tmp7_ = TRUE;
			} else {
				_tmp7_ = token == '-';
			}
			if (_tmp7_) {
				if (arg_desc == 't') {
					GValue _tmp10_ = {0};
					GValue _tmp11_;
					number = task_scanner_get_seconds (self, &token);
					g_value_array_append (task_get_arguments (task), (_tmp11_ = (g_value_init (&_tmp10_, G_TYPE_DOUBLE), g_value_set_double (&_tmp10_, (double) number), _tmp10_), &_tmp11_));
					G_IS_VALUE (&_tmp10_) ? (g_value_unset (&_tmp10_), NULL) : NULL;
				} else {
					number = task_scanner_get_signed_number (self, &token);
					if (token == G_TOKEN_INT) {
						GValue _tmp12_ = {0};
						GValue _tmp13_;
						g_value_array_append (task_get_arguments (task), (_tmp13_ = (g_value_init (&_tmp12_, G_TYPE_INT), g_value_set_int (&_tmp12_, (gint) number), _tmp12_), &_tmp13_));
						G_IS_VALUE (&_tmp12_) ? (g_value_unset (&_tmp12_), NULL) : NULL;
					} else {
						if (token == G_TOKEN_FLOAT) {
							GValue _tmp14_ = {0};
							GValue _tmp15_;
							g_value_array_append (task_get_arguments (task), (_tmp15_ = (g_value_init (&_tmp14_, G_TYPE_DOUBLE), g_value_set_double (&_tmp14_, (double) number), _tmp14_), &_tmp15_));
							G_IS_VALUE (&_tmp14_) ? (g_value_unset (&_tmp14_), NULL) : NULL;
						}
					}
				}
			}
		}
		arg_n++;
	}
	if (command_get_n_args (command) != task_get_arguments (task)->n_values) {
		g_printerr ("Command '%s' takes %u arguments (got %u)\n", (*command).name, command_get_n_args (command), task_get_arguments (task)->n_values);
		result = NULL;
		_g_object_unref0 (task);
		_command_free0 (command);
		return result;
	}
	{
		guint arg_i;
		arg_i = (guint) 0;
		{
			gboolean _tmp16_;
			_tmp16_ = TRUE;
			while (TRUE) {
				gchar arg_desc;
				GValue _tmp17_ = {0};
				GValue arg_value;
				if (!_tmp16_) {
					arg_i++;
				}
				_tmp16_ = FALSE;
				if (!(arg_i < arg_n)) {
					break;
				}
				arg_desc = command_get_arg_desc (command, arg_i);
				arg_value = G_IS_VALUE (&task_get_arguments (task)->values[arg_i]) ? (g_value_init (&_tmp17_, G_VALUE_TYPE (&task_get_arguments (task)->values[arg_i])), g_value_copy (&task_get_arguments (task)->values[arg_i], &_tmp17_), _tmp17_) : task_get_arguments (task)->values[arg_i];
				switch (arg_desc) {
					case 's':
					{
						if (!G_VALUE_HOLDS (&arg_value, G_TYPE_STRING)) {
							g_printerr ("Argument %u of '%s' must be a string\n", arg_i, (*command).name);
							result = NULL;
							G_IS_VALUE (&arg_value) ? (g_value_unset (&arg_value), NULL) : NULL;
							_g_object_unref0 (task);
							_command_free0 (command);
							return result;
						}
						break;
					}
					case 'i':
					{
						if (!G_VALUE_HOLDS (&arg_value, G_TYPE_INT)) {
							g_printerr ("Argument %u of '%s' must be an integer\n", arg_i, (*command).name);
							result = NULL;
							G_IS_VALUE (&arg_value) ? (g_value_unset (&arg_value), NULL) : NULL;
							_g_object_unref0 (task);
							_command_free0 (command);
							return result;
						}
						break;
					}
					case 't':
					{
						if (!G_VALUE_HOLDS (&arg_value, G_TYPE_DOUBLE)) {
							g_printerr ("Argument %u of '%s' must be in seconds\n", arg_i, (*command).name);
							result = NULL;
							G_IS_VALUE (&arg_value) ? (g_value_unset (&arg_value), NULL) : NULL;
							_g_object_unref0 (task);
							_command_free0 (command);
							return result;
						}
						number = g_value_get_double (&arg_value);
						if (number < 0.0) {
							g_printerr ("Argument %u of '%s' cannot be negative\n", arg_i, (*command).name);
							result = NULL;
							G_IS_VALUE (&arg_value) ? (g_value_unset (&arg_value), NULL) : NULL;
							_g_object_unref0 (task);
							_command_free0 (command);
							return result;
						}
						break;
					}
				}
				G_IS_VALUE (&arg_value) ? (g_value_unset (&arg_value), NULL) : NULL;
			}
		}
	}
	result = task;
	_command_free0 (command);
	return result;
}


static double task_scanner_get_seconds (TaskScanner* self, GTokenType* last_token) {
	double result = 0.0;
	gint relative = 0;
	double seconds;
	g_return_val_if_fail (self != NULL, 0.0);
	seconds = task_scanner_get_number (self, last_token, &relative);
	if (relative != 0) {
		seconds = seconds + (relative * self->priv->last_time_seconds);
	}
	result = seconds;
	return result;
}


static double task_scanner_get_signed_number (TaskScanner* self, GTokenType* last_token) {
	double result = 0.0;
	gint relative = 0;
	double number;
	g_return_val_if_fail (self != NULL, 0.0);
	number = task_scanner_get_number (self, last_token, &relative);
	if (relative == (-1)) {
		result = -number;
		return result;
	}
	result = number;
	return result;
}


static double task_scanner_get_number (TaskScanner* self, GTokenType* last_token, gint* relative) {
	double result = 0.0;
	double number = 0.0;
	GTokenType token;
	g_return_val_if_fail (self != NULL, 0.0);
	token = g_scanner_get_next_token (self->priv->scanner);
	if (token == '+') {
		*relative = 1;
	} else {
		if (token == '-') {
			*relative = -1;
		} else {
			*relative = 0;
		}
	}
	if ((*relative) != 0) {
		token = g_scanner_get_next_token (self->priv->scanner);
	}
	if (token == G_TOKEN_INT) {
		number = (double) self->priv->scanner->value.v_int;
	} else {
		if (token == G_TOKEN_FLOAT) {
			number = self->priv->scanner->value.v_float;
		} else {
			number = (double) 0;
		}
	}
	*last_token = token;
	result = number;
	return result;
}


static void _lambda3_ (void* key, void* val, TaskScanner* self) {
	char* name;
	Command* command;
	name = g_strdup ((const char*) key);
	command = (Command*) val;
	g_printerr ("  %s:\n    %s\n", name, (*command).description);
	_g_free0 (name);
}


static void __lambda3__gh_func (void* key, void* value, gpointer self) {
	_lambda3_ (key, value, self);
}


void task_scanner_print_description (TaskScanner* self) {
	g_return_if_fail (self != NULL);
	g_scanner_scope_foreach_symbol (self->priv->scanner, (guint) 0, __lambda3__gh_func, self);
}


Command* task_scanner_lookup_command (TaskScanner* self, const char* command_name) {
	Command* result = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (command_name != NULL, NULL);
	result = _command_dup0 ((Command*) g_scanner_lookup_symbol (self->priv->scanner, command_name));
	return result;
}


static void task_scanner_class_init (TaskScannerClass * klass) {
	task_scanner_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (TaskScannerPrivate));
	G_OBJECT_CLASS (klass)->finalize = task_scanner_finalize;
}


static void task_scanner_instance_init (TaskScanner * self) {
	self->priv = TASK_SCANNER_GET_PRIVATE (self);
}


static void task_scanner_finalize (GObject* obj) {
	TaskScanner * self;
	self = TASK_SCANNER (obj);
	_g_scanner_destroy0 (self->priv->scanner);
	G_OBJECT_CLASS (task_scanner_parent_class)->finalize (obj);
}


GType task_scanner_get_type (void) {
	static volatile gsize task_scanner_type_id__volatile = 0;
	if (g_once_init_enter (&task_scanner_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (TaskScannerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) task_scanner_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TaskScanner), 0, (GInstanceInitFunc) task_scanner_instance_init, NULL };
		GType task_scanner_type_id;
		task_scanner_type_id = g_type_register_static (G_TYPE_OBJECT, "TaskScanner", &g_define_type_info, 0);
		g_once_init_leave (&task_scanner_type_id__volatile, task_scanner_type_id);
	}
	return task_scanner_type_id__volatile;
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




