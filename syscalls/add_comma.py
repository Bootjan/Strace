file = open('result.txt', 'r')

for line in file:
	print(f'\t[{line[:-1]}],')