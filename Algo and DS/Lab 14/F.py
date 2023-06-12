def diof(a, b):
	if a == 0:
		return 0, 1
	x, y = diof(b % a, a)
	return y - (b // a) * x, x
	
t = int(input())
for _ in range(t):
	a, b, n, m = map(int, input().split())
	x, y = diof(m, n)
	ans = (a * (x % n) * m + b * (y % m) * n) % (n * m)
	print(ans)