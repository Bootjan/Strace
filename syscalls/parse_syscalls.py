def	is_number(str):
	if 'size_t' in str:
		return True
	if 'int' in str:
		return True
	if 'long' in str:
		return True
	if 'unsigned' in str:
		return True
	if 'u64' in str:
		return True
	if 'u32' in str:
		return True
	return False

def	print_arguments(cols):
	print('"', end='')
	for index, el in enumerate(cols):
		if el == '-' or el == '-\n' or el == '?' or el == '?\n':
			print('"')
			return
		if index != 0:
			print(', ', end='')
		if el.find('*') != -1:
			print('%p', end='')
		elif is_number(el) == True:
			print('%i', end='')
		elif el.find('_t') != -1:
			print('%i', end='')
		else:
			print(el, end='')
	print('"')
	

def	print_syscalls():
	file = open('syscall.txt', 'r')
	for line in file:
		cols = line.split('\t')
		# print(cols);
		print(f'"{cols[1]}", ', end='')
		print_arguments(cols[-6:])

print_syscalls()