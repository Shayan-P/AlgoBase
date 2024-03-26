#pragma once

namespace data_structure {
    template<typename ValueType>
    class SegmentTreeSimple {
    protected:
        std::vector<ValueType> data;
        int n;

    public:
        SegmentTreeSimple(int _n): n(_n), data(4 * _n) {}

        inline void add(int pos, ValueType val) { _add(pos, val, 0, n, 1); }
        inline void set(int pos, ValueType val) { _set(pos, val, 0, n, 1); }
        inline ValueType ask(int f, int s) { if(f >= s) return ValueType(); return _ask(f, s, 0, n, 1); }

        void _add(int pos, ValueType val, int l, int r, int id) {
            data[id]+= val;
            if(r-l == 1)
                return;
            int mid = (l+r)>>1;
            if(pos < mid)
                _add(pos, val, l, mid, 2*id);
            else    
                _add(pos, val, mid, r, 2*id+1);
        }

        void _set(int pos, ValueType val, int l, int r, int id) {
            if(r-l == 1) {
                data[id] = val;
                return;
            }
            int mid = (l+r)>>1;
            if(pos < mid)
                _set(pos, val, l, mid, 2*id);
            else
                _set(pos, val, mid, r, 2*id+1);
            data[id] = data[2 * id];
            data[id]+= data[2 * id+1];
        }

        ValueType _ask(int f, int s, int l, int r, int id) { // [f, s)
            if(f <= l && r <= s) {
                return data[id];
            }
            int mid = (l+r)>>1;
            if(mid <= f) return _ask(f, s, mid, r, 2*id+1);
            if(s <= mid) return _ask(f, s, l, mid, 2*id);
            ValueType res = _ask(f, s, l, mid, 2*id);
            res += _ask(f, s, mid, r, 2*id+1);
            return res;
        }
    };

    template<typename ValueType>
    class SegmentTreeAbstract {
        using LazyType = ValueType;
    protected:
        std::vector<ValueType> data;
        std::vector<LazyType> lazy;
        std::vector<std::optional<LazyType>> lazy_set;

        int n;

    public:
        SegmentTreeAbstract(int _n): n(_n), data(4 * _n), lazy(4 * _n), lazy_set(4 * _n) {}

        inline void add(int pos, ValueType val) { _add(pos, val, 0, n, 1); }
        inline void add(int f, int s, ValueType val) { if(f >= s) return; _add(f, s, val, 0, n, 1); }
        inline void set(int pos, ValueType val) { _set(pos, val, 0, n, 1); }
        inline void set(int f, int s, ValueType val) { _set(f, s, val, 0, n, 1); }
        inline ValueType ask(int f, int s) { if(f >= s) return ValueType(); return _ask(f, s, 0, n, 1); }
        inline void print() { _print(0, n, 1); }

    protected:
        void _add(int pos, ValueType val, int l, int r, int id) {
            push_down(l, r, id);
            data[id] += val;
            if(r-l == 1) {
                return;
            }
            int mid = (l+r)>>1;
            if(pos < mid)
                _add(pos, val, l, mid, 2*id);
            else
                _add(pos, val, mid, r, 2*id+1);
        }

        void _add(int f, int s, ValueType val, int l, int r, int id) { // [f, s)
            push_down(l, r, id);
            int mid = (l+r)>>1;
            if(f <= l && r <= s) {
                lazy[id]+= val;
                push_down(l, r, id);
                return;
            }
            if(l < s && f < r) {
                _add(f, s, val, l, mid, 2*id);
                _add(f, s, val, mid, r, 2*id+1);
                // merge
                data[id] = data[2 * id];
                data[id] += data[2*id+1];
            }
        }

        void _set(int pos, ValueType val, int l, int r, int id) {
            push_down(l, r, id);
            if(r-l == 1) {
                data[id] = val;
                return;
            }
            int mid = (l+r)>>1;
            if(pos < mid)
                _set(pos, val, l, mid, 2*id), push_down(mid, r, 2*id+1); // in order to be able to update, children should be pushed down
            else
                _set(pos, val, mid, r, 2*id+1), push_down(l, mid, 2*id);
            data[id] = data[2 * id];
            data[id]+= data[2 * id+1];
        }

        void _set(int f, int s, ValueType val, int l, int r, int id) { // [f, s)
            push_down(l, r, id);
            int mid = (l+r)>>1;
            if(f <= l && r <= s) {
                lazy_set[id] = val;
                push_down(l, r, id);
                return;
            }
            if(l < s && f < r) {
                _set(f, s, val, l, mid, 2*id);
                _set(f, s, val, mid, r, 2*id+1);
                // merge
                data[id] = data[2 * id];
                data[id] += data[2*id+1];
            }
        }

        ValueType _ask(int f, int s, int l, int r, int id) { // [f, s)
            push_down(l, r, id);
            if(f <= l && r <= s) {
                return data[id];
            }
            int mid = (l+r)>>1;
            if(mid <= f) return _ask(f, s, mid, r, 2*id+1);
            if(s <= mid) return _ask(f, s, l, mid, 2*id);
            ValueType res = _ask(f, s, l, mid, 2*id);
            res += _ask(f, s, mid, r, 2*id+1);
            return res;
        }

        void push_down(int l, int r, int id) {
            // there can only be one lazy type there at each point because we shift down at each point...
            // assume lazy_set has priority
            if(lazy_set[id].has_value()) {
                if(r-l > 1) {
                    lazy_set[2*id] = lazy_set[id];
                    lazy_set[2*id+1] = lazy_set[id];
                    lazy[2*id].reset();
                    lazy[2*id+1].reset();
                }
                set_aggregate(data[id], lazy_set[id].value(), r-l);
                lazy_set[id] = {};
            }

            if(r-l > 1) {
                if(lazy_set[2*id].has_value())
                    lazy_set[2*id].value() += lazy[id];
                else
                    lazy[2*id] += lazy[id];
                if(lazy_set[2*id+1].has_value())
                    lazy_set[2*id+1].value() += lazy[id];
                else
                    lazy[2*id+1] += lazy[id];
            }
            sum_aggregate(data[id], lazy[id], r-l);
            lazy[id].reset();
        }

        void _print(int l, int r, int id) {
            cout << "l=" << l << ", r=" << r << ", id=" << id << ", data=" << data[id] << ", lazy_set[id]=" << lazy_set[id] << ", lazy[id]=" << lazy[id] << endl;
            if(r-l <= 1)
                return;
            int mid = (l+r)>>1;
            _print(l, mid, 2*id);
            _print(mid, r, 2*id+1);
        }
    };



    template<typename ValueType, typename ModifierType>
    class SegmentTreeGenericModification {
    protected:
        std::vector<ValueType> data;
        std::vector<ModifierType> lazy;

        int n;

    public:
        SegmentTreeGenericModification(int _n): n(_n), data(4 * _n), lazy(4 * _n) {}

        inline void add(int pos, ModifierType val) { _add(pos, val, 0, n, 1); }
        inline void add(int f, int s, ModifierType val) { if(f >= s) return; _add(f, s, val, 0, n, 1); }
        inline void set(int pos, ValueType val) { _set(pos, val, 0, n, 1); }
        inline ValueType ask(int f, int s) { if(f >= s) return ValueType(); return _ask(f, s, 0, n, 1); }
        inline void print() { _print(0, n, 1); }

    protected:
        void _add(int pos, ModifierType md, int l, int r, int id) {
            push_down(l, r, id);
            if(r-l == 1) {
                data[id] += md;
                return;
            }
            int mid = (l+r)>>1;
            if(pos < mid)
                _add(pos, md, l, mid, 2*id), push_down(mid, r, 2*id+1);
            else
                _add(pos, md, mid, r, 2*id+1), push_down(l, mid, 2*id);
            data[id] = data[2 * id];
            data[id] += data[2*id+1];
        }

        void _set(int pos, ValueType val, int l, int r, int id) {
            push_down(l, r, id);
            if(r-l == 1) {
                data[id] = val;
                return;
            }
            int mid = (l+r)>>1;
            if(pos < mid)
                _set(pos, val, l, mid, 2*id), push_down(mid, r, 2*id+1);
            else
                _set(pos, val, mid, r, 2*id+1), push_down(l, mid, 2*id);
            data[id] = data[2 * id];
            data[id] += data[2*id+1];
        }

        void _add(int f, int s, ModifierType md, int l, int r, int id) { // [f, s)
            push_down(l, r, id);
            int mid = (l+r)>>1;
            if(f <= l && r <= s) {
                lazy[id]+= md;
                push_down(l, r, id);
                return;
            }
            if(l < s && f < r) {
                _add(f, s, md, l, mid, 2*id);
                _add(f, s, md, mid, r, 2*id+1);
                // merge
                data[id] = data[2 * id];
                data[id] += data[2*id+1];
            }
        }

        ValueType _ask(int f, int s, int l, int r, int id) { // [f, s)
            push_down(l, r, id);
            if(f <= l && r <= s) {
                return data[id];
            }
            int mid = (l+r)>>1;
            if(mid <= f) return _ask(f, s, mid, r, 2*id+1);
            if(s <= mid) return _ask(f, s, l, mid, 2*id);
            ValueType res = _ask(f, s, l, mid, 2*id);
            res += _ask(f, s, mid, r, 2*id+1);
            return res;
        }

        void push_down(int l, int r, int id) {
            if(r-l > 1) {
                lazy[2*id] += lazy[id];
                lazy[2*id+1] += lazy[id];
            }
            sum_aggregate(data[id], lazy[id], r-l);
            lazy[id].reset();
        }

        void _print(int l, int r, int id) {
            cout << "l=" << l << ", r=" << r << ", id=" << id << ", data=" << data[id] << ", lazy[id]=" << lazy[id] << endl;
            if(r-l <= 1)
                return;
            int mid = (l+r)>>1;
            _print(l, mid, 2*id);
            _print(mid, r, 2*id+1);
        }
    };
}
