#!/usr/bin/perl
# tcp-mtclient.pl -- Ein multithreaded interaktiver TCP-Client.
# Verwendung: $0 remote_host remote_port

use strict;
use IO::Socket;

my $sock = '';

use constant TIMEOUT => 5;
$sock = new IO::Socket::INET(PeerAddr => $ARGV[0],
			     PeerPort => $ARGV[1],
			     Proto    => 'tcp', Timeout => TIMEOUT)
    or die "can't connect to $ARGV[0]:$ARGV[1]: $@\n";

# An dieser Stelle teilen wir mit fork() in zwei Prozesse auf:
if (fork()) # == 0 --> Kind
  {
  # Der Kindprozess: Server -> Mensch
  while (<$sock>) { print $_; }
  $sock->close() if defined $sock;
  die "server closed connection.\n";
  exit 0;
  } 
else 
  {
  # Der Elternprozess: Mensch -> Server
  while (<STDIN>) { print $sock $_; }
  $sock->close();    # fertig, aufhaengen!
  wait();
  }
