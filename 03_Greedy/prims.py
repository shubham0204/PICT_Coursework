class Graph:
    def __init__(self, num_nodes: int):
        self.num_nodes = num_nodes
        self.adj_list = [[] for _ in range(self.num_nodes)]
        self.edges = []

    def add_edge(self, node_1: int, node_2: int, weight: int):
        self.adj_list[node_1].append((node_2, weight))
        self.adj_list[node_2].append((node_1, weight))
        self.edges.append((node_1, node_2, weight))

    def check_cycle(self, src: int, dst: int) -> bool:
        queue = [src]
        visited = [src]
        while len(queue) != 0:
            front = queue[0]
            del queue[0]
            if front == dst:
                return True
            neighbors = self.adj_list[front]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])
        return False

    def bfs(self):
        queue = [0]
        visited = [0]
        travel_sequence = []
        while len(queue) != 0:
            front = queue[0]
            del queue[0]
            travel_sequence.append(front)
            neighbors = self.adj_list[front]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])
        print(travel_sequence)

    def __str__(self) -> str:
        str_repr = ""
        for i in range(len(self.adj_list)):
            str_repr += f"{i} {self.adj_list[i]}\n"
        return str_repr


def min_spanning_tree(graph: Graph):
    curr_node: int = 0
    tree_num_nodes: int = 1
    min_cost: int = 0
    visited: list[int] = [curr_node]
    spanning_tree: Graph = Graph(graph.num_nodes)
    while tree_num_nodes != graph.num_nodes:
        min_weight_edge = min(
            [
                neighbor
                for neighbor in graph.adj_list[curr_node]
                if neighbor[0] not in visited
            ],
            key=lambda x: x[1],
        )
        spanning_tree.add_edge(curr_node, min_weight_edge[0], min_weight_edge[1])
        min_cost += min_weight_edge[1]
        curr_node = min_weight_edge[0]
        tree_num_nodes += 1
        visited.append(min_weight_edge[0])
    print(min_cost)


graph = Graph(5)
graph.add_edge(0, 1, 1)
graph.add_edge(1, 2, 3)
graph.add_edge(2, 3, 4)
graph.add_edge(0, 2, 7)
graph.add_edge(0, 3, 10)
graph.add_edge(3, 4, 2)
graph.add_edge(0, 4, 5)
graph.bfs()

min_spanning_tree(graph)
