/* auto-pipeline.c generated by valac, the Vala compiler
 * generated from auto-pipeline.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
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
typedef struct _AutoPipelinePrivate AutoPipelinePrivate;
typedef GScanner TaskScanner;
#define _g_scanner_destroy0(var) ((var == NULL) ? NULL : (var = (g_scanner_destroy (var), NULL)))
#define _g_timer_destroy0(var) ((var == NULL) ? NULL : (var = (g_timer_destroy (var), NULL)))
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_main_loop_unref0(var) ((var == NULL) ? NULL : (var = (g_main_loop_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_TASK (task_get_type ())
#define TASK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TASK, Task))
#define TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TASK, TaskClass))
#define IS_TASK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TASK))
#define IS_TASK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TASK))
#define TASK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TASK, TaskClass))

typedef struct _Task Task;
typedef struct _TaskClass TaskClass;

struct _AutoPipeline {
	GObject parent_instance;
	AutoPipelinePrivate * priv;
};

struct _AutoPipelineClass {
	GObjectClass parent_class;
};

struct _AutoPipelinePrivate {
	TaskScanner* _scanner;
	GTimer* _timer;
	GstBin* _pipeline;
	GMainLoop* _loop;
};


static gpointer auto_pipeline_parent_class = NULL;

GType auto_pipeline_get_type (void);
#define AUTO_PIPELINE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_AUTO_PIPELINE, AutoPipelinePrivate))
enum  {
	AUTO_PIPELINE_DUMMY_PROPERTY,
	AUTO_PIPELINE_STATE,
	AUTO_PIPELINE_PIPELINE,
	AUTO_PIPELINE_LOOP,
	AUTO_PIPELINE_SCANNER,
	AUTO_PIPELINE_TIMER
};
static void auto_pipeline_on_bus_message (AutoPipeline* self, GstMessage* message);
static void _auto_pipeline_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self);
void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error);
void auto_pipeline_set_state (AutoPipeline* self, GstState value);
GType task_get_type (void);
guint task_exec (Task* self, AutoPipeline* ctx);
guint auto_pipeline_exec_task (AutoPipeline* self, Task* task);
AutoPipeline* auto_pipeline_new (void);
AutoPipeline* auto_pipeline_construct (GType object_type);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
void auto_pipeline_set_pipeline (AutoPipeline* self, GstBin* value);
GMainLoop* auto_pipeline_get_loop (AutoPipeline* self);
void auto_pipeline_set_loop (AutoPipeline* self, GMainLoop* value);
TaskScanner* auto_pipeline_get_scanner (AutoPipeline* self);
GTimer* auto_pipeline_get_timer (AutoPipeline* self);
TaskScanner* task_scanner_new (void);
TaskScanner* task_scanner_new (void);
static GObject * auto_pipeline_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void auto_pipeline_finalize (GObject* obj);
static void auto_pipeline_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void auto_pipeline_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


static void _auto_pipeline_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self) {
	auto_pipeline_on_bus_message (self, message);
}


void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error) {
	GError * _inner_error_;
	GstElement* _tmp0_;
	GstBin* _tmp2_;
	GstElement* _tmp1_;
	GstBus* bus;
	g_return_if_fail (self != NULL);
	g_return_if_fail (description != NULL);
	_inner_error_ = NULL;
	_tmp0_ = gst_parse_launch (description, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	self->priv->_pipeline = (_tmp2_ = (_tmp1_ = _tmp0_, GST_IS_BIN (_tmp1_) ? ((GstBin*) _tmp1_) : NULL), _gst_object_unref0 (self->priv->_pipeline), _tmp2_);
	bus = _gst_object_ref0 (((GstElement*) self->priv->_pipeline)->bus);
	gst_bus_add_signal_watch (bus);
	g_signal_connect_object (bus, "message", (GCallback) _auto_pipeline_on_bus_message_gst_bus_message, self, 0);
	_gst_object_unref0 (bus);
}


static void auto_pipeline_on_bus_message (AutoPipeline* self, GstMessage* message) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	switch (message->type) {
		case GST_MESSAGE_ERROR:
		{
			{
				GError* e;
				char* s;
				char* _tmp3_;
				char* _tmp2_ = NULL;
				GError* _tmp1_;
				GError* _tmp0_ = NULL;
				e = NULL;
				s = NULL;
				(gst_message_parse_error (message, &_tmp0_, &_tmp2_), e = (_tmp1_ = _tmp0_, _g_error_free0 (e), _tmp1_));
				s = (_tmp3_ = _tmp2_, _g_free0 (s), _tmp3_);
				g_critical ("auto-pipeline.vala:59: Bus error: %s %s\n", e->message, s);
				_g_error_free0 (e);
				_g_free0 (s);
				break;
			}
		}
		case GST_MESSAGE_EOS:
		{
			{
				g_print ("Got eos\n");
				auto_pipeline_set_state (self, GST_STATE_NULL);
				g_main_loop_quit (self->priv->_loop);
				break;
			}
		}
		default:
		{
			break;
		}
	}
}


guint auto_pipeline_exec_task (AutoPipeline* self, Task* task) {
	guint result = 0U;
	g_return_val_if_fail (self != NULL, 0U);
	g_return_val_if_fail (task != NULL, 0U);
	result = task_exec (task, self);
	return result;
}


AutoPipeline* auto_pipeline_construct (GType object_type) {
	AutoPipeline * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


AutoPipeline* auto_pipeline_new (void) {
	return auto_pipeline_construct (TYPE_AUTO_PIPELINE);
}


void auto_pipeline_set_state (AutoPipeline* self, GstState value) {
	g_return_if_fail (self != NULL);
	gst_element_set_state ((GstElement*) self->priv->_pipeline, value);
	g_object_notify ((GObject *) self, "state");
}


GstBin* auto_pipeline_get_pipeline (AutoPipeline* self) {
	GstBin* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_pipeline;
	return result;
}


void auto_pipeline_set_pipeline (AutoPipeline* self, GstBin* value) {
	GstBin* _tmp0_;
	g_return_if_fail (self != NULL);
	self->priv->_pipeline = (_tmp0_ = _gst_object_ref0 (value), _gst_object_unref0 (self->priv->_pipeline), _tmp0_);
	g_object_notify ((GObject *) self, "pipeline");
}


GMainLoop* auto_pipeline_get_loop (AutoPipeline* self) {
	GMainLoop* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_loop;
	return result;
}


static gpointer _g_main_loop_ref0 (gpointer self) {
	return self ? g_main_loop_ref (self) : NULL;
}


void auto_pipeline_set_loop (AutoPipeline* self, GMainLoop* value) {
	GMainLoop* _tmp0_;
	g_return_if_fail (self != NULL);
	self->priv->_loop = (_tmp0_ = _g_main_loop_ref0 (value), _g_main_loop_unref0 (self->priv->_loop), _tmp0_);
	g_object_notify ((GObject *) self, "loop");
}


TaskScanner* auto_pipeline_get_scanner (AutoPipeline* self) {
	TaskScanner* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_scanner;
	return result;
}


GTimer* auto_pipeline_get_timer (AutoPipeline* self) {
	GTimer* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_timer;
	return result;
}


static GObject * auto_pipeline_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	AutoPipeline * self;
	parent_class = G_OBJECT_CLASS (auto_pipeline_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = AUTO_PIPELINE (obj);
	{
		GMainLoop* _tmp0_;
		TaskScanner* _tmp1_;
		GTimeVal current_tv = {0};
		GTimer* _tmp2_;
		self->priv->_loop = (_tmp0_ = g_main_loop_new (NULL, FALSE), _g_main_loop_unref0 (self->priv->_loop), _tmp0_);
		self->priv->_scanner = (_tmp1_ = task_scanner_new (), _g_scanner_destroy0 (self->priv->_scanner), _tmp1_);
		g_get_current_time (&current_tv);
		self->priv->_timer = (_tmp2_ = g_timer_new (), _g_timer_destroy0 (self->priv->_timer), _tmp2_);
	}
	return obj;
}


static void auto_pipeline_class_init (AutoPipelineClass * klass) {
	auto_pipeline_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (AutoPipelinePrivate));
	G_OBJECT_CLASS (klass)->get_property = auto_pipeline_get_property;
	G_OBJECT_CLASS (klass)->set_property = auto_pipeline_set_property;
	G_OBJECT_CLASS (klass)->constructor = auto_pipeline_constructor;
	G_OBJECT_CLASS (klass)->finalize = auto_pipeline_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_STATE, g_param_spec_enum ("state", "state", "state", GST_TYPE_STATE, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_PIPELINE, g_param_spec_object ("pipeline", "pipeline", "pipeline", GST_TYPE_BIN, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_LOOP, g_param_spec_pointer ("loop", "loop", "loop", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_SCANNER, g_param_spec_pointer ("scanner", "scanner", "scanner", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_TIMER, g_param_spec_pointer ("timer", "timer", "timer", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void auto_pipeline_instance_init (AutoPipeline * self) {
	self->priv = AUTO_PIPELINE_GET_PRIVATE (self);
}


static void auto_pipeline_finalize (GObject* obj) {
	AutoPipeline * self;
	self = AUTO_PIPELINE (obj);
	_g_scanner_destroy0 (self->priv->_scanner);
	_g_timer_destroy0 (self->priv->_timer);
	_gst_object_unref0 (self->priv->_pipeline);
	_g_main_loop_unref0 (self->priv->_loop);
	G_OBJECT_CLASS (auto_pipeline_parent_class)->finalize (obj);
}


GType auto_pipeline_get_type (void) {
	static volatile gsize auto_pipeline_type_id__volatile = 0;
	if (g_once_init_enter (&auto_pipeline_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (AutoPipelineClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) auto_pipeline_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (AutoPipeline), 0, (GInstanceInitFunc) auto_pipeline_instance_init, NULL };
		GType auto_pipeline_type_id;
		auto_pipeline_type_id = g_type_register_static (G_TYPE_OBJECT, "AutoPipeline", &g_define_type_info, 0);
		g_once_init_leave (&auto_pipeline_type_id__volatile, auto_pipeline_type_id);
	}
	return auto_pipeline_type_id__volatile;
}


static void auto_pipeline_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	AutoPipeline * self;
	self = AUTO_PIPELINE (object);
	switch (property_id) {
		case AUTO_PIPELINE_PIPELINE:
		g_value_set_object (value, auto_pipeline_get_pipeline (self));
		break;
		case AUTO_PIPELINE_LOOP:
		g_value_set_pointer (value, auto_pipeline_get_loop (self));
		break;
		case AUTO_PIPELINE_SCANNER:
		g_value_set_pointer (value, auto_pipeline_get_scanner (self));
		break;
		case AUTO_PIPELINE_TIMER:
		g_value_set_pointer (value, auto_pipeline_get_timer (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void auto_pipeline_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	AutoPipeline * self;
	self = AUTO_PIPELINE (object);
	switch (property_id) {
		case AUTO_PIPELINE_STATE:
		auto_pipeline_set_state (self, g_value_get_enum (value));
		break;
		case AUTO_PIPELINE_PIPELINE:
		auto_pipeline_set_pipeline (self, g_value_get_object (value));
		break;
		case AUTO_PIPELINE_LOOP:
		auto_pipeline_set_loop (self, g_value_get_pointer (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




