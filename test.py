import time

numbers = range(1000000)

number_list = list(numbers)


start_time = time.time()
print(51232422 in number_list)
end_time = time.time()
print(f"list took {end_time - start_time} seconds")

number_set = set(numbers)
start_time = time.time()
print(51232422 in number_set)
end_time = time.time()
print(f"set took {end_time - start_time} seconds")