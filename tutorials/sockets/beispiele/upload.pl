!/usr/bin/perl
# Einfaches Script fuer File-Upload

use strict;
use CGI qw(:standard);

# Upload Dir, kein Slash am Ende!
my $updir = "/home/httpd/htdocs/upload";

# Referer (mit .htaccess geschuetztes Verzeichnis wo Formular liegt)
my $ref = "http://atlas.ee.fhm.edu/ups/upload.html";

my $data; # Lesepuffer

##### BITTE BEACHTEN ######################################################
# Die Felder des Formulars
#   <form action="/cgi-bin/ups.pl" method="post" enctype="multipart/form-data">
#   Lokaler Dateiname:
#   <input type="file" name="datei" size=40><BR>
#   Dateiname auf dem Server:
#   <input name="dateiname" size="40">
#   <input type="Submit" value="Upload">
#   <input type="reset" value="L&ouml;schen">
#   </form>

print header;
print start_html('Datei-Upload');

if ($ENV{'HTTP_REFERER'} ne $ref)
  {
  print "<H1>Fehler!</H1>\n";
  print "Es wurde versucht, ohne Erlaubnis hochzuladen! Abbruch...";
  print $ENV{'HTTP_REFERER'};
  print end_html;
  exit;
  }

my $datei = param('datei');
my $dateiname = param('dateiname');

if (! $datei or ! $dateiname)
  {
  print "<H1>Fehler!</H1>\n";
  print "Datei oder Dateiname fehlt! Abbruch...";
  print end_html;
  exit;
  }

if (! open WF, ">$updir/$dateiname")
  {
  print "<H1>Fehler!</H1>\n";
  print "Datei kann nicht geschrieben werden! Abbruch...";
  print end_html;
  exit;
  }


if (! open WF, ">$updir/$dateiname")
  {
  print "<H1>Fehler!</H1>\n";
  print "Datei kann nicht geschrieben werden! Abbruch...";
  print end_html;
  exit;
  }

binmode $datei;
binmode WF;
while(read $datei,$data,1024)
  { print WF $data; }
close WF;


print "<H1>Upload O. K.</H1>\n";
print "Die Datei wurde hochgeladen.<BR>\n";
print "Remote Path and Filename: $updir/$dateiname\n";

print end_html;
exit;
