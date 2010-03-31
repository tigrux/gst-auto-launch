class Task: Object {
    double _seconds;
    Command _command;


    public double seconds {
        get {
            return _seconds;
        }
    }


    public Task(double seconds, Command command) {
        _seconds = seconds;
        _command = command;
    }

    
    public uint exec(AutoPipeline ctx) {
        return Timeout.add((uint)(seconds*1000),
            () => {
            print("Time = %0.3lf\n", ctx.timer.elapsed());
            _command.function(ctx);
            return false;
        });
    }
}

