const Command[] COMMANDS = {
    {"play", "Change pipeline state to PLAYING", command_play},
    {"pause", "Change pipeline state to PAUSED", command_pause},
    {"ready", "Change pipeline state to READY", command_ready},
    {"stop", "Change pipeline state to READY", command_ready},
    {"null", "Change pipeline state to NULL", command_null},
    {"eos", "Send eos to the source elements", command_eos},
    {"quit", "Quit the event loop", command_quit},
    {"set", "Set properties of an object", command_set},
    {"seek", "Seek to the specified time", command_seek},
    {"seek", "Seek to the specified time", command_seek},
    {"m", "Enable print messages", command_enable_messages},
    {null}
};


void command_play(AutoPipeline ctx, Task task) {
    print("Changing to PLAYING\n");
    ctx.state = Gst.State.PLAYING;
}


void command_pause(AutoPipeline ctx, Task task) {
    print("Changing to PAUSED\n");
    ctx.state = Gst.State.PAUSED;
}


void command_ready(AutoPipeline ctx, Task task) {
    print("Changing to READY\n");
    ctx.state = Gst.State.READY;
}


void command_null(AutoPipeline ctx, Task task) {
    print("Changing to NULL\n");
    ctx.state = Gst.State.NULL;
}


void command_quit(AutoPipeline ctx, Task task) {
    print("Quitting\n");
    ctx.quit();
}


void command_set(AutoPipeline ctx, Task task) {
    if(task.arguments.n_values != 3) {
        print("Command 'set' takes exactly 3 arguments\n");
        return;
    }

    if(!task.arguments.values[0].holds(typeof(string))) {
        print("Element name (arg 0) for command 'set' must be a string\n");
        return;
    }

    var element_name = task.arguments.values[0].get_string();

    if(!task.arguments.values[1].holds(typeof(string))) {
        print("Property name (arg 1) for command 'set' must be a string\n");
        return;
    }

    var prop_name = task.arguments.values[1].get_string();
    
    var element = ctx.pipeline.get_by_name(element_name);
    
    if(element == null) {
        print("There is no element named '%s'\n", element_name);
        return;
    }
    
    var prop_value = task.arguments.values[2];
    element.set_property(prop_name, prop_value);
}


void command_seek(AutoPipeline ctx, Task task) {
    if(task.arguments.n_values != 1) {
        print("Command 'seek' takes exactly 1 argument\n");
        return;
    }

    var position_value = Value(typeof(double));
    task.arguments.values[0].transform(ref position_value);
    var position_seconds = position_value.get_double();
    var position_useconds = (int64)(position_seconds * Gst.SECOND);

    print("Seeking to %.3lf\n", position_seconds);
    var seek_event =
        new Gst.Event.seek(
            1.0, Gst.Format.TIME,
            Gst.SeekFlags.FLUSH | Gst.SeekFlags.KEY_UNIT,
            Gst.SeekType.SET,  position_useconds,
            Gst.SeekType.NONE, 0);
    ctx.pipeline.send_event(seek_event);
}


void command_eos(AutoPipeline ctx, Task task) {
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


void command_enable_messages(AutoPipeline ctx, Task task) {
    print("Enabling print messages\n");
    ctx.print_messages = true;
}


void scanner_register_symbols(Scanner scanner, uint scope) {
    Command *command = &COMMANDS[0];
    while(command->name != null) {
        scanner.scope_add_symbol(scope, command->name, command);
        command++;
    }
}

