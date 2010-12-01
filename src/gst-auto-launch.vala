bool output_messages;
bool force_eos;

const OptionEntry[] options = {
    { "gst-messages", 'm', 0, OptionArg.NONE, ref output_messages,
      "Output messages", null },
    { "eos-on-shutdown", 'e', 0, OptionArg.NONE, ref force_eos,
      "Force EOS on sources before shutting the pipeline down", null },
    {null}
};


AutoPipeline auto_pipeline;
uint how_many_control_c_pressed = 0;

void on_control_c() {
    if(auto_pipeline == null)
        return;
    if(how_many_control_c_pressed == 0)
        auto_pipeline.send_eos();
    else
        auto_pipeline.quit();
    how_many_control_c_pressed++;
}

int main(string[] args) {
    OptionContext opt_context;
    try {
        opt_context = new OptionContext("- Build pipelines and run commands on them");
        opt_context.set_help_enabled(true);
        opt_context.add_main_entries(options, "messages");
        opt_context.add_group(Gst.init_get_option_group());
        opt_context.parse(ref args);
    }
    catch (OptionError e) {
        printerr("Option parsing failed: %s\n", e.message);
        return -1;
    }

    auto_pipeline = new AutoPipeline();

    if(force_eos)
        Posix.signal(Posix.SIGINT, on_control_c);

    if(output_messages) {
        printerr("Logging message to '%s'\n", LOG_FILENAME);
        auto_pipeline.output_messages_enabled = output_messages;
    }

    TimeVal tv;

    if(output_messages) {
        auto_pipeline.log("{\n");
        tv = TimeVal();
        auto_pipeline.log(" 'start' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
    }

    var scanner = new TaskScanner();

    if(args.length < 2) {
        printerr(opt_context.get_help(true, null));        
        printerr("Commands are of the form <seconds>:<command>\n");
        printerr("Supported commands are:\n");

        scanner.print_description();

        printerr("\nExamples:\n");
        printerr("  %s videotestsrc ! autovideosink 0:pause 1:play +5:eos\n", args[0]);
        printerr("  %s videotestsrc ! clockoverlay name=clock ! autovideosink 0:play 2:set:clock:valignment:bottom 5:eos\n", args[0]);

        return 1;
    }

    var tasks = new List<Task> ();
    var effective_args_list = new List<string> ();

    foreach(var arg in args[1:args.length]) {
        var task = scanner.get_task_from_arg(arg);
        if(task != null)
            tasks.append(task);
        else if(!arg.has_prefix("--")) {
            if(" " in arg && "=" in arg) {
                var parts = arg.split("=", 2);
                var prop_name_regex = /^[A-Za-z][a-zA-Z0-9_-]+$/;
                if(prop_name_regex.match(parts[0])) {
                    var new_arg = "%s=\"%s\"".printf(parts[0],parts[1]);
                    effective_args_list.append(new_arg);
                    continue;
                }
            }
            effective_args_list.append(arg);
        }
        else
            return 1;
    }

    if(tasks.length() == 0) {
        var auto_symbol = "play";
        printerr("No commands given, will exec '%s' automatically\n", auto_symbol);
        var auto_command = scanner.lookup_command(auto_symbol);
        if(auto_command != null) {
            var auto_task = new Task(0, auto_command);
            tasks.append(auto_task);
        }
        else
            printerr("Could not find a command named '%s'\n", auto_symbol);
    }

    var i = 0;
    var effective_args = new string[effective_args_list.length()];
    foreach(var arg in effective_args_list) {
        effective_args[i] = arg;
        i++;
    }
    var pipeline_desc = string.joinv(" ", effective_args);

    try {
        if(output_messages) {
            tv = TimeVal();
            auto_pipeline.log(" 'description' : '%s',\n", pipeline_desc);
        }
        auto_pipeline.parse_launch(pipeline_desc);
        if(output_messages) {
            tv = TimeVal();
            auto_pipeline.log(" 'launch' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
        }
        
    }
    catch(Error e) {
        printerr("Error: %s\n", e.message);
        if(auto_pipeline.pipeline != null)
            auto_pipeline.pipeline.set_state(Gst.State.NULL);
        return 1;
    }

    foreach(var task in tasks)
        auto_pipeline.exec_task(task);
    var loop = new MainLoop();
    auto_pipeline.quit.connect(loop.quit);
    if(output_messages)
        auto_pipeline.log(" 'message' : [\n");
    loop.run();
    if(output_messages)
        auto_pipeline.log(" ],\n");
    auto_pipeline.pipeline.set_state(Gst.State.NULL);
    if(output_messages) {
        tv = TimeVal();
        auto_pipeline.log(" 'end' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
        auto_pipeline.log("}\n");
    }

    return auto_pipeline.return_status;
}

