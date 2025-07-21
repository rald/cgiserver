test.cgi: test.c test.html
	gcc test.c -o test.cgi -I $(HOME)/projects/cgic -L $(HOME)/projects/cgic -I $(HOME)/projects/libctemplate -L $(HOME)/projects/libctemplate -lcgic -lctemplate
	chmod 755 test.cgi

clean:
	rm test.cgi
