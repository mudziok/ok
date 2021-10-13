import os
import sys
from subprocess import PIPE, Popen

import numpy as np
from matplotlib import pyplot as plt

INSTANCE_DIR = "instances"

def run_exe(filepath, stdin):
    process = Popen([filepath, 'f'], stdout=PIPE, stdin=PIPE)    
    stdout = process.communicate(input=str.encode(stdin))[0].decode()
    return stdout

def load_instance_file(filepath):
    instance = np.array([])
    instance.shape = (0, 2)

    with open(filepath, 'r') as f:
        n = int(next(f))
        for _ in range(n):
            _, x, y = [int(x) for x in next(f).split()]
            instance = np.concatenate((instance, np.array([[x, y]])))
    
    with open(filepath, 'r') as f:
        return (instance, f.read())

def trace(instance, hamilton):
    lines = np.array([])
    lines.shape = (0, 2)

    hamilton.append(hamilton[0])
    for h in hamilton:
        x, y = instance[h - 1]
        lines = np.concatenate((lines, np.array([[x, y]])))
    plt.plot(*lines.T, color = 'tab:blue')

def process_instance(filepath):
    instance, txt = load_instance_file(filepath)

    stdout = run_exe('greedy.exe', txt)
    hamilton = [int(x) for x in stdout.split()]

    plt.title(filepath)
    plt.scatter(*instance.T, color = 'tab:blue')
    trace(instance, hamilton)

    plt.show()

if __name__ == '__main__':
    if len(sys.argv) == 1:
        for filename in os.listdir(INSTANCE_DIR):
            filepath = INSTANCE_DIR + '/' + filename
            process_instance(filepath)
    else:
        for filepath in sys.argv[1:]:
            process_instance(filepath)