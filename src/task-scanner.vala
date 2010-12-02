class TaskScanner: Object {
    Scanner scanner;
    double last_time_seconds;


    public TaskScanner() {
        last_time_seconds = 0;
        scanner = new Scanner(null);
        scanner.config.scan_identifier_1char = true;
        scanner.config.identifier_2_string = true;
        scanner_register_symbols(scanner, 0);
        scanner.config.cset_identifier_nth =
            CharacterSet.a_2_z + CharacterSet.A_2_Z + " _-0123456789" +
            CharacterSet.LATINC + CharacterSet.LATINS;
    }


    public Task? get_task_from_arg(string arg) {
        if(!arg.contains(":"))
            return null;
        scanner.input_text(arg, (uint)arg.length);

        TokenType token;

        double number = get_seconds(out token);
        if(token != TokenType.INT && token != TokenType.FLOAT)
            return null;

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

        weak Command? command = (Command?)scanner.value.symbol;
        Task task = new Task(number, command);

        uint arg_n = 0;
        while( (token = scanner.get_next_token()) == ':') {
            char arg_desc = command.get_arg_desc(arg_n);

            token = scanner.peek_next_token();
            if(token == TokenType.STRING) {
                scanner.get_next_token();
                string s = scanner.value.string;
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
                    task.arguments.append((double)number);
                }
                else {
                    number = get_signed_number(out token);
                    if(token == TokenType.INT)
                        task.arguments.append((int)number);
                    else
                    if(token == TokenType.FLOAT)
                        task.arguments.append((double)number);
                }
            }
            arg_n++;
        }

        if(command.get_n_args() != task.arguments.n_values) {
            printerr("Command '%s' takes %u arguments (got %u)\n",
                command.name, command.get_n_args(), task.arguments.n_values);
            return null;
        }

        for(uint arg_i = 0; arg_i < arg_n; arg_i++) {
            char arg_desc = command.get_arg_desc(arg_i);
            Value arg_value = task.arguments.values[arg_i];
            switch(arg_desc) {
                case 's':
                    if(!arg_value.holds(typeof(string))) {
                        printerr("Argument %u of '%s' must be a string\n",
                            arg_i, command.name);
                        return null;
                    }
                    break;
                case 'i':
                    if(!arg_value.holds(typeof(int))) {
                        printerr("Argument %u of '%s' must be an integer\n",
                            arg_i, command.name);
                        return null;
                    }
                    break;
                case 't':
                    if(!arg_value.holds(typeof(double))) {
                        printerr("Argument %u of '%s' must be in seconds\n",
                            arg_i, command.name);
                        return null;
                    }
                    number = arg_value.get_double();
                    if(number < 0.0) {
                        printerr("Argument %u of '%s' cannot be negative\n",
                            arg_i, command.name);
                        return null;
                    }
                    break;
            }
        }

        return task;
    }


    double get_seconds(out TokenType last_token) {
        int relative;
        double seconds = get_number(out last_token, out relative);

        if(relative != 0)
            seconds += relative * last_time_seconds;

        return seconds;
    }


    double get_signed_number(out TokenType last_token) {
        int relative;
        double number = get_number(out last_token, out relative);

        if(relative == -1)
            return -number;
        return number;
    }


    double get_number(out TokenType last_token, out int relative) {
        double number;
        TokenType token = scanner.get_next_token();

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
                string name = (string)key;
                weak Command? command = (Command?)val;
                printerr("  %s:\n    %s\n", name, command.description);
            }
        );
    }


    public unowned Command? lookup_command(string command_name) {
        return (Command?)scanner.lookup_symbol(command_name);
    }
}

