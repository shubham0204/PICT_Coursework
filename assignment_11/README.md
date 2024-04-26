# Assignment 11: Hadoop MapReduce

Hadoop UI available on `localhost:9870`

```
su - hadoop
ssh localhost

cd hadoop-3.3.5/sbin
start-dfs.sh
start-yarn.sh
jps

hdfs dfs -mkdir /input
hdfs dfs -put passage.txt /input

[OPTIONAL] export HADOOP_CLASSPATH=/usr/lib/jvm/java-8-openjdk-amd64/lib/tools.jar
hadoop com.sun.tools.javac.Main WordCount.java
jar cf wc.jar WordCount*.class
hadoop jar wc.jar WordCount /input/passage.txt /output

hadoop fs -cat /output/part-r-00000
```

## Resources

* https://github.com/RohanDoshi21/PICT-TE-SEM6/blob/main/DSBDAL/hadoop.md
* https://hadoop.apache.org/docs/current/hadoop-mapreduce-client/hadoop-mapreduce-client-core/MapReduceTutorial.html
* https://sparkbyexamples.com/apache-hadoop/hadoop-how-to-list-files-and-directories-using-hdfs-dfs/