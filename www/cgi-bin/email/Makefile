email.cgi: email.c email.html
	gcc email.c -o email.cgi -DSMTP_OPENSSL -I /data/data/com.termux/files/home/projects/cgic -L /data/data/com.termux/files/home/projects/cgic -I /data/data/com.termux/files/home/projects/smtp-client -L /data/data/com.termux/files/home/projects/smtp-client -lsmtp -lcgic -lssl -lcrypto
	chmod 755 email.cgi

clean:
	rm email.cgi
