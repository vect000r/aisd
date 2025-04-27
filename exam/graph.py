# Graph representation from class
# Adjacency matrix style 

def makeGraph(mx = 5):
    return [[0 for _ in range(mx)] for _ in range(mx)]

def addEdge(g, x, y):
    from copy import deepcopy
    gg = deepcopy(g)
    gg[x][y] = 1
    return gg

def neighbours(g, x):
    nei = []
    for i in range(len(g)):
        if g[x][i] == 1:
            nei.append(i)
    return nei

