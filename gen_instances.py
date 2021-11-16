import random

def get_town(map_size):
    x = random.randint(0, map_size)
    y = random.randint(0, map_size)
    return (x, y)

def get_instance_string(quantity, map_size):
    instance = f"{quantity}\n"

    for i in range(quantity):
        x, y = get_town(map_size)
        instance += f'{i + 1} {x} {y}\n'

    return instance

print(get_instance_string(6, 1000))