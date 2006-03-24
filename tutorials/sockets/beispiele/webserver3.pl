#!/usr/bin/perl
# Ein Mini-Webserver - Dateiausgabe, aber nur Text

use strict;
use IO::Socket;
use POSIX ":sys_wait_h";

# Port waehlen
use constant MYPORT => 8080;

$|=1;

# Startdirectory (Server-Root) festlegen
my $startdir = '/home/plate/server/';
my $sock = '';
my $client = '';
my %child_pids = ();

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

# Kinder abschliessen
$SIG{CHLD} = sub 
  {
  my($p);
  foreach $p (keys(%child_pids))
    {
    if(waitpid($p,WNOHANG)==0)
      {
      print "Terminated: $p\n";
      delete $child_pids{$p};
      }
    }
  };

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Verbindung ist aufgebaut
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Erzeugen eines Kindprozesses und Uebergabe an $client.
  my $pid = fork();
  if ($pid == 0) # Kindprozess 
    {
    $sock->close;  # not needed in server
    $child_pids{$pid} = 1; # merken
    my ($input, $get, $file);
    $client->autoflush;
    # Gaaaaaanz einfacher Webserver
    # Eingabe wird untersucht und ausgegeben
    do
      {
      chomp($input = <$client>);
      print "$input\n";
      $get = $input if ($input =~ /GET/);
      }
      while(length($input) > 1);
    # Aus der GET-Zeile Dateinamen extrahieren
    $get =~ /GET ([^ ]*) HTTP/;
    $file= "$1";
    $file = $file . 'index.html' if ($file =~ /\/$/);
    $file =~ s/^\///g;          # '/' am Anfang weg
    $file =~ s/\.\.\///g;       # URLS der Form '../../' unterbinden
    $file = $startdir . $file;  # Server-Root davor setzen
    print "Senden $file\n";

    # Datei oeffnen und zum Client schicken.
    if (!open(DATEI,"$file"))
      {
      print $client "HTTP/1.0 404 Not Found\n";
      print $client "Server: Tralala 1.0\n";
      print $client "Content-Type: text/html\n";
      print $client "Connection: close\n";
      print $client "\n";
      print $client "<html><head><title>404 Not Found</title></head>\n";
      print $client "<body><h1>404 Not Found</h1>\n";
      print $client "</body></html>\n";
      print "*** FERTIG **\n";
      $client->close;
      exit 1;
      }
    else
      {
      print $client "HTTP/1.0 200 OK\n";
      print $client "Server: Tralala 1.0\n";
      print $client "Content-Type: text/html\n";
      print $client "Connection: close\n";
      print $client "\n";
      print $client $_ while(<DATEI>);
      print $client "\n";
      close(DATEI);
      print "*** FERTIG **\n";
      $client->close;
      exit 0;
      }
    }
  $client->close;  # not needed in server
  }
