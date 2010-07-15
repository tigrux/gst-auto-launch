const string LOG_FILENAME = "gst-auto-launch.log";

[PrintfFormat]
extern int vprintf(string format, va_list ap);

[PrintfFormat]
extern int vfprintf(FileStream stream, string format, va_list ap);


class AutoPipeline: Object {

    public signal void quit();

    FileStream log_stream;

    bool _print_messages_enabled;

    public bool print_messages_enabled {
        set {
            if(!_print_messages_enabled && value)
                log_stream = FileStream.open(LOG_FILENAME, "w");
            _print_messages_enabled = value;
        }
        get {
            return _print_messages_enabled;
        }
    }

    public void log(string format, ...) {
        var args_vl = va_list();
        if(log_stream != null)
            vfprintf(log_stream, format, args_vl);
        vprintf(format, args_vl);
    }

    public Gst.State state {
        set {
            _pipeline.set_state(value);
        }
    }


    public Gst.Bin pipeline {
        get; set;
    }


    public void parse_launch(string description) throws Error {
        _pipeline = Gst.parse_launch(description) as Gst.Bin;
        var bus = _pipeline.bus;
        bus.add_signal_watch();
        bus.message.connect(on_bus_message);
    }


    void on_bus_message(Gst.Message message) {
        if(_print_messages_enabled) {
            var seqnum = message.get_seqnum();
            var src = message.src;
            var s = message.get_structure();
            string src_name = null;
            
            if(src is Gst.Element)
                src_name = src.name;
            else if(src is Gst.Pad) {
                var pad = (Gst.Pad)src;
                var pad_name = pad.name;
                var parent_name = pad.get_parent_element().name;
                src_name = "%s:%s".printf(parent_name, pad_name);
            }
            else if(src is Gst.Object)
                src_name = src.name;

            log("  {\n");
            log("   'seqnum' : %u,\n", seqnum);
            log("   'type' : '%s',\n", message.type.to_string());
            var tv = TimeVal();
            log("   'time' : %lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
            if(src_name != null)
                log("   'src' : '%s',\n", src_name);
            if(s != null) {
                log("   'structure' : {\n");
                log("    'name' : '%s',\n", s.get_name());
                s.foreach(
                    (q, v) => {
                        Value vs = "";
                        v.transform(ref vs);
                        log("    '%s' : '''%s''',\n", q.to_string(), vs.get_string());
                        return true;
                });
                log("   }\n");
            }
            log("  },\n");

        }

        switch(message.type) {
            case Gst.MessageType.ERROR: {
                Error e;
                string s;
                message.parse_error(out e, out s);
                critical("Bus error: %s %s\n", e.message, s);
                break;
            }
            case Gst.MessageType.EOS: {
                state = Gst.State.NULL;
                quit();
                break;
            }
            default:
                break;
        }
    }


    public uint exec_task(Task task) {
        return task.exec(this);
    }
}

