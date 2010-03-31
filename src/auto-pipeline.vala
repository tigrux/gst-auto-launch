class AutoPipeline: Object {

    Timer _timer;

    construct {
        _loop = new MainLoop();
        var current_tv = TimeVal();
        _timer = new Timer();
    }


    public Gst.State state {
        set {
            _pipeline.set_state(value);
        }
    }


    public Gst.Bin pipeline {
        get; set;
    }


    public MainLoop loop {
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
        switch(message.type) {
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
                _loop.quit();
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

