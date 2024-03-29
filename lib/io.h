#pragma once

#include<iostream>
#include<vector>

template<typename A, typename B> std::ostream& operator << (std::ostream& out, std::pair<A, B> p);
template<typename T> std::ostream& operator << (std::ostream& out, std::vector<T> v);
template<typename A, typename B> std::istream& operator >> (std::istream& in, std::pair<A, B> &p);
template<typename T> std::ostream& operator << (std::ostream& out, std::optional<T> opt);

#include "data_structure/groups.h"

template<typename T> std::ostream& operator << (std::ostream& out, const data_structure::Group<T> &g);

template<typename T> std::ostream& operator << (std::ostream& out, const data_structure::Group<T> &g){
    out << "G{" << g.val << "}";
    return out;
}

template<typename A, typename B> std::ostream& operator << (std::ostream& out, std::pair<A, B> p){
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}
template<typename T> std::ostream& operator << (std::ostream& out, std::vector<T> v){
    out << "[";
    for(int i = 0; i < (int)v.size(); i++){
	out << v[i];
	if(i+1 != (int)v.size())
	    out << ", ";
    }
    out << "]";
    return out;
}
template<typename T> std::ostream& operator << (std::ostream& out, std::optional<T> opt){
    out << "Opt{";
    if(opt.has_value())
        out << opt.value();
    out << "}";
    return out;
}
template<typename A, typename B> std::istream& operator >> (std::istream& in, std::pair<A, B> &p){
    in >> p.first >> p.second;
    return in;
}

template<typename T>
inline std::vector<T> read_vector(int n) {
    std::vector<T> res(n);
    for(int i = 0; i < n; i++) {
        std::cin >> res[i];
    }
    return res;
}
