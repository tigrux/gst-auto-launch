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
            CharacterSet.a_2_z + CharacterSet.A_2_Z + "_-0123456789";
    }


    public Task? get_task_from_arg(string arg) {
        if(!arg.contains(":"))
            return null;
        scanner.input_text(arg, (uint)arg.length);

        TokenType token;

        var number = get_seconds(out token);
        last_time_seconds = number;

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
        var task = new Task(number, command);

        uint arg_i = 0;
        while( (token = scanner.get_next_token()) == ':') {
            var arg_desc = command.get_arg_desc(arg_i);
            if(arg_desc == 0)
                break;

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
            else
            if(token == TokenType.INT || token == TokenType.FLOAT ||
               token == '+' || token == '-') {
                if(arg_desc == 't') {
                    number = get_seconds(out token);
                    task.arguments.append(number);
                }
                else {
                    number = get_signed_number(out token);
                    task.arguments.append(number);
                }
            }
            arg_i++;
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
            number = scanner.value.int;
        else if(token == TokenType.FLOAT)
            number = scanner.value.float;
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

