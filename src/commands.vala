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
    {"navigation", "Send the specified navigation event name to an element in the given coords", "ssii", command_navigation},
    {null}
};


int command_play(AutoPipeline auto_pipeline, Task task) {
    print("Passing to PLAYING\n");
    var status = auto_pipeline.pipeline.set_state(Gst.State.PLAYING);
    return status != Gst.StateChangeReturn.FAILURE ? 0 : 1;
}


int command_pause(AutoPipeline auto_pipeline, Task task) {
    print("Passing to PAUSED\n");
    var status = auto_pipeline.pipeline.set_state(Gst.State.PAUSED);
    return status != Gst.StateChangeReturn.FAILURE ? 0 : 1;
}


int command_ready(AutoPipeline auto_pipeline, Task task) {
    print("Passing to READY\n");
    var status = auto_pipeline.pipeline.set_state(Gst.State.READY);
    return status != Gst.StateChangeReturn.FAILURE ? 0 : 1;
}


int command_null(AutoPipeline auto_pipeline, Task task) {
    print("Passing to NULL\n");
    var status = auto_pipeline.pipeline.set_state(Gst.State.NULL);
    return status != Gst.StateChangeReturn.FAILURE ? 0 : 1;
}


int command_quit(AutoPipeline auto_pipeline, Task task) {
    print("Quitting\n");
    auto_pipeline.quit();
    return 0;
}


int command_set(AutoPipeline auto_pipeline, Task task) {
    var element_name = task.arguments.values[0].get_string();
    
    var element = auto_pipeline.pipeline.get_by_name(element_name);
    if(element == null) {
        printerr("No element named '%s'\n", element_name);
        return 1;
    }

    var prop_name = task.arguments.values[1].get_string();
    weak ParamSpec prop_spec = element.get_class().find_property(prop_name);
    
    if(prop_spec == null) {
        printerr("No property '%s' in element '%s'\n", prop_name, element_name);
        return 1;
    }
    var prop_type = prop_spec.value_type;

    var prop_value = task.arguments.values[2];
    if(prop_value.holds(typeof(string))) {
        var prop_string = prop_value.get_string();
        if(prop_type.is_enum()) {
            weak EnumClass enum_class = (EnumClass)prop_type.class_peek();
            weak EnumValue enum_value = enum_class.get_value_by_nick(prop_string);
            if(enum_value != null)
                prop_value = enum_value.value;
            else {
                printerr("'%s' is not a valid value for enum '%s'\n",
                    prop_string, prop_type.name());
                return 1;
            }
        }
    }

    Value string_value = "";
    prop_value.transform(ref string_value);
    var value_as_string = string_value.get_string();

    Value converted_value = Value(prop_type);

    if(!prop_spec.value_convert(prop_value, converted_value, true)) {
        print("'%s' is not a valid value for property '%s' of type '%s'\n",
            value_as_string, prop_name, prop_type.name());
        return 1;
    }

    print("Setting property '%s' of element '%s' to '%s'\n",
        prop_name, element.get_name(), value_as_string);

    element.set_property(prop_name, converted_value);
    return 0;
}


int command_seek(AutoPipeline auto_pipeline, Task task) {
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
    auto_pipeline.pipeline.send_event(seek_event);
    return 0;
}


int command_eos(AutoPipeline auto_pipeline, Task task) {
    auto_pipeline.send_eos();
    return 1;
}


int command_navigation(AutoPipeline auto_pipeline, Task task) {
    var element_name = task.arguments.values[0].get_string();
    var event_name = task.arguments.values[1].get_string();
    var pointer_x = task.arguments.values[2].get_int();
    var pointer_y = task.arguments.values[3].get_int();
    var button = (event_name != "mouse-move") ? 1 : 0;

    var element = auto_pipeline.pipeline.get_by_name(element_name);
    if(element == null) {
        printerr("No element named '%s'\n", element_name);
        return 1;
    }

    var s = new Gst.Structure("application/x-gst-navigation",
        "event", typeof(string), event_name,
        "button", typeof(int), button,
        "pointer_x", typeof(double), (double)pointer_x,
        "pointer_y", typeof(double), (double)pointer_y,
        null);

    var src_pad = element.get_static_pad("src");
    if(src_pad == null) {
        printerr("No src pad in element %s", element_name);
        return 1;
    }

    src_pad.send_event(new Gst.Event.navigation(s));
    return 0;
}


void scanner_register_symbols(Scanner scanner, uint scope) {
    Command *command = &COMMANDS[0];
    while(command->name != null) {
        scanner.scope_add_symbol(scope, command->name, command);
        command++;
    }
}

