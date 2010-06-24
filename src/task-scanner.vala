class TaskScanner: Object {
	Scanner scanner;
    double last_time_seconds;


    public TaskScanner() {
    	last_time_seconds = 0;
        scanner = new Scanner(null);
        scanner.config.scan_identifier_1char = false;
        scanner.config.identifier_2_string = true;
        scanner_register_symbols(scanner, 0);
        scanner.config.cset_identifier_nth =
            CharacterSet.a_2_z +
            "_-0123456789" +
            CharacterSet.A_2_Z +
            CharacterSet.LATINS +
            CharacterSet.LATINC;
    }


    public Task? get_task_from_arg(string arg) {
        if(!arg.contains(":"))
            return null;
        scanner.input_text(arg, (uint)arg.length);

        TokenType token;

        var seconds = get_seconds(out token);
        last_time_seconds = seconds;

        token = scanner.get_next_token();
        if(token != ':') {
            printerr("Expected ':' between seconds and command\n");
            return null;
        }

        token = scanner.get_next_token();
        if(token != TokenType.SYMBOL) {
            printerr("Expected a valid command\n");
            return null;
        }

        var command = (Command?)scanner.value.symbol;
        var task = new Task(seconds, command);

        while( (token = scanner.get_next_token()) == ':') {
            token = scanner.peek_next_token();

            if(token == TokenType.STRING) {
                scanner.get_next_token();
                var s = scanner.value.string;
                if(s == "true")
                 task.arguments.append(true);
                else if(s == "false")
                    task.arguments.append(false);
                else
                    task.arguments.append(s);
            }

            if(token == TokenType.INT || token == TokenType.FLOAT ||
               token == '+' || token == '-') {
                var number = get_signed_number(out token);
                task.arguments.append(number);
            }
        }

        return task;
    }


    double get_seconds(out TokenType last_token) {
        int relative;
        var seconds = get_number(out last_token, out relative);

        if(relative != 0)
            seconds += relative * last_time_seconds;

        return seconds;
    }


    double get_signed_number(out TokenType last_token) {
        int relative;
        var number = get_number(out last_token, out relative);

        if(relative == -1)
            return -number;
        return number;
    }


    double get_number(out TokenType last_token, out int relative) {
        double number;
        var token = scanner.get_next_token();

        if(token == '+')
            relative = 1;
        else if(token == '-')
            relative = -1;
        else
            relative = 0;

        if(relative != 0)
            token = scanner.get_next_token();

        if(token == TokenType.INT)
            number = (float)scanner.value.int;
        else if(token == TokenType.FLOAT)
            number = (float)scanner.value.float;
        else
            number = 0;

        last_token = token;
        return number;
    }


    public void print_description() {
        scanner.scope_foreach_symbol(0,
            (key, val) => {
                var name = (string)key;
                var command = (Command*)val;
                printerr("  %s:\n    %s\n", name, command->description);
            }
        );
    }


    public Command? lookup_command(string command_name) {
    	return (Command?)scanner.lookup_symbol(command_name);
    }
}

