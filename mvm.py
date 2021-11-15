import numpy as np
from cffi import FFI

ffi =  FFI()

# q = [1, 2, 8, 6, 8]
# t = [1, 2, 9, 3, 3, 5, 9]

ffi.cdef("""
    typedef struct match_t {
                  int** matches;
                  float distance;
                  }
    match_t; match_t mvm(float* query, int lenq, float* target, int lent); 
""")
mvmlib = ffi.dlopen("./libmvm.so")

def mvm(query, target):
    lq = len(query)
    lt = len(target)
    query = ffi.new(f"float[{lq}]", query)
    target = ffi.new(f"float[{lt}]", target)
    res = ffi.new("match_t *")
    res = mvmlib.mvm(query, lq, target, lt)

    p1 = [res.matches[i][0] for i in range(lq)]
    p2 = [res.matches[i][1] for i in range(lq)]
    distance = res.distance
    return (np.array(p1), np.array(p2)), distance



mvm(q, t)
