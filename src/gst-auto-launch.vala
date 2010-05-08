int main(string[] args) {

    var tv = TimeVal();
    print("{\n");
    print(" 'start' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);

    var auto_pipeline = new AutoPipeline();
    var scanner = new TaskScanner();

    if(args.length < 2) {
        printerr("Usage: %s <pipelines.xml> <pipeline_id> <commands>\n", args[0]);
        printerr("Where each command is of the form <seconds>:<name>\n");
        printerr("Supported commands are:\n");

        scanner.scope_foreach_symbol(0,
            (key, val) => {
                var name = (string)key;
                var command = (Command*)val;
                printerr("  %s:\n    %s\n", name, command->description);
            }
        );

        printerr("\nIf no xml file can be parsed, it will get the pipeline from the command line\n\n");
        printerr("Examples:\n");
        printerr("  %s pipelines.xml videotest 0:pause 1:play +5:eos\n", args[0]);
        printerr("  %s videotestsrc ! autovideosink 0:pause 1:play +5:eos\n", args[0]);

        return 1;
    }

    var tasks = scanner.get_tasks_from_args(args);
    if(tasks.length() == 0) {
        var auto_symbol = "play";
        printerr("No commands given, will exec '%s' automatically\n", auto_symbol);
        var auto_command = (Command?)scanner.lookup_symbol(auto_symbol);
        if(auto_command != null) {
            var auto_task = new Task(0, auto_command);
            tasks.append(auto_task);
        }
        else
            printerr("Could not find a command named '%s'\n", auto_symbol);
    }

    var effective_args_list = new List<string> ();
    foreach(var arg in args[1:args.length])
        if(!arg.has_prefix("-") && !arg.contains(":"))
            effective_args_list.append(arg);

    var should_parse_xml = false;
    
    if(effective_args_list.length() == 2)
        should_parse_xml = true;

    string pipeline_desc = null;

    if(should_parse_xml) {
        should_parse_xml = try_to_get_desc_from_xml(args, ref pipeline_desc);
        if(!should_parse_xml)
            print("Could not get pipeline description from xml file\n");
    }

    if(!should_parse_xml) {
        printerr("Getting pipeline description from the command line\n");

        uint i = 0;
        var effective_args = new string[effective_args_list.length()];
        foreach(var arg in effective_args_list) {
            effective_args[i] = arg;
            i++;
        }
        pipeline_desc = string.joinv(" ", effective_args);
        if(!pipeline_desc.contains("!")) {
            printerr("Not a valid pipeline\n");
            return 1;
        }
    }

    tv = TimeVal();
    Gst.init(ref args);
    tv = TimeVal();
    print(" 'init' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);


    try {
        print(" 'description' : '%s',\n", pipeline_desc);
        auto_pipeline.parse_launch(pipeline_desc);
        tv = TimeVal();
        print(" 'launch' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
    }
    catch(Error e) {
        printerr("Error: %s\n", e.message);
        if(auto_pipeline.pipeline != null)
            auto_pipeline.state = Gst.State.NULL;
        return 1;
    }

    foreach(var task in tasks)
        auto_pipeline.exec_task(task);

    var loop = new MainLoop();
    auto_pipeline.quit += loop.quit;
    if(auto_pipeline.print_messages)
        print(" 'message' : [\n");
    loop.run();
    if(auto_pipeline.print_messages)
        print(" ],\n");
    auto_pipeline.state = Gst.State.NULL;
    tv = TimeVal();
    print(" 'end' : %6lu.%06lu,\n", tv.tv_sec, tv.tv_usec);
    print("}\n");
    return 0;
}


bool try_to_get_desc_from_xml(string[] args, ref string pipeline_desc) {
    var xml_file = args[1];
    if(!FileUtils.test(xml_file, FileTest.IS_REGULAR)) {
        printerr("'%s' is not a regular file\n", xml_file);
        return false;
    }

    var parser = new XmlParser();
    var parsed = false;

    try {
        parsed = parser.parse_file(xml_file);
    }
    catch(Error e) {
        printerr("Error: %s\n", e.message);
        return false;
    }

    if(!parsed) {
        printerr("Could not parse file '%s'\n", xml_file);
        return false;
    }

    var pipeline_id = args[2];

    pipeline_desc = parser[pipeline_id];
    if(pipeline_desc == null) {
        printerr("No pipeline found for id '%s'\n", pipeline_id);
        return false;
    }

    printerr("Getting pipeline description from file '%s'\n", xml_file);
    return true;
}

