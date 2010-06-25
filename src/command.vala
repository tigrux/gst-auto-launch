delegate void CommandFunc(AutoPipeline ctx, Task task);


struct Command {
    string name;
    string description;
    string args_desc;
    CommandFunc function;

    public char get_arg_desc(uint arg_i) {
        if(arg_i >= args_desc.length)
            return 0;
        char arg_desc = ((char*)args_desc)[arg_i];
        return arg_desc;
    }

    public uint get_n_args() {
        return (uint)args_desc.length;
    }
}

