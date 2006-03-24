#!/usr/bin/perl
# 
# Aufnahme eines neuen Users
#
#
use strict;

# Init Variable

my $PASS  = "/opt/www/etc/.users";         # Userdatei
my $LOG   = "/opt/www/etc/anmeldung.log";  # Logdatei (Adresse)

my $usernam = '';                  # Benutzerkennung
my $password = '';                 # Passwort
my $nam = '';                      # Nachname des Anmelders
my $vnam = '';                     # Vorname -"-
my $email = '';                    # E-Mail-Adresse _"_
my $found = 'no';                  # $usernam in der Userdatei gefunden
my @users = ();                    # alle Username, die $usernam enthalten
my %ein = ();                      # Hash fuer Formulareingabedaten

my $einput = '';                   # Eingabezeile
my $name = '';                     # Parameterbearbeitung
my $value = '';                    #      _"_ 
my $namlen = 0;                    # Laenge $usernam
my $line = '';                     # Eingabezeile
my @terms = ();                    # zerlegte Eingabezeile
my $uid = '';                      # Userid aus der Userdatei(-zeile)
my $pass = '';                     # Passwort aus der Userdate(-zeile)
my $usernum = 0;                   # Zaehler bei gleichem Namen 
my $newuid = '';                   # neue Userid
my $newpass = '';                  # neues Passwort

# Get the input
read(STDIN,$einput,$ENV{CONTENT_LENGTH});

# Split the name-value pairs
foreach (split("&",$einput)) {
  /(.*)=(.*)/;
  $name = $1;

  $value = $2;
  $value =~ s/\+/ /g;
  $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
  $ein{$name}=$value;
  }

# Print HTML-Header
print "Content-type: text/html", "\r\n\r\n";
print "<HTHL>", "\n";
print "<HEAD><TITLE>User-Anmeldung</TITLE></HEAD>", "\n";
print "<BODY BGCOLOR=\"#000000\" TEXT=\"#FFFFFF\" LINK=\"#0000FF\" VLINK=\"#0000CC\" ALINK=\"#FF0000\">", "\n";
print "<H1 ALIGN=CENTER>User-Anmeldung</H1>", "\n";

# Eingaben uebernehmen
$nam = $ein{'Name'};
$usernam = $nam;
$vnam = $ein{'Vorname'};
$password = $ein{'Password'};
$email = $ein{'EMail'};

# Usernamen aus nam erzeugen:
# - Umlaute konvertieren
# - alles weg, was nicht Buchstabe ist
# - alles in Kleinbuchstaben umwandeln
$usernam =~ s/ä/ae/g;
$usernam =~ s/ö/oe/g;
$usernam =~ s/ü/ue/g;
$usernam =~ s/Ä/Ae/g;
$usernam =~ s/Ö/Oe/g;
$usernam =~ s/Ü/Ue/g;
$usernam =~ s/ß/ss/g;
$usernam =~ tr/a-zA-Z//cd;  
$usernam =~ tr/A-Z/a-z/;         

$namlen = length $usernam;      # Namenslaenge checken
if ($namlen < 3)
  {
  print "Fehler: Der Nachname muss mindestens 3 Buchstaben lang sein.<BR>\n";
  print "Bitte dr\&uuml;cken Sie den BACK- oder ZUR\&Uuml;CK-Button ihres ";
  print "Browsers und versuchen Sie es nocheinmal mit einem l\&auml;ngeren ";
  print "Nachnamen\n";
  print "</BODY></HTML>", "\n";
  exit;
  }
$namlen = length $password;      # Passwortlaenge checken
if ($namlen < 3)
  {
  print "Fehler: Das Passwort muss mindestens 3 Buchstaben lang sein.<BR>\n";
  print "Bitte dr\&uuml;cken Sie den BACK- oder ZUR\&Uuml;CK-Button ihres ";
  print "Browsers und versuchen Sie es nocheinmal mit einem l\&auml;ngeren ";
  print "Nachnamen\n";
  print "</BODY></HTML>", "\n";
  exit;
  }

# Userdatei durchsuchen
if (! open DAT, $PASS) 
  {
  print "Fehler \"$!\" beim \&Ouml;ffnen der Datendatei!", "\n";
  print "</BODY></HTML>", "\n";
  exit;
  }
while (<DAT>)
  {
  chomp; $_ =~ s/\r//;            # <CR><LF> am Ende weg
  $line = $_; 
  $line =~ s/ *%/%/g;             # Zeile aufbereiten
  $line =~ s/%( *)/%/g;
  ($uid,$pass) = split(":", $line); # user:passwort
  $uid =~ tr/0-9//d;              # Ziffern weg
  if ($uid eq $usernam)           # userid "passt"
    {
    $found = 'yes'; 
    push(@users,$terms[0]);       # userid speichern
    } 
  }
close DAT;

# Neue userid generieren
if ($found eq 'yes')  
  {
  $usernum = substr($users[$#users],$namlen);
  $usernum++;
  $newuid = $usernam . $usernum;
  }
else
  {
  $newuid = $usernam;
  }
$newpass = crypt($password, "JP");	

# Userdatei erweitern
if (! open DAT, ">>".$PASS) {
  print "Fehler \"$!\" beim \&Ouml;ffnen der Datendatei!", "\n";
  print "</BODY></HTML>", "\n";
  exit;
  }
print DAT $newuid, ":", $newpass, "\n";
close DAT;

# Entry to Logfile
open(LOGFILE, ">>".$LOG);
print LOGFILE $nam, ";", $vnam, ";", $password, ";", $email, ";", $newuid, "\n";
close(LOGFILE);

print "<P>Sie wurden in der Benutzerdatenbank \n";
print "mit folgenden Daten eingetragen:<P>\n";
print "<BLOCKQUOTE>\n";
print "<B>Benutzerkennung: ",  $newuid, "</B><BR>\n";
print "<B>Passwort: ", $password, "</B><P>\n";
print "</BLOCKQUOTE>\n";
print "Bitte notieren Sie beides und beachten Sie bei der Eingabe\n";
print "auch die exakte Gross- und Kleinschreibung.<P>\n";

print "</BODY></HTML>", "\n";
exit(0);
