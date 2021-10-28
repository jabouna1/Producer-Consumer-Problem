gcc producer.c -pthread -Irt -o producer
gcc consumer.c -pthread -Irt -o consumer
./producer & ./consumer & 
