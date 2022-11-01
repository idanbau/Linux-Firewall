all: user_dynamic_firewall

user_dynamic_firewall: user_dynamic_firewall.o
	g++ -o user_dynamic_firewall user_dynamic_firewall.o

user_dynamic_firewall.o: user_dynamic_firewall.cpp
	g++ -c user_dynamic_firewall.cpp

clean:
	rm *.o user_dynamic_firewall