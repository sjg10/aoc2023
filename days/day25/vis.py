from pyvis.network import Network
import sys

# Gather all nodes
nodes = set()
edges = set()
with open(sys.argv[1]) as f:
    for l in f:
        nodes.add(l[0:3])
        n=5
        while n < len(l):
            nodes.add(l[n:n+3])
            edges.add((l[0:3], l[n:n+3]))
            n+=4

# And visualise
net=Network()
net.add_nodes(nodes)
for e in edges:
    net.add_edge(e[0], e[1])
net.show('mygraph.html', notebook=False)

