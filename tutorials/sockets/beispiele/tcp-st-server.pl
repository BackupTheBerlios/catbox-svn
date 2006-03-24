#!/usr/bin/perl
# tcp-server-st.pl -- Ein Single-threaded-TCP-Server

use strict;
use IO::Socket;

use constant MYPORT => 2000;
my $sock = '';
my $client = 0;

$sock = new IO::Socket::INET(LocalPort => MYPORT,
		             Reuse     => 1,
		             Listen    => 5)
    or die "can't create local socket: $@\n";

print "Accepting connections on Port ", MYPORT, "...\n";
while ($client = $sock->accept()) 
  {
  # Eine Verbindung ist eingetroffen.
  print "Accepted connection from ",
        $client->peerhost(), ":", $client->peerport(), "\n";

  # Echo, das alles umdreht:
  while (<$client>) 
    {
    chomp;
    print $client scalar(reverse($_)), "\n";
    }
  $client->close() if defined $client;
  }
$sock->close();