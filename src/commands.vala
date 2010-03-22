const Command[] COMMANDS = {
    {"play", "Change pipeline state to PLAYING", command_play},
    {"pause", "Change pipeline state to PAUSED", command_pause},
    {"ready", "Change pipeline state to READY", command_ready},
    {"stop", "Change pipeline state to READY", command_ready},
    {"null", "Change pipeline state to NULL", command_null},
    {"eos", "Send eos to the source elements", command_eos},
    {"quit", "Quit the event loop", command_quit},
    {null}
};


void command_play(AutoPipeline ctx) {
    print("Changing to PLAYING\n");
    ctx.state = Gst.State.PLAYING;
}


void command_pause(AutoPipeline ctx) {
    print("Changing to PAUSED\n");
    ctx.state = Gst.State.PAUSED;
}


void command_ready(AutoPipeline ctx) {
    print("Changing to READY\n");
    ctx.state = Gst.State.READY;
}


void command_null(AutoPipeline ctx) {
    print("Changing to NULL\n");
    ctx.state = Gst.State.NULL;
}


void command_quit(AutoPipeline ctx) {
    print("Quitting\n");
    ctx.loop.quit();
}


void command_eos(AutoPipeline ctx) {
    print("Trying to send eos to the sources\n");
    ctx.pipeline.iterate_elements().foreach(
        (data) => {
            var elem = data as Gst.Element;
            if("src" in elem.name || elem is Gst.BaseSrc) {
                print("Sending eos to %s\n", elem.name);
                elem.send_event(new Gst.Event.eos());
            }
        });
}


void scanner_register_symbols(Scanner scanner, uint scope) {
    Command *command = &COMMANDS[0];
    while(command->name != null) {
        scanner.scope_add_symbol(scope, command->name, command);
        command++;
    }
}

