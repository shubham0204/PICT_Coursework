class Graph:
    def __init__(self, num_nodes: int):
        self.num_nodes = num_nodes
        self.adj_list = [[] for _ in range(self.num_nodes)]

    def add_edge(self, node_1: int, node_2: int):
        self.adj_list[node_1].append(node_2)
        self.adj_list[node_2].append(node_1)

    def __str__(self) -> str:
        str_repr = ""
        for i in range(len(self.adj_list)):
            str_repr += f"{i} {self.adj_list[i]}\n"
        return str_repr

    def depth_first_iter(self, key: int):
        stack = [(0, 0)]
        visited = [(0, 0)]
        search_sequence: list[tuple[int, int]] = []
        while len(stack) != 0:
            curr_node = stack[-1]
            curr_node_element = curr_node[0]
            curr_node_level = curr_node[1]
            del stack[-1]
            search_sequence.append(curr_node)
            if curr_node_element == key:
                print(f"Node {curr_node_element} found!")
                break
            neighbors = self.adj_list[curr_node_element]
            for neighbor in neighbors:
                if neighbor not in [visited_element[0] for visited_element in visited]:
                    visited.append((neighbor, curr_node_level + 1))
                    stack.append((neighbor, curr_node_level + 1))
        else:
            print("Node not found by iterative DFS")
        print(f"Search sequence: {search_sequence}")

    def breadth_first_iter(self, key: int):
        queue = [(0, 0)]
        visited = [(0, 0)]
        search_sequence: list[tuple[int, int]] = []
        while len(queue) != 0:
            curr_node = queue[0]
            curr_node_element = curr_node[0]
            curr_node_level = curr_node[1]
            del queue[0]
            search_sequence.append(curr_node)
            if curr_node_element == key:
                print(f"Node {curr_node_element} found!")
                break
            neighbors = self.adj_list[curr_node_element]
            for neighbor in neighbors:
                if neighbor not in [visited_element[0] for visited_element in visited]:
                    visited.append((neighbor, curr_node_level + 1))
                    queue.append((neighbor, curr_node_level + 1))
        else:
            print("Node not found by iterative BFS")
        print(f"Search sequence: {search_sequence}")

    def depth_first_recur(self, key: int):
        visited = []
        self.depth_first_recur_impl(0, visited, key)

    def depth_first_recur_impl(self, node: int, visited: list[int], key: int):
        if node is None:
            return
        if node == key:
            print(f"Visited node {node}")
            print(f"Node {key} found!")
            return
        for neighbor in self.adj_list[node]:
            if neighbor not in visited:
                visited.append(neighbor)
                self.depth_first_recur_impl(neighbor, visited, key)

    def breadth_first_recur(self, key: int):
        queue = [0]
        visited = [0]
        self.breadth_first_recur_impl(queue, visited, key)

    def breadth_first_recur_impl(self, queue: list[int], visited: list[int], key: int):
        if len(queue) == 0:
            return
        front = queue[0]
        del queue[0]
        if front == key:
            print(f"Visited node {front}")
            print(f"Node {key} found!")
            return
        visited.append(front)
        for neighbor in self.adj_list[front]:
            if neighbor not in visited:
                queue.append(neighbor)
        self.breadth_first_recur_impl(queue, visited, key)


graph = Graph(5)
graph.add_edge(0, 1)
graph.add_edge(0, 2)
graph.add_edge(1, 3)
graph.add_edge(1, 4)
print(graph)

graph.breadth_first_iter(3)
graph.depth_first_iter(3)

graph.depth_first_recur(3)
graph.breadth_first_recur(3)
