import sys
def solve():
    try:
        n=int(sys.stdin.readline())
        arr=list(map(int,sys.stdin.readline().split()))
    except:
        return
    s=set()
    arr.sort()
    for i in range(n):
        for j in range(i+1,n):
            s.add(arr[j]-arr[i])
    print(len(s))
solve()
