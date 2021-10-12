import os
import sys
from subprocess import PIPE, Popen

import numpy as np
from matplotlib import pyplot as plt

INSTANCE_DIR = "./instances"

def load_instance(path):
    instance = np.array([])
    instance.shape = (2, 0)

    with open(path, 'r') as f:
        n = int(next(f))
        for _ in range(n):
            _, x, y = [int(x) for x in next(f).split()]
            instance = np.concatenate((instance, np.array([[x], [y]])), axis=1)
    
    with open(path, 'r') as f:
        return (instance, f.read())

def trace(instance, hamilton):
    lines = np.array([])
    lines.shape = (2, 0)

    hamilton.append(hamilton[0])
    for h in hamilton:
        x, y = instance.T[h - 1].T
        lines = np.concatenate((lines, np.array([[x], [y]])), axis=1)
    plt.plot(*lines, color = 'tab:blue')

def process_instance(filepath):
    instance, txt = load_instance(filepath)

    process = Popen(['greedy.exe', 'f'], stdout=PIPE, stdin=PIPE)    
    out = process.communicate(input=str.encode(txt))[0].decode()
    hamilton = [int(x) for x in out.split()]

    plt.scatter(*instance)
    trace(instance, hamilton)

    plt.show()

if len(sys.argv) == 1:
    for filename in os.listdir(INSTANCE_DIR):
        filepath = INSTANCE_DIR + '/' + filename
        process_instance(filepath)
else:
    for filepath in sys.argv[1:]:
        process_instance(filepath)
