#!/usr/bin/perl
# tcp-client.pl -- Ein einfacher TCP-Client.
# Verwendung: $0 remote_host remote_port

use strict;
use IO::Socket;

use constant TIMEOUT => 5;
my $sock = '';
my $reply = '';

$sock = new IO::Socket::INET(PeerAddr => $ARGV[0],
			     PeerPort => $ARGV[1],
			     Proto    => 'tcp', Timeout => TIMEOUT)
    or die "can't connect to $ARGV[0]:$ARGV[1]: $@\n";

while (<STDIN>) 
  {
  print $sock $_;
  last unless defined($reply = <$sock>);
  print ">> $reply";
  }

$sock->close() if defined $sock;
