#!/usr/local/bin/perl -w
# Ein single-threaded interaktiver TCP-Client.
# Benutzt nur einen Prozess, aber IO::Select.
# Verwendung: $0 remote_host remote_port

use IO::Socket;
use IO::Select;
use strict;

my ($socket, $select, $handle);
my @ready = ();

$sock = new IO::Socket::INET(PeerAddr => $ARGV[0] 
                             PeerPort => $ARGV[1],
                             Proto    => 'tcp', 
                             Timeout  => 5)
    or die "can't connect to $ARGV[0]:$ARGV[1]: $@\n";

$select = IO::Select->new();

$select->add($sock);
$select->add(\*STDIN);

while (@ready = $select->can_read()) 
  {
  foreach $handle (@ready) 
    {
	last unless defined($reply = <$handle>);
	if ($handle == $sock) { print $reply; } 
	else                  { print $sock $reply; }
    }
  }
$sock->close();    # fertig, aufhaengen!
