const Command[] COMMANDS = {
    {"play", "Change pipeline state to PLAYING", command_play},
    {"pause", "Change pipeline state to PAUSED", command_pause},
    {"ready", "Change pipeline state to READY", command_ready},
    {"null", "Change pipeline state to NULL", command_null},
    {"wait", "Wait the supplied number of seconds", command_wait},
    {"w", "Wait the supplied number of seconds", command_wait},
    {"eos", "Send eos to the source elements", command_eos},
    {"quit", "Quit the event loop", command_quit}
};

void command_play(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Changing to PLAYING\n");
    ctx.state = Gst.State.PLAYING;
    ctx.continue_exec();
}


void command_pause(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Changing to PAUSED\n");
    ctx.state = Gst.State.PAUSED;
    ctx.continue_exec();
}


void command_ready(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Changing to READY\n");
    ctx.state = Gst.State.READY;
    ctx.continue_exec();
}


void command_null(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Changing to NULL\n");
    ctx.state = Gst.State.NULL;
    ctx.continue_exec();
}


void command_wait(AutoPipeline ctx, ObjectList<string> ?param) {
    if(param == null || param.length < 1) {
        print("Command '%s' needs an argument\n", param.name);
        ctx.continue_exec();
        return;
    }
    var seconds = param[0].to_int();
    print("Waiting %d seconds\n", seconds);
    ctx.continue_exec_in_seconds(seconds);
}


void command_quit(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Quitting\n");
    ctx.loop.quit();
    ctx.continue_exec();
}


void command_eos(AutoPipeline ctx, ObjectList<string> ?param) {
    print("Trying to send eos to the sources\n");
    ctx.pipeline.iterate_elements().foreach(
        (data) => {
            var elem = data as Gst.Element;
            if("src" in elem.name) {
                print("Sending eos to %s\n", elem.name);
                elem.send_event(new Gst.Event.eos());
            }
        });
    ctx.continue_exec();
}


delegate void CommandFunc(AutoPipeline ctx, ObjectList<string> ?param);

struct Command {
    string name;
    string description;
    CommandFunc function;
}


delegate void ForeachCommandFunc(Command command);

void foreach_command(ForeachCommandFunc func) {
    foreach(var command in COMMANDS)
        func(command);
}


bool find_command(string name, out Command ?out_command) {
    foreach(var command in COMMANDS)
        if(command.name == name) {
            if(&out_command != null)
                out_command = command;
            return true;
        }
    return false;
}


