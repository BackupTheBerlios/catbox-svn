#!/usr/bin/perl
# CGI-Script zur Steuerung von Relais
# Das Skript liest die Dateni eines Formulars ein und nimmt
# dann Kontakt zum eigentlichen Steuer-Server auf.

use strict;
use IO::Socket;
use Digest::MD5  qw(md5 md5_hex md5_base64);

# Sicherheitsmassnahmen: 
#  1. Formular nur von einem bestimmten Rechner aus zulassen
#  2. Passwort im Formular.
my $referer = "http://www.netzmafia.de/skripten/server/relais.html";
my $PASS= '';

# Der Server, an dem das Relais-Interface angeschlossen ist
my $SERVER = "blackhole.ee.fhm.edu";
# Server-Port des obigen Servers
my $PORT = 666;


my $eingabe = '';
my $ausgabe = '';
my $rs = '';
my $key = '';
my $buffer = '';
my $pair = '';
my $name = '';
my $value = '';
my $stat = '';
my $cmd = '';
my %in = ();
my @nvpairs = ();
my $sock = '';

# Formulardaten einlesen. Alle Daten bis auf das Passwort
# werden im Hash %in gesammelt.
if ($ENV{'REQUEST_METHOD'} eq "GET") { $buffer = $ENV{'QUERY_STRING'}; }
else { read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'}); }

@nvpairs = split(/&/,$buffer);
foreach $pair (@nvpairs)
  {
  ($name, $value) = split(/=/, $pair);
  $value =~ tr/+/ /;
  $value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;
  if ($name eq "PASS") { $PASS = $value; }
  else                 { $in{$name} = $value; }
  }

# Ausgabe des Skripts: Kopfzeilen
print "Content-type: text/html\n\n";
print "<HTML><HEAD><TITLE>Relais-Steuerung</TITLE></HEAD><BODY>\n";
print "<H2 ALIGN=CENTER>Relais-Steuerung</H2><CENTER>\n";
print "<TABLE BORDER=1 BGCOLOR=\"#CCCCFF\" CELLPADDING=5 CELLSPACING=0 WIDTH=\"60%\">\n";
print "<TR><TD VALIGN=TOP ALIGN=CENTER>\n";

# Formular kommt vom anderen Rechner --> verboten!
if ($ENV{HTTP_REFERER} ne $referer)
  {
  print "<B>You are not allowed to do this!</B>";
  print "</TABLE></CENTER></BODY></HTML>\n";
  exit;
  }

# Kommando zusammenfrickeln
$cmd = "";
foreach $key (keys %in)
  { 
  if ($in{$key}) { $cmd = $cmd . "-s$key "; }
  else           { $cmd = $cmd . "-r$key "; }
  }

# Kontakt zum Relais-Server aufnehmen, Protokoll abarbeiten
$sock = new IO::Socket::INET(PeerAddr => $SERVER, 
                             PeerPort => $PORT,
                             Proto    => 'tcp', 
                             Timeout => 50); 
if ($@ ne '')
  {
  print "<B>Sorry, cannot connect to Server ($@)</B>";
  print "</TABLE></CENTER></BODY></HTML>\n";
  exit(1);
  }

$eingabe = <$sock>; chomp($eingabe);
if ($eingabe ne "AUTH") 
  { 
  print "<B>Authentication failure</B><br>\n"; 
  print "</TABLE></CENTER></BODY></HTML>\n";
  close($sock); exit(1); 
  }
$eingabe = <$sock>; chomp($eingabe);
$rs = <$sock>; chomp($rs);
$ausgabe = md5_hex($eingabe, $rs, $PASS);
print $sock "$ausgabe\n";
$ausgabe = substr(rand(),2,4); 
print $sock "$ausgabe\n";
$ausgabe = md5_hex($eingabe, $ausgabe, $PASS); 
$eingabe = <$sock>; chomp($eingabe);
if($eingabe ne $ausgabe) 
  { 
  print "<B>Authentication failure</B><br>\n"; 
  print "</TABLE></CENTER></BODY></HTML>\n";
  close($sock); exit(1); 
  }
print $sock "$cmd\n";
$stat = <$sock>;

# Statusausgabe: Fehlermeldung oder Relaisstellung binaer
if ($stat =~ /^OK/) 
  {
  $stat =~ s/[^\d]//g;
  my $bin = ''; my $cnt = 8; my $rest = 0;
  while ($cnt > 0)
    {
    $rest = $stat%2;
    $stat = ($stat-$rest)/2;
    $bin = "$rest" . ' ' . $bin;
    $cnt--;
    }
  print "<H4>Ergebnis</H4>\n";
  print "Status: OK<P><PRE>\n";
  print "Relais Nr.  8 7 6 5 4 3 2 1\n";
  print "Zustand      $bin</PRE>\n";
  }
else
  {
  print "<H4>Failure</H4>\n";
  print "Status: $stat<P>\n";
  }
print "</TR></TABLE></CENTER></BODY></HTML>\n";

