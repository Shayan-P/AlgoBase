import os
import re
import argparse
from datetime import datetime

lib_path = os.path.join(os.path.dirname(__file__), 'lib') # change this if you were move lib or this script

def main():
    parser = argparse.ArgumentParser()
    
    parser.add_argument("--inp", help="input file", required=True)
    parser.add_argument("--out", help="output file")
    args = parser.parse_args()

    if not args.inp.endswith(".cpp"):
        raise Exception("input file should be .cpp")
    if args.out is None:
        args.out = args.inp.removesuffix('.cpp') + "_bundle.cpp"

    current_datetime = datetime.now()
    datetime_string = current_datetime.strftime("%Y-%m-%d %H:%M:%S")
    result = f"""
// AlgoBase {datetime_string}
"""
    result += recurse(os.path.abspath(args.inp))

    print(args.out)
    with open(args.out, 'w') as f:
        f.write(result)


def find_full_path(filename, from_path):
    filename_candids = [filename]
    if filename.startswith("AlgoBase/"):
        filename_candids.append(filename.removeprefix("AlgoBase/"))
    for filename in filename_candids:
        from_path_iter = from_path
        while from_path_iter.startswith(lib_path):
            candid_path = os.path.abspath(os.path.join(from_path_iter, filename))
            if os.path.exists(candid_path):
                return candid_path    
            from_path_iter = os.path.dirname(from_path_iter)
    raise Exception(f"{filename} not found within {from_path}")


def get_included_files(text, from_path):
    pattern = r'#include\s*"([^"]+)"'
    matches = re.findall(pattern, text)
    return re.sub(pattern, "", text), [find_full_path(match, from_path) for match in matches] 


def recurse(filename, visited=set(), from_path=lib_path):
    visited.add(filename)
    res = ""
    with open(filename, 'r') as f:
        text = f.read()
        text, paths = get_included_files(text, from_path)
        for path in paths:
            pathname = path.split("/")[-1] 
            if path not in visited:
                res += f"""
// start {pathname}
"""
                res += recurse(path, visited, os.path.dirname(path)) 
                res += f"""
// end {pathname}
"""
        res += text
    return res


if __name__ == "__main__":
    main()
