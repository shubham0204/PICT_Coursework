from functools import reduce

dataset = """
This is a sample dataset.
It contains both uppercase and lowercase letters.
The count should be case-insensitive.
"""

def mapper(text):
    filtered_text = filter(str.isalpha, text.lower())
    return "".join(filtered_text)

def reducer(counts, char):
    counts[char] = counts.get(char, 0) + 1
    return counts

mapped_data = map(mapper, dataset)
character_counts = reduce(reducer, "".join(mapped_data), {})
sorted_character_counts = {k: character_counts[k] for k in sorted(character_counts)}

for char, count in sorted_character_counts.items():
    print(f"{char}: {count}")