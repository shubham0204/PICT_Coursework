# Assignment 11: Hadoop Map-Reduce

```
cd hadoop-3.3.5/sbin
start-dfs.sh
start-yarn.sh
jps

hdfs dfs -mkdir /input
hdfs dfs -mkdir /output
hdfs dfs -put passage.txt /input

hadoop com.sun.tools.javac.Main WordCount.java
jar cf wc.jar WordCount*.class
hadoop jar wc.jar WordCount /input/passage.txt /output

hadoop fs -cat /output/part-r-00000
```

## Resources

* https://github.com/RohanDoshi21/PICT-TE-SEM6/blob/main/DSBDAL/hadoop.md
* https://hadoop.apache.org/docs/current/hadoop-mapreduce-client/hadoop-mapreduce-client-core/MapReduceTutorial.html
* https://sparkbyexamples.com/apache-hadoop/hadoop-how-to-list-files-and-directories-using-hdfs-dfs/