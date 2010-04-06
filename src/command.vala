delegate void CommandFunc(AutoPipeline ctx, Task task);


struct Command {
    string name;
    string description;
    CommandFunc function;
}


