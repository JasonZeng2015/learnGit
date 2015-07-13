g++ -g -c db_mysql.cpp -I/usr/include/mysql
g++ -g -c test.cpp -I. -I/usr/include/mysql
g++ -g -o testmysql test.o db_mysql.o  -L/usr/lib64/mysql -lmysqlclient -ldl -lpthread -lrt
