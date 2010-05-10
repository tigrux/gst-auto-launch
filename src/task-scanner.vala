class TaskScanner: Scanner {
    public TaskScanner() {
        base(null);
        config.scan_identifier_1char = false;
        scanner_register_symbols(this, 0);
    }


    public List<Task> get_tasks_from_args(string[] args) {
        double last_time_seconds = 0;
        var tasks = new List<Task> ();

        foreach(var arg in args) {
            if(arg.has_prefix("--"))
                continue;

            input_text(arg, (uint)arg.length);

            var relative = 0;
            var tok_type = peek_next_token();
            if(tok_type == TokenType.EOF)
                break;
            
            if(tok_type == '+')
                relative = 1;
            else if(tok_type == '-')
                relative = -1;
            
            if(relative != 0)
                get_next_token();

            tok_type = peek_next_token();
            if(tok_type != TokenType.FLOAT && tok_type != TokenType.INT)
                continue;
            get_next_token();

            double seconds;
            if(tok_type == TokenType.FLOAT)
                seconds = value.float;
            else
                seconds = value.int;

            if(relative != 0)
                seconds = last_time_seconds + relative*seconds;

            if(peek_next_token() != ':')
                continue;
            get_next_token();

            if(peek_next_token() != TokenType.SYMBOL)
                continue;
            get_next_token();
            var command = (Command?)value.symbol;

            var task = new Task(seconds, command);

            while(peek_next_token() == ':') {
                get_next_token();
                tok_type = get_next_token();
                switch(tok_type) {
                    case TokenType.INT:
                        task.arguments.append(value.int);
                        break;
                    case TokenType.FLOAT:
                        task.arguments.append(value.float);
                        break;
                    case TokenType.IDENTIFIER:
                    case TokenType.STRING:
                        if(value.string == "true")
                            task.arguments.append(true);
                        else if(value.string == "false")
                            task.arguments.append(false);
                        else
                            task.arguments.append(value.string);
                        break;
                    default:
                        printerr("** TokType = %c\n", tok_type);
                        break;
                }
            }

            tasks.append(task);
            last_time_seconds = seconds;
        }
        return tasks;
    }
}

