// This opens up an interactive shell
// Create a new input1.txt file
val input = sc.textFile("passage.txt")

// Create a new RDD by splitting the input RDD on the basis of space
val words = input.flatMap(x => x.split(" "))

// Create a new RDD by mapping each word to a tuple of (word, 1)
val counts = words.map(x => (x, 1))

// Create a new RDD by reducing the tuples by key
val reducedCounts = counts.reduceByKey((x, y) => x + y)

// Save the RDD to a file
reducedCounts.saveAsTextFile("output.txt")

// Print the contents of the file
reducedCounts.foreach(println)