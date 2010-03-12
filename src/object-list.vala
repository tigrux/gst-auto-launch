class ObjectList<T>: Object {
    List<T> _list;
    uint _length;


    public uint length {
        get {
            return _length;
        }
    }


    public string name {
        get; set;
    }

    construct {
        _list = new List<T>();
    }


    public void append(T s) {
        _list.append(s);
        _length ++;
    }


    public new T get(uint i)
    requires(i < _length) {
        return _list.nth_data(i);
    }


    public Iterator<T> iterator() {
        return new Iterator<T>(this);
    }


    public class Iterator<T> {
        weak List<T> _iter;


        public Iterator(ObjectList<T> list) {
            _iter = list._list;
        }

        
        public bool next() {
            return _iter != null;
        }

        
        public new weak T get() {
            weak T data = _iter.data;
            _iter = _iter.next;
            return data;
        }
    }
}

