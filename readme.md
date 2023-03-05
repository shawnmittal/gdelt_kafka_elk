# GDELT Visualization Using Containerized Elastic Stack (ELK) + Kafka

The purpose of this project is to help re-familiarize myself with ELK and Kafka while having a bit of fun. 

The goal is to visualize GDELT data on a map in Kibana in real time.However, in order to keep things interesting, I want to run everything on my home kubernetes cluster. The first step of that is prototyping the end to end pipeline using docker-compose.

The intent is to have a GDELT Kafka Producer that sends GDELT events as JSON messages to the Kafka broker while Logstash serves as the consumer.

This project heavily borrows from the following projects:

- ![Elastic Stack on Docker](https://github.com/deviantony/docker-elk)
- ![GDELT Twitter Kafka Elk](https://github.com/geoffo-dev/gdelt-twitter-kafka-elk)

Nothing in this repository is meant to serve as "best practices". I develop production code for my day job, so this is for personal enjoyment only.