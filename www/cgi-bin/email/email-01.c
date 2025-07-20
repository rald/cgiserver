#include "cgic.h"
#include "smtp_client.h"

#define SMTP_SAMPLE_HOSTNAME "smtp.gmail.com"
#define SMTP_SAMPLE_PORT 465
#define SMTP_SAMPLE_NAME_FROM   "fria"
#define SMTP_SAMPLE_MAIL_FROM   "friaelagua@gmail.com"
#define SMTP_SAMPLE_NAME_TO     "friend"
#define SMTP_SAMPLE_MAIL_TO     "thecoconutnutisagiantnut@gmail.com"
#define SMTP_SAMPLE_LOGIN       "friaelagua@gmail.com"
#define SMTP_SAMPLE_PASSWORD    "vakb erou mpqj qkah "
#define SMTP_SAMPLE_USE_SSL     1

void cgiInclude(FILE *fout,char *filename) {
	char line[256];
	FILE *fin=fopen(filename,"r");
	while(fgets(line,255,fin)) {
		fprintf(fout,"%s",line);
	}
}

int cgiMain() {

	char email_to[256];
	char email_subject[256];
	char email_body[1024];

	cgiHeaderContentType("text/html");

	cgiFormStringNoNewlines("email_to",email_to,sizeof(email_to));
	cgiFormStringNoNewlines("email_subject",email_subject,sizeof(email_subject));
	cgiFormString("email_body",email_body,sizeof(email_body));

	fprintf(cgiOut,
		"<form action='email.cgi' method='post'>"
		"To: <input name='email_to' type='email' value='%s'><br>"
		"Subject: <input name='email_subject' type='text' value='%s'><br>"
		"Body: <textarea name='email_body'>%s</textarea><br>"
		"<input name='send' type='submit' value='send'><br>"
		"</form>",email_to,email_subject,email_body
	);



	if(cgiFormSubmitClicked("send")==cgiFormSuccess) {

		if(strlen(email_to)==0) { fprintf(cgiOut,"email to required.<br>"); return 1; }

		if(strlen(email_subject)==0) { fprintf(cgiOut,"email subject required.<br>"); return 1; }

		if(strlen(email_body)==0) { fprintf(cgiOut,"email body required.<br>"); return 1; }

		fprintf(cgiOut,"To: %s<br>",email_to);
		fprintf(cgiOut,"Subject: %s<br>",email_subject);
		fprintf(cgiOut,"Body:<pre>%s</pre>",email_body);

    ssize_t ret;
    SMTP_Client *smtp;

    int security = SMTP_NONSECURE;
    const char *smtpServer     = SMTP_SAMPLE_HOSTNAME;
    const char *smtpLogin      = SMTP_SAMPLE_LOGIN;
    const char *smtpPassword   = SMTP_SAMPLE_PASSWORD;

    if(smtp_init(&smtp) < 0) {
      fprintf(cgiOut, "Can't initialize SMTP!<br>");
      return 1;
    }

    /* To turn on debug output, set those flags */
    smtp->debugPrint  = 1;
    smtp->debugStream = stderr;

    /* Initialize letter data */
    ret = smtp_createLetter(
	    smtp,
	    SMTP_TextHTML,
	    SMTP_SAMPLE_NAME_FROM, SMTP_SAMPLE_MAIL_FROM,
	    SMTP_SAMPLE_NAME_TO, email_to,
	   	email_subject, email_body
   	);

    if(ret >= 0)
    	ret = smtp_endLetter(smtp);

    if(ret < 0) {
        fprintf(cgiOut, "prepare FAILED ... [%s]<br>", smtp->errorString);
        smtp_free(&smtp);
        return 1;
    }
    fprintf(cgiOut,"prepare OK ...<br>");

    #if SMTP_SAMPLE_USE_SSL
        security = SMTP_SSL;
    #endif

    if(smtp_connect(smtp, smtpServer, SMTP_SAMPLE_PORT, security) < 0) {
			fprintf(cgiOut, "connect FAILED ... [%s]<br>", smtp->errorString);
			smtp_free(&smtp);
			return 1 ;
    }
    fprintf(cgiOut,"connect OK ...<br>");

    ret = smtp_login(smtp, smtpLogin, smtpPassword);
    if(ret < 0) {
			fprintf(cgiOut, "auth FAILED ... [%s]<br>", smtp->errorString);
			smtp_free(&smtp);
			return 1 ;
    }
    fprintf(cgiOut,"auth OK ...<br>");

    ret = smtp_sendLetter(smtp);
    if(ret < 0) {
			fprintf(cgiOut, "send FAIL ... [%s]<br>", smtp->errorString);
			smtp_free(&smtp);
			return 1;
    }
    fprintf(cgiOut,"send OK ...<br>");

    smtp_free(&smtp);

	}

	return 0;
}
