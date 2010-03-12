int main(string[] args) {
    if(args.length < 4) {
        print("Usage: %s <pipelines.xml> <pipeline_id> <commands>\n", args[0]);
        print("Supported commands are:\n");

        uint i = 0;
        while(true) {
            Command command = COMMANDS[i];
            if(command.name == null)
                break;
            print("  -%s:\n    %s\n", command.name, command.description);
            i++;
        }

        return 1;
    }

    var pipelines_config = args[1];
    if(!FileUtils.test(pipelines_config, FileTest.IS_REGULAR)) {
        print("'%s' is not a regular file\n", pipelines_config);
        return 1;
    }


    var parser = new ConfigParser();
    var parsed = false;

    try {
        parsed = parser.parse_file(pipelines_config);
    }
    catch(Error e) {
        print("Error: %s\n", e.message);
    }

    if(!parsed) {
        print("Could not parse file '%s'\n", pipelines_config);
        return 1;
    }

    var pipeline_id = args[2];

   
    var description = parser[pipeline_id];
    if(description == null) {
        print("No pipeline found for id '%s'\n", pipeline_id);
        return 1;
    }

    var pipeline = new AutoPipeline();

    Gst.init(ref args);


    try {
        pipeline.parse(description);
    }
    catch(Error e) {
        print("Error: %s\n", e.message);
        return 1;
    }

    pipeline.parse_parameters(args[3 : args.length]);
    pipeline.exec_parameters();
    pipeline.loop.run();
    return 0;
}

