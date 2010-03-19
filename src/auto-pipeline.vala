class AutoPipeline: Object {

    Scanner _scanner;
    Timer _timer;

    construct {
        _loop = new MainLoop();
        _scanner = new Scanner(null);
        _scanner.config.scan_identifier_1char = false;
        _scanner.config.int_2_float = true;
        scanner_register_symbols(_scanner, 0);
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


    public Scanner scanner {
        get {
            return _scanner;
        }
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


    public List<Task> parse_tasks_from_args(string[] args, out string[] new_args) {
        double last_time_seconds = 0;
        var remaining_args = new List<string> ();
        var tasks = new List<Task> ();

        foreach(var arg in args) {
            if(arg.has_prefix("--")) {
                remaining_args.append(arg);
                continue;
            }

            _scanner.input_text(arg, (uint)arg.length);

            int relative;
            var tok_type = _scanner.peek_next_token();
            if(tok_type == TokenType.EOF)
                break;
            
            if(tok_type == '+')
                relative = 1;
            else if(tok_type == '-')
                relative = -1;
            else
                relative = 0;
            
            if(relative != 0)
                _scanner.get_next_token();

            if(_scanner.peek_next_token() != TokenType.FLOAT) {
                remaining_args.append(arg);
                continue;
            }
            _scanner.get_next_token();
            double seconds = _scanner.value.float;

            if(relative != 0)
                seconds = last_time_seconds + relative*seconds;

            if(_scanner.peek_next_token() != ':') {
                remaining_args.append(arg);
                continue;
            }
            _scanner.get_next_token();

            if(_scanner.peek_next_token() != TokenType.SYMBOL) {
                remaining_args.append(arg);
                continue;
            }
            _scanner.get_next_token();
            var p_command = (Command*)_scanner.value.symbol;

            tasks.append(new Task(seconds, p_command));
            last_time_seconds = seconds;
        }
        
        new_args = new string[remaining_args.length()];
        uint i = 0;
        foreach(var arg in remaining_args) {
            new_args[i] = arg;
            i++;
        }

        return tasks;
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

