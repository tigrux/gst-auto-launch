[CCode (has_target=false)]
delegate int CommandFunc(AutoPipeline auto_pipeline, Task task);


struct Command {
    string name;
    string description;
    string args_desc;
    CommandFunc function;

    public char get_arg_desc(uint arg_i) {
        if(arg_i >= args_desc.length)
            return 0;
        return (char)args_desc[arg_i];
    }

    public uint get_n_args() {
        return (uint)args_desc.length;
    }
}

