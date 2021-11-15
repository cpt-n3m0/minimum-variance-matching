import numpy as np
from cffi import FFI

ffi =  FFI()

# q = [1, 2, 8, 6, 8]
# t = [1, 2, 9, 3, 3, 5, 9]
q = [0.0, 0.9252726978168981, 1.0, 0.6713158366378984, 0.60317265522059, 0.42315022197739866, 0.4285243710280754, 0.3002655804513076, 0.27819876769320073, 0.23459553614258344, 0.18455819491825076, 0.16422998142614934, 0.12848022966610997]
t = [0.0, 0.062429049502839104, 0.9912598621664643, 1.0, 0.8541429353141469, 0.691770689508663, 0.5702610588598883, 0.44807037921271536, 0.38507375279485556, 0.3286038414346032, 0.3284335927161369, 0.3372871485085173, 0.25141316449365686, 0.18739499164046589, 0.175936422076098, 0.14977297464644504, 0.07763904457209415]

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
    print("here")
    res = mvmlib.mvm(query, lq, target, lt)
    #format output to be similar to that of dtw
    p1 = [res.matches[i][0] for i in range(lq)]
    p2 = [res.matches[i][1] for i in range(lq)]
    distance = res.distance
    return (np.array(p1), np.array(p2)), distance



mvm(q, t)
