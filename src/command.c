/* command.c generated by valac, the Vala compiler
 * generated from command.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>


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

typedef void (*CommandFunc) (AutoPipeline* ctx, Task* task, void* user_data);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
	gpointer function_target;
	GDestroyNotify function_target_destroy_notify;
};



GType auto_pipeline_get_type (void);
GType task_get_type (void);
GType command_get_type (void);
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
gchar command_get_arg_desc (Command *self, guint arg_i);



static glong string_get_length (const char* self) {
	glong result;
	g_return_val_if_fail (self != NULL, 0L);
	result = g_utf8_strlen (self, -1);
	return result;
}


gchar command_get_arg_desc (Command *self, guint arg_i) {
	gchar result = '\0';
	gchar arg_desc;
	if (arg_i >= string_get_length ((*self).args_desc)) {
		result = (gchar) 0;
		return result;
	}
	arg_desc = ((gchar*) (*self).args_desc)[arg_i];
	result = arg_desc;
	return result;
}


void command_copy (const Command* self, Command* dest) {
	dest->name = g_strdup (self->name);
	dest->description = g_strdup (self->description);
	dest->args_desc = g_strdup (self->args_desc);
	dest->function = self->function;
}


void command_destroy (Command* self) {
	_g_free0 (self->name);
	_g_free0 (self->description);
	_g_free0 (self->args_desc);
	((*self).function_target_destroy_notify == NULL) ? NULL : ((*self).function_target_destroy_notify ((*self).function_target), NULL);
	self->function = NULL;
	(*self).function_target = NULL;
	(*self).function_target_destroy_notify = NULL;
}


Command* command_dup (const Command* self) {
	Command* dup;
	dup = g_new0 (Command, 1);
	command_copy (self, dup);
	return dup;
}


void command_free (Command* self) {
	command_destroy (self);
	g_free (self);
}


GType command_get_type (void) {
	static volatile gsize command_type_id__volatile = 0;
	if (g_once_init_enter (&command_type_id__volatile)) {
		GType command_type_id;
		command_type_id = g_boxed_type_register_static ("Command", (GBoxedCopyFunc) command_dup, (GBoxedFreeFunc) command_free);
		g_once_init_leave (&command_type_id__volatile, command_type_id);
	}
	return command_type_id__volatile;
}




