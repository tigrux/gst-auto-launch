class AutoPipeline: Object {

    Timer _timer;
    bool _print_messages;

    construct {
        var current_tv = TimeVal();
        _timer = new Timer();
    }


    public signal void quit();


    public bool print_messages {
        set {
            _print_messages = value;
        }
    }


    public Gst.State state {
        set {
            _pipeline.set_state(value);
        }
    }


    public Gst.Bin pipeline {
        get; set;
    }


    public Timer timer {
        get {
            return _timer;
        }
    }


    public void parse_launch(string description) throws Error {
        _pipeline = Gst.parse_launch(description) as Gst.Bin;
        var bus = _pipeline.bus;
        bus.add_signal_watch();
        bus.message.connect(on_bus_message);
    }


    void on_bus_message(Gst.Message message) {
        if(_print_messages) {
            var seq_num = message.get_seqnum();
            var src_obj = message.src();
            var s = message.get_structure();
            unowned string obj_type;
            string obj_name;
            
            if(src_obj is Gst.Element) {
                obj_type = "element";
                obj_name = src_obj.name;
            }
            else if(src_obj is Gst.Pad) {
                obj_type = "pad";
                var pad = (Gst.Pad)src_obj;
                var pad_name = pad.name;
                var parent_name = pad.get_parent_element().name;
                obj_name = "%s:%s".printf(pad_name, parent_name);
            }
            else if(src_obj is Gst.Object) {
                obj_type = "object";
                obj_name = src_obj.name;
            }
            else
                obj_type = obj_name = "(unknown)";

            var ts = Gst.util_get_timestamp();
            print("Got message #%u from %s \"%s\" (%s) at %s\n",
                seq_num, obj_type, obj_name,
                message.type().to_string(),
                ts.to_string()
            );

            if(s != null)
                print("%s\n", s.to_string());
        }

        switch(message.type()) {
            case Gst.MessageType.ERROR: {
                Error e;
                string s;
                message.parse_error(out e, out s);
                critical("Bus error: %s %s\n", e.message, s);
                break;
            }
            case Gst.MessageType.EOS: {
                print("Got eos\n");
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

