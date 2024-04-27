# Assignment 12: Hadoop MapReduce on Weather Data

Code credits: Shantanu Wable

```
su - hadoop
ssh localhost

cd hadoop-3.3.5/sbin
start-dfs.sh
start-yarn.sh
jps

hdfs dfs -mkdir /input
hdfs dfs -put sample_weather.txt /input

[OPTIONAL] export HADOOP_CLASSPATH=/usr/lib/jvm/java-8-openjdk-amd64/lib/tools.jar) 
hadoop com.sun.tools.javac.Main WeatherDataAverage.java

jar cf sample_weather.jar WeatherDataAverage*.class
(optional: hdfs dfs -rm -r /output)
hadoop jar sample_weather.jar WeatherDataAverage /input/sample_weather.txt /output

hadoop fs -cat /output/part-r-00000
```

