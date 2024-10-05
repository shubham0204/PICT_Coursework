import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize

text = """
C is a widely-used, general-purpose programming language originally developed by Dennis Ritchie at Bell Labs in 1972. It is a foundational language that has influenced many others, including C++, Java, and Python. Known for its simplicity, efficiency, and control over system resources, C is particularly favored in systems programming, operating systems, and embedded systems. It provides low-level memory manipulation, making it both powerful and flexible. The language is procedural, meaning programs are organized into functions and data is passed through arguments. C's portability makes it ideal for cross-platform applications, and its performance optimization capabilities make it suitable for resource-constrained environments. Despite its long history, C remains relevant today due to its minimalistic design, giving programmers fine-grained control over hardware and memory, allowing efficient code execution.

The language also introduces a comprehensive standard library, which aids in managing tasks like input/output and mathematical computations. C's popularity in the development of compilers and operating systems is notable. Programs like Unix, Linux, and Windows kernels are written in C, making it indispensable in the tech industry. The language's structure is compact, allowing clear and maintainable code. However, it requires caution due to the absence of some modern safety features, such as automatic memory management, which leads to risks like buffer overflows and memory leaks. Nonetheless, C's combination of versatility and control ensures it remains a critical tool for both software and hardware development.
"""
text = text.lower()

words = text.split()
stop_words = set(stopwords.words("english"))
filtered_words = [word for word in words if word.lower() not in stop_words]
cleaned_text = " ".join(filtered_words)

print("Original Text:", text)
print("---" * 20)
print("Text after Stop Word Removal:", cleaned_text)
