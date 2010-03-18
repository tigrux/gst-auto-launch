int main(string[] args) {
    var pipeline = new AutoPipeline();

    if(args.length < 4) {
        print("Usage: %s <pipelines.xml> <pipeline_id> <commands>\n", args[0]);
        print("Where each command is of the form <seconds>:<name>\n");
        print("Supported commands are:\n");

        pipeline.scanner.scope_foreach_symbol(0,
            (key, val) => {
                var name = (string)key;
                var command = (Command*)val;
                print("  %s:\n    %s\n", name, command->description);
            }
        );

        print("\nExample:\n");
        print("%s pipelines.xml videotest 0:pause 1:play +5:eos\n", args[0]);

        return 1;
    }

    var pipelines_config = args[1];
    if(!FileUtils.test(pipelines_config, FileTest.IS_REGULAR)) {
        print("'%s' is not a regular file\n", pipelines_config);
        return 1;
    }


    var parser = new XmlParser();
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

    string[] new_args;
    var tasks = pipeline.parse_args(args, out new_args);
    args = new_args;

    Gst.init(ref args);

    try {
        pipeline.parse_launch(description);
    }
    catch(Error e) {
        print("Error: %s\n", e.message);
        return 1;
    }

    pipeline.timer.start();
    foreach(var task in tasks)
        pipeline.exec_task(task);

    pipeline.loop.run();
    return 0;
}

