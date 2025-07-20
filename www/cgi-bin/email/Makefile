email.cgi: email.c email.html
	gcc email.c -o email.cgi -I /data/data/com.termux/files/home/projects/cgic -L /data/data/com.termux/files/home/projects/cgic -I /data/data/com.termux/files/home/projects/libsmtpclient -L /data/data/com.termux/files/home/projects/libsmtpclient -lcgic -lsmtpclient -lssl -lcrypto
	chmod 755 email.cgi

clean:
	rm email.cgi
