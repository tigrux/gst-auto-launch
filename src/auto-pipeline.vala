class AutoPipeline: Object {

    construct {
        _loop = new MainLoop();
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


    public ObjectList< ObjectList<string> > parameters {
        get; set;
    }


    public void parse(string description) throws Error {
        _pipeline = Gst.parse_launch(description) as Gst.Bin;
        var bus = _pipeline.bus;
        bus.add_signal_watch();
        bus.message.connect(on_bus_message);
    }

    
    bool do_exec_parameters() {
        if(iterator.next()) {
            var param = iterator.get();
            weak string param_name = param.name;
            Command command;
            if(find_command(param_name, out command)) {
                Idle.add(
                    () => {
                        command.function(this, param);
                        return false;
                    });
            }
        }
        return false;
    }


    public bool parse_parameters(string[] args) {
        _parameters = new ObjectList< ObjectList<string> > ();
        ObjectList<string> current_parameter = null;
        foreach(var arg in args) {
            if(arg.has_prefix("-")) {
                if(current_parameter != null)
                    _parameters.append(current_parameter);

                var param_name = arg.next_char();
                if(!find_command(param_name, null)) {
                    warning("There is no command '%s'\n", param_name);
                    return false;
                }
                current_parameter = new ObjectList<string>();
                current_parameter.name = param_name;
            }
            else
                if(current_parameter != null)
                    current_parameter.append(arg);
                else
                    warning(
                        "Got argument '%s' without preceding parameter\n", arg);
        }
        if(current_parameter != null)
            _parameters.append(current_parameter);

        return true;
    }


    ObjectList.Iterator< ObjectList<string> > iterator;

    public void exec_parameters() {
        iterator = parameters.iterator();
        continue_exec();
    }


    public void continue_exec() {
        Idle.add(do_exec_parameters);
    }


    public void continue_exec_in_seconds(uint n_seconds) {
        Timeout.add_seconds(n_seconds, do_exec_parameters);
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
}

