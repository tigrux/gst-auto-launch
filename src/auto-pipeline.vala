class AutoPipeline: Object {

    bool _print_messages = true;


    public signal void quit();


    public bool print_messages {
        set {
            _print_messages = value;
        }
        get {
            return _print_messages;
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


    public void parse_launch(string description) throws Error {
        _pipeline = Gst.parse_launch(description) as Gst.Bin;
        var bus = _pipeline.bus;
        bus.add_signal_watch();
        bus.message.connect(on_bus_message);
    }


    void on_bus_message(Gst.Message message) {
        if(_print_messages) {
            var seqnum = message.get_seqnum();
            var src = message.src();
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

            print("  {\n");
            print("   'seqnum' : %u,\n", seqnum);
            print("   'type' : '%s',\n", message.type().to_string());
            var tv = TimeVal();
            print("   'time' : %lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
            if(src_name != null)
                print("   'src' : '%s',\n", src_name);
            if(s != null) {
                print("   'structure' : {\n");
                s.foreach(
                    (q, v) => {
                        Value vs = "";
                        v.transform(ref vs);
                        print("    '%s' : '%s',\n", q.to_string(), vs.get_string());
                        return true;
                });
                print("   }\n");
            }
            print("  },\n");

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

