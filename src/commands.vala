const Command[] COMMANDS = {
    {"play", "Change pipeline state to PLAYING", "", command_play},
    {"pause", "Change pipeline state to PAUSED", "", command_pause},
    {"ready", "Change pipeline state to READY", "", command_ready},
    {"stop", "Change pipeline state to READY", "", command_ready},
    {"null", "Change pipeline state to NULL", "", command_null},
    {"eos", "Send eos to the source elements", "", command_eos},
    {"quit", "Quit the event loop", "", command_quit},
    {"set", "Set properties of an object", "ssv", command_set},
    {"seek", "Seek to the specified time", "t", command_seek},
    {"switch-video-output", "Switch overlay num to the specified manager name", "is", command_switch_video_output},
    {"navigation", "Send the specified navigation event name to an element in the given coords", "ssii", command_navigation},
    {null}
};


void command_play(AutoPipeline ctx, Task task) {
    print("Passing to PLAYING\n");
    ctx.state = Gst.State.PLAYING;
}


void command_pause(AutoPipeline ctx, Task task) {
    print("Passing to PAUSED\n");
    ctx.state = Gst.State.PAUSED;
}


void command_ready(AutoPipeline ctx, Task task) {
    print("Passing to READY\n");
    ctx.state = Gst.State.READY;
}


void command_null(AutoPipeline ctx, Task task) {
    print("Passing to NULL\n");
    ctx.state = Gst.State.NULL;
}


void command_quit(AutoPipeline ctx, Task task) {
    print("Quitting\n");
    ctx.quit();
}


void command_set(AutoPipeline ctx, Task task) {
    var element_name = task.arguments.values[0].get_string();
    var prop_name = task.arguments.values[1].get_string();
    
    var element = ctx.pipeline.get_by_name(element_name);
    
    if(element == null) {
        printerr("There is no element named '%s'\n", element_name);
        return;
    }
    
    var prop_value = task.arguments.values[2];
    
    if(prop_value.holds(typeof(string))) {
        weak ParamSpec prop = element.get_class().find_property(prop_name);
        if(prop != null) {
            weak EnumClass e_class = (EnumClass)prop.value_type.class_peek();
            var prop_string = prop_value.get_string();
            weak EnumValue e_value = e_class.get_value_by_nick(prop_string);
            if(e_value != null)
                prop_value = e_value.value;
        }
    }

    Value prop_value_s = "";
    if(prop_value.transform(ref prop_value_s))
        print("Setting property '%s' of element '%s' to '%s'\n",
            prop_name, element.get_name(), prop_value_s.get_string());
    else
        print("Setting property '%s' of element '%s'\n",
            prop_name, element.get_name());
    element.set_property(prop_name, prop_value);
}


void command_seek(AutoPipeline ctx, Task task) {
    var position_value = Value(typeof(double));
    task.arguments.values[0].transform(ref position_value);
    var position_seconds = position_value.get_double();
    var position_useconds = (int64)(position_seconds * Gst.SECOND);

    var seek_event =
        new Gst.Event.seek(
            1.0, Gst.Format.TIME,
            Gst.SeekFlags.FLUSH | Gst.SeekFlags.KEY_UNIT,
            Gst.SeekType.SET,  position_useconds,
            Gst.SeekType.NONE, 0);

    print("Seeking to second %lf\n", position_seconds);
    ctx.pipeline.send_event(seek_event);
}


void command_eos(AutoPipeline ctx, Task task) {
    bool eos_was_sent = false;
    ctx.pipeline.iterate_elements().foreach(
        (data) => {
            var elem = data as Gst.Element;
            if("src" in elem.name || elem is Gst.BaseSrc) {
                eos_was_sent = true;
                print("Sending EOS event to element '%s'\n", elem.get_name());
                elem.send_event(new Gst.Event.eos());
            }
        });

    if(!eos_was_sent) {
        print("Could not find a src element\n");
        print("Sending EOS to the pipeline\n");
        ctx.pipeline.send_event(new Gst.Event.eos());
    }
}


const string GST_NAVIGATION_EVENT_NAME = "application/x-gst-navigation";


void command_navigation(AutoPipeline ctx, Task task) {
    var element_name = task.arguments.values[0].get_string();
    var event_name = task.arguments.values[1].get_string();
    var pointer_x = task.arguments.values[2].get_int();
    var pointer_y = task.arguments.values[3].get_int();
    var button = (event_name != "mouse-move") ? 1 : 0;

    var element = ctx.pipeline.get_by_name(element_name);
    if(element == null) {
        printerr("There is no element named '%s'\n", element_name);
        return;
    }

    var s = new Gst.Structure(GST_NAVIGATION_EVENT_NAME,
        "event", typeof(string), event_name,
        "button", typeof(int), button,
        "pointer_x", typeof(double), (double)pointer_x,
        "pointer_y", typeof(double), (double)pointer_y,
        null);

    var src_pad = element.get_static_pad("src");
    if(src_pad == null) {
        printerr("Element %s does not have a src pad", element_name);
    }

    src_pad.send_event(new Gst.Event.navigation(s));
}

void command_switch_video_output(AutoPipeline ctx, Task task) {
    var overlay_num = task.arguments.values[0].get_int();
    var manager_name = task.arguments.values[1].get_string();

    write_string_to_path("0", "/sys/devices/platform/omapdss/overlay0/zorder");
    write_string_to_path("1", "/sys/devices/platform/omapdss/overlay1/zorder");
    write_string_to_path("3", "/sys/devices/platform/omapdss/overlay2/zorder");
    write_string_to_path("2", "/sys/devices/platform/omapdss/overlay3/zorder");
    
    var overlay_name = @"overlay$overlay_num";
    print("Changing manager of %s\n", overlay_name);

    switch(manager_name) {
        case "lcd1":
            print("Enabling primary display: lcd\n");
            write_string_to_path(
                "1", "/sys/devices/platform/omapdss/display0/enabled");
            manager_name = "lcd";
            break;
        case "lcd2":
            print("Enabling secondary display: 2lcd\n");
            write_string_to_path(
                "1", "/sys/devices/platform/omapdss/display1/enabled");
            manager_name = "2lcd";
            break;
        case "tv":
            print("Enabling hdmi display: tv\n");
            write_string_to_path(
                "1", "/sys/devices/platform/omapdss/display2/enabled");
            break;
    }

    if(FileUtils.test("/dev/fb1", FileTest.EXISTS)) {
        print("2 framebuffers detected: adjusting overlay number\n");
        overlay_num += 1;
        overlay_name = @"overlay$overlay_num";
        print("Updated overlay %s\n",  overlay_name);
    }

    try {
        string overlay_enabled;
        FileUtils.get_contents(
            "/sys/devices/platform/omapdss/$overlay_name/enabled",
            out overlay_enabled);
        write_string_to_path(
            overlay_enabled,
            @"/sys/devices/platform/omapdss/$overlay_name/enabled");
    }
    catch(FileError e) {
        printerr("Could not check if the overlay was enabled\n");
    }

    write_string_to_path(
        "0", @"/sys/devices/platform/omapdss/$overlay_name/enabled");
    write_string_to_path(
        manager_name, @"/sys/devices/platform/omapdss/$overlay_name/manager");
}


void write_string_to_path(string content, string path) {
    var path_file = FileStream.open(path, "w");
    if(path_file != null) {
        printerr("Writing '%s' to '%s'\n", content, path);
        path_file.printf("%s", content);
        path_file.flush();
    }
    else
        printerr("Could not open '%s'\n", path);
}


void scanner_register_symbols(Scanner scanner, uint scope) {
    Command *command = &COMMANDS[0];
    while(command->name != null) {
        scanner.scope_add_symbol(scope, command->name, command);
        command++;
    }
}

