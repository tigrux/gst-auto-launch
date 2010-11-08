class Task: Object {
    double _seconds;
    Command _command;
    ValueArray _arguments;


    public double seconds {
        get {
            return _seconds;
        }
    }


    public ValueArray arguments {
        get {
            return _arguments;
        }
    }


    public Task(double seconds, Command command) {
        _seconds = seconds;
        _command = command;
        _arguments = new ValueArray(0);
    }


    public uint exec(AutoPipeline auto_pipeline) {
        return Timeout.add((uint)(seconds*1000),
            () => {
            if(auto_pipeline.return_status == 0)
                _command.function(auto_pipeline, this);
            return false;
        });
    }
}

