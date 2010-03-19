int main(string[] args) {
    var auto_pipeline = new AutoPipeline();

    if(args.length < 2) {
        print("Usage: %s <pipelines.xml> <pipeline_id> <commands>\n", args[0]);
        print("Where each command is of the form <seconds>:<name>\n");
        print("Supported commands are:\n");

        auto_pipeline.scanner.scope_foreach_symbol(0,
            (key, val) => {
                var name = (string)key;
                var command = (Command*)val;
                print("  %s:\n    %s\n", name, command->description);
            }
        );

        print("\nIf no xml file can be parsed, it will get the pipeline from the command line\n\n");
        print("Examples:\n");
        print("  %s pipelines.xml videotest 0:pause 1:play +5:eos\n", args[0]);
        print("  %s videotestsrc ! autovideosink 0:pause 1:play +5:eos\n", args[0]);

        return 1;
    }

    string[] remaining_args;
    var tasks = auto_pipeline.parse_tasks_from_args(args, out remaining_args);

    var effective_args_list = new List<string> ();
    foreach(var arg in remaining_args)
        if(!arg.has_prefix("-"))
            effective_args_list.append(arg);

    var should_parse_xml = false;
    
    if(effective_args_list.length() == 3)
        if(!("=" in effective_args_list.nth_data(2)))
            should_parse_xml = true;

    string pipeline_desc = null;

    if(should_parse_xml) {
        should_parse_xml = try_to_get_desc_from_xml(args, ref pipeline_desc);
        if(!should_parse_xml)
            print("Could get pipeline description from xml file\n");
    }

    if(!should_parse_xml) {
        print("Getting pipeline description from the command line\n");

        uint i = 0;
        var effective_args = new string[effective_args_list.length()];
        foreach(var arg in effective_args_list) {
            effective_args[i] = arg;
            i++;
        }
        pipeline_desc = string.joinv(
            " ", effective_args[1:effective_args.length]);
    }

    Gst.init(ref remaining_args);

    try {
        print("Pipeline to use is:\n%s\n\n", pipeline_desc);
        auto_pipeline.parse_launch(pipeline_desc);
    }
    catch(Error e) {
        print("Error: %s\n", e.message);
        if(auto_pipeline.pipeline != null)
            auto_pipeline.state = Gst.State.NULL;
        return 1;
    }

    auto_pipeline.timer.start();
    foreach(var task in tasks)
        auto_pipeline.exec_task(task);

    auto_pipeline.loop.run();
    auto_pipeline.state = Gst.State.NULL;
    return 0;
}


bool try_to_get_desc_from_xml(string[] args, ref string pipeline_desc) {
        var xml_file = args[1];
        if(!FileUtils.test(xml_file, FileTest.IS_REGULAR)) {
            print("'%s' is not a regular file\n", xml_file);
            return false;
        }

        var parser = new XmlParser();
        var parsed = false;

        try {
            parsed = parser.parse_file(xml_file);
        }
        catch(Error e) {
            print("Error: %s\n", e.message);
            return false;
        }

        if(!parsed) {
            print("Could not parse file '%s'\n", xml_file);
            return false;
        }

        var pipeline_id = args[2];

        pipeline_desc = parser[pipeline_id];
        if(pipeline_desc == null) {
            print("No pipeline found for id '%s'\n", pipeline_id);
            return false;
        }

        print("Getting pipeline description from file '%s'\n", xml_file);
        return true;
}

