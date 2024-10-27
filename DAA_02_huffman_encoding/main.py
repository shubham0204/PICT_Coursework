import heapq


def construct_char_freq_map(text):
    char_freq_map = {}
    for char in text:
        if char in char_freq_map:
            char_freq_map[char] += 1
        else:
            char_freq_map[char] = 1
    return char_freq_map


def construct_huffmann_tree(text):
    char_freq_map = construct_char_freq_map(text)
    # node structure as a tuple
    # (frequency, character, left_node, right_node)
    heap = [(freq, char, None, None) for char, freq in char_freq_map.items()]
    heapq.heapify(heap)
    while len(heap) > 1:
        left_node = heapq.heappop(heap)
        right_node = heapq.heappop(heap)
        heapq.heappush(
            heap, (left_node[0] + right_node[0], "internal", left_node, right_node)
        )
    return heap[0]


def encode(text):
    heap_root_node = construct_huffmann_tree(text)
    char_code_map = {}

    def _encode(node, code):
        if node is None:
            return
        if node[1] != "internal":
            char_code_map[node[1]] = code
        else:
            _encode(node[2], code + "0")
            _encode(node[3], code + "1")

    _encode(heap_root_node, "")

    return "".join([char_code_map[char] for char in text]), char_code_map


text = input("Enter the text to encode: ")
encoded_text, char_code_map = encode(text)
print(f"Encoded text: {encoded_text}")
print(f"Length of encoded text: {len(encoded_text)}")
print("Character codes:")
for char, code in char_code_map.items():
    print(f"{char}: {code}")
