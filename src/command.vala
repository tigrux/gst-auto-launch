delegate void CommandFunc(AutoPipeline ctx);


struct Command {
    string name;
    string description;
    CommandFunc function;
}


