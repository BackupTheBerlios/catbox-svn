#!/usr/bin/perl
# tcp-server-mt.pl -- Ein Mini-Webserver

use strict;
use IO::Socket;

use constant MYPORT => 8080;
my $sock = '';
my $client = '';

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

$SIG{'CHLD'} = sub { wait(); $client ->close; };    # Zombies verhindern

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Verbindung ist aufgebaut
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Erzeugen eines Kindprozesses und Uebergabe an $client.
  if (fork() == 0) # Kindprozess 
    {
    my ($dummy);
    # Gaaaaaanz einfacher Webserver
    # Eingabe wird ignoriert, aber ausgegeben
    do
      {
      chomp($dummy = <$client>);
      print "$dummy\n";
      }
      while(length($dummy) > 1);
    print $client "HTTP/1.0 404 Not Found\n";
    print $client "Server: Tralala 1.0\n";
    print $client "Content-Type: text/html\n";
    print $client "Connection: close\n";
    print $client "\n";
    print $client "<html><head><title>404 Not Found</title></head>\n";
    print $client "<body><h1>404 Not Found</h1>\n";
    print $client "&Auml;tschib&auml;tsch!\n";
    print $client "</body></html>\n";
#    $client->close;
    exit 0;
    }
  }
