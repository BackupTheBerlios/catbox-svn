#!/usr/bin/perl
# tcp-server-mt-zombies.pl -- Ein Multithreaded-TCP-Server.
#                             ACHTUNG: Gefahr durch Zombies!

use strict;
use IO::Socket;

use constant MYPORT => 2000;
my $sock = '';
my $client = '';

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Verbindung ist aufgebaut
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Erzeugen eines Kindprozesses und Uebergabe an $client.
  if (fork() == 0) # Kindprozess
    {
    # Echo, das alles umdreht:
    while (<$client>) 
      {
      chomp;
      print $client scalar(reverse($_)), "\n";
      }
    exit 0;
    }
  }

