/* auto-pipeline.c generated by valac 0.10.0, the Vala compiler
 * generated from auto-pipeline.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <gst/gst.h>


#define TYPE_AUTO_PIPELINE (auto_pipeline_get_type ())
#define AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUTO_PIPELINE, AutoPipeline))
#define AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUTO_PIPELINE, AutoPipelineClass))
#define IS_AUTO_PIPELINE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUTO_PIPELINE))
#define IS_AUTO_PIPELINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUTO_PIPELINE))
#define AUTO_PIPELINE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUTO_PIPELINE, AutoPipelineClass))

typedef struct _AutoPipeline AutoPipeline;
typedef struct _AutoPipelineClass AutoPipelineClass;
typedef struct _AutoPipelinePrivate AutoPipelinePrivate;
#define _fclose0(var) ((var == NULL) ? NULL : (var = (fclose (var), NULL)))
#define _gst_object_unref0(var) ((var == NULL) ? NULL : (var = (gst_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _gst_structure_free0(var) ((var == NULL) ? NULL : (var = (gst_structure_free (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

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
	FILE* log_stream;
	gboolean _print_messages_enabled;
	GstBin* _pipeline;
};


static gpointer auto_pipeline_parent_class = NULL;

#define LOG_FILENAME "gst-auto-launch.log"
gint vprintf (const char* format, va_list ap);
gint vfprintf (FILE* stream, const char* format, va_list ap);
GType auto_pipeline_get_type (void) G_GNUC_CONST;
#define AUTO_PIPELINE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_AUTO_PIPELINE, AutoPipelinePrivate))
enum  {
	AUTO_PIPELINE_DUMMY_PROPERTY,
	AUTO_PIPELINE_PRINT_MESSAGES_ENABLED,
	AUTO_PIPELINE_STATE,
	AUTO_PIPELINE_PIPELINE
};
void auto_pipeline_log (AutoPipeline* self, const char* format, ...);
void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error);
static void auto_pipeline_on_bus_message (AutoPipeline* self, GstMessage* message);
static void _auto_pipeline_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self);
static gboolean _lambda0_ (GQuark q, GValue* v, AutoPipeline* self);
static gboolean __lambda0__gst_structure_foreach_func (GQuark field_id, GValue* value, gpointer self);
void auto_pipeline_set_state (AutoPipeline* self, GstState value);
GType task_get_type (void) G_GNUC_CONST;
guint auto_pipeline_exec_task (AutoPipeline* self, Task* task);
guint task_exec (Task* self, AutoPipeline* ctx);
AutoPipeline* auto_pipeline_new (void);
AutoPipeline* auto_pipeline_construct (GType object_type);
gboolean auto_pipeline_get_print_messages_enabled (AutoPipeline* self);
void auto_pipeline_set_print_messages_enabled (AutoPipeline* self, gboolean value);
GstBin* auto_pipeline_get_pipeline (AutoPipeline* self);
void auto_pipeline_set_pipeline (AutoPipeline* self, GstBin* value);
static void auto_pipeline_finalize (GObject* obj);
static void auto_pipeline_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void auto_pipeline_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



void auto_pipeline_log (AutoPipeline* self, const char* format, ...) {
	va_list args_vl;
	g_return_if_fail (self != NULL);
	g_return_if_fail (format != NULL);
	va_start (args_vl, format);
	if (self->priv->log_stream != NULL) {
		vfprintf (self->priv->log_stream, format, args_vl);
	}
	vprintf (format, args_vl);
	va_end (args_vl);
}


static gpointer _gst_object_ref0 (gpointer self) {
	return self ? gst_object_ref (self) : NULL;
}


static void _auto_pipeline_on_bus_message_gst_bus_message (GstBus* _sender, GstMessage* message, gpointer self) {
	auto_pipeline_on_bus_message (self, message);
}


void auto_pipeline_parse_launch (AutoPipeline* self, const char* description, GError** error) {
	GstElement* _tmp0_;
	GstElement* _tmp1_;
	GstBin* _tmp2_;
	GstBus* bus;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (description != NULL);
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


static gpointer _gst_structure_copy0 (gpointer self) {
	return self ? gst_structure_copy (self) : NULL;
}


static gboolean _lambda0_ (GQuark q, GValue* v, AutoPipeline* self) {
	gboolean result = FALSE;
	GValue _tmp0_ = {0};
	GValue vs;
	vs = (g_value_init (&_tmp0_, G_TYPE_STRING), g_value_set_string (&_tmp0_, ""), _tmp0_);
	g_value_transform (v, &vs);
	auto_pipeline_log (self, "    '%s' : '''%s''',\n", g_quark_to_string (q), g_value_get_string (&vs), NULL);
	result = TRUE;
	G_IS_VALUE (&vs) ? (g_value_unset (&vs), NULL) : NULL;
	return result;
}


static gboolean __lambda0__gst_structure_foreach_func (GQuark field_id, GValue* value, gpointer self) {
	gboolean result;
	result = _lambda0_ (field_id, value, self);
	return result;
}


static void auto_pipeline_on_bus_message (AutoPipeline* self, GstMessage* message) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (message != NULL);
	if (self->priv->_print_messages_enabled) {
		guint32 seqnum;
		GstObject* src;
		GstStructure* s;
		char* src_name;
		GTimeVal tv = {0};
		seqnum = gst_message_get_seqnum (message);
		src = _gst_object_ref0 (message->src);
		s = _gst_structure_copy0 (gst_message_get_structure (message));
		src_name = NULL;
		if (GST_IS_ELEMENT (src)) {
			char* _tmp0_;
			src_name = (_tmp0_ = g_strdup (gst_object_get_name (src)), _g_free0 (src_name), _tmp0_);
		} else {
			if (GST_IS_PAD (src)) {
				GstPad* pad;
				char* pad_name;
				GstElement* _tmp1_;
				char* _tmp2_;
				char* parent_name;
				char* _tmp3_;
				pad = _gst_object_ref0 (GST_PAD (src));
				pad_name = g_strdup (gst_object_get_name ((GstObject*) pad));
				parent_name = (_tmp2_ = g_strdup (gst_object_get_name ((GstObject*) (_tmp1_ = gst_pad_get_parent_element (pad)))), _gst_object_unref0 (_tmp1_), _tmp2_);
				src_name = (_tmp3_ = g_strdup_printf ("%s:%s", parent_name, pad_name), _g_free0 (src_name), _tmp3_);
				_g_free0 (parent_name);
				_g_free0 (pad_name);
				_gst_object_unref0 (pad);
			} else {
				if (GST_IS_OBJECT (src)) {
					char* _tmp4_;
					src_name = (_tmp4_ = g_strdup (gst_object_get_name (src)), _g_free0 (src_name), _tmp4_);
				}
			}
		}
		auto_pipeline_log (self, "  {\n", NULL);
		auto_pipeline_log (self, "   'seqnum' : %u,\n", seqnum, NULL);
		auto_pipeline_log (self, "   'type' : '%s',\n", gst_message_type_get_name (message->type), NULL);
		g_get_current_time (&tv);
		auto_pipeline_log (self, "   'time' : %lu.%06lu,\n", tv.tv_sec, tv.tv_usec, NULL);
		if (src_name != NULL) {
			auto_pipeline_log (self, "   'src' : '%s',\n", src_name, NULL);
		}
		if (s != NULL) {
			auto_pipeline_log (self, "   'structure' : {\n", NULL);
			auto_pipeline_log (self, "    'name' : '%s',\n", gst_structure_get_name (s), NULL);
			gst_structure_foreach (s, __lambda0__gst_structure_foreach_func, self);
			auto_pipeline_log (self, "   }\n", NULL);
		}
		auto_pipeline_log (self, "  },\n", NULL);
		_g_free0 (src_name);
		_gst_structure_free0 (s);
		_gst_object_unref0 (src);
	}
	switch (message->type) {
		case GST_MESSAGE_ERROR:
		{
			{
				GError* e;
				char* s;
				GError* _tmp5_ = NULL;
				GError* _tmp6_;
				char* _tmp7_ = NULL;
				char* _tmp8_;
				e = NULL;
				s = NULL;
				(gst_message_parse_error (message, &_tmp5_, &_tmp7_), e = (_tmp6_ = _tmp5_, _g_error_free0 (e), _tmp6_));
				s = (_tmp8_ = _tmp7_, _g_free0 (s), _tmp8_);
				g_critical ("auto-pipeline.vala:102: Bus error: %s %s\n", e->message, s);
				_g_free0 (s);
				_g_error_free0 (e);
				break;
			}
		}
		case GST_MESSAGE_EOS:
		{
			{
				auto_pipeline_set_state (self, GST_STATE_NULL);
				g_signal_emit_by_name (self, "quit");
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
	self = (AutoPipeline*) g_object_new (object_type, NULL);
	return self;
}


AutoPipeline* auto_pipeline_new (void) {
	return auto_pipeline_construct (TYPE_AUTO_PIPELINE);
}


gboolean auto_pipeline_get_print_messages_enabled (AutoPipeline* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_print_messages_enabled;
	return result;
}


void auto_pipeline_set_print_messages_enabled (AutoPipeline* self, gboolean value) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	if (!self->priv->_print_messages_enabled) {
		_tmp0_ = value;
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		FILE* _tmp1_;
		self->priv->log_stream = (_tmp1_ = fopen (LOG_FILENAME, "w"), _fclose0 (self->priv->log_stream), _tmp1_);
	}
	self->priv->_print_messages_enabled = value;
	g_object_notify ((GObject *) self, "print-messages-enabled");
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


static void auto_pipeline_class_init (AutoPipelineClass * klass) {
	auto_pipeline_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (AutoPipelinePrivate));
	G_OBJECT_CLASS (klass)->get_property = auto_pipeline_get_property;
	G_OBJECT_CLASS (klass)->set_property = auto_pipeline_set_property;
	G_OBJECT_CLASS (klass)->finalize = auto_pipeline_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_PRINT_MESSAGES_ENABLED, g_param_spec_boolean ("print-messages-enabled", "print-messages-enabled", "print-messages-enabled", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_STATE, g_param_spec_enum ("state", "state", "state", GST_TYPE_STATE, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUTO_PIPELINE_PIPELINE, g_param_spec_object ("pipeline", "pipeline", "pipeline", GST_TYPE_BIN, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_signal_new ("quit", TYPE_AUTO_PIPELINE, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}


static void auto_pipeline_instance_init (AutoPipeline * self) {
	self->priv = AUTO_PIPELINE_GET_PRIVATE (self);
}


static void auto_pipeline_finalize (GObject* obj) {
	AutoPipeline * self;
	self = AUTO_PIPELINE (obj);
	_fclose0 (self->priv->log_stream);
	_gst_object_unref0 (self->priv->_pipeline);
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
		case AUTO_PIPELINE_PRINT_MESSAGES_ENABLED:
		g_value_set_boolean (value, auto_pipeline_get_print_messages_enabled (self));
		break;
		case AUTO_PIPELINE_PIPELINE:
		g_value_set_object (value, auto_pipeline_get_pipeline (self));
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
		case AUTO_PIPELINE_PRINT_MESSAGES_ENABLED:
		auto_pipeline_set_print_messages_enabled (self, g_value_get_boolean (value));
		break;
		case AUTO_PIPELINE_STATE:
		auto_pipeline_set_state (self, g_value_get_enum (value));
		break;
		case AUTO_PIPELINE_PIPELINE:
		auto_pipeline_set_pipeline (self, g_value_get_object (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




