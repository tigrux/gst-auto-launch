

class TaskScanner: Scanner {

    public TaskScanner() {
        base(null);
        config.scan_identifier_1char = false;
        config.int_2_float = true;
        scanner_register_symbols(this, 0);
    }

    public List<Task> get_tasks_from_args(string[] args) {
        double last_time_seconds = 0;
        var tasks = new List<Task> ();

        foreach(var arg in args) {
            if(arg.has_prefix("--"))
                continue;

            input_text(arg, (uint)arg.length);

            int relative;
            var tok_type = peek_next_token();
            if(tok_type == TokenType.EOF)
                break;
            
            if(tok_type == '+')
                relative = 1;
            else if(tok_type == '-')
                relative = -1;
            else
                relative = 0;
            
            if(relative != 0)
                get_next_token();

            if(peek_next_token() != TokenType.FLOAT)
                continue;
            get_next_token();
            double seconds = value.float;

            if(relative != 0)
                seconds = last_time_seconds + relative*seconds;

            if(peek_next_token() != ':')
                continue;
            get_next_token();

            if(peek_next_token() != TokenType.SYMBOL)
                continue;
            get_next_token();
            var p_command = (Command*)value.symbol;

            var task = new Task(seconds, p_command);
            tasks.append(task);
            last_time_seconds = seconds;
        }
        return tasks;
    }
}

