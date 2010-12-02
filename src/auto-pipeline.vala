const string LOG_FILENAME = "gst-auto-launch.log";

[PrintfFormat]
extern int vprintf(string format, va_list ap);

[PrintfFormat]
extern int vfprintf(FileStream stream, string format, va_list ap);


class AutoPipeline: Object {

    public signal void quit();

    FileStream log_stream;

    bool _output_messages_enabled;
    public int return_status {get; set; default = 0;}

    public bool output_messages_enabled {
        set {
            if(!_output_messages_enabled && value)
                log_stream = FileStream.open(LOG_FILENAME, "w");
            _output_messages_enabled = value;
        }
        get {
            return _output_messages_enabled;
        }
    }

    public void log(string format, ...) {
        va_list args_vl = va_list();
        if(log_stream != null)
            vfprintf(log_stream, format, args_vl);
        vprintf(format, args_vl);
    }


    public Gst.Bin pipeline {
        get; set;
    }


    public void parse_launch(string description) throws Error {
        _pipeline = Gst.parse_launch(description) as Gst.Bin;
        Gst.Bus bus = _pipeline.bus;
        bus.add_signal_watch();
        bus.message.connect(on_bus_message);
    }


    void on_bus_message(Gst.Message message) {
        if(_output_messages_enabled) {
            uint32 seqnum = message.get_seqnum();
            Gst.Object src = message.src;
            Gst.Structure s = message.get_structure();
            string src_name = null;
            
            if(src is Gst.Element)
                src_name = src.name;
            else if(src is Gst.Pad) {
                Gst.Pad pad = (Gst.Pad)src;
                string pad_name = pad.name;
                string parent_name = pad.get_parent_element().name;
                src_name = "%s:%s".printf(parent_name, pad_name);
            }
            else if(src is Gst.Object)
                src_name = src.name;

            log("  {\n");
            log("   'seqnum' : %u,\n", seqnum);
            log("   'type' : '%s',\n", message.type.to_string());
            TimeVal tv = TimeVal();
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
                return_status = 1;
                quit();
                break;
            }
            case Gst.MessageType.EOS: {
                pipeline.set_state(Gst.State.NULL);
                quit();
                break;
            }
            default:
                break;
        }
    }


    public void send_eos() {
        bool eos_was_sent = false;
        auto_pipeline.pipeline.iterate_elements().foreach(
            (data) => {
                Gst.Element elem = data as Gst.Element;
                if("src" in elem.name || elem is Gst.BaseSrc) {
                    eos_was_sent = true;
                    print("Sending EOS event to element '%s'\n", elem.get_name());
                    elem.send_event(new Gst.Event.eos());
                }
            });

        if(!eos_was_sent) {
            print("Could not find a src element\n");
            print("Sending EOS to the pipeline\n");
            auto_pipeline.pipeline.send_event(new Gst.Event.eos());
        }
    }

}

