class ConfigParser: Object {
    const MarkupParser _parser = {
        start,
        end,
        text,
        null,
        null
    };

    MarkupParseContext _context;
    string _current_id;
    HashTable<string, string> _ht;

    construct {
        _context = new MarkupParseContext(_parser, 0, this, null);
        _ht = new HashTable<string, string> (str_hash, str_equal);
    }


    public new string? get(string key) {
        return _ht.lookup(key);
    }

    public bool parse(string content)
    throws MarkupError {
        return _context.parse(content, -1);
    }


    public bool parse_file(string filename) throws Error {
        string content;
        if(FileUtils.get_contents(filename, out content, null))
            return parse(content);
        return false;
    }

    void start(MarkupParseContext context, string name,
               string[] attr_names, string[] attr_values)
    throws MarkupError {
        if(name == "pipeline") {
            uint i=0;
            weak string attr_name;
            while((attr_name = attr_names[i]) != null) {
                if(attr_name == "id") {
                    weak string id = attr_values[i];
                    _current_id = id;
                }
                i++;
            }
        }
    }


    void end(MarkupParseContext context, string name)
    throws MarkupError {
        _current_id = null;
    }


    void text(MarkupParseContext context, string text, size_t text_len)
    throws MarkupError {
        string stripped_text = text.strip();
        if(_current_id != null)
            _ht.insert(_current_id, stripped_text);
        else
            warning(
                "Got text '%s' but there is no current pipeline\n",
                stripped_text);
    }
}

