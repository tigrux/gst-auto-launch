/* task.c generated by valac 0.10.0, the Vala compiler
 * generated from task.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;
typedef struct _TaskPrivate TaskPrivate;

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
#define _g_value_array_free0(var) ((var == NULL) ? NULL : (var = (g_value_array_free (var), NULL)))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
typedef struct _Block2Data Block2Data;

struct _Task {
	GObject parent_instance;
	TaskPrivate * priv;
};

struct _TaskClass {
	GObjectClass parent_class;
};

typedef gint (*CommandFunc) (AutoPipeline* auto_pipeline, Task* task);
struct _Command {
	char* name;
	char* description;
	char* args_desc;
	CommandFunc function;
};

struct _TaskPrivate {
	double _seconds;
	Command _command;
	GValueArray* _arguments;
};

struct _Block2Data {
	int _ref_count_;
	Task * self;
	AutoPipeline* auto_pipeline;
};


static gpointer task_parent_class = NULL;

GType task_get_type (void) G_GNUC_CONST;
GType command_get_type (void) G_GNUC_CONST;
GType auto_pipeline_get_type (void) G_GNUC_CONST;
Command* command_dup (const Command* self);
void command_free (Command* self);
void command_copy (const Command* self, Command* dest);
void command_destroy (Command* self);
#define TASK_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_TASK, TaskPrivate))
enum  {
	TASK_DUMMY_PROPERTY,
	TASK_SECONDS,
	TASK_ARGUMENTS
};
Task* task_new (double seconds, Command* command);
Task* task_construct (GType object_type, double seconds, Command* command);
guint task_exec (Task* self, AutoPipeline* auto_pipeline);
double task_get_seconds (Task* self);
static gboolean _lambda1_ (Block2Data* _data2_);
gint auto_pipeline_get_return_status (AutoPipeline* self);
void auto_pipeline_set_return_status (AutoPipeline* self, gint value);
static gboolean __lambda1__gsource_func (gpointer self);
static Block2Data* block2_data_ref (Block2Data* _data2_);
static void block2_data_unref (Block2Data* _data2_);
GValueArray* task_get_arguments (Task* self);
static void task_finalize (GObject* obj);
static void task_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);



Task* task_construct (GType object_type, double seconds, Command* command) {
	Task * self;
	Command _tmp0_ = {0};
	Command _tmp1_;
	GValueArray* _tmp2_;
	self = (Task*) g_object_new (object_type, NULL);
	self->priv->_seconds = seconds;
	self->priv->_command = (_tmp1_ = (command_copy (command, &_tmp0_), _tmp0_), command_destroy (&self->priv->_command), _tmp1_);
	self->priv->_arguments = (_tmp2_ = g_value_array_new ((guint) 0), _g_value_array_free0 (self->priv->_arguments), _tmp2_);
	return self;
}


Task* task_new (double seconds, Command* command) {
	return task_construct (TYPE_TASK, seconds, command);
}


static gboolean _lambda1_ (Block2Data* _data2_) {
	Task * self;
	gboolean result = FALSE;
	self = _data2_->self;
	if (auto_pipeline_get_return_status (_data2_->auto_pipeline) == 0) {
		gint status;
		status = self->priv->_command.function (_data2_->auto_pipeline, self);
		if (status != 0) {
			auto_pipeline_set_return_status (_data2_->auto_pipeline, status);
			g_signal_emit_by_name (_data2_->auto_pipeline, "quit");
		}
	}
	result = FALSE;
	return result;
}


static gboolean __lambda1__gsource_func (gpointer self) {
	gboolean result;
	result = _lambda1_ (self);
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static Block2Data* block2_data_ref (Block2Data* _data2_) {
	g_atomic_int_inc (&_data2_->_ref_count_);
	return _data2_;
}


static void block2_data_unref (Block2Data* _data2_) {
	if (g_atomic_int_dec_and_test (&_data2_->_ref_count_)) {
		_g_object_unref0 (_data2_->self);
		_g_object_unref0 (_data2_->auto_pipeline);
		g_slice_free (Block2Data, _data2_);
	}
}


guint task_exec (Task* self, AutoPipeline* auto_pipeline) {
	guint result = 0U;
	Block2Data* _data2_;
	g_return_val_if_fail (self != NULL, 0U);
	g_return_val_if_fail (auto_pipeline != NULL, 0U);
	_data2_ = g_slice_new0 (Block2Data);
	_data2_->_ref_count_ = 1;
	_data2_->self = g_object_ref (self);
	_data2_->auto_pipeline = _g_object_ref0 (auto_pipeline);
	result = g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) (task_get_seconds (self) * 1000), __lambda1__gsource_func, block2_data_ref (_data2_), block2_data_unref);
	block2_data_unref (_data2_);
	return result;
}


double task_get_seconds (Task* self) {
	double result;
	g_return_val_if_fail (self != NULL, 0.0);
	result = self->priv->_seconds;
	return result;
}


GValueArray* task_get_arguments (Task* self) {
	GValueArray* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_arguments;
	return result;
}


static void task_class_init (TaskClass * klass) {
	task_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (TaskPrivate));
	G_OBJECT_CLASS (klass)->get_property = task_get_property;
	G_OBJECT_CLASS (klass)->finalize = task_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), TASK_SECONDS, g_param_spec_double ("seconds", "seconds", "seconds", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), TASK_ARGUMENTS, g_param_spec_boxed ("arguments", "arguments", "arguments", G_TYPE_VALUE_ARRAY, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void task_instance_init (Task * self) {
	self->priv = TASK_GET_PRIVATE (self);
}


static void task_finalize (GObject* obj) {
	Task * self;
	self = TASK (obj);
	command_destroy (&self->priv->_command);
	_g_value_array_free0 (self->priv->_arguments);
	G_OBJECT_CLASS (task_parent_class)->finalize (obj);
}


GType task_get_type (void) {
	static volatile gsize task_type_id__volatile = 0;
	if (g_once_init_enter (&task_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (TaskClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) task_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Task), 0, (GInstanceInitFunc) task_instance_init, NULL };
		GType task_type_id;
		task_type_id = g_type_register_static (G_TYPE_OBJECT, "Task", &g_define_type_info, 0);
		g_once_init_leave (&task_type_id__volatile, task_type_id);
	}
	return task_type_id__volatile;
}


static void task_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	Task * self;
	self = TASK (object);
	switch (property_id) {
		case TASK_SECONDS:
		g_value_set_double (value, task_get_seconds (self));
		break;
		case TASK_ARGUMENTS:
		g_value_set_boxed (value, task_get_arguments (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




